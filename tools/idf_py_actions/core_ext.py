import fnmatch
import locale
import os
import re
import shutil
import subprocess
import sys
from urllib.error import URLError
from urllib.request import Request, urlopen
from webbrowser import open_new_tab

import click
from idf_py_actions.constants import GENERATORS, PREVIEW_TARGETS, SUPPORTED_TARGETS, URL_TO_DOC
from idf_py_actions.errors import FatalError
from idf_py_actions.global_options import global_options
from idf_py_actions.tools import (TargetChoice, ensure_build_directory, get_target, idf_version, merge_action_lists,
                                  realpath, run_target)


def action_extensions(base_actions, project_path):
    def build_target(target_name, ctx, args):
        """
        Execute the target build system to build target 'target_name'

        Calls ensure_build_directory() which will run cmake to generate a build
        directory (with the specified generator) as needed.
        """
        ensure_build_directory(args, ctx.info_name)
        run_target(target_name, args)

    def size_target(target_name, ctx, args):
        """
        Builds the app and then executes a size-related target passed in 'target_name'.
        `tool_error_handler` handler is used to suppress errors during the build,
        so size action can run even in case of overflow.

        """

        def tool_error_handler(e):
            pass

        ensure_build_directory(args, ctx.info_name)
        run_target('all', args, custom_error_handler=tool_error_handler)
        run_target(target_name, args)

    def list_build_system_targets(target_name, ctx, args):
        """Shows list of targets known to build sytem (make/ninja)"""
        build_target('help', ctx, args)

    def menuconfig(target_name, ctx, args, style):
        """
        Menuconfig target is build_target extended with the style argument for setting the value for the environment
        variable.
        """
        if sys.version_info[0] < 3:
            # The subprocess lib cannot accept environment variables as "unicode".
            # This encoding step is required only in Python 2.
            style = style.encode(sys.getfilesystemencoding() or 'utf-8')
        os.environ['MENUCONFIG_STYLE'] = style
        build_target(target_name, ctx, args)

    def fallback_target(target_name, ctx, args):
        """
        Execute targets that are not explicitly known to idf.py
        """
        ensure_build_directory(args, ctx.info_name)

        try:
            subprocess.check_output(GENERATORS[args.generator]['dry_run'] + [target_name], cwd=args.build_dir)

        except Exception:
            raise FatalError(
                'command "%s" is not known to idf.py and is not a %s target' % (target_name, args.generator))

        run_target(target_name, args)

    def verbose_callback(ctx, param, value):
        if not value or ctx.resilient_parsing:
            return

        for line in ctx.command.verbose_output:
            print(line)

        return value

    def clean(action, ctx, args):
        if not os.path.isdir(args.build_dir):
            print("Build directory '%s' not found. Nothing to clean." % args.build_dir)
            return
        build_target('clean', ctx, args)

    def _delete_windows_symlinks(directory):
        """
        It deletes symlinks recursively on Windows. It is useful for Python 2 which doesn't detect symlinks on Windows.
        """
        deleted_paths = []
        if os.name == 'nt':
            import ctypes

            for root, dirnames, _filenames in os.walk(directory):
                for d in dirnames:
                    full_path = os.path.join(root, d)
                    try:
                        full_path = full_path.decode('utf-8')
                    except Exception:
                        pass
                    if ctypes.windll.kernel32.GetFileAttributesW(full_path) & 0x0400:
                        os.rmdir(full_path)
                        deleted_paths.append(full_path)
        return deleted_paths

    def fullclean(action, ctx, args):
        build_dir = args.build_dir
        if not os.path.isdir(build_dir):
            print("Build directory '%s' not found. Nothing to clean." % build_dir)
            return
        if len(os.listdir(build_dir)) == 0:
            print("Build directory '%s' is empty. Nothing to clean." % build_dir)
            return

        if not os.path.exists(os.path.join(build_dir, 'CMakeCache.txt')):
            raise FatalError(
                "Directory '%s' doesn't seem to be a CMake build directory. Refusing to automatically "
                "delete files in this directory. Delete the directory manually to 'clean' it." % build_dir)
        red_flags = ['CMakeLists.txt', '.git', '.svn']
        for red in red_flags:
            red = os.path.join(build_dir, red)
            if os.path.exists(red):
                raise FatalError(
                    "Refusing to automatically delete files in directory containing '%s'. Delete files manually if you're sure."
                    % red)
        # OK, delete everything in the build directory...
        # Note: Python 2.7 doesn't detect symlinks on Windows (it is supported form 3.2). Tools promising to not
        # follow symlinks will actually follow them. Deleting the build directory with symlinks deletes also items
        # outside of this directory.
        deleted_symlinks = _delete_windows_symlinks(build_dir)
        if args.verbose and len(deleted_symlinks) > 1:
            print('The following symlinks were identified and removed:\n%s' % '\n'.join(deleted_symlinks))
        for f in os.listdir(build_dir):  # TODO: once we are Python 3 only, this can be os.scandir()
            f = os.path.join(build_dir, f)
            if args.verbose:
                print('Removing: %s' % f)
            if os.path.isdir(f):
                shutil.rmtree(f)
            else:
                os.remove(f)

    def python_clean(action, ctx, args):
        for root, dirnames, filenames in os.walk(os.environ['IDF_PATH']):
            for d in dirnames:
                if d == '__pycache__':
                    dir_to_delete = os.path.join(root, d)
                    if args.verbose:
                        print('Removing: %s' % dir_to_delete)
                    shutil.rmtree(dir_to_delete)
            for filename in fnmatch.filter(filenames, '*.py[co]'):
                file_to_delete = os.path.join(root, filename)
                if args.verbose:
                    print('Removing: %s' % file_to_delete)
                os.remove(file_to_delete)

    def set_target(action, ctx, args, idf_target):
        if (not args['preview'] and idf_target in PREVIEW_TARGETS):
            raise FatalError(
                "%s is still in preview. You have to append '--preview' option after idf.py to use any preview feature."
                % idf_target)
        args.define_cache_entry.append('IDF_TARGET=' + idf_target)
        sdkconfig_path = os.path.join(args.project_dir, 'sdkconfig')
        sdkconfig_old = sdkconfig_path + '.old'
        if os.path.exists(sdkconfig_old):
            os.remove(sdkconfig_old)
        if os.path.exists(sdkconfig_path):
            os.rename(sdkconfig_path, sdkconfig_old)
        print('Set Target to: %s, new sdkconfig created. Existing sdkconfig renamed to sdkconfig.old.' % idf_target)
        ensure_build_directory(args, ctx.info_name, True)

    def reconfigure(action, ctx, args):
        ensure_build_directory(args, ctx.info_name, True)

    def validate_root_options(ctx, args, tasks):
        args.project_dir = realpath(args.project_dir)
        if args.build_dir is not None and args.project_dir == realpath(args.build_dir):
            raise FatalError(
                'Setting the build directory to the project directory is not supported. Suggest dropping '
                "--build-dir option, the default is a 'build' subdirectory inside the project directory.")
        if args.build_dir is None:
            args.build_dir = os.path.join(args.project_dir, 'build')
        args.build_dir = realpath(args.build_dir)

    def idf_version_callback(ctx, param, value):
        if not value or ctx.resilient_parsing:
            return

        version = idf_version()

        if not version:
            raise FatalError('ESP-WDF version cannot be determined')

        print('ESP-WDF %s' % version)
        sys.exit(0)

    def list_targets_callback(ctx, param, value):
        if not value or ctx.resilient_parsing:
            return

        for target in SUPPORTED_TARGETS:
            print(target)

        if 'preview' in ctx.params:
            for target in PREVIEW_TARGETS:
                print(target)

        sys.exit(0)

    def show_docs(action, ctx, args, no_browser, language, starting_page, version, target):
        if language == 'cn':
            language = 'zh_CN'
        if not version:
            # '0.0-dev' here because if 'dev' in version it will transform in to 'latest'
            version = re.search(r'v\d+\.\d+\.?\d*(-dev|-beta\d|-rc)?', idf_version() or '0.0-dev').group()
            if 'dev' in version:
                version = 'latest'
        elif version[0] != 'v':
            version = 'v' + version
        target = target or get_target(args.project_dir) or 'esp32'
        link = '/'.join([URL_TO_DOC, language, version, target, starting_page or ''])
        redirect_link = False
        try:
            req = Request(link)
            webpage = urlopen(req)
            redirect_link = webpage.geturl().endswith('404.html')
        except URLError:
            print("We can't check the link's functionality because you don't have an internet connection")
        if redirect_link:
            print('Target', target, 'doesn\'t exist for version', version)
            link = '/'.join([URL_TO_DOC, language, version, starting_page or ''])
        if not no_browser:
            print('Opening documentation in the default browser:')
            print(link)
            open_new_tab(link)
        else:
            print('Please open the documentation link in the browser:')
            print(link)
        sys.exit(0)

    def get_default_language():
        try:
            language = 'zh_CN' if locale.getdefaultlocale()[0] == 'zh_CN' else 'en'
        except ValueError:
            language = 'en'
        return language

    root_options = {
        'global_options': [
            {
                'names': ['--version'],
                'help': 'Show WDF version and exit.',
                'is_flag': True,
                'expose_value': False,
                'callback': idf_version_callback,
            },
            {
                'names': ['--list-targets'],
                'help': 'Print list of supported targets and exit.',
                'is_flag': True,
                'expose_value': False,
                'callback': list_targets_callback,
            },
            {
                'names': ['-C', '--project-dir'],
                'scope': 'shared',
                'help': 'Project directory.',
                'type': click.Path(),
                'default': os.getcwd(),
            },
            {
                'names': ['-B', '--build-dir'],
                'help': 'Build directory.',
                'type': click.Path(),
                'default': None,
            },
            {
                'names': ['-w/-n', '--cmake-warn-uninitialized/--no-warnings'],
                'help': ('Enable CMake uninitialized variable warnings for CMake files inside the project directory. '
                         "(--no-warnings is now the default, and doesn't need to be specified.)"),
                'envvar': 'IDF_CMAKE_WARN_UNINITIALIZED',
                'is_flag': True,
                'default': False,
            },
            {
                'names': ['-v', '--verbose'],
                'help': 'Verbose build output.',
                'is_flag': True,
                'is_eager': True,
                'default': False,
                'callback': verbose_callback,
            },
            {
                'names': ['--ccache/--no-ccache'],
                'help': 'Use ccache in build. Disabled by default.',
                'is_flag': True,
                'envvar': 'IDF_CCACHE_ENABLE',
                'default': False,
            },
            {
                'names': ['-G', '--generator'],
                'help': 'CMake generator.',
                'type': click.Choice(GENERATORS.keys()),
            },
            {
                'names': ['--dry-run'],
                'help': "Only process arguments, but don't execute actions.",
                'is_flag': True,
                'hidden': True,
                'default': False,
            },
        ],
        'global_action_callbacks': [validate_root_options],
    }

    build_actions = {
        'actions': {
            'all': {
                'aliases': ['build'],
                'callback': build_target,
                'short_help': 'Build the project.',
                'help': (
                    'Build the project. This can involve multiple steps:\n\n'
                    '1. Create the build directory if needed. '
                    "The sub-directory 'build' is used to hold build output, "
                    'although this can be changed with the -B option.\n\n'
                    '2. Run CMake as necessary to configure the project '
                    'and generate build files for the main build tool.\n\n'
                    '3. Run the main build tool (Ninja or GNU Make). '
                    'By default, the build tool is automatically detected '
                    'but it can be explicitly set by passing the -G option to idf.py.\n\n'),
                'options': global_options,
                'order_dependencies': [
                    'reconfigure',
                    'menuconfig',
                    'clean',
                    'fullclean',
                ],
            },
            'menuconfig': {
                'callback': menuconfig,
                'help': 'Run "menuconfig" project configuration tool.',
                'options': global_options + [
                    {
                        'names': ['--style', '--color-scheme', 'style'],
                        'help': (
                            'Menuconfig style.\n'
                            'The built-in styles include:\n\n'
                            '- default - a yellowish theme,\n\n'
                            '- monochrome -  a black and white theme, or\n\n'
                            '- aquatic - a blue theme.\n\n'
                            'It is possible to customize these themes further'
                            ' as it is described in the Color schemes section of the kconfiglib documentation.\n'
                            'The default value is \"aquatic\".'),
                        'envvar': 'MENUCONFIG_STYLE',
                        'default': 'aquatic',
                    }
                ],
            },
            'confserver': {
                'callback': build_target,
                'help': 'Run JSON configuration server.',
                'options': global_options,
            },
            'build-system-targets': {
                'callback': list_build_system_targets,
                'help': 'Print list of build system targets.',
            },
            'fallback': {
                'callback': fallback_target,
                'help': 'Handle for targets not known for idf.py.',
                'hidden': True,
            }
        }
    }

    clean_actions = {
        'actions': {
            'reconfigure': {
                'callback': reconfigure,
                'short_help': 'Re-run CMake.',
                'help': (
                    "Re-run CMake even if it doesn't seem to need re-running. "
                    "This isn't necessary during normal usage, "
                    'but can be useful after adding/removing files from the source tree, '
                    'or when modifying CMake cache variables. '
                    "For example, \"idf.py -DNAME='VALUE' reconfigure\" "
                    'can be used to set variable "NAME" in CMake cache to value "VALUE".'),
                'options': global_options,
                'order_dependencies': ['menuconfig', 'fullclean'],
            },
            'clean': {
                'callback': clean,
                'short_help': 'Delete build output files from the build directory.',
                'help': (
                    'Delete build output files from the build directory, '
                    "forcing a 'full rebuild' the next time "
                    "the project is built. Cleaning doesn't delete "
                    'CMake configuration output and some other files'),
                'order_dependencies': ['fullclean'],
            },
            'fullclean': {
                'callback': fullclean,
                'short_help': 'Delete the entire build directory contents.',
                'help': (
                    'Delete the entire build directory contents. '
                    'This includes all CMake configuration output.'
                    'The next time the project is built, '
                    'CMake will configure it from scratch. '
                    'Note that this option recursively deletes all files '
                    'in the build directory, so use with care.'
                    'Project configuration is not deleted.')
            },
            'python-clean': {
                'callback': python_clean,
                'short_help': 'Delete generated Python byte code from the WDF directory',
                'help': (
                    'Delete generated Python byte code from the WDF directory '
                    'which may cause issues when switching between WDF and Python versions. '
                    'It is advised to run this target after switching versions.')
            },
        }
    }

    return merge_action_lists(root_options, build_actions, clean_actions)

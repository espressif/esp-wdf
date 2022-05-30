# This script should be sourced, not executed.

function __main
    set basedir (realpath (dirname (status -f)))

    set -x IDF_PATH $basedir

    set oldpath = $PATH

    echo "Detecting the Python interpreter"
    source "$IDF_PATH"/tools/detect_python.fish

    echo "Adding ESP-WDF tools to PATH..."
    # Call idf_tools.py to export tool paths
    set -x IDF_TOOLS_EXPORT_CMD "$IDF_PATH"/export.fish
    set -x IDF_TOOLS_INSTALL_CMD "$IDF_PATH"/install.fish
    set idf_exports ("$ESP_PYTHON" "$IDF_PATH"/tools/idf_tools.py export) || return 1
    eval "$idf_exports"

    echo "Checking if Python packages are up to date..."
    python "$IDF_PATH"/tools/check_python_dependencies.py || return 1

    set added_path_variables
    for entry in $PATH;
        if not contains $entry $oldpath
            set -a added_path_variables $entry
        end
    end
    if set -q added_path_variables[1]
        echo "Added the following directories to PATH:"
        for entry in $added_path_variables;
            echo $entry
        end
    else
        echo "All paths are already set."
    end

    # Clean up
    set -e added_path_variables
    set -e cmd
    set -e old_path
    set -e paths
    set -e path_prefix
    set -e path_entry
    set -e IDF_ADD_PATHS_EXTRAS
    set -e idf_exports
    set -e ESP_PYTHON

    # Not unsetting IDF_PYTHON_ENV_PATH, it can be used by IDF build system
    # to check whether we are using a private Python environment

    echo ""
    echo "Done! You can now compile ESP-WDF projects."
    echo "Go to the project directory and run:"
    echo ""
    echo "  idf.py build"
    echo ""
end

__main

set click_version (python -c 'import click; print(click.__version__.split(".")[0])')
if test $click_version -lt 8
    eval (env _IDF.PY_COMPLETE=source_fish idf.py)
else
    eval (env _IDF.PY_COMPLETE=fish_source idf.py)
end


set -e __main
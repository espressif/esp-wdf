// Copyright 2022 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdarg.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "sdkconfig.h"
#include "libc_builtin_ext_data_seq.h"

#ifdef CONFIG_IOCTL_GPIO
#include "ioctl/esp_gpio_ioctl.h"
#endif

extern int __real_ioctl(int fd, int cmd, ...);

#ifdef CONFIG_IOCTL_GPIO
static int gpio_ioctl(int fd, int cmd, va_list va_list)
{
    int ret;
    data_seq_t *ds;
    gpioc_cfg_t *cfg;
    
    ds = data_seq_alloc(1);
    if (!ds) {
        errno = ENOMEM;
        return -1;
    }

    cfg = va_arg(va_list, gpioc_cfg_t *);
    if (!cfg) {
        data_seq_free(ds);
        errno = ENOMEM;
        return -1;
    }

    DATA_SEQ_PUSH(ds, DATA_SEQ_GPIOC_CFG_FLAGS, cfg->flags);

    ret = __real_ioctl(fd, cmd, ds);

    data_seq_free(ds);

    return ret;
}
#endif

int __wrap_ioctl(int fd, int cmd, ...)
{
    int ret;

    switch (cmd) {
#ifdef CONFIG_IOCTL_GPIO
        case GPIOCSCFG: {
            va_list va_list;

            va_start(va_list, cmd);
            ret = gpio_ioctl(fd, cmd, va_list);
            va_end(va_list);

            break;
        }
#endif
        default: {
            errno = EINVAL;
            ret = -1;
        }
    }

    return ret;
}

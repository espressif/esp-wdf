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

#ifdef CONFIG_IOCTL_I2C
#include "ioctl/esp_i2c_ioctl.h"
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

#ifdef CONFIG_IOCTL_I2C
static int i2c_ioctl(int fd, int cmd, va_list va_list)
{
    int ret;
    data_seq_t *ds;
    void *ptr;
    int ds_num = 0;    

    if (cmd == I2CIOCSCFG) {
        ds_num = 5;
    } else if (cmd == I2CIOCRDWR) {
        ds_num = 4;
    } else {
        ds_num = 7;
    }

    ds = data_seq_alloc(ds_num);
    if (!ds) {
        errno = ENOMEM;
        return -1;
    }

    ptr = va_arg(va_list, void *);
    if (!ptr) {
        data_seq_free(ds);
        errno = ENOMEM;
        return -1;
    }

    if (cmd == I2CIOCSCFG) {
        i2c_cfg_t *cfg = (i2c_cfg_t *)ptr;

        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_SDA_PIN, cfg->sda_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_SCL_PIN, cfg->scl_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_FLAGS,   cfg->flags);
        if (cfg->flags & I2C_MASTER) {
            DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_MASTER_CLK, cfg->master.clock);
        } else {
            DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_SLAVE_MAX_CLK, cfg->slave.max_clock);
            DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_CFG_SLAVE_ADDR,    cfg->slave.addr);
        }
    } else if (cmd == I2CIOCRDWR) {
        i2c_msg_t *msg = (i2c_msg_t *)ptr;

        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_MSG_FLAGS, msg->flags);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_MSG_ADDR,  msg->addr);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_MSG_SIZE,  msg->size);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_MSG_BUF,   msg->buffer);
    } else if (cmd == I2CIOCEXCHANGE) {
        i2c_ex_msg_t *ex_msg = (i2c_ex_msg_t *)ptr;

        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_FLAGS,  ex_msg->flags);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_ADDR,   ex_msg->addr);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_DELAY_US,  ex_msg->delay_ms);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_TXBUF,  ex_msg->tx_buffer);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_TXSIZE, ex_msg->tx_size);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_RXBUF,  ex_msg->rx_buffer);
        DATA_SEQ_PUSH(ds, DATA_SEQ_I2C_EX_MSG_RXSIZE, ex_msg->rx_size);
    }

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
#ifdef CONFIG_IOCTL_I2C
        case I2CIOCSCFG: 
        case I2CIOCRDWR: 
        case I2CIOCEXCHANGE: {
            va_list va_list;

            va_start(va_list, cmd);
            ret = i2c_ioctl(fd, cmd, va_list);
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

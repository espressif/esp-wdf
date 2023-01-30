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
#include <stdlib.h>
#include <sys/ioctl.h>

#include "sdkconfig.h"
#include "libc_builtin_ext_data_seq.h"

#ifdef CONFIG_IOCTL_GPIO
#include "ioctl/esp_gpio_ioctl.h"
#endif

#ifdef CONFIG_IOCTL_I2C
#include "ioctl/esp_i2c_ioctl.h"
#endif

#ifdef CONFIG_IOCTL_SPI
#include "ioctl/esp_spi_ioctl.h"
#endif

#ifdef CONFIG_IOCTL_LEDC
#include "ioctl/esp_ledc_ioctl.h"
#endif

#define DATA_SEQ_PUSH_LEDC_CFG(ds, t, i, v) \
    DATA_SEQ_PUSH((ds), DATA_SEQ_LEDC_CFG_CHANNEL_SUB(DATA_SEQ_LEDC_CFG_CHANNEL_CFG, (t), (i)), (v))

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

#ifdef CONFIG_IOCTL_SPI
static int spi_ioctl(int fd, int cmd, va_list va_list)
{
    int ret;
    data_seq_t *ds;
    void *ptr;
    int ds_num = 0;    

    if (cmd == SPIIOCSCFG) {
        ds_num = 6;
    } else if (cmd == SPIIOCEXCHANGE) {
        ds_num = 3;
    } else {
        errno = EINVAL;
        return -1;
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

    if (cmd == SPIIOCSCFG) {
        spi_cfg_t *cfg = (spi_cfg_t *)ptr;

        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_CS_PIN, cfg->cs_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_SCLK_PIN, cfg->sclk_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_MOSI_PIN, cfg->mosi_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_MISO_PIN, cfg->miso_pin);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_FLAGS,   cfg->flags);
        if (cfg->flags & I2C_MASTER) {
            DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_CFG_MASTER_CLK, cfg->master.clock);
        }
    } else if (cmd == SPIIOCEXCHANGE) {
        spi_ex_msg_t *ex_msg = (spi_ex_msg_t *)ptr;

        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_EX_MSG_TXBUF, ex_msg->tx_buffer);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_EX_MSG_RXBUF, ex_msg->rx_buffer);
        DATA_SEQ_PUSH(ds, DATA_SEQ_SPI_EX_MSG_SIZE,  ex_msg->size);
    }

    ret = __real_ioctl(fd, cmd, ds);

    data_seq_free(ds);

    return ret;
}
#endif

#ifdef CONFIG_IOCTL_LEDC
static int ledc_ioctl(int fd, int cmd, va_list va_list)
{
    int ret = -1;
    data_seq_t *ds = NULL;

    if (cmd == LEDCIOCSCFG) {
        ledc_cfg_t *cfg = va_arg(va_list, ledc_cfg_t *);
        if (!cfg) {
            errno = EINVAL;
            return -1;
        }

        ds = data_seq_alloc(2 + cfg->channel_num * 3);
        if (!ds) {
            errno = ENOMEM;
            return -1;
        }

        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_CFG_FREQUENCY,   cfg->frequency);
        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_CFG_CHANNEL_NUM, cfg->channel_num);

        for (int i = 0; i < cfg->channel_num; i++) {
            DATA_SEQ_PUSH_LEDC_CFG(ds, DATA_SEQ_LEDC_CHANNEL_CFG_OUTPUT_PIN, i, cfg->channel_cfg[i].output_pin);
            DATA_SEQ_PUSH_LEDC_CFG(ds, DATA_SEQ_LEDC_CHANNEL_CFG_DUTY, i, cfg->channel_cfg[i].duty);
            DATA_SEQ_PUSH_LEDC_CFG(ds, DATA_SEQ_LEDC_CHANNEL_CFG_PHASE, i, cfg->channel_cfg[i].phase);
        }

        ret = __real_ioctl(fd, cmd, ds);
    } else if (cmd == LEDCIOCSSETFREQ) {
        uint32_t frequency = va_arg(va_list, uint32_t);
        
        ret = __real_ioctl(fd, cmd, frequency);
    } else if (cmd == LEDCIOCSSETDUTY) {
        ledc_duty_cfg_t *cfg = va_arg(va_list, ledc_duty_cfg_t *);
        if (!cfg) {
            errno = EINVAL;
            return -1;
        }

        ds = data_seq_alloc(2);
        if (!ds) {
            errno = ENOMEM;
            return -1;
        }

        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_DUTY_CFG_CHANNEL, cfg->channel);
        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_DUTY_CFG_DUTY, cfg->duty);

        ret = __real_ioctl(fd, cmd, ds);
    } else if (cmd == LEDCIOCSSETPHASE) {
        ledc_phase_cfg_t *cfg = va_arg(va_list, ledc_phase_cfg_t *);
        if (!cfg) {
            errno = EINVAL;
            return -1;
        }

        ds = data_seq_alloc(2);
        if (!ds) {
            errno = ENOMEM;
            return -1;
        }

        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_PHASE_CFG_CHANNEL, cfg->channel);
        DATA_SEQ_PUSH(ds, DATA_SEQ_LEDC_PHASE_CFG_PHASE, cfg->phase);

        ret = __real_ioctl(fd, cmd, ds);
    } else if (cmd == LEDCIOCSPAUSE || cmd == LEDCIOCSRESUME) {
        ret = __real_ioctl(fd, cmd);
    }

    if (ds) {
        data_seq_free(ds);
    }

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
#ifdef CONFIG_IOCTL_SPI
        case SPIIOCSCFG: 
        case SPIIOCEXCHANGE: {
            va_list va_list;

            va_start(va_list, cmd);
            ret = spi_ioctl(fd, cmd, va_list);
            va_end(va_list);

            break;
        }
#endif
#ifdef CONFIG_IOCTL_LEDC
        case LEDCIOCSCFG: 
        case LEDCIOCSSETDUTY:
        case LEDCIOCSSETPHASE: 
        case LEDCIOCSSETFREQ:
        case LEDCIOCSPAUSE:
        case LEDCIOCSRESUME: {
            va_list va_list;

            va_start(va_list, cmd);
            ret = ledc_ioctl(fd, cmd, va_list);
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

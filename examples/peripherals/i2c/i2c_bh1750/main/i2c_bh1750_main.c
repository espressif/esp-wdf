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

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>

#include "sdkconfig.h"
#include "ioctl/esp_i2c_ioctl.h"

#define I2C_DEVICE_BASE     "/dev/i2c/0"

#define I2C_DEVICE_CLOCK    (100 * 1000)
#define I2C_DEVICE_SDA_PIN  CONFIG_I2C_SDA_PIN_NUM
#define I2C_DEVICE_SCL_PIN  CONFIG_I2C_SCL_PIN_NUM

#define I2C_BH1750_ADDRESS  CONFIG_BH1750_ADDR
#define I2C_BH1750_OPMODE   CONFIG_BH1750_OPMODE
#define I2C_BH1750_TIME     (30 * 1000)

#define I2C_TEST_COUNT      CONFIG_I2C_TEST_COUNT

void on_init(void)
{
    int fd;
    int ret;
    i2c_cfg_t cfg;
    const char device[] = I2C_DEVICE_BASE;

    fd = open(device, O_WRONLY);
    if (fd < 0) {
        printf("Opening device %s for writing failed, errno=%d.\n", device, errno);
        return;
    } else {
        printf("Opening device %s for writing OK, fd=%d.\n", device, fd);
    }

    cfg.flags   = I2C_MASTER | I2C_SDA_PULLUP | I2C_SCL_PULLUP;
    cfg.sda_pin = I2C_DEVICE_SDA_PIN;
    cfg.scl_pin = I2C_DEVICE_SCL_PIN;
    cfg.master.clock = I2C_DEVICE_CLOCK;
    ret = ioctl(fd, I2CIOCSCFG, &cfg);
    if (ret < 0) {
        printf("Configure I2C failed, errno=%d.\n", errno);
        close(fd);
        return;
    }

    for (int i = 0; i < I2C_TEST_COUNT; i++) {
        uint8_t data[2];
#ifdef CONFIG_I2C_READ_BH1750_BY_EXCHANGE
        i2c_ex_msg_t ex_msg;
        uint8_t opmode = I2C_BH1750_OPMODE;

        ex_msg.flags     = I2C_EX_MSG_DELAY_EN;
        ex_msg.addr      = I2C_BH1750_ADDRESS;
        ex_msg.delay_ms  = I2C_BH1750_TIME / 1000;
        ex_msg.tx_buffer = &opmode;
        ex_msg.tx_size   = 1;
        ex_msg.rx_buffer = data;
        ex_msg.rx_size   = 2;
        ret = ioctl(fd, I2CIOCEXCHANGE, &ex_msg);
        if (ret < 0) {
            printf("Exchange data failed, errno=%d.\n", errno);
            close(fd);
            return;
        }
#else
        i2c_msg_t msg;

        data[0] = I2C_BH1750_OPMODE;
        msg.flags  = I2C_MSG_WRITE | I2C_MSG_CHECK_ACK;
        msg.addr   = I2C_BH1750_ADDRESS;
        msg.buffer = data;
        msg.size   = 1;
        ret = ioctl(fd, I2CIOCRDWR, &msg);
        if (ret < 0) {
            printf("Write data to I2C slave failed, errno=%d.\n", errno);
            close(fd);
            return;
        }

        /* BH1750 measuring time */
        usleep(I2C_BH1750_TIME);

        msg.flags  = 0;
        msg.addr   = I2C_BH1750_ADDRESS;
        msg.buffer = data;
        msg.size   = 2;
        ret = ioctl(fd, I2CIOCRDWR, &msg);
        if (ret < 0) {
            printf("Read data from I2C slave failed, errno=%d.\n", errno);
            close(fd);
            return;
        }
#endif

        printf("Sensor val: %.02f [Lux].\n", (data[0] << 8 | data[1]) / 1.2);

        sleep(1);
    }

    ret = close(fd);
    if (ret < 0) {
        printf("Close device failed, errno=%d.\n", errno);
        return;
    } else {
        printf("Close device OK.\n");
    }
}

int main(int argc, char *argv[])
{
    on_init();

    return 0;
}

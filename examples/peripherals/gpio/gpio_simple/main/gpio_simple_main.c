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

#include "sdkconfig.h"

#define _COMBINE(a, b)      a #b
#define COMBINE(a, b)       _COMBINE(a, b)

#define GPIO_PIN_NUM        CONFIG_GPIO_SIMPLE_GPIO_PIN_NUM
#define GPIO_DEVICE_BASE    "/dev/gpio/"
#define GPIO_DEVICE         COMBINE(GPIO_DEVICE_BASE, GPIO_PIN_NUM)

#define GPIO_TEST_COUNT     10

void on_init(void)
{
    int fd;
    int ret;
    uint8_t state = 0;
    const char device[] = GPIO_DEVICE;

    fd = open(device, O_WRONLY);
    if (fd < 0) {
        printf("Opening device %s for writing failed, errno=%d.\n", device, errno);
        return;
    } else {
        printf("Opening device %s for writing OK, fd=%d.\n", device, fd);
    }

    /**
     * Change GPIO's output value GPIO_TEST_COUNT * 2 times, see changing GPIO's output
     * value from 1 to 0 as 1 time.
     */
    for (int i = 0; i < GPIO_TEST_COUNT * 2; i++) {
        state = !state;
        ret = write(fd, &state, 1);
        if (ret < 0) {
            printf("Set GPIO-%d to be %d failed, errno=%d.\n", GPIO_PIN_NUM, state, errno);
            close(fd);
            return;
        } else {
            printf("Set GPIO-%d to be %d OK.\n", GPIO_PIN_NUM, state);
        }

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

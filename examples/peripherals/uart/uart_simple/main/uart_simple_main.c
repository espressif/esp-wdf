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

#include "sdkconfig.h"

#ifdef CONFIG_UART_DEVICE_UART0
#define UART_DEVICE "/dev/uart/0"
#elif defined(CONFIG_UART_DEVICE_USB_SERIAL_JTAG_CONTROLLER)
#define UART_DEVICE "/dev/usbserjtag"
#endif

void on_init(void)
{
    int fd;
    int ret;
    const char device[] = UART_DEVICE;
    const char text[] = "Hello World!\n";
    int text_size = sizeof(text);

    printf("Opening device %s for writing", device);
    fd = open(device, O_RDWR);
    if (fd < 0) {
        printf(" failed, errno=%d.\n", errno);
        return;
    } else {
        printf(" OK, fd=%d.\n", fd);
    }

    printf("Write text total %d bytes into device", text_size);
    ret = write(fd, text, text_size);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        close(fd);
        return;
    } else {
        printf(" OK.\n");
    }

    printf("Close device");
    ret = close(fd);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        return;
    } else {
        printf(" OK.\n");
    }
}

int main(int argc, char *argv[])
{
    on_init();

    return 0;
}

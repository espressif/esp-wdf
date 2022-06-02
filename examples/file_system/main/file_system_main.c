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

#define BUFFER_SIZE 32

void on_init(void)
{
    int fd;
    int ret;
    const char file[] = "/storage/hello.txt";
    const char text[] = "Hello World!";
    int text_size = sizeof(text);
    char buffer[BUFFER_SIZE] = { 0 };

    printf("Opening file %s for writing", file);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0) {
        printf(" failed, errno=%d.\n", errno);
        return;
    } else {
        printf(" OK, fd=%d.\n", fd);
    }

    printf("Write text \"%s\" total %d bytes into file", text, text_size);
    ret = write(fd, text, text_size);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        close(fd);
        return;
    } else {
        printf(" OK.\n");
    }

    printf("Close file");
    ret = close(fd);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        return; 
    } else {
        printf(" OK.\n");
    }

    printf("Opening file %s for reading", file);
    fd = open(file, O_RDONLY);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        return; 
    } else {
        printf(" OK, fd=%d.\n", fd);
    }

    printf("Read text from file");
    ret = read(fd, buffer, BUFFER_SIZE - 1);
    if (ret <= 0) {
        printf(" failed errno=%d.\n", errno);
        close(fd);
        return;
    } else {
        printf(" OK, read text is \"%s\".\n", buffer);
    }

    printf("Close file");
    ret = close(fd);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        return; 
    } else {
        printf(" OK.\n");
    }

    printf("Opening file %s for seeking", file);
    fd = open(file, O_RDONLY);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        return; 
    } else {
        printf(" OK, fd=%d.\n", fd);
    }

    printf("Seek file end");
    ret = lseek(fd, 0, SEEK_END);
    if (ret < 0) {
        printf(" failed errno=%d.\n", errno);
        close(fd);
        return;
    } else {
        printf(" OK, file size is %d.\n", ret);
    }

    printf("Close file");
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

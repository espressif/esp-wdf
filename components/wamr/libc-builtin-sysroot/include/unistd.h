/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _WAMR_LIBC_UNISTD_H
#define _WAMR_LIBC_UNISTD_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int close(int);
off_t lseek(int, off_t, int);

int fsync(int);

ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);
ssize_t pread(int, void *, size_t, off_t);
ssize_t pwrite(int, const void *, size_t, off_t);

unsigned sleep(unsigned);
int usleep(unsigned);

#ifdef __cplusplus
}
#endif

#endif

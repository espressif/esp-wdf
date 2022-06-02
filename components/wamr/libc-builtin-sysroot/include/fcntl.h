/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _WAMR_LIBC_FCNTL_H
#define _WAMR_LIBC_FCNTL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t __wasi_fdflags_t;
typedef uint16_t __wasi_oflags_t;
typedef uint8_t __wasi_whence_t;

#define __WASI_FDFLAGS_APPEND ((__wasi_fdflags_t)(1 << 0))
#define __WASI_FDFLAGS_NONBLOCK ((__wasi_fdflags_t)(1 << 2))
#define __WASI_FDFLAGS_SYNC ((__wasi_fdflags_t)(1 << 4))

#define __WASI_OFLAGS_CREAT ((__wasi_oflags_t)(1 << 0))
#define __WASI_OFLAGS_DIRECTORY ((__wasi_oflags_t)(1 << 1))
#define __WASI_OFLAGS_EXCL ((__wasi_oflags_t)(1 << 2))
#define __WASI_OFLAGS_TRUNC ((__wasi_oflags_t)(1 << 3))

#define __WASI_WHENCE_SET (UINT8_C(0))
#define __WASI_WHENCE_CUR (UINT8_C(1))
#define __WASI_WHENCE_END (UINT8_C(2))

#define O_APPEND __WASI_FDFLAGS_APPEND
#define O_NONBLOCK __WASI_FDFLAGS_NONBLOCK
#define O_SYNC __WASI_FDFLAGS_SYNC

#define O_CREAT (__WASI_OFLAGS_CREAT << 12)
#define O_DIRECTORY (__WASI_OFLAGS_DIRECTORY << 12)
#define O_EXCL (__WASI_OFLAGS_EXCL << 12)
#define O_TRUNC (__WASI_OFLAGS_TRUNC << 12)

#define O_NOFOLLOW (0x01000000)
#define O_RDONLY   (0x04000000)
#define O_WRONLY   (0x10000000)

#define O_RDWR (O_RDONLY | O_WRONLY)

#define SEEK_CUR __WASI_WHENCE_CUR
#define SEEK_END __WASI_WHENCE_END
#define SEEK_SET __WASI_WHENCE_SET

int fcntl(int, int, ...);
int open(const char *, int, ...);

#ifdef __cplusplus
}
#endif

#endif
/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _WAMR_LIBC_ERRNO_H
#define _WAMR_LIBC_ERRNO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t __wasi_errno_t;

/**
 * No error occurred. System call completed successfully.
 */
#define __WASI_ERRNO_SUCCESS (UINT16_C(0))

/**
 * Argument list too long.
 */
#define __WASI_ERRNO_2BIG (UINT16_C(1))

/**
 * Permission denied.
 */
#define __WASI_ERRNO_ACCES (UINT16_C(2))

/**
 * Address in use.
 */
#define __WASI_ERRNO_ADDRINUSE (UINT16_C(3))

/**
 * Address not available.
 */
#define __WASI_ERRNO_ADDRNOTAVAIL (UINT16_C(4))

/**
 * Address family not supported.
 */
#define __WASI_ERRNO_AFNOSUPPORT (UINT16_C(5))

/**
 * Resource unavailable, or operation would block.
 */
#define __WASI_ERRNO_AGAIN (UINT16_C(6))

/**
 * Connection already in progress.
 */
#define __WASI_ERRNO_ALREADY (UINT16_C(7))

/**
 * Bad file descriptor.
 */
#define __WASI_ERRNO_BADF (UINT16_C(8))

/**
 * Bad message.
 */
#define __WASI_ERRNO_BADMSG (UINT16_C(9))

/**
 * Device or resource busy.
 */
#define __WASI_ERRNO_BUSY (UINT16_C(10))

/**
 * Operation canceled.
 */
#define __WASI_ERRNO_CANCELED (UINT16_C(11))

/**
 * No child processes.
 */
#define __WASI_ERRNO_CHILD (UINT16_C(12))

/**
 * Connection aborted.
 */
#define __WASI_ERRNO_CONNABORTED (UINT16_C(13))

/**
 * Connection refused.
 */
#define __WASI_ERRNO_CONNREFUSED (UINT16_C(14))

/**
 * Connection reset.
 */
#define __WASI_ERRNO_CONNRESET (UINT16_C(15))

/**
 * Resource deadlock would occur.
 */
#define __WASI_ERRNO_DEADLK (UINT16_C(16))

/**
 * Destination address required.
 */
#define __WASI_ERRNO_DESTADDRREQ (UINT16_C(17))

/**
 * Mathematics argument out of domain of function.
 */
#define __WASI_ERRNO_DOM (UINT16_C(18))

/**
 * Reserved.
 */
#define __WASI_ERRNO_DQUOT (UINT16_C(19))

/**
 * File exists.
 */
#define __WASI_ERRNO_EXIST (UINT16_C(20))

/**
 * Bad address.
 */
#define __WASI_ERRNO_FAULT (UINT16_C(21))

/**
 * File too large.
 */
#define __WASI_ERRNO_FBIG (UINT16_C(22))

/**
 * Host is unreachable.
 */
#define __WASI_ERRNO_HOSTUNREACH (UINT16_C(23))

/**
 * Identifier removed.
 */
#define __WASI_ERRNO_IDRM (UINT16_C(24))

/**
 * Illegal byte sequence.
 */
#define __WASI_ERRNO_ILSEQ (UINT16_C(25))

/**
 * Operation in progress.
 */
#define __WASI_ERRNO_INPROGRESS (UINT16_C(26))

/**
 * Interrupted function.
 */
#define __WASI_ERRNO_INTR (UINT16_C(27))

/**
 * Invalid argument.
 */
#define __WASI_ERRNO_INVAL (UINT16_C(28))

/**
 * I/O error.
 */
#define __WASI_ERRNO_IO (UINT16_C(29))

/**
 * Socket is connected.
 */
#define __WASI_ERRNO_ISCONN (UINT16_C(30))

/**
 * Is a directory.
 */
#define __WASI_ERRNO_ISDIR (UINT16_C(31))

/**
 * Too many levels of symbolic links.
 */
#define __WASI_ERRNO_LOOP (UINT16_C(32))

/**
 * File descriptor value too large.
 */
#define __WASI_ERRNO_MFILE (UINT16_C(33))

/**
 * Too many links.
 */
#define __WASI_ERRNO_MLINK (UINT16_C(34))

/**
 * Message too large.
 */
#define __WASI_ERRNO_MSGSIZE (UINT16_C(35))

/**
 * Reserved.
 */
#define __WASI_ERRNO_MULTIHOP (UINT16_C(36))

/**
 * Filename too long.
 */
#define __WASI_ERRNO_NAMETOOLONG (UINT16_C(37))

/**
 * Network is down.
 */
#define __WASI_ERRNO_NETDOWN (UINT16_C(38))

/**
 * Connection aborted by network.
 */
#define __WASI_ERRNO_NETRESET (UINT16_C(39))

/**
 * Network unreachable.
 */
#define __WASI_ERRNO_NETUNREACH (UINT16_C(40))

/**
 * Too many files open in system.
 */
#define __WASI_ERRNO_NFILE (UINT16_C(41))

/**
 * No buffer space available.
 */
#define __WASI_ERRNO_NOBUFS (UINT16_C(42))

/**
 * No such device.
 */
#define __WASI_ERRNO_NODEV (UINT16_C(43))

/**
 * No such file or directory.
 */
#define __WASI_ERRNO_NOENT (UINT16_C(44))

/**
 * Executable file format error.
 */
#define __WASI_ERRNO_NOEXEC (UINT16_C(45))

/**
 * No locks available.
 */
#define __WASI_ERRNO_NOLCK (UINT16_C(46))

/**
 * Reserved.
 */
#define __WASI_ERRNO_NOLINK (UINT16_C(47))

/**
 * Not enough space.
 */
#define __WASI_ERRNO_NOMEM (UINT16_C(48))

/**
 * No message of the desired type.
 */
#define __WASI_ERRNO_NOMSG (UINT16_C(49))

/**
 * Protocol not available.
 */
#define __WASI_ERRNO_NOPROTOOPT (UINT16_C(50))

/**
 * No space left on device.
 */
#define __WASI_ERRNO_NOSPC (UINT16_C(51))

/**
 * Function not supported.
 */
#define __WASI_ERRNO_NOSYS (UINT16_C(52))

/**
 * The socket is not connected.
 */
#define __WASI_ERRNO_NOTCONN (UINT16_C(53))

/**
 * Not a directory or a symbolic link to a directory.
 */
#define __WASI_ERRNO_NOTDIR (UINT16_C(54))

/**
 * Directory not empty.
 */
#define __WASI_ERRNO_NOTEMPTY (UINT16_C(55))

/**
 * State not recoverable.
 */
#define __WASI_ERRNO_NOTRECOVERABLE (UINT16_C(56))

/**
 * Not a socket.
 */
#define __WASI_ERRNO_NOTSOCK (UINT16_C(57))

/**
 * Not supported, or operation not supported on socket.
 */
#define __WASI_ERRNO_NOTSUP (UINT16_C(58))

/**
 * Inappropriate I/O control operation.
 */
#define __WASI_ERRNO_NOTTY (UINT16_C(59))

/**
 * No such device or address.
 */
#define __WASI_ERRNO_NXIO (UINT16_C(60))

/**
 * Value too large to be stored in data type.
 */
#define __WASI_ERRNO_OVERFLOW (UINT16_C(61))

/**
 * Previous owner died.
 */
#define __WASI_ERRNO_OWNERDEAD (UINT16_C(62))

/**
 * Operation not permitted.
 */
#define __WASI_ERRNO_PERM (UINT16_C(63))

/**
 * Broken pipe.
 */
#define __WASI_ERRNO_PIPE (UINT16_C(64))

/**
 * Protocol error.
 */
#define __WASI_ERRNO_PROTO (UINT16_C(65))

/**
 * Protocol not supported.
 */
#define __WASI_ERRNO_PROTONOSUPPORT (UINT16_C(66))

/**
 * Protocol wrong type for socket.
 */
#define __WASI_ERRNO_PROTOTYPE (UINT16_C(67))

/**
 * Result too large.
 */
#define __WASI_ERRNO_RANGE (UINT16_C(68))

/**
 * Read-only file system.
 */
#define __WASI_ERRNO_ROFS (UINT16_C(69))

/**
 * Invalid seek.
 */
#define __WASI_ERRNO_SPIPE (UINT16_C(70))

/**
 * No such process.
 */
#define __WASI_ERRNO_SRCH (UINT16_C(71))

/**
 * Reserved.
 */
#define __WASI_ERRNO_STALE (UINT16_C(72))

/**
 * Connection timed out.
 */
#define __WASI_ERRNO_TIMEDOUT (UINT16_C(73))

/**
 * Text file busy.
 */
#define __WASI_ERRNO_TXTBSY (UINT16_C(74))

/**
 * Cross-device link.
 */
#define __WASI_ERRNO_XDEV (UINT16_C(75))
/**
 * Extension: Capabilities insufficient.
 */
#define __WASI_ERRNO_NOTCAPABLE (UINT16_C(76))

#define E2BIG __WASI_ERRNO_2BIG
#define EACCES __WASI_ERRNO_ACCES
#define EADDRINUSE __WASI_ERRNO_ADDRINUSE
#define EADDRNOTAVAIL __WASI_ERRNO_ADDRNOTAVAIL
#define EAFNOSUPPORT __WASI_ERRNO_AFNOSUPPORT
#define EAGAIN __WASI_ERRNO_AGAIN
#define EALREADY __WASI_ERRNO_ALREADY
#define EBADF __WASI_ERRNO_BADF
#define EBADMSG __WASI_ERRNO_BADMSG
#define EBUSY __WASI_ERRNO_BUSY
#define ECANCELED __WASI_ERRNO_CANCELED
#define ECHILD __WASI_ERRNO_CHILD
#define ECONNABORTED __WASI_ERRNO_CONNABORTED
#define ECONNREFUSED __WASI_ERRNO_CONNREFUSED
#define ECONNRESET __WASI_ERRNO_CONNRESET
#define EDEADLK __WASI_ERRNO_DEADLK
#define EDESTADDRREQ __WASI_ERRNO_DESTADDRREQ
#define EDOM __WASI_ERRNO_DOM
#define EDQUOT __WASI_ERRNO_DQUOT
#define EEXIST __WASI_ERRNO_EXIST
#define EFAULT __WASI_ERRNO_FAULT
#define EFBIG __WASI_ERRNO_FBIG
#define EHOSTUNREACH __WASI_ERRNO_HOSTUNREACH
#define EIDRM __WASI_ERRNO_IDRM
#define EILSEQ __WASI_ERRNO_ILSEQ
#define EINPROGRESS __WASI_ERRNO_INPROGRESS
#define EINTR __WASI_ERRNO_INTR
#define EINVAL __WASI_ERRNO_INVAL
#define EIO __WASI_ERRNO_IO
#define EISCONN __WASI_ERRNO_ISCONN
#define EISDIR __WASI_ERRNO_ISDIR
#define ELOOP __WASI_ERRNO_LOOP
#define EMFILE __WASI_ERRNO_MFILE
#define EMLINK __WASI_ERRNO_MLINK
#define EMSGSIZE __WASI_ERRNO_MSGSIZE
#define EMULTIHOP __WASI_ERRNO_MULTIHOP
#define ENAMETOOLONG __WASI_ERRNO_NAMETOOLONG
#define ENETDOWN __WASI_ERRNO_NETDOWN
#define ENETRESET __WASI_ERRNO_NETRESET
#define ENETUNREACH __WASI_ERRNO_NETUNREACH
#define ENFILE __WASI_ERRNO_NFILE
#define ENOBUFS __WASI_ERRNO_NOBUFS
#define ENODEV __WASI_ERRNO_NODEV
#define ENOENT __WASI_ERRNO_NOENT
#define ENOEXEC __WASI_ERRNO_NOEXEC
#define ENOLCK __WASI_ERRNO_NOLCK
#define ENOLINK __WASI_ERRNO_NOLINK
#define ENOMEM __WASI_ERRNO_NOMEM
#define ENOMSG __WASI_ERRNO_NOMSG
#define ENOPROTOOPT __WASI_ERRNO_NOPROTOOPT
#define ENOSPC __WASI_ERRNO_NOSPC
#define ENOSYS __WASI_ERRNO_NOSYS
#define ENOTCONN __WASI_ERRNO_NOTCONN
#define ENOTDIR __WASI_ERRNO_NOTDIR
#define ENOTEMPTY __WASI_ERRNO_NOTEMPTY
#define ENOTRECOVERABLE __WASI_ERRNO_NOTRECOVERABLE
#define ENOTSOCK __WASI_ERRNO_NOTSOCK
#define ENOTSUP __WASI_ERRNO_NOTSUP
#define ENOTTY __WASI_ERRNO_NOTTY
#define ENXIO __WASI_ERRNO_NXIO
#define EOVERFLOW __WASI_ERRNO_OVERFLOW
#define EOWNERDEAD __WASI_ERRNO_OWNERDEAD
#define EPERM __WASI_ERRNO_PERM
#define EPIPE __WASI_ERRNO_PIPE
#define EPROTO __WASI_ERRNO_PROTO
#define EPROTONOSUPPORT __WASI_ERRNO_PROTONOSUPPORT
#define EPROTOTYPE __WASI_ERRNO_PROTOTYPE
#define ERANGE __WASI_ERRNO_RANGE
#define EROFS __WASI_ERRNO_ROFS
#define ESPIPE __WASI_ERRNO_SPIPE
#define ESRCH __WASI_ERRNO_SRCH
#define ESTALE __WASI_ERRNO_STALE
#define ETIMEDOUT __WASI_ERRNO_TIMEDOUT
#define ETXTBSY __WASI_ERRNO_TXTBSY
#define EXDEV __WASI_ERRNO_XDEV
#define ENOTCAPABLE __WASI_ERRNO_NOTCAPABLE

#define EOPNOTSUPP ENOTSUP
#define EWOULDBLOCK EAGAIN

#ifdef __cplusplus
extern thread_local int errno;
#else
extern _Thread_local int errno;
#endif

#define errno errno

#ifdef __cplusplus
}
#endif

#endif
// *************************************************************************
//
// Copyright (c) 2021 Andrei Gramakov. All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************


#pragma once

#include <iostream>
#include <stdint.h>
#include <string>
#include "errno.h"

/**
 * @brief Based on newlib/libc/include/sys/errno.h
 */
typedef enum {
    ERROR_FAIL           = -1,
    NO_ERROR             = 0,            ///< No errors
    ERROR_PERM           = 1,            ///< Not super-user
    ERROR_NOENT          = 2,            ///< No such file or directory
    ERROR_SRCH           = 3,            ///< No such process
    ERROR_INTR           = 4,            ///< Interrupted system call
    ERROR_IO             = 5,            ///< I/O error
    ERROR_NXIO           = 6,            ///< No such device or address
    ERROR_2BIG           = 7,            ///< Arg list too long
    ERROR_NOEXEC         = 8,            ///< Exec format error
    ERROR_BADF           = 9,            ///< Bad file number
    ERROR_CHILD          = 10,           ///< No children
    ERROR_AGAIN          = 11,           ///< No more processes
    ERROR_WOULDBLOCK     = ERROR_AGAIN,  ///< Operation would block
    ERROR_NOMEM          = 12,           ///< Not enough core
    ERROR_ACCES          = 13,           ///< Permission denied
    ERROR_FAULT          = 14,           ///< Bad address
    ERROR_NOTBLK         = 15,           ///< Block device required
    ERROR_BUSY           = 16,           ///< Mount device busy
    ERROR_EXIST          = 17,           ///< File exists
    ERROR_XDEV           = 18,           ///< Cross-device link
    ERROR_NODEV          = 19,           ///< No such device
    ERROR_NOTDIR         = 20,           ///< Not a directory
    ERROR_ISDIR          = 21,           ///< Is a directory
    ERROR_INVAL          = 22,           ///< Invalid argument
    ERROR_NFILE          = 23,           ///< Too many open files in system
    ERROR_MFILE          = 24,           ///< Too many open files
    ERROR_NOTTY          = 25,           ///< Not a typewriter
    ERROR_TXTBSY         = 26,           ///< Text file busy
    ERROR_FBIG           = 27,           ///< File too large
    ERROR_NOSPC          = 28,           ///< No space left on device
    ERROR_SPIPE          = 29,           ///< Illegal seek
    ERROR_ROFS           = 30,           ///< Read only file system
    ERROR_MLINK          = 31,           ///< Too many links
    ERROR_PIPE           = 32,           ///< Broken pipe
    ERROR_DOM            = 33,           ///< Math arg out of domain of func
    ERROR_RANGE          = 34,           ///< Math result not representable
    ERROR_NOMSG          = 35,           ///< No message of desired type
    ERROR_IDRM           = 36,           ///< Identifier removed
    ERROR_CHRNG          = 37,           ///< Channel number out of range
    ERROR_L2NSYNC        = 38,           ///< Level 2 not synchronized
    ERROR_L3HLT          = 39,           ///< Level 3 halted
    ERROR_L3RST          = 40,           ///< Level 3 reset
    ERROR_LNRNG          = 41,           ///< Link number out of range
    ERROR_UNATCH         = 42,           ///< Protocol driver not attached
    ERROR_NOCSI          = 43,           ///< No CSI structure available
    ERROR_L2HLT          = 44,           ///< Level 2 halted
    ERROR_DEADLK         = 45,           ///< Deadlock condition
    ERROR_NOLCK          = 46,           ///< No record locks available
    ERROR_BADE           = 50,           ///< Invalid exchange
    ERROR_BADR           = 51,           ///< Invalid request descriptor
    ERROR_XFULL          = 52,           ///< Exchange full
    ERROR_NOANO          = 53,           ///< No anode
    ERROR_BADRQC         = 54,           ///< Invalid request code
    ERROR_BADSLT         = 55,           ///< Invalid slot
    ERROR_DEADLOCK       = 56,           ///< File locking deadlock error
    ERROR_BFONT          = 57,           ///< Bad font file fmt
    ERROR_NOSTR          = 60,           ///< Device not a stream
    ERROR_NODATA         = 61,           ///< No data (for no delay io)
    ERROR_TIME           = 62,           ///< Timer expired
    ERROR_NOSR           = 63,           ///< Out of streams resources
    ERROR_NONET          = 64,           ///< Machine is not on the network
    ERROR_NOPKG          = 65,           ///< Package not installed
    ERROR_REMOTE         = 66,           ///< The object is remote
    ERROR_NOLINK         = 67,           ///< The link has been severed
    ERROR_ADV            = 68,           ///< Advertise error
    ERROR_SRMNT          = 69,           ///< Srmount error
    ERROR_COMM           = 70,           ///< Communication error on send
    ERROR_PROTO          = 71,           ///< Protocol error
    ERROR_MULTIHOP       = 74,           ///< Multihop attempted
    ERROR_LBIN           = 75,           ///< Inode is remote (not really error)
    ERROR_DOTDOT         = 76,           ///< Cross mount point (not really error)
    ERROR_BADMSG         = 77,           ///< Trying to read unreadable message
    ERROR_FTYPE          = 79,           ///< Inappropriate file type or format
    ERROR_NOTUNIQ        = 80,           ///< Given log. name not unique
    ERROR_BADFD          = 81,           ///< f.d. invalid for this operation
    ERROR_REMCHG         = 82,           ///< Remote address changed
    ERROR_LIBACC         = 83,           ///< Can't access a needed shared lib
    ERROR_LIBBAD         = 84,           ///< Accessing a corrupted shared lib
    ERROR_LIBSCN         = 85,           ///< .lib section in a.out corrupted
    ERROR_LIBMAX         = 86,           ///< Attempting to link in too many libs
    ERROR_LIBEXEC        = 87,           ///< Attempting to exec a shared library
    ERROR_NOSYS          = 88,           ///< Function not implemented
    ERROR_NMFILE         = 89,           ///< No more files
    ERROR_NOTEMPTY       = 90,           ///< Directory not empty
    ERROR_NAMETOOLONG    = 91,           ///< File or path name too long
    ERROR_LOOP           = 92,           ///< Too many symbolic links
    ERROR_OPNOTSUPP      = 95,           ///< Operation not supported on transport endpoint
    ERROR_PFNOSUPPORT    = 96,           ///< Protocol family not supported
    ERROR_CONNRESET      = 104,          ///< Connection reset by peer
    ERROR_NOBUFS         = 105,          ///< No buffer space available
    ERROR_AFNOSUPPORT    = 106,          ///< Address family not supported by protocol family
    ERROR_PROTOTYPE      = 107,          ///< Protocol wrong type for socket
    ERROR_NOTSOCK        = 108,          ///< Socket operation on non-socket
    ERROR_NOPROTOOPT     = 109,          ///< Protocol not available
    ERROR_SHUTDOWN       = 110,          ///< Can't send after socket shutdown
    ERROR_CONNREFUSED    = 111,          ///< Connection refused
    ERROR_ADDRINUSE      = 112,          ///< Address already in use
    ERROR_CONNABORTED    = 113,          ///< Connection aborted
    ERROR_NETUNREACH     = 114,          ///< Network is unreachable
    ERROR_NETDOWN        = 115,          ///< Network interface is not configured
    ERROR_TIMEDOUT       = 116,          ///< Connection timed out
    ERROR_HOSTDOWN       = 117,          ///< Host is down
    ERROR_HOSTUNREACH    = 118,          ///< Host is unreachable
    ERROR_INPROGRESS     = 119,          ///< Connection already in progress
    ERROR_ALREADY        = 120,          ///< Socket already connected
    ERROR_DESTADDRREQ    = 121,          ///< Destination address required
    ERROR_MSGSIZE        = 122,          ///< Message too long
    ERROR_PROTONOSUPPORT = 123,          ///< Unknown protocol
    ERROR_SOCKTNOSUPPORT = 124,          ///< Socket type not supported
    ERROR_ADDRNOTAVAIL   = 125,          ///< Address not available
    ERROR_NETRESET       = 126,
    ERROR_ISCONN         = 127,  ///< Socket is already connected
    ERROR_NOTCONN        = 128,  ///< Socket is not connected
    ERROR_TOOMANYREFS    = 129,
    ERROR_PROCLIM        = 130,
    ERROR_USERS          = 131,
    ERROR_DQUOT          = 132,
    ERROR_STALE          = 133,
    ERROR_NOTSUP         = 134,  ///< Not supported
    ERROR_NOMEDIUM       = 135,  ///< No medium (in tape drive)
    ERROR_NOSHARE        = 136,  ///< No such host or network path
    ERROR_CASECLASH      = 137,  ///< Filename exists with different case
    ERROR_ILSEQ          = 138,
    ERROR_OVERFLOW       = 139,   ///< Value too large for defined data type
    ERROR_CANCELED       = 140,   ///< Operation canceled
    ERROR_NOTRECOVERABLE = 141,   ///< State not recoverable
    ERROR_OWNERDEAD      = 142,   ///< Previous owner died
    ERROR_STRPIPE        = 143,   ///< Streams pipe error
    _ERROR_LASTERROR     = 2000,  ///< Users can add values starting here
    ERROR_NOTEXIST       = 2000,  ///< Entity doesn't exists
    ERROR_WRONGSTATE     = 2001,  ///< System is in incorrect/unexpected state
} error_t;


#define RETURN_ON_ERROR(x)   \
    do {                     \
        error_t res = (x);   \
        if (res != NO_ERROR) \
            return res;      \
    } while (0)

inline void CRITICAL_ERROR(error_t err, const std::string &msg) {
    std::cout << "ERROR " << int(err) << ": " << msg << std::endl;
    throw err;
}
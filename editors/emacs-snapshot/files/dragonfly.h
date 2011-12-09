/* System description header for DragonFly systems.
   This file describes the parameters that system description files
   should define or not.
   Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
   Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Get most of the stuff from bsd-common */
#include "bsd-common.h"

/* For mem-limits.h. */
#define BSD4_2

/* These aren't needed, since we have getloadavg.  */
#undef KERNEL_FILE
#undef LDAV_SYMBOL

#define PENDING_OUTPUT_COUNT(FILE) __fpending(FILE)

#define LIBS_DEBUG
#define LIBS_SYSTEM -lutil
#define TERMINFO
#define LIBS_TERMCAP -lncurses
#define SYSV_SYSTEM_DIR

/* freebsd has POSIX-style pgrp behavior. */
#undef BSD_PGRPS
#define GETPGRP_NO_ARG

#ifdef DFLY_CRT_USRLIB
#define ORDINARY_LINK
#define LIB_STANDARD -lc
#else
#define START_FILES pre-crt0.o /usr/lib/gcc41/crt1.o /usr/lib/gcc41/crti.o /usr/lib/gcc41/crtbegin.o
#define LIB_STANDARD -L/usr/lib/gcc41 -lgcc -lc -lgcc /usr/lib/gcc41/crtend.o /usr/lib/gcc41/crtn.o
#endif

#define LD_SWITCH_SYSTEM_1
#define UNEXEC unexelf.o
#undef LIB_GCC
#define LIB_GCC

#define HAVE_WAIT_HEADER
#define HAVE_GETLOADAVG 1
#define HAVE_TERMIOS
#define NO_TERMIO
#define DECLARE_GETPWUID_WITH_UID_T

/* freebsd uses OXTABS instead of the expected TAB3. */
#define TABDLY OXTABS
#define TAB3 OXTABS

/* this silences a few compilation warnings */
#undef BSD_SYSTEM
#define BSD_SYSTEM 199506

/* Needed to avoid hanging when child process writes an error message
   and exits -- enami tsugutomo <enami@ba2.so-net.or.jp>.  */
#define vfork fork

/* Don't close pty in process.c to make it as controlling terminal.
   It is already a controlling terminal of subprocess, because we did
   ioctl TIOCSCTTY.  */
#define DONT_REOPEN_PTY

/* If the system's imake configuration file defines `NeedWidePrototypes'
   as `NO', we must define NARROWPROTO manually.  Such a define is
   generated in the Makefile generated by `xmkmf'.  If we don't 
   define NARROWPROTO, we will see the wrong function prototypes
   for X functions taking float or double parameters.  */

#define NARROWPROTO 1

#define C_SWITCH_SYSTEM
#define LD_SWITCH_SYSTEM

/* Circumvent a bug in FreeBSD.  In the following sequence of
   writes/reads on a PTY, read(2) returns bogus data:

   write(2)  1022 bytes
   write(2)   954 bytes, get EAGAIN
   read(2)   1024 bytes in process_read_output
   read(2)     11 bytes in process_read_output

   That is, read(2) returns more bytes than have ever been written
   successfully.  The 1033 bytes read are the 1022 bytes written
   successfully after processing (for example with CRs added if the
   terminal is set up that way which it is here).  The same bytes will
   be seen again in a later read(2), without the CRs.  */

#define BROKEN_PTY_READ_AFTER_EAGAIN 1

/* Tell that garbage collector that setjmp is known to save all
   registers relevant for conservative garbage collection in the
   jmp_buf.  */

#define GC_SETJMP_WORKS 1

/* Use the GC_MAKE_GCPROS_NOOPS (see lisp.h) method for marking the
   stack.  */

#define GC_MARK_STACK 	GC_MAKE_GCPROS_NOOPS

/* Define USE_MMAP_FOR_BUFFERS to let Emacs use mmap(2) to allocate
   buffer text.  This overrides REL_ALLOC.  */

#define USE_MMAP_FOR_BUFFERS	1

/* Use sigprocmask(2) and friends instead of sigblock(2); the man page
   of sigblock says it is obsolete.  */

#define POSIX_SIGNALS		1

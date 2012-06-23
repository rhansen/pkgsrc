$NetBSD: patch-gcc_config_dragonfly.h,v 1.1 2012/06/23 22:13:02 marino Exp $

--- gcc/config/dragonfly.h.orig	2012-06-22 10:35:29.000000000 +0000
+++ gcc/config/dragonfly.h
@@ -0,0 +1,135 @@
+/* Base configuration file for all DragonFly targets.
+   Copyright (C) 1999, 2000, 2001, 2007, 2008 Free Software Foundation, Inc.
+
+This file is part of GCC.
+
+GCC is free software; you can redistribute it and/or modify
+it under the terms of the GNU General Public License as published by
+the Free Software Foundation; either version 3, or (at your option)
+any later version.
+
+GCC is distributed in the hope that it will be useful,
+but WITHOUT ANY WARRANTY; without even the implied warranty of
+MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+GNU General Public License for more details.
+
+You should have received a copy of the GNU General Public License
+along with GCC; see the file COPYING3.  If not see
+<http://www.gnu.org/licenses/>.  */
+
+/* Common DragonFly configuration.
+   All DragonFly architectures should include this file, which will specify
+   their commonalities.
+   Adapted from gcc/config/i386/freebsd-elf.h by
+   David O'Brien <obrien@FreeBSD.org>.
+   Further work by David O'Brien <obrien@FreeBSD.org> and
+   Loren J. Rittle <ljrittle@acm.org>.  */
+
+#undef  TARGET_OS_CPP_BUILTINS
+#define TARGET_OS_CPP_BUILTINS()            \
+  do                                        \
+    {                                       \
+       builtin_define_std ("unix");         \
+       builtin_define ("__DragonFly__");    \
+       builtin_assert ("system=unix");      \
+       builtin_assert ("system=bsd");       \
+       builtin_assert ("system=DragonFly"); \
+    }                                       \
+  while (0)
+
+#undef  CPP_SPEC
+#define CPP_SPEC \
+ "%(cpp_cpu) %(cpp_arch) %{posix:-D_POSIX_SOURCE}"
+
+#undef  STARTFILE_SPEC
+#define STARTFILE_SPEC	\
+  "%{!shared: \
+     %{pg:gcrt1.o%s} \
+     %{!pg: \
+       %{p:gcrt1.o%s} \
+       %{!p: \
+         %{profile: gcrt1.o%s} \
+         %{!profile: \
+           %{pie: Scrt1.o%s;:crt1.o%s}}}}} \
+   crti.o%s \
+   %{shared|pie:crtbeginS.o%s;:crtbegin.o%s}"
+
+#undef  ENDFILE_SPEC
+#define ENDFILE_SPEC \
+  "%{shared|pie:crtendS.o%s;:crtend.o%s} crtn.o%s"
+
+#undef  LIB_SPEC
+#define LIB_SPEC \
+  "%{pthread:-lpthread} -lc"
+
+#if defined(HAVE_LD_EH_FRAME_HDR)
+#define LINK_EH_SPEC "--eh-frame-hdr"
+#endif
+
+/* Provide a LINK_SPEC appropriate for DragonFly.  Here we provide support
+   for the special GCC options -static and -shared, which allow us to
+   link things in one of these three modes by applying the appropriate
+   combinations of options at link-time.
+
+   When the -shared link option is used a final link is not being
+   done.  */
+
+#define DFBSD_LINK_SPEC \
+ "%{p:%nconsider using '-pg' instead of '-p' with gprof(1)} \
+  %{v:-V} \
+  %{assert*} %{R*} %{rpath*} %{defsym*} \
+  %{shared:-Bshareable %{h*} %{soname*}} \
+  %{!shared: \
+   %{!static: \
+    %{rdynamic:-export-dynamic} \
+    -dynamic-linker %(dfbsd_dynamic_linker) \
+   } \
+  %{static:-Bstatic}} \
+  %{!static:--hash-style=both} \
+  %{symbolic:-Bsymbolic}"
+
+#undef  LINK_SPEC
+#define LINK_SPEC DFBSD_LINK_SPEC
+
+#define DFBSD_DYNAMIC_LINKER "/usr/libexec/ld-elf.so.2"
+
+
+/* Use --as-needed -lgcc_s for eh support.  */
+#ifdef HAVE_LD_AS_NEEDED
+#define USE_LD_AS_NEEDED 1
+#endif
+
+/************************[  Target stuff  ]***********************************/
+
+/* All DragonFly Architectures support the ELF object file format.  */
+#undef  OBJECT_FORMAT_ELF
+#define OBJECT_FORMAT_ELF
+
+/* Don't assume anything about the header files.  */
+#undef  NO_IMPLICIT_EXTERN_C
+#define NO_IMPLICIT_EXTERN_C	1
+
+/* Follow DragonFly's standard headers (<machine/stdint.h>, etc...).  */
+
+#undef  WCHAR_TYPE
+#define WCHAR_TYPE "int"
+
+#undef  WINT_TYPE
+#define WINT_TYPE "int"
+
+/* 
+ * Profile libraries are found at /usr/lib/profile with standard names
+ * #define MATH_LIBRARY_PROFILE    "m_p" 
+ */
+
+/* Code generation parameters.  */
+
+/* Use periods rather than dollar signs in special g++ assembler names.
+   This ensures the configuration knows our system correctly so we can link
+   with libraries compiled with the native cc.  */
+#undef NO_DOLLAR_IN_LABEL
+
+/* Used by libgcc2.c.  We support file locking with fcntl / F_SETLKW.
+   This enables the test coverage code to use file locking when exiting a
+   program, which avoids race conditions if the program has forked.  */
+#define TARGET_POSIX_IO

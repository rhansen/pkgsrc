$NetBSD: patch-common_uposixdefs.h,v 1.4 2018/01/12 12:43:08 jperkin Exp $

Don't perform _STDC_C99 workaround with clang.

--- common/uposixdefs.h.orig	2017-03-14 21:01:57.000000000 +0000
+++ common/uposixdefs.h
@@ -44,8 +44,10 @@
      * and define _XOPEN_SOURCE to different values depending on __STDC_VERSION__.
      * In C++ source code (e.g., putil.cpp), __STDC_VERSION__ is not defined at all.
      */
+#if !defined(_SCO_DS)
 #   define _XOPEN_SOURCE 600
 #endif
+#endif
 
 /*
  * Make sure things like readlink and such functions work.
@@ -54,9 +56,11 @@
  *
  * z/OS needs this definition for timeval and to get usleep.
  */
+#if !defined(__sun) && !defined(_SCO_DS)
 #if !defined(_XOPEN_SOURCE_EXTENDED) && defined(__TOS_MVS__)
 #   define _XOPEN_SOURCE_EXTENDED 1
 #endif
+#endif
 
 /**
  * Solaris says:
@@ -64,8 +68,11 @@
  *   than a c99 or later compiler."
  * Apparently C++11 is not "or later". Work around this.
  */
-#if defined(__cplusplus) && (defined(sun) || defined(__sun)) && !defined (_STDC_C99)
+#if defined(__cplusplus) && (defined(sun) || defined(__sun)) && !defined (_STDC_C99) && !defined(__clang__)
 #   define _STDC_C99
 #endif
 
+#if defined(__cplusplus) && defined(__NetBSD__)
+#define _ISOC99_SOURCE
+#endif
 #endif  /* __UPOSIXDEFS_H__ */

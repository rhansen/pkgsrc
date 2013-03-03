$NetBSD: patch-src_argp_argp-fmtstream.c,v 1.1 2013/03/03 01:09:34 joerg Exp $

--- src/argp/argp-fmtstream.c.orig	2003-03-13 17:59:09.000000000 +0000
+++ src/argp/argp-fmtstream.c
@@ -389,6 +389,7 @@ __argp_fmtstream_printf (struct argp_fmt
 weak_alias (__argp_fmtstream_printf, argp_fmtstream_printf)
 #endif
 
+#if __STDC_VERSION__ - 199900L < 1
 /* Duplicate the inline definitions in argp-fmtstream.h, for compilers
  * that don't do inlining. */
 size_t
@@ -471,5 +472,6 @@ __argp_fmtstream_point (argp_fmtstream_t
     __argp_fmtstream_update (__fs);
   return __fs->point_col >= 0 ? __fs->point_col : 0;
 }
+#endif
 
 #endif /* !ARGP_FMTSTREAM_USE_LINEWRAP */

$NetBSD: patch-InOut_libsnd.c,v 1.1 2014/03/06 10:16:53 mrg Exp $

--- InOut/libsnd.c.orig	2014-01-07 08:53:47.000000000 -0800
+++ InOut/libsnd.c	2014-02-12 23:47:56.000000000 -0800
@@ -31,6 +31,7 @@
 #ifdef PIPES
 # if defined(SGI) || defined(LINUX) || defined(__BEOS__) || defined(NeXT) ||  \
      defined(__MACH__)
+     defined(__MACH__) || defined(__NetBSD__) || defined(__DragonFly__)
 #  define _popen popen
 #  define _pclose pclose
 # endif

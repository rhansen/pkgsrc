$NetBSD: patch-mozilla_build_autoconf_gcc-pr49911.m4,v 1.1 2012/03/10 03:26:05 ryoon Exp $

--- mozilla/build/autoconf/gcc-pr49911.m4.orig	2012-02-16 14:08:40.000000000 +0000
+++ mozilla/build/autoconf/gcc-pr49911.m4
@@ -56,7 +56,7 @@ CXXFLAGS="$_SAVE_CXXFLAGS"
 
 AC_LANG_RESTORE
 
-if test "$ac_have_gcc_pr49911" == "yes"; then
+if test "$ac_have_gcc_pr49911" = "yes"; then
    AC_MSG_RESULT(yes)
    CFLAGS="$CFLAGS -fno-tree-vrp"
    CXXFLAGS="$CXXFLAGS -fno-tree-vrp"

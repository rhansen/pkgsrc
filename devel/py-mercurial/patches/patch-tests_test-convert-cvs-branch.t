$NetBSD: patch-tests_test-convert-cvs-branch.t,v 1.1 2014/12/28 17:16:54 wiz Exp $

Fix cvs-specific tests with cvs-1.12.
http://bz.selenic.com/show_bug.cgi?id=4482

--- tests/test-convert-cvs-branch.t.orig	2014-12-18 20:59:22.000000000 +0000
+++ tests/test-convert-cvs-branch.t
@@ -21,6 +21,7 @@ create cvs repository
   $ CVS_OPTIONS=-f
   $ export CVS_OPTIONS
   $ cd ..
+  $ rmdir cvsrepo
   $ cvscall -q -d "$CVSROOT" init
 
 Create a new project

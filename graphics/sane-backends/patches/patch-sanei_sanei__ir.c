$NetBSD: patch-sanei_sanei__ir.c,v 1.2 2015/10/27 11:29:35 wiz Exp $

Remove unportable header inclusion.
https://alioth.debian.org/tracker/index.php?func=detail&aid=315208&group_id=30186&atid=410366

--- sanei/sanei_ir.c.orig	2015-09-29 01:10:43.000000000 +0000
+++ sanei/sanei_ir.c
@@ -29,7 +29,6 @@
 
 #include <stdlib.h>
 #include <string.h>
-#include <values.h>
 #include <math.h>
 
 #define BACKEND_NAME sanei_ir	/* name of this module for debugging */

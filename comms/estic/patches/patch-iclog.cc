$NetBSD: patch-iclog.cc,v 1.1 2012/02/16 16:47:58 hans Exp $

--- iclog.cc.orig	2012-01-25 18:32:44.447476635 +0100
+++ iclog.cc	2012-01-25 18:50:27.905634296 +0100
@@ -31,6 +31,7 @@
 #include "iccli.h"
 #include "iclog.h"
 
+#undef DS
 
 
 /*****************************************************************************/

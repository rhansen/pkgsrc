$NetBSD: patch-src_weapon.cpp,v 1.1.1.1 2012/01/08 15:52:12 wiz Exp $

Add missing header.

--- src/weapon.cpp.orig	2005-10-03 05:42:21.000000000 +0000
+++ src/weapon.cpp
@@ -5,6 +5,7 @@
 #include "vc6.h" // Fixes things if you're using VC6, does nothing if otherwise
 
 #include <string>
+#include <string.h>
 
 #include "weapon.h"
 

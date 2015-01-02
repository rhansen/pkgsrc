$NetBSD: patch-mozilla_js_src_jit_arm_Architecture-arm.cpp,v 1.1 2015/01/02 04:26:21 ryoon Exp $

--- mozilla/js/src/jit/arm/Architecture-arm.cpp.orig	2014-12-03 06:22:56.000000000 +0000
+++ mozilla/js/src/jit/arm/Architecture-arm.cpp
@@ -16,7 +16,7 @@
 #include "jit/arm/Assembler-arm.h"
 #include "jit/RegisterSets.h"
 
-#if defined(ANDROID) || defined(JS_ARM_SIMULATOR)
+#if defined(ANDROID) || defined(JS_ARM_SIMULATOR) || defined(__NetBSD__)
 // The Android NDK and B2G do not include the hwcap.h kernel header, and it is not
 // defined when building the simulator, so inline the header defines we need.
 # define HWCAP_VFP        (1 << 6)

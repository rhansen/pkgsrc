$NetBSD: patch-mozilla_ipc_chromium_src_base_third__party_nspr_prtime.cc,v 1.3 2012/09/02 06:43:42 ryoon Exp $

--- mozilla/ipc/chromium/src/base/third_party/nspr/prtime.cc.orig	2012-08-25 00:31:11.000000000 +0000
+++ mozilla/ipc/chromium/src/base/third_party/nspr/prtime.cc
@@ -180,7 +180,7 @@ PR_ImplodeTime(const PRExplodedTime *exp
     LL_ADD(retVal, retVal, temp);
 
     return retVal;
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_DRAGONFLY)
     struct tm exp_tm = {0};
     exp_tm.tm_sec  = exploded->tm_sec;
     exp_tm.tm_min  = exploded->tm_min;
@@ -213,6 +213,24 @@ PR_ImplodeTime(const PRExplodedTime *exp
     result *= kSecondsToMicroseconds;
     result += exploded->tm_usec;
     return result;
+#elif defined(OS_FREEBSD) || defined(OS_NETBSD)
+    struct tm exp_tm = {0};
+    exp_tm.tm_sec  = exploded->tm_sec;
+    exp_tm.tm_min  = exploded->tm_min;
+    exp_tm.tm_hour = exploded->tm_hour;
+    exp_tm.tm_mday = exploded->tm_mday;
+    exp_tm.tm_mon  = exploded->tm_month;
+    exp_tm.tm_year = exploded->tm_year - 1900;
+
+    // time_t is 64bit
+    time_t absolute_time = timegm(&exp_tm);
+
+    PRTime result = static_cast<PRTime>(absolute_time);
+    result -= exploded->tm_params.tp_gmt_offset +
+              exploded->tm_params.tp_dst_offset;
+    result *= kSecondsToMicroseconds;
+    result += exploded->tm_usec;
+    return result;
 #else
 #error No PR_ImplodeTime implemented on your platform.
 #endif

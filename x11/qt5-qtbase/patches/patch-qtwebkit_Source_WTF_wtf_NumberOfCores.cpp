$NetBSD: patch-qtwebkit_Source_WTF_wtf_NumberOfCores.cpp,v 1.1 2013/12/13 14:38:35 ryoon Exp $

* Add NetBSD support

--- qtwebkit/Source/WTF/wtf/NumberOfCores.cpp.orig	2013-11-27 01:01:21.000000000 +0000
+++ qtwebkit/Source/WTF/wtf/NumberOfCores.cpp
@@ -50,7 +50,7 @@ int numberOfProcessorCores()
     if (s_numberOfCores > 0)
         return s_numberOfCores;
 
-#if OS(DARWIN) || OS(OPENBSD) || OS(NETBSD) || OS(FREEBSD)
+#if OS(DARWIN) || OS(OPENBSD) || OS(FREEBSD)
     unsigned result;
     size_t length = sizeof(result);
     int name[] = {
@@ -60,7 +60,7 @@ int numberOfProcessorCores()
     int sysctlResult = sysctl(name, sizeof(name) / sizeof(int), &result, &length, 0, 0);
 
     s_numberOfCores = sysctlResult < 0 ? defaultIfUnavailable : result;
-#elif OS(LINUX) || OS(AIX) || OS(SOLARIS)
+#elif OS(LINUX) || OS(AIX) || OS(SOLARIS) || OS(NETBSD)
     long sysconfResult = sysconf(_SC_NPROCESSORS_ONLN);
 
     s_numberOfCores = sysconfResult < 0 ? defaultIfUnavailable : static_cast<int>(sysconfResult);

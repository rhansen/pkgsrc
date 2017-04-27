$NetBSD: patch-mozilla_ipc_glue_GeckoChildProcessHost.cpp,v 1.1 2017/04/27 13:38:19 ryoon Exp $

--- mozilla/ipc/glue/GeckoChildProcessHost.cpp.orig	2016-04-07 21:33:19.000000000 +0000
+++ mozilla/ipc/glue/GeckoChildProcessHost.cpp
@@ -4,7 +4,13 @@
  * License, v. 2.0. If a copy of the MPL was not distributed with this
  * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
+#if defined(__NetBSD__)
+_Pragma("GCC visibility push(default)")
+#endif
 #include "GeckoChildProcessHost.h"
+#if defined(__NetBSD__)
+_Pragma("GCC visibility pop")
+#endif
 
 #include "base/command_line.h"
 #include "base/string_util.h"
@@ -633,7 +639,7 @@ GeckoChildProcessHost::PerformAsyncLaunc
   // and passing wstrings from one config to the other is unsafe.  So
   // we split the logic here.
 
-#if defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD) || defined(OS_SOLARIS)
   base::environment_map newEnvVars;
   ChildPrivileges privs = mPrivileges;
   if (privs == base::PRIVILEGES_DEFAULT) {
@@ -759,7 +765,7 @@ GeckoChildProcessHost::PerformAsyncLaunc
   childArgv.push_back(pidstring);
 
 #if defined(MOZ_CRASHREPORTER)
-#  if defined(OS_LINUX) || defined(OS_BSD)
+#  if defined(OS_LINUX) || defined(OS_BSD) || defined(OS_SOLARIS)
   int childCrashFd, childCrashRemapFd;
   if (!CrashReporter::CreateNotificationPipeForChild(
         &childCrashFd, &childCrashRemapFd))
@@ -792,7 +798,7 @@ GeckoChildProcessHost::PerformAsyncLaunc
   childArgv.push_back(childProcessType);
 
   base::LaunchApp(childArgv, mFileMap,
-#if defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD)
+#if defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD) || defined(OS_SOLARIS)
                   newEnvVars, privs,
 #endif
                   false, &process, arch);

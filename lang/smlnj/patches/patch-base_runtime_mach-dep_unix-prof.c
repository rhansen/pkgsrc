$NetBSD: patch-base_runtime_mach-dep_unix-prof.c,v 1.1 2016/04/14 21:58:22 dholland Exp $

Use own abstractions correctly.

--- base/runtime/mach-dep/unix-prof.c~	2005-01-18 17:58:39.000000000 +0000
+++ base/runtime/mach-dep/unix-prof.c
@@ -34,7 +34,7 @@ void EnableProfSignals ()
  */
 void DisableProfSignals ()
 {
-    SIG_SetHandler (SIGVTALRM, SIG_DFL);
+    SIG_SetDefault (SIGVTALRM);
 
 } /* end of DisableProfSignals */
 

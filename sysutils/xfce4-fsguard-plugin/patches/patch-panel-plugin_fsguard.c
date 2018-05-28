$NetBSD: patch-panel-plugin_fsguard.c,v 1.3 2018/05/28 23:41:53 youri Exp $

Fix NetBSD support.
Add SunOS, OS X and DragonFlyBSD support.

--- panel-plugin/fsguard.c.orig	2016-10-29 06:43:10.000000000 +0000
+++ panel-plugin/fsguard.c
@@ -38,13 +38,18 @@
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
+#include <sys/statvfs.h>
 #if defined(__linux__) || defined(__GNU__)
 #include <sys/vfs.h>
-#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD_kernel__)
+#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD_kernel__) || defined(__APPLE__) || defined(__DragonFly__)
 #include <sys/param.h>
 #include <sys/mount.h>
 #endif
 
+#if defined(__NetBSD__) || defined(__sun)
+#define statfs statvfs
+#endif
+
 #include <gtk/gtk.h>
 #include <libxfce4util/libxfce4util.h>
 #include <libxfce4ui/libxfce4ui.h>
@@ -277,7 +282,11 @@ fsguard_check_fs (FsGuard *fsguard)
     err = statfs (fsguard->path, &fsd);
 
     if (err != -1) {
+#ifdef __NetBSD__
+        blocksize       = fsd.f_frsize;
+#else
         blocksize       = fsd.f_bsize;
+#endif
         freeblocks      = fsd.f_bavail;
         totalblocks     = fsd.f_blocks;
         freespace       = (freeblocks * blocksize) / 1048576;

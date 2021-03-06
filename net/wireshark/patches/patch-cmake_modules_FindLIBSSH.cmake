$NetBSD: patch-cmake_modules_FindLIBSSH.cmake,v 1.1 2020/09/15 10:19:20 wiz Exp $

Fix detection of libssh >= 0.9.5. Upstream commit fd7739de6b.

--- cmake/modules/FindLIBSSH.cmake.orig	Wed Aug 12 17:53:19 2020
+++ cmake/modules/FindLIBSSH.cmake
@@ -59,15 +59,21 @@ else ()
       ${LIBSSH_LIBRARY}
     )
 
-    file(STRINGS ${LIBSSH_INCLUDE_DIR}/libssh/libssh.h LIBSSH_VERSION_MAJOR
+    # libssh >= 0.9.5 has libssh_version.h
+    set(_libssh_version_header "${LIBSSH_INCLUDE_DIR}/libssh/libssh_version.h")
+    if(NOT EXISTS "${_libssh_version_header}")
+        set(_libssh_version_header "${LIBSSH_INCLUDE_DIR}/libssh/libssh.h")
+    endif()
+
+    file(STRINGS "${_libssh_version_header}" LIBSSH_VERSION_MAJOR
       REGEX "#define[ ]+LIBSSH_VERSION_MAJOR[ ]+[0-9]+")
     # Older versions of libssh like libssh-0.2 have LIBSSH_VERSION but not LIBSSH_VERSION_MAJOR
     if(LIBSSH_VERSION_MAJOR)
       string(REGEX MATCH "[0-9]+" LIBSSH_VERSION_MAJOR ${LIBSSH_VERSION_MAJOR})
-      file(STRINGS ${LIBSSH_INCLUDE_DIR}/libssh/libssh.h LIBSSH_VERSION_MINOR
+      file(STRINGS "${_libssh_version_header}" LIBSSH_VERSION_MINOR
         REGEX "#define[ ]+LIBSSH_VERSION_MINOR[ ]+[0-9]+")
       string(REGEX MATCH "[0-9]+" LIBSSH_VERSION_MINOR ${LIBSSH_VERSION_MINOR})
-      file(STRINGS ${LIBSSH_INCLUDE_DIR}/libssh/libssh.h LIBSSH_VERSION_PATCH
+      file(STRINGS "${_libssh_version_header}" LIBSSH_VERSION_PATCH
         REGEX "#define[ ]+LIBSSH_VERSION_MICRO[ ]+[0-9]+")
       string(REGEX MATCH "[0-9]+" LIBSSH_VERSION_PATCH ${LIBSSH_VERSION_PATCH})
       set(LIBSSH_VERSION ${LIBSSH_VERSION_MAJOR}.${LIBSSH_VERSION_MINOR}.${LIBSSH_VERSION_PATCH})

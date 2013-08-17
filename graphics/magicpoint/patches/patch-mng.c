$NetBSD: patch-mng.c,v 1.1 2013/08/17 14:39:24 taca Exp $

* Use modern libmng API.

--- mng.c.orig	2004-09-01 03:50:32.000000000 +0000
+++ mng.c
@@ -48,13 +48,13 @@ void mng_window_setup __P((mngstuff *mym
 /* callbacks for the mng decoder */
 
 /* memory allocation; data must be zeroed */
-mng_ptr mymngalloc(mng_uint32 size)
+mng_ptr mymngalloc(mng_size_t size)
 {
 	return (mng_ptr)calloc(1, size);
 }
 
 /* memory deallocation */
-void mymngfree(mng_ptr p, mng_uint32 size)
+void mymngfree(mng_ptr p, mng_size_t size)
 {
 	free(p);
 	return;

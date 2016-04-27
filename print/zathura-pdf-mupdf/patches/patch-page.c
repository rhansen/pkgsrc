$NetBSD: patch-page.c,v 1.1 2016/04/27 12:38:45 leot Exp $

Update to mupdf-1.9 API.

--- page.c.orig	2016-02-14 22:49:46.000000000 +0000
+++ page.c
@@ -43,12 +43,12 @@ pdf_page_init(zathura_page_t* page)
   /* setup text */
   mupdf_page->extracted_text = false;
 
-  mupdf_page->text = fz_new_text_page(mupdf_page->ctx);
+  mupdf_page->text = fz_new_stext_page(mupdf_page->ctx);
   if (mupdf_page->text == NULL) {
     goto error_free;
   }
 
-  mupdf_page->sheet = fz_new_text_sheet(mupdf_page->ctx);
+  mupdf_page->sheet = fz_new_stext_sheet(mupdf_page->ctx);
   if (mupdf_page->sheet == NULL) {
     goto error_free;
   }
@@ -74,11 +74,11 @@ pdf_page_clear(zathura_page_t* page, mup
 
   if (mupdf_page != NULL) {
     if (mupdf_page->text != NULL) {
-      fz_drop_text_page(mupdf_page->ctx, mupdf_page->text);
+      fz_drop_stext_page(mupdf_page->ctx, mupdf_page->text);
     }
 
     if (mupdf_page->sheet != NULL) {
-      fz_drop_text_sheet(mupdf_page->ctx, mupdf_page->sheet);
+      fz_drop_stext_sheet(mupdf_page->ctx, mupdf_page->sheet);
     }
 
     if (mupdf_page->page != NULL) {

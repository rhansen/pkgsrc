$NetBSD: patch-src_libjasper_jp2_jp2__dec.c,v 1.3 2016/12/16 09:44:44 he Exp $

Only output debug info if debuglevel >= 1.

--- src/libjasper/jp2/jp2_dec.c.orig	2016-11-16 15:03:41.000000000 +0000
+++ src/libjasper/jp2/jp2_dec.c
@@ -302,7 +302,9 @@ jas_image_t *jp2_decode(jas_stream_t *in
 			goto error;
 		}
 		jas_iccprof_gethdr(iccprof, &icchdr);
-		jas_eprintf("ICC Profile CS %08x\n", icchdr.colorspc);
+		if (jas_getdbglevel() >= 1) {
+			jas_eprintf("ICC Profile CS %08x\n", icchdr.colorspc);
+		}
 		jas_image_setclrspc(dec->image, fromiccpcs(icchdr.colorspc));
 		dec->image->cmprof_ = jas_cmprof_createfromiccprof(iccprof);
 		assert(dec->image->cmprof_);

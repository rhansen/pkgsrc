$NetBSD: patch-src_webpimg.c,v 1.1 2015/06/30 10:20:11 ryoon Exp $

Fix build with libvpx-1.4.0.

https://github.com/libgd/libgd/commit/d41eb72cd4545c394578332e5c102dee69e02ee8#diff-6df10f67563acb6f093f2d9fe3549f08

--- src/webpimg.c.orig	2015-01-14 03:09:04.000000000 +0000
+++ src/webpimg.c
@@ -711,14 +711,14 @@ static WebPResult VPXEncode(const uint8*
     codec_ctl(&enc, VP8E_SET_STATIC_THRESHOLD, 0);
     codec_ctl(&enc, VP8E_SET_TOKEN_PARTITIONS, 2);
 
-    vpx_img_wrap(&img, IMG_FMT_I420,
+    vpx_img_wrap(&img, VPX_IMG_FMT_I420,
                  y_width, y_height, 16, (uint8*)(Y));
-    img.planes[PLANE_Y] = (uint8*)(Y);
-    img.planes[PLANE_U] = (uint8*)(U);
-    img.planes[PLANE_V] = (uint8*)(V);
-    img.stride[PLANE_Y] = y_stride;
-    img.stride[PLANE_U] = uv_stride;
-    img.stride[PLANE_V] = uv_stride;
+    img.planes[VPX_PLANE_Y] = (uint8*)(Y);
+    img.planes[VPX_PLANE_U] = (uint8*)(U);
+    img.planes[VPX_PLANE_V] = (uint8*)(V);
+    img.stride[VPX_PLANE_Y] = y_stride;
+    img.stride[VPX_PLANE_U] = uv_stride;
+    img.stride[VPX_PLANE_V] = uv_stride;
 
     res = vpx_codec_encode(&enc, &img, 0, 1, 0, VPX_DL_BEST_QUALITY);
 

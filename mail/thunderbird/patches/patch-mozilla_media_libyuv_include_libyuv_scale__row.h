$NetBSD: patch-mozilla_media_libyuv_include_libyuv_scale__row.h,v 1.1 2015/07/09 15:17:34 ryoon Exp $

--- mozilla/media/libyuv/include/libyuv/scale_row.h.orig	2015-06-08 17:49:23.000000000 +0000
+++ mozilla/media/libyuv/include/libyuv/scale_row.h
@@ -219,10 +219,10 @@ void ScaleARGBFilterCols_SSSE3(uint8* ds
 void ScaleARGBColsUp2_SSE2(uint8* dst_argb, const uint8* src_argb,
                            int dst_width, int x, int dx);
 // Row functions.
-void ScaleARGBRowDownEven_NEON(const uint8* src_argb, int src_stride,
+void ScaleARGBRowDownEven_NEON(const uint8* src_argb, ptrdiff_t src_stride,
                                int src_stepx,
                                uint8* dst_argb, int dst_width);
-void ScaleARGBRowDownEvenBox_NEON(const uint8* src_argb, int src_stride,
+void ScaleARGBRowDownEvenBox_NEON(const uint8* src_argb, ptrdiff_t src_stride,
                                   int src_stepx,
                                   uint8* dst_argb, int dst_width);
 void ScaleARGBRowDown2_NEON(const uint8* src_ptr, ptrdiff_t src_stride,

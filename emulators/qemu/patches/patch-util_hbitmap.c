$NetBSD: patch-util_hbitmap.c,v 1.1 2013/06/16 18:27:25 tsutsui Exp $

Avoid conflicts against popcountl(3) in NetBSD's libc.

--- util/hbitmap.c.orig	2013-05-24 13:37:58.000000000 +0000
+++ util/hbitmap.c
@@ -92,7 +92,7 @@ struct HBitmap {
     unsigned long *levels[HBITMAP_LEVELS];
 };
 
-static inline int popcountl(unsigned long l)
+static inline int qemu_popcountl(unsigned long l)
 {
     return BITS_PER_LONG == 32 ? ctpop32(l) : ctpop64(l);
 }
@@ -199,14 +199,14 @@ static uint64_t hb_count_between(HBitmap
         if (pos >= (end >> BITS_PER_LEVEL)) {
             break;
         }
-        count += popcountl(cur);
+        count += qemu_popcountl(cur);
     }
 
     if (pos == (end >> BITS_PER_LEVEL)) {
         /* Drop bits representing the END-th and subsequent items.  */
         int bit = end & (BITS_PER_LONG - 1);
         cur &= (1UL << bit) - 1;
-        count += popcountl(cur);
+        count += qemu_popcountl(cur);
     }
 
     return count;

$NetBSD: patch-oggenc_audio.c,v 1.1 2015/12/29 15:12:20 bsiegert Exp $

From 04815d3e1bfae3a6cdfb2c25358a5a72b61299f7 Mon Sep 17 00:00:00 2001
From: Mark Harris <mark.hsj@gmail.com>
Date: Sun, 30 Aug 2015 05:54:46 -0700
Subject: [PATCH] oggenc: Fix large alloca on bad AIFF input

Fixes https://trac.xiph.org/ticket/2212
---
 oggenc/audio.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

diff --git a/oggenc/audio.c b/oggenc/audio.c
index 477da8c..4921fb9 100644
--- oggenc/audio.c
+++ oggenc/audio.c
@@ -245,8 +245,8 @@ static int aiff_permute_matrix[6][6] =
 int aiff_open(FILE *in, oe_enc_opt *opt, unsigned char *buf, int buflen)
 {
     int aifc; /* AIFC or AIFF? */
-    unsigned int len;
-    unsigned char *buffer;
+    unsigned int len, readlen;
+    unsigned char buffer[22];
     unsigned char buf2[8];
     aiff_fmt format;
     aifffile *aiff = malloc(sizeof(aifffile));
@@ -269,9 +269,9 @@ int aiff_open(FILE *in, oe_enc_opt *opt, unsigned char *buf, int buflen)
         return 0; /* Weird common chunk */
     }
 
-    buffer = alloca(len);
-
-    if(fread(buffer,1,len,in) < len)
+    readlen = len < sizeof(buffer) ? len : sizeof(buffer);
+    if(fread(buffer,1,readlen,in) < readlen ||
+       (len > readlen && !seek_forward(in, len-readlen)))
     {
         fprintf(stderr, _("Warning: Unexpected EOF in reading AIFF header\n"));
         return 0;

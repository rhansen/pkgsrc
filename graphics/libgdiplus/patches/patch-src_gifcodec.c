$NetBSD: patch-src_gifcodec.c,v 1.4 2015/05/23 06:36:18 kefren Exp $

Fixes for giflib 5.x

--- src/gifcodec.c.orig	2015-01-05 12:27:06.000000000 +0200
+++ src/gifcodec.c	2015-05-21 19:23:31.000000000 +0300
@@ -131,7 +131,7 @@ AddExtensionBlockMono(SavedImage *New, i
 
 	if (ExtData) {
 		memcpy(ep->Bytes, ExtData, Len);
-		ep->Function = New->Function;
+		ep->Function = New->ExtensionBlocks[New->ExtensionBlockCount++].Function;
 	}
 
 	return (GIF_OK);
@@ -234,7 +234,7 @@ DGifSlurpMono(GifFileType * GifFile, Sav
 			}
 
 			case EXTENSION_RECORD_TYPE: {
-				if (DGifGetExtension(GifFile, &temp_save.Function, &ExtData) == GIF_ERROR) {
+				if (DGifGetExtension(GifFile, &temp_save.ExtensionBlocks[temp_save.ExtensionBlockCount].Function, &ExtData) == GIF_ERROR) {
 					return (GIF_ERROR);
 				}
 
@@ -247,7 +247,9 @@ DGifSlurpMono(GifFileType * GifFile, Sav
 					if (DGifGetExtensionNext(GifFile, &ExtData) == GIF_ERROR) {
 						return (GIF_ERROR);
 					}
+#if GIFLIB_MAJOR < 5
 					temp_save.Function = 0;
+#endif
 				}
 				break;
 			}
@@ -306,9 +308,9 @@ gdip_load_gif_image (void *stream, GpIma
 	loop_counter = FALSE;
 
 	if (from_file) {
-		gif = DGifOpen(stream, &gdip_gif_fileinputfunc);
+		gif = DGifOpen(stream, &gdip_gif_fileinputfunc, NULL);
 	} else {
-		gif = DGifOpen (stream, &gdip_gif_inputfunc);
+		gif = DGifOpen(stream, &gdip_gif_inputfunc, NULL);
 	}
 	
 	if (gif == NULL) {
@@ -583,7 +585,7 @@ gdip_load_gif_image (void *stream, GpIma
 	}
 
 	FreeExtensionMono(&global_extensions);
-	DGifCloseFile (gif);
+	DGifCloseFile(gif, NULL);
 
 	*image = result;
 	return Ok;
@@ -599,7 +601,7 @@ error:	
 
 	if (gif != NULL) {
 		FreeExtensionMono (&global_extensions);
-		DGifCloseFile (gif);
+		DGifCloseFile(gif, NULL);
 	}
 
 	*image = NULL;
@@ -663,9 +665,9 @@ gdip_save_gif_image (void *stream, GpIma
 	}
 
 	if (from_file) {
-		fp = EGifOpenFileName (stream, 0);
+		fp = EGifOpenFileName(stream, 0, NULL);
 	} else {
-		fp = EGifOpen (stream, gdip_gif_outputfunc);
+		fp = EGifOpen(stream, gdip_gif_outputfunc, NULL);
 	}
 		
 	if (!fp) {
@@ -704,7 +706,7 @@ gdip_save_gif_image (void *stream, GpIma
 					goto error; 
 				}
 
-				cmap = MakeMapObject(cmap_size, 0);
+				cmap = GifMakeMapObject(cmap_size, 0);
 
 				pixbuf = GdipAlloc(pixbuf_size);
 				if (pixbuf == NULL) {
@@ -795,7 +797,7 @@ gdip_save_gif_image (void *stream, GpIma
 				pixbuf = pixbuf_org;
 			} else {
 				cmap_size = 256;
-				cmap  = MakeMapObject (cmap_size, 0);
+				cmap  = GifMakeMapObject(cmap_size, 0);
 
 				red = GdipAlloc(pixbuf_size);
 				green = GdipAlloc(pixbuf_size);
@@ -826,13 +828,13 @@ gdip_save_gif_image (void *stream, GpIma
 						v += 4;
 					}
 				}
-				if (QuantizeBuffer(bitmap_data->width, bitmap_data->height, &cmap_size, 
+				if (GifQuantizeBuffer(bitmap_data->width, bitmap_data->height, &cmap_size, 
 						red,  green, blue, pixbuf, cmap->Colors) == GIF_ERROR) {
 					goto error;
 				}
 			}
 
-			cmap->BitsPerPixel = BitSize (cmap_size);
+			cmap->BitsPerPixel = GifBitSize(cmap_size);
 			cmap->ColorCount = 1 << cmap->BitsPerPixel;
 
 			if ((frame == 0) && (k == 0)) {
@@ -850,8 +852,10 @@ gdip_save_gif_image (void *stream, GpIma
 						Buffer[0] = 1;
 						Buffer[1] = ptr[0];
 						Buffer[2] = ptr[1];
-						EGifPutExtensionFirst(fp, APPLICATION_EXT_FUNC_CODE, 11, "NETSCAPE2.0");
-						EGifPutExtensionLast(fp, APPLICATION_EXT_FUNC_CODE, 3, Buffer);
+						EGifPutExtensionLeader(fp, APPLICATION_EXT_FUNC_CODE);
+						EGifPutExtensionBlock(fp, 11, "NETSCAPE2.0");
+						EGifPutExtensionBlock(fp, 3, Buffer);
+						EGifPutExtensionTrailer(fp);
 					}
 				}
 
@@ -903,7 +907,7 @@ gdip_save_gif_image (void *stream, GpIma
 				pixbuf += bitmap_data->width;
 			}
 
-			FreeMapObject (cmap);
+			GifFreeMapObject(cmap);
 			if (red != NULL) {
 				GdipFree (red);
 			}
@@ -925,13 +929,13 @@ gdip_save_gif_image (void *stream, GpIma
 		}
 	}
 
-	EGifCloseFile (fp);	
+	EGifCloseFile(fp, NULL);	
 	
 	return Ok;
 
 error:
 	if (cmap != NULL) {
-		FreeMapObject (cmap);
+		GifFreeMapObject(cmap);
 	}
 
 	if (red != NULL) {

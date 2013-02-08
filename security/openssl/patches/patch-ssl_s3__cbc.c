$NetBSD: patch-ssl_s3__cbc.c,v 1.1 2013/02/08 14:11:08 jperkin Exp $

Apply data-corruption patch from:

  http://git.openssl.org/gitweb/?p=openssl.git;a=commitdiff;h=32cc247

Fix IV check and padding removal.

Fix the calculation that checks there is enough room in a record
after removing padding and optional explicit IV. (by Steve)

For AEAD remove the correct number of padding bytes (by Andy)

--- ssl/s3_cbc.c
+++ ssl/s3_cbc.c
@@ -139,31 +139,22 @@ int tls1_cbc_remove_padding(const SSL* s,
 			    unsigned mac_size)
 	{
 	unsigned padding_length, good, to_check, i;
-	const char has_explicit_iv =
-		s->version >= TLS1_1_VERSION || s->version == DTLS1_VERSION;
-	const unsigned overhead = 1 /* padding length byte */ +
-				  mac_size +
-				  (has_explicit_iv ? block_size : 0);
-
-	/* These lengths are all public so we can test them in non-constant
-	 * time. */
-	if (overhead > rec->length)
-		return 0;
-
-	/* We can always safely skip the explicit IV. We check at the beginning
-	 * of this function that the record has at least enough space for the
-	 * IV, MAC and padding length byte. (These can be checked in
-	 * non-constant time because it's all public information.) So, if the
-	 * padding was invalid, then we didn't change |rec->length| and this is
-	 * safe. If the padding was valid then we know that we have at least
-	 * overhead+padding_length bytes of space and so this is still safe
-	 * because overhead accounts for the explicit IV. */
-	if (has_explicit_iv)
+	const unsigned overhead = 1 /* padding length byte */ + mac_size;
+	/* Check if version requires explicit IV */
+	if (s->version >= TLS1_1_VERSION || s->version == DTLS1_VERSION)
 		{
+		/* These lengths are all public so we can test them in
+		 * non-constant time.
+		 */
+		if (overhead + block_size > rec->length)
+			return 0;
+		/* We can now safely skip explicit IV */
 		rec->data += block_size;
 		rec->input += block_size;
 		rec->length -= block_size;
 		}
+	else if (overhead > rec->length)
+		return 0;
 
 	padding_length = rec->data[rec->length-1];
 
@@ -190,7 +181,7 @@ int tls1_cbc_remove_padding(const SSL* s,
 	if (EVP_CIPHER_flags(s->enc_read_ctx->cipher)&EVP_CIPH_FLAG_AEAD_CIPHER)
 		{
 		/* padding is already verified */
-		rec->length -= padding_length;
+		rec->length -= padding_length + 1;
 		return 1;
 		}
 

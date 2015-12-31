$NetBSD: patch-src__readpassphrase_compat.h,v 1.1.1.1 2015/12/31 18:29:50 agc Exp $

missing header file - taken from openssh, v1.3

--- /dev/null	2015-12-28 15:45:54.000000000 -0800
+++ src/readpassphrase_compat.h	2015-12-28 15:51:15.000000000 -0800
@@ -0,0 +1,48 @@
+/*	$ NetBSD: readpassphrase.h,v 1.3 2015/04/03 23:58:19 christos Exp $	*/
+/*	$OpenBSD: readpassphrase.h,v 1.1 2000/11/21 00:48:38 millert Exp $	*/
+
+/*
+ * Copyright (c) 2000 Todd C. Miller <Todd.Miller@courtesan.com>
+ * All rights reserved.
+ *
+ * Redistribution and use in source and binary forms, with or without
+ * modification, are permitted provided that the following conditions
+ * are met:
+ * 1. Redistributions of source code must retain the above copyright
+ *    notice, this list of conditions and the following disclaimer.
+ * 2. Redistributions in binary form must reproduce the above copyright
+ *    notice, this list of conditions and the following disclaimer in the
+ *    documentation and/or other materials provided with the distribution.
+ * 3. The name of the author may not be used to endorse or promote products
+ *    derived from this software without specific prior written permission.
+ *
+ * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
+ * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
+ * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
+ * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
+ * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
+ * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
+ * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
+ * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
+ * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
+ * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
+ */
+
+#ifndef _READPASSPHRASE_H_
+#define _READPASSPHRASE_H_
+
+#define RPP_ECHO_OFF    0x00		/* Turn off echo (default). */
+#define RPP_ECHO_ON     0x01		/* Leave echo on. */
+#define RPP_REQUIRE_TTY 0x02		/* Fail if there is no tty. */
+#define RPP_FORCELOWER  0x04		/* Force input to lower case. */
+#define RPP_FORCEUPPER  0x08		/* Force input to upper case. */
+#define RPP_SEVENBIT    0x10		/* Strip the high bit from input. */
+
+#include <sys/cdefs.h>
+
+__BEGIN_DECLS
+char * readpassphrase __P((const char *, char *, size_t, int));
+char * getpass __P((const char *));
+__END_DECLS
+
+#endif /* !_READPASSPHRASE_H_ */

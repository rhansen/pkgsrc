$NetBSD: patch-examples_reverse__client.cc,v 1.1 2013/10/04 07:03:37 fhajny Exp $

Need unistd.h for STDOUT_FILENO.

--- examples/reverse_client.cc.orig	2013-02-14 11:34:29.000000000 +0000
+++ examples/reverse_client.cc
@@ -42,6 +42,7 @@
 #include <cstring>
 #include <iostream>
 #include <string>
+#include <unistd.h>
 
 #include <libgearman/gearman.h>
 #include <boost/program_options.hpp>

$NetBSD: patch-src_core_CLucene_queryParser_QueryParser.cpp,v 1.1 2018/01/26 15:27:04 jperkin Exp $

Fix -Wc++11-narrowing.

--- src/core/CLucene/queryParser/QueryParser.cpp.orig	2011-03-17 00:21:07.000000000 +0000
+++ src/core/CLucene/queryParser/QueryParser.cpp
@@ -79,8 +79,8 @@ const TCHAR* QueryParserConstants::token
     _T("<RANGEEX_GOOP>")
 };
 
-const int32_t QueryParser::jj_la1_0[] = {0x180,0x180,0xe00,0xe00,0x1f69f80,0x48000,0x10000,0x1f69000,0x1348000,0x80000,0x80000,0x10000,0x18000000,0x2000000,0x18000000,0x10000,0x80000000,0x20000000,0x80000000,0x10000,0x80000,0x10000,0x1f68000};
-const int32_t QueryParser::jj_la1_1[] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x0};
+const uint32_t QueryParser::jj_la1_0[] = {0x180,0x180,0xe00,0xe00,0x1f69f80,0x48000,0x10000,0x1f69000,0x1348000,0x80000,0x80000,0x10000,0x18000000,0x2000000,0x18000000,0x10000,0x80000000,0x20000000,0x80000000,0x10000,0x80000,0x10000,0x1f68000};
+const uint32_t QueryParser::jj_la1_1[] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x0};
 
 struct QueryParser::JJCalls {
 public:

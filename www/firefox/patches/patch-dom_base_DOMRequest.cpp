$NetBSD: patch-dom_base_DOMRequest.cpp,v 1.1 2015/10/07 23:21:22 joerg Exp $

--- dom/base/DOMRequest.cpp.orig	2015-09-17 22:13:30.000000000 +0000
+++ dom/base/DOMRequest.cpp
@@ -19,7 +19,6 @@ using mozilla::dom::DOMError;
 using mozilla::dom::DOMRequest;
 using mozilla::dom::DOMRequestService;
 using mozilla::dom::DOMCursor;
-using mozilla::dom::Promise;
 using mozilla::dom::AutoJSAPI;
 
 DOMRequest::DOMRequest(nsPIDOMWindow* aWindow)

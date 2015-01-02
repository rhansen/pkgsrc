$NetBSD: patch-config_baseconfig.mk,v 1.5 2015/01/02 04:26:21 ryoon Exp $

--- config/baseconfig.mk.orig	2014-12-03 06:11:58.000000000 +0000
+++ config/baseconfig.mk
@@ -2,10 +2,10 @@
 # directly in python/mozbuild/mozbuild/base.py for gmake validation.
 # We thus use INCLUDED_AUTOCONF_MK to enable/disable some parts depending
 # whether a normal build is happening or whether the check is running.
-includedir := $(includedir)/$(MOZ_APP_NAME)-$(MOZ_APP_VERSION)
-idldir = $(datadir)/idl/$(MOZ_APP_NAME)-$(MOZ_APP_VERSION)
-installdir = $(libdir)/$(MOZ_APP_NAME)-$(MOZ_APP_VERSION)
-sdkdir = $(libdir)/$(MOZ_APP_NAME)-devel-$(MOZ_APP_VERSION)
+includedir := $(includedir)/$(MOZILLA_PKG_NAME)
+idldir = $(datadir)/idl/$(MOZILLA_PKG_NAME)
+installdir = $(libdir)/$(MOZILLA_PKG_NAME)
+sdkdir = $(libdir)/$(MOZILLA_PKG_NAME)-sdk
 MOZILLA_SRCDIR = $(topsrcdir)/mozilla
 MOZDEPTH = $(DEPTH)
 DIST = $(MOZDEPTH)/dist

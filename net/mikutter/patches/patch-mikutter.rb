$NetBSD: patch-mikutter.rb,v 1.2 2017/01/08 14:20:05 tsutsui Exp $

- pkgsrc can handle location of ruby binary
 http://dev.mikutter.hachune.net/issues/889

--- mikutter.rb.orig	2016-12-11 07:54:54.000000000 +0000
+++ mikutter.rb
@@ -1,7 +1,5 @@
-#!/bin/sh
+#! /usr/bin/ruby
 # -*- coding: utf-8 -*-
-exec ruby -x "$0" "$@" 
-#!ruby
 =begin rdoc
 = mikutter - the moest twitter client
 Copyright (C) 2009-2017 Toshiaki Asai

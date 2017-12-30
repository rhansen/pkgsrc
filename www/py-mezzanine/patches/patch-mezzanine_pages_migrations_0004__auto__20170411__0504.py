$NetBSD: patch-mezzanine_pages_migrations_0004__auto__20170411__0504.py,v 1.1 2017/12/30 13:44:21 adam Exp $

Django 1.11 support.
https://github.com/stephenmcd/mezzanine/pull/1750

--- mezzanine/pages/migrations/0004_auto_20170411_0504.py.orig	2017-12-25 08:43:14.000000000 +0000
+++ mezzanine/pages/migrations/0004_auto_20170411_0504.py
@@ -0,0 +1,21 @@
+# -*- coding: utf-8 -*-
+# Generated by Django 1.11 on 2017-04-11 05:04
+from __future__ import unicode_literals
+
+from django.db import migrations, models
+
+
+class Migration(migrations.Migration):
+
+    dependencies = [
+        ('pages', '0003_auto_20150527_1555'),
+    ]
+
+    operations = [
+        migrations.AlterField(
+            model_name='page',
+            name='slug',
+            field=models.CharField(blank=True, default='', help_text='Leave blank to have the URL auto-generated from the title.', max_length=2000, verbose_name='URL'),
+            preserve_default=False,
+        ),
+    ]

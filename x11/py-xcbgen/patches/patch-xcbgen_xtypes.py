$NetBSD: patch-xcbgen_xtypes.py,v 1.1 2016/05/19 07:08:14 wiz Exp $

Python-3.x fixes.

--- xcbgen/xtypes.py.orig	2016-05-01 07:44:48.000000000 +0000
+++ xcbgen/xtypes.py
@@ -501,7 +501,7 @@ class ComplexType(Type):
                 int(required_start_align_element.get('align', "4"), 0),
                 int(required_start_align_element.get('offset', "0"), 0))
             if verbose_align_log:
-                print "Explicit start-align for %s: %s\n" % (self, self.required_start_align)
+                print ("Explicit start-align for %s: %s\n" % (self, self.required_start_align))
 
     def resolve(self, module):
         if self.resolved:
@@ -592,7 +592,7 @@ class ComplexType(Type):
                 if verbose_align_log:
                     print ("calc_required_start_align: %s has start-align %s"
                         % (str(self), str(self.required_start_align)))
-                    print "Details:\n" + str(log)
+                    print ("Details:\n" + str(log))
                 if self.required_start_align.offset != 0:
                     print (("WARNING: %s\n\thas start-align with non-zero offset: %s"
                         + "\n\tsuggest to add explicit definition with:"
@@ -619,12 +619,12 @@ class ComplexType(Type):
             for offset in range(0,align):
                 align_candidate = Alignment(align, offset)
                 if verbose_align_log:
-                    print "trying %s for %s" % (str(align_candidate), str(self))
+                    print ("trying %s for %s" % (str(align_candidate), str(self)))
                 my_log = AlignmentLog()
                 if self.is_possible_start_align(align_candidate, callstack, my_log):
                     log.append(my_log)
                     if verbose_align_log:
-                        print "found start-align %s for %s" % (str(align_candidate), str(self))
+                        print ("found start-align %s for %s" % (str(align_candidate), str(self)))
                     return align_candidate
                 else:
                     my_ok_count = my_log.ok_count()
@@ -641,7 +641,7 @@ class ComplexType(Type):
         # none of the candidates applies
         # this type has illegal internal aligns for all possible start_aligns
         if verbose_align_log:
-            print "didn't find start-align for %s" % str(self)
+            print ("didn't find start-align for %s" % str(self))
         log.append(best_log)
         return None
 
@@ -900,7 +900,7 @@ class SwitchType(ComplexType):
     # aux function for unchecked_get_alignment_after
     def get_align_for_selected_case_field(self, case_field, start_align, callstack, log):
         if verbose_align_log:
-            print "get_align_for_selected_case_field: %s, case_field = %s" % (str(self), str(case_field))
+            print ("get_align_for_selected_case_field: %s, case_field = %s" % (str(self), str(case_field)))
         total_align = start_align
         for field in self.bitcases:
             my_callstack = callstack[:]

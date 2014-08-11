$NetBSD: patch-libvncserver_lzoconf.h,v 1.1 2014/08/11 21:22:15 markd Exp $

Update LZO to version 2.07 in libvncserver. 

Temporary fix for CVE-2014-4607 for 4.14.

--- libvncserver/lzoconf.h
+++ libvncserver/lzoconf.h
@@ -1,22 +1,8 @@
-/* lzoconf.h -- configuration for the LZO real-time data compression library
+/* lzoconf.h -- configuration of the LZO data compression library
 
    This file is part of the LZO real-time data compression library.
 
-   Copyright (C) 2010 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2009 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2008 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2007 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2006 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2005 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2004 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2003 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2002 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2001 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 2000 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 1999 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 1998 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 1997 Markus Franz Xaver Johannes Oberhumer
-   Copyright (C) 1996 Markus Franz Xaver Johannes Oberhumer
+   Copyright (C) 1996-2014 Markus Franz Xaver Johannes Oberhumer
    All Rights Reserved.
 
    The LZO library is free software; you can redistribute it and/or
@@ -43,9 +29,9 @@
 #ifndef __LZOCONF_H_INCLUDED
 #define __LZOCONF_H_INCLUDED 1
 
-#define LZO_VERSION             0x2040
-#define LZO_VERSION_STRING      "2.04"
-#define LZO_VERSION_DATE        "Oct 31 2010"
+#define LZO_VERSION             0x2070
+#define LZO_VERSION_STRING      "2.07"
+#define LZO_VERSION_DATE        "Jun 25 2014"
 
 /* internal Autoconf configuration file - only used when building LZO */
 #if defined(LZO_HAVE_CONFIG_H)
@@ -62,7 +48,7 @@
 #if !defined(CHAR_BIT) || (CHAR_BIT != 8)
 #  error "invalid CHAR_BIT"
 #endif
-#if !defined(UCHAR_MAX) || !defined(UINT_MAX) || !defined(ULONG_MAX)
+#if !defined(UCHAR_MAX) || !defined(USHRT_MAX) || !defined(UINT_MAX) || !defined(ULONG_MAX)
 #  error "check your compiler installation"
 #endif
 #if (USHRT_MAX < 1) || (UINT_MAX < 1) || (ULONG_MAX < 1)
@@ -83,14 +69,6 @@
 /***********************************************************************
 // some core defines
 ************************************************************************/
-
-#if !defined(LZO_UINT32_C)
-#  if (UINT_MAX < LZO_0xffffffffL)
-#    define LZO_UINT32_C(c)     c ## UL
-#  else
-#    define LZO_UINT32_C(c)     ((c) + 0U)
-#  endif
-#endif
 
 /* memory checkers */
 #if !defined(__LZO_CHECKER)
@@ -110,28 +88,31 @@
 // integral and pointer types
 ************************************************************************/
 
-/* lzo_uint should match size_t */
+/* lzo_uint must match size_t */
 #if !defined(LZO_UINT_MAX)
-#  if defined(LZO_ABI_LLP64) /* WIN64 */
-#    if defined(LZO_OS_WIN64)
+#  if (LZO_ABI_LLP64)
+#    if (LZO_OS_WIN64)
      typedef unsigned __int64   lzo_uint;
      typedef __int64            lzo_int;
 #    else
-     typedef unsigned long long lzo_uint;
-     typedef long long          lzo_int;
+     typedef lzo_ullong_t       lzo_uint;
+     typedef lzo_llong_t        lzo_int;
 #    endif
+#    define LZO_SIZEOF_LZO_UINT 8
 #    define LZO_UINT_MAX        0xffffffffffffffffull
 #    define LZO_INT_MAX         9223372036854775807LL
 #    define LZO_INT_MIN         (-1LL - LZO_INT_MAX)
-#  elif defined(LZO_ABI_IP32L64) /* MIPS R5900 */
+#  elif (LZO_ABI_IP32L64) /* MIPS R5900 */
      typedef unsigned int       lzo_uint;
      typedef int                lzo_int;
+#    define LZO_SIZEOF_LZO_UINT LZO_SIZEOF_INT
 #    define LZO_UINT_MAX        UINT_MAX
 #    define LZO_INT_MAX         INT_MAX
 #    define LZO_INT_MIN         INT_MIN
 #  elif (ULONG_MAX >= LZO_0xffffffffL)
      typedef unsigned long      lzo_uint;
      typedef long               lzo_int;
+#    define LZO_SIZEOF_LZO_UINT LZO_SIZEOF_LONG
 #    define LZO_UINT_MAX        ULONG_MAX
 #    define LZO_INT_MAX         LONG_MAX
 #    define LZO_INT_MIN         LONG_MIN
@@ -140,42 +121,22 @@
 #  endif
 #endif
 
-/* Integral types with 32 bits or more. */
-#if !defined(LZO_UINT32_MAX)
-#  if (UINT_MAX >= LZO_0xffffffffL)
-     typedef unsigned int       lzo_uint32;
-     typedef int                lzo_int32;
-#    define LZO_UINT32_MAX      UINT_MAX
-#    define LZO_INT32_MAX       INT_MAX
-#    define LZO_INT32_MIN       INT_MIN
-#  elif (ULONG_MAX >= LZO_0xffffffffL)
-     typedef unsigned long      lzo_uint32;
-     typedef long               lzo_int32;
-#    define LZO_UINT32_MAX      ULONG_MAX
-#    define LZO_INT32_MAX       LONG_MAX
-#    define LZO_INT32_MIN       LONG_MIN
-#  else
-#    error "lzo_uint32"
-#  endif
-#endif
-
-/* The larger type of lzo_uint and lzo_uint32. */
-#if (LZO_UINT_MAX >= LZO_UINT32_MAX)
+/* The larger type of lzo_uint and lzo_uint32_t. */
+#if (LZO_SIZEOF_LZO_UINT >= 4)
 #  define lzo_xint              lzo_uint
 #else
-#  define lzo_xint              lzo_uint32
-#endif
-
-/* Memory model that allows to access memory at offsets of lzo_uint. */
-#if !defined(__LZO_MMODEL)
-#  if (LZO_UINT_MAX <= UINT_MAX)
-#    define __LZO_MMODEL        /*empty*/
-#  elif defined(LZO_HAVE_MM_HUGE_PTR)
-#    define __LZO_MMODEL_HUGE   1
-#    define __LZO_MMODEL        __huge
-#  else
-#    define __LZO_MMODEL        /*empty*/
-#  endif
+#  define lzo_xint              lzo_uint32_t
+#endif
+
+typedef int lzo_bool;
+
+/* sanity checks */
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint) == LZO_SIZEOF_LZO_UINT)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_xint) >= sizeof(lzo_uint))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_xint) >= sizeof(lzo_uint32_t))
+
+#ifndef __LZO_MMODEL
+#define __LZO_MMODEL            /*empty*/
 #endif
 
 /* no typedef here because of const-pointer issues */
@@ -184,17 +145,52 @@
 #define lzo_voidp               void __LZO_MMODEL *
 #define lzo_shortp              short __LZO_MMODEL *
 #define lzo_ushortp             unsigned short __LZO_MMODEL *
-#define lzo_uint32p             lzo_uint32 __LZO_MMODEL *
-#define lzo_int32p              lzo_int32 __LZO_MMODEL *
+#define lzo_intp                lzo_int __LZO_MMODEL *
 #define lzo_uintp               lzo_uint __LZO_MMODEL *
-#define lzo_intp                lzo_int __LZO_MMODEL *
 #define lzo_xintp               lzo_xint __LZO_MMODEL *
 #define lzo_voidpp              lzo_voidp __LZO_MMODEL *
 #define lzo_bytepp              lzo_bytep __LZO_MMODEL *
-/* deprecated - use 'lzo_bytep' instead of 'lzo_byte *' */
-#define lzo_byte                unsigned char __LZO_MMODEL
-
-typedef int lzo_bool;
+
+#define lzo_int8_tp             lzo_int8_t __LZO_MMODEL *
+#define lzo_uint8_tp            lzo_uint8_t __LZO_MMODEL *
+#define lzo_int16_tp            lzo_int16_t __LZO_MMODEL *
+#define lzo_uint16_tp           lzo_uint16_t __LZO_MMODEL *
+#define lzo_int32_tp            lzo_int32_t __LZO_MMODEL *
+#define lzo_uint32_tp           lzo_uint32_t __LZO_MMODEL *
+#if defined(lzo_int64_t)
+#define lzo_int64_tp            lzo_int64_t __LZO_MMODEL *
+#define lzo_uint64_tp           lzo_uint64_t __LZO_MMODEL *
+#endif
+
+/* Older LZO versions used to support ancient systems and memory models
+ * like 16-bit MSDOS with __huge pointers and Cray PVP, but these
+ * obsolete configurations are not supported any longer.
+ */
+#if defined(__LZO_MMODEL_HUGE)
+#error "__LZO_MMODEL_HUGE is unsupported"
+#endif
+#if (LZO_MM_PVP)
+#error "LZO_MM_PVP is unsupported"
+#endif
+#if (LZO_SIZEOF_INT < 4)
+#error "LZO_SIZEOF_INT < 4 is unsupported"
+#endif
+#if (__LZO_UINTPTR_T_IS_POINTER)
+#error "__LZO_UINTPTR_T_IS_POINTER is unsupported"
+#endif
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(int) >= 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint) >= 4)
+/* Strange configurations where sizeof(lzo_uint) != sizeof(size_t) should
+ * work but have not received much testing lately, so be strict here.
+ */
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint) == sizeof(size_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint) == sizeof(ptrdiff_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint) == sizeof(lzo_uintptr_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(void *)   == sizeof(lzo_uintptr_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(char *)   == sizeof(lzo_uintptr_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(long *)   == sizeof(lzo_uintptr_t))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(void *)   == sizeof(lzo_voidp))
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(char *)   == sizeof(lzo_bytep))
 
 
 /***********************************************************************
@@ -289,7 +285,7 @@
     /* a progress indicator callback function (set to 0 to disable) */
     lzo_progress_func_t nprogress;
 
-    /* NOTE: the first parameter "self" of the nalloc/nfree/nprogress
+    /* INFO: the first parameter "self" of the nalloc/nfree/nprogress
      * callbacks points back to this struct, so you are free to store
      * some extra info in the following variables. */
     lzo_voidp user1;
@@ -308,7 +304,7 @@
  */
 #define LZO_E_OK                    0
 #define LZO_E_ERROR                 (-1)
-#define LZO_E_OUT_OF_MEMORY         (-2)    /* [not used right now] */
+#define LZO_E_OUT_OF_MEMORY         (-2)    /* [lzo_alloc_func_t failure] */
 #define LZO_E_NOT_COMPRESSIBLE      (-3)    /* [not used right now] */
 #define LZO_E_INPUT_OVERRUN         (-4)
 #define LZO_E_OUTPUT_OVERRUN        (-5)
@@ -316,6 +312,10 @@
 #define LZO_E_EOF_NOT_FOUND         (-7)
 #define LZO_E_INPUT_NOT_CONSUMED    (-8)
 #define LZO_E_NOT_YET_IMPLEMENTED   (-9)    /* [not used right now] */
+#define LZO_E_INVALID_ARGUMENT      (-10)
+#define LZO_E_INVALID_ALIGNMENT     (-11)   /* pointer argument is not properly aligned */
+#define LZO_E_OUTPUT_NOT_CONSUMED   (-12)
+#define LZO_E_INTERNAL_ERROR        (-99)
 
 
 #ifndef lzo_sizeof_dict_t
@@ -329,7 +329,7 @@
  * compiler's view of various types are consistent.
  */
 #define lzo_init() __lzo_init_v2(LZO_VERSION,(int)sizeof(short),(int)sizeof(int),\
-    (int)sizeof(long),(int)sizeof(lzo_uint32),(int)sizeof(lzo_uint),\
+    (int)sizeof(long),(int)sizeof(lzo_uint32_t),(int)sizeof(lzo_uint),\
     (int)lzo_sizeof_dict_t,(int)sizeof(char *),(int)sizeof(lzo_voidp),\
     (int)sizeof(lzo_callback_t))
 LZO_EXTERN(int) __lzo_init_v2(unsigned,int,int,int,int,int,int,int,int,int);
@@ -352,18 +352,22 @@
     lzo_memset(lzo_voidp buf, int c, lzo_uint len);
 
 /* checksum functions */
-LZO_EXTERN(lzo_uint32)
-    lzo_adler32(lzo_uint32 c, const lzo_bytep buf, lzo_uint len);
-LZO_EXTERN(lzo_uint32)
-    lzo_crc32(lzo_uint32 c, const lzo_bytep buf, lzo_uint len);
-LZO_EXTERN(const lzo_uint32p)
+LZO_EXTERN(lzo_uint32_t)
+    lzo_adler32(lzo_uint32_t c, const lzo_bytep buf, lzo_uint len);
+LZO_EXTERN(lzo_uint32_t)
+    lzo_crc32(lzo_uint32_t c, const lzo_bytep buf, lzo_uint len);
+LZO_EXTERN(const lzo_uint32_tp)
     lzo_get_crc32_table(void);
 
 /* misc. */
 LZO_EXTERN(int) _lzo_config_check(void);
-typedef union { lzo_bytep p; lzo_uint u; } __lzo_pu_u;
-typedef union { lzo_bytep p; lzo_uint32 u32; } __lzo_pu32_u;
-typedef union { void *vp; lzo_bytep bp; lzo_uint u; lzo_uint32 u32; unsigned long l; } lzo_align_t;
+typedef union {
+    lzo_voidp a00; lzo_bytep a01; lzo_uint a02; lzo_xint a03; lzo_uintptr_t a04;
+    void *a05; unsigned char *a06; unsigned long a07; size_t a08; ptrdiff_t a09;
+#if defined(lzo_int64_t)
+    lzo_uint64_t a10;
+#endif
+} lzo_align_t;
 
 /* align a char pointer on a boundary that is a multiple of 'size' */
 LZO_EXTERN(unsigned) __lzo_align_gap(const lzo_voidp p, lzo_uint size);
@@ -372,8 +376,29 @@
 
 
 /***********************************************************************
-// deprecated macros - only for backward compatibility with LZO v1.xx
-************************************************************************/
+// deprecated macros - only for backward compatibility
+************************************************************************/
+
+/* deprecated - use 'lzo_bytep' instead of 'lzo_byte *' */
+#define lzo_byte                unsigned char
+/* deprecated type names */
+#define lzo_int32               lzo_int32_t
+#define lzo_uint32              lzo_uint32_t
+#define lzo_int32p              lzo_int32_t __LZO_MMODEL *
+#define lzo_uint32p             lzo_uint32_t __LZO_MMODEL *
+#define LZO_INT32_MAX           LZO_INT32_C(2147483647)
+#define LZO_UINT32_MAX          LZO_UINT32_C(4294967295)
+#if defined(lzo_int64_t)
+#define lzo_int64               lzo_int64_t
+#define lzo_uint64              lzo_uint64_t
+#define lzo_int64p              lzo_int64_t __LZO_MMODEL *
+#define lzo_uint64p             lzo_uint64_t __LZO_MMODEL *
+#define LZO_INT64_MAX           LZO_INT64_C(9223372036854775807)
+#define LZO_UINT64_MAX          LZO_UINT64_C(18446744073709551615)
+#endif
+/* deprecated types */
+typedef union { lzo_bytep a; lzo_uint b; } __lzo_pu_u;
+typedef union { lzo_bytep a; lzo_uint32_t b; } __lzo_pu32_u;
 
 #if defined(LZO_CFG_COMPAT)
 


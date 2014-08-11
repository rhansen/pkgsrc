$NetBSD: patch-libvncserver_minilzo.c,v 1.1 2014/08/11 21:22:15 markd Exp $

Update LZO to version 2.07 in libvncserver. 

Temporary fix for CVE-2014-4607 for 4.14.

--- libvncserver/minilzo.c
+++ libvncserver/minilzo.c
@@ -2,21 +2,7 @@
 
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
@@ -66,12 +52,6 @@
 #if defined(__CYGWIN32__) && !defined(__CYGWIN__)
 #  define __CYGWIN__ __CYGWIN32__
 #endif
-#if defined(__IBMCPP__) && !defined(__IBMC__)
-#  define __IBMC__ __IBMCPP__
-#endif
-#if defined(__ICL) && defined(_WIN32) && !defined(__INTEL_COMPILER)
-#  define __INTEL_COMPILER __ICL
-#endif
 #if 1 && defined(__INTERIX) && defined(__GNUC__) && !defined(_ALL_SOURCE)
 #  define _ALL_SOURCE 1
 #endif
@@ -80,17 +60,28 @@
 #    define __LONG_MAX__ 9223372036854775807L
 #  endif
 #endif
-#if defined(__INTEL_COMPILER) && defined(__linux__)
+#if !defined(LZO_CFG_NO_DISABLE_WUNDEF)
+#if defined(__ARMCC_VERSION)
+#  pragma diag_suppress 193
+#elif defined(__clang__) && defined(__clang_minor__)
+#  pragma clang diagnostic ignored "-Wundef"
+#elif defined(__INTEL_COMPILER)
 #  pragma warning(disable: 193)
-#endif
-#if defined(__KEIL__) && defined(__C166__)
+#elif defined(__KEIL__) && defined(__C166__)
 #  pragma warning disable = 322
-#elif 0 && defined(__C251__)
-#  pragma warning disable = 322
-#endif
-#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__)
-#  if (_MSC_VER >= 1300)
+#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__PATHSCALE__)
+#  if ((__GNUC__-0) >= 5 || ((__GNUC__-0) == 4 && (__GNUC_MINOR__-0) >= 2))
+#    pragma GCC diagnostic ignored "-Wundef"
+#  endif
+#elif defined(_MSC_VER) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__)
+#  if ((_MSC_VER-0) >= 1300)
 #    pragma warning(disable: 4668)
+#  endif
+#endif
+#endif
+#if 0 && defined(__POCC__) && defined(_WIN32)
+#  if (__POCC__ >= 400)
+#    pragma warn(disable: 2216)
 #  endif
 #endif
 #if 0 && defined(__WATCOMC__)
@@ -101,13 +92,29 @@
 #if defined(__BORLANDC__) && defined(__MSDOS__) && !defined(__FLAT__)
 #  pragma option -h
 #endif
+#if !(LZO_CFG_NO_DISABLE_WCRTNONSTDC)
+#ifndef _CRT_NONSTDC_NO_DEPRECATE
+#define _CRT_NONSTDC_NO_DEPRECATE 1
+#endif
+#ifndef _CRT_NONSTDC_NO_WARNINGS
+#define _CRT_NONSTDC_NO_WARNINGS 1
+#endif
+#ifndef _CRT_SECURE_NO_DEPRECATE
+#define _CRT_SECURE_NO_DEPRECATE 1
+#endif
+#ifndef _CRT_SECURE_NO_WARNINGS
+#define _CRT_SECURE_NO_WARNINGS 1
+#endif
+#endif
 #if 0
-#define LZO_0xffffL             0xfffful
-#define LZO_0xffffffffL         0xfffffffful
-#else
-#define LZO_0xffffL             65535ul
-#define LZO_0xffffffffL         4294967295ul
-#endif
+#define LZO_0xffffUL            0xfffful
+#define LZO_0xffffffffUL        0xfffffffful
+#else
+#define LZO_0xffffUL            65535ul
+#define LZO_0xffffffffUL        4294967295ul
+#endif
+#define LZO_0xffffL             LZO_0xffffUL
+#define LZO_0xffffffffL         LZO_0xffffffffUL
 #if (LZO_0xffffL == LZO_0xffffffffL)
 #  error "your preprocessor is broken 1"
 #endif
@@ -121,6 +128,13 @@
 #if (65535u >= 4294967295ul)
 #  error "your preprocessor is broken 4"
 #endif
+#endif
+#if defined(__COUNTER__)
+#  ifndef LZO_CFG_USE_COUNTER
+#  define LZO_CFG_USE_COUNTER 1
+#  endif
+#else
+#  undef LZO_CFG_USE_COUNTER
 #endif
 #if (UINT_MAX == LZO_0xffffL)
 #if defined(__ZTC__) && defined(__I86__) && !defined(__OS2__)
@@ -252,14 +266,31 @@
 #endif
 #define LZO_PP_STRINGIZE(x)             #x
 #define LZO_PP_MACRO_EXPAND(x)          LZO_PP_STRINGIZE(x)
+#define LZO_PP_CONCAT0()                /*empty*/
+#define LZO_PP_CONCAT1(a)               a
 #define LZO_PP_CONCAT2(a,b)             a ## b
 #define LZO_PP_CONCAT3(a,b,c)           a ## b ## c
 #define LZO_PP_CONCAT4(a,b,c,d)         a ## b ## c ## d
 #define LZO_PP_CONCAT5(a,b,c,d,e)       a ## b ## c ## d ## e
+#define LZO_PP_CONCAT6(a,b,c,d,e,f)     a ## b ## c ## d ## e ## f
+#define LZO_PP_CONCAT7(a,b,c,d,e,f,g)   a ## b ## c ## d ## e ## f ## g
+#define LZO_PP_ECONCAT0()               LZO_PP_CONCAT0()
+#define LZO_PP_ECONCAT1(a)              LZO_PP_CONCAT1(a)
 #define LZO_PP_ECONCAT2(a,b)            LZO_PP_CONCAT2(a,b)
 #define LZO_PP_ECONCAT3(a,b,c)          LZO_PP_CONCAT3(a,b,c)
 #define LZO_PP_ECONCAT4(a,b,c,d)        LZO_PP_CONCAT4(a,b,c,d)
 #define LZO_PP_ECONCAT5(a,b,c,d,e)      LZO_PP_CONCAT5(a,b,c,d,e)
+#define LZO_PP_ECONCAT6(a,b,c,d,e,f)    LZO_PP_CONCAT6(a,b,c,d,e,f)
+#define LZO_PP_ECONCAT7(a,b,c,d,e,f,g)  LZO_PP_CONCAT7(a,b,c,d,e,f,g)
+#define LZO_PP_EMPTY                    /*empty*/
+#define LZO_PP_EMPTY0()                 /*empty*/
+#define LZO_PP_EMPTY1(a)                /*empty*/
+#define LZO_PP_EMPTY2(a,b)              /*empty*/
+#define LZO_PP_EMPTY3(a,b,c)            /*empty*/
+#define LZO_PP_EMPTY4(a,b,c,d)          /*empty*/
+#define LZO_PP_EMPTY5(a,b,c,d,e)        /*empty*/
+#define LZO_PP_EMPTY6(a,b,c,d,e,f)      /*empty*/
+#define LZO_PP_EMPTY7(a,b,c,d,e,f,g)    /*empty*/
 #if 1
 #define LZO_CPP_STRINGIZE(x)            #x
 #define LZO_CPP_MACRO_EXPAND(x)         LZO_CPP_STRINGIZE(x)
@@ -267,12 +298,16 @@
 #define LZO_CPP_CONCAT3(a,b,c)          a ## b ## c
 #define LZO_CPP_CONCAT4(a,b,c,d)        a ## b ## c ## d
 #define LZO_CPP_CONCAT5(a,b,c,d,e)      a ## b ## c ## d ## e
+#define LZO_CPP_CONCAT6(a,b,c,d,e,f)    a ## b ## c ## d ## e ## f
+#define LZO_CPP_CONCAT7(a,b,c,d,e,f,g)  a ## b ## c ## d ## e ## f ## g
 #define LZO_CPP_ECONCAT2(a,b)           LZO_CPP_CONCAT2(a,b)
 #define LZO_CPP_ECONCAT3(a,b,c)         LZO_CPP_CONCAT3(a,b,c)
 #define LZO_CPP_ECONCAT4(a,b,c,d)       LZO_CPP_CONCAT4(a,b,c,d)
 #define LZO_CPP_ECONCAT5(a,b,c,d,e)     LZO_CPP_CONCAT5(a,b,c,d,e)
-#endif
-#define __LZO_MASK_GEN(o,b)     (((((o) << ((b)-1)) - (o)) << 1) + (o))
+#define LZO_CPP_ECONCAT6(a,b,c,d,e,f)   LZO_CPP_CONCAT6(a,b,c,d,e,f)
+#define LZO_CPP_ECONCAT7(a,b,c,d,e,f,g) LZO_CPP_CONCAT7(a,b,c,d,e,f,g)
+#endif
+#define __LZO_MASK_GEN(o,b)     (((((o) << ((b)-!!(b))) - (o)) << 1) + (o)*!!(b))
 #if 1 && defined(__cplusplus)
 #  if !defined(__STDC_CONSTANT_MACROS)
 #    define __STDC_CONSTANT_MACROS 1
@@ -282,9 +317,13 @@
 #  endif
 #endif
 #if defined(__cplusplus)
-#  define LZO_EXTERN_C extern "C"
-#else
-#  define LZO_EXTERN_C extern
+#  define LZO_EXTERN_C          extern "C"
+#  define LZO_EXTERN_C_BEGIN    extern "C" {
+#  define LZO_EXTERN_C_END      }
+#else
+#  define LZO_EXTERN_C          extern
+#  define LZO_EXTERN_C_BEGIN    /*empty*/
+#  define LZO_EXTERN_C_END      /*empty*/
 #endif
 #if !defined(__LZO_OS_OVERRIDE)
 #if (LZO_OS_FREESTANDING)
@@ -385,12 +424,12 @@
 #elif defined(__VMS)
 #  define LZO_OS_VMS            1
 #  define LZO_INFO_OS           "vms"
-#elif ((defined(__mips__) && defined(__R5900__)) || defined(__MIPS_PSX2__))
+#elif (defined(__mips__) && defined(__R5900__)) || defined(__MIPS_PSX2__)
 #  define LZO_OS_CONSOLE        1
 #  define LZO_OS_CONSOLE_PS2    1
 #  define LZO_INFO_OS           "console"
 #  define LZO_INFO_OS_CONSOLE   "ps2"
-#elif (defined(__mips__) && defined(__psp__))
+#elif defined(__mips__) && defined(__psp__)
 #  define LZO_OS_CONSOLE        1
 #  define LZO_OS_CONSOLE_PSP    1
 #  define LZO_INFO_OS           "console"
@@ -418,9 +457,18 @@
 #  elif defined(__linux__) || defined(__linux) || defined(__LINUX__)
 #    define LZO_OS_POSIX_LINUX      1
 #    define LZO_INFO_OS_POSIX       "linux"
-#  elif defined(__APPLE__) || defined(__MACOS__)
-#    define LZO_OS_POSIX_MACOSX     1
-#    define LZO_INFO_OS_POSIX       "macosx"
+#  elif defined(__APPLE__) && defined(__MACH__)
+#    if ((__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__-0) >= 20000)
+#      define LZO_OS_POSIX_DARWIN     1040
+#      define LZO_INFO_OS_POSIX       "darwin_iphone"
+#    elif ((__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__-0) >= 1040)
+#      define LZO_OS_POSIX_DARWIN     __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
+#      define LZO_INFO_OS_POSIX       "darwin"
+#    else
+#      define LZO_OS_POSIX_DARWIN     1
+#      define LZO_INFO_OS_POSIX       "darwin"
+#    endif
+#    define LZO_OS_POSIX_MACOSX     LZO_OS_POSIX_DARWIN
 #  elif defined(__minix__) || defined(__minix)
 #    define LZO_OS_POSIX_MINIX      1
 #    define LZO_INFO_OS_POSIX       "minix"
@@ -455,18 +503,18 @@
 #endif
 #if (LZO_OS_DOS16 || LZO_OS_OS216 || LZO_OS_WIN16)
 #  if (UINT_MAX != LZO_0xffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #  if (ULONG_MAX != LZO_0xffffffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #endif
 #if (LZO_OS_DOS32 || LZO_OS_OS2 || LZO_OS_WIN32 || LZO_OS_WIN64)
 #  if (UINT_MAX != LZO_0xffffffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #  if (ULONG_MAX != LZO_0xffffffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #endif
 #if defined(CIL) && defined(_GNUCC) && defined(__GNUC__)
@@ -482,59 +530,65 @@
 #  define LZO_INFO_CC           "sdcc"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(SDCC)
 #elif defined(__PATHSCALE__) && defined(__PATHCC_PATCHLEVEL__)
-#  define LZO_CC_PATHSCALE      (__PATHCC__ * 0x10000L + __PATHCC_MINOR__ * 0x100 + __PATHCC_PATCHLEVEL__)
+#  define LZO_CC_PATHSCALE      (__PATHCC__ * 0x10000L + (__PATHCC_MINOR__-0) * 0x100 + (__PATHCC_PATCHLEVEL__-0))
 #  define LZO_INFO_CC           "Pathscale C"
 #  define LZO_INFO_CCVER        __PATHSCALE__
-#elif defined(__INTEL_COMPILER)
-#  define LZO_CC_INTELC         1
+#  if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
+#    define LZO_CC_PATHSCALE_GNUC (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
+#  endif
+#elif defined(__INTEL_COMPILER) && ((__INTEL_COMPILER-0) > 0)
+#  define LZO_CC_INTELC         __INTEL_COMPILER
 #  define LZO_INFO_CC           "Intel C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__INTEL_COMPILER)
-#  if defined(_WIN32) || defined(_WIN64)
-#    define LZO_CC_SYNTAX_MSC 1
-#  else
-#    define LZO_CC_SYNTAX_GNUC 1
+#  if defined(_MSC_VER) && ((_MSC_VER-0) > 0)
+#    define LZO_CC_INTELC_MSC   _MSC_VER
+#  elif defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
+#    define LZO_CC_INTELC_GNUC   (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
 #  endif
 #elif defined(__POCC__) && defined(_WIN32)
 #  define LZO_CC_PELLESC        1
 #  define LZO_INFO_CC           "Pelles C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__POCC__)
-#elif defined(__clang__) && defined(__llvm__) && defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
+#elif defined(__ARMCC_VERSION) && defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
 #  if defined(__GNUC_PATCHLEVEL__)
-#    define LZO_CC_CLANG_GNUC   (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
+#    define LZO_CC_ARMCC_GNUC   (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
 #  else
-#    define LZO_CC_CLANG_GNUC   (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100)
-#  endif
+#    define LZO_CC_ARMCC_GNUC   (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100)
+#  endif
+#  define LZO_CC_ARMCC          __ARMCC_VERSION
+#  define LZO_INFO_CC           "ARM C Compiler"
+#  define LZO_INFO_CCVER        __VERSION__
+#elif defined(__clang__) && defined(__llvm__) && defined(__VERSION__)
 #  if defined(__clang_major__) && defined(__clang_minor__) && defined(__clang_patchlevel__)
-#    define LZO_CC_CLANG_CLANG  (__clang_major__ * 0x10000L + __clang_minor__ * 0x100 + __clang_patchlevel__)
+#    define LZO_CC_CLANG        (__clang_major__ * 0x10000L + (__clang_minor__-0) * 0x100 + (__clang_patchlevel__-0))
 #  else
-#    define LZO_CC_CLANG_CLANG  0x020700L
-#  endif
-#  define LZO_CC_CLANG          LZO_CC_CLANG_GNUC
+#    define LZO_CC_CLANG        0x010000L
+#  endif
+#  if defined(_MSC_VER) && ((_MSC_VER-0) > 0)
+#    define LZO_CC_CLANG_MSC    _MSC_VER
+#  elif defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
+#    define LZO_CC_CLANG_GNUC   (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
+#  endif
 #  define LZO_INFO_CC           "clang"
 #  define LZO_INFO_CCVER        __VERSION__
 #elif defined(__llvm__) && defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
 #  if defined(__GNUC_PATCHLEVEL__)
-#    define LZO_CC_LLVM_GNUC    (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
+#    define LZO_CC_LLVM_GNUC    (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
 #  else
-#    define LZO_CC_LLVM_GNUC    (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100)
+#    define LZO_CC_LLVM_GNUC    (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100)
 #  endif
 #  define LZO_CC_LLVM           LZO_CC_LLVM_GNUC
 #  define LZO_INFO_CC           "llvm-gcc"
-#  define LZO_INFO_CCVER        __VERSION__
-#elif defined(__GNUC__) && defined(__VERSION__)
-#  if defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
-#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
-#  elif defined(__GNUC_MINOR__)
-#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L + __GNUC_MINOR__ * 0x100)
-#  else
-#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L)
-#  endif
-#  define LZO_INFO_CC           "gcc"
 #  define LZO_INFO_CCVER        __VERSION__
 #elif defined(__ACK__) && defined(_ACK)
 #  define LZO_CC_ACK            1
 #  define LZO_INFO_CC           "Amsterdam Compiler Kit C"
 #  define LZO_INFO_CCVER        "unknown"
+#elif defined(__ARMCC_VERSION) && !defined(__GNUC__)
+#  define LZO_CC_ARMCC          __ARMCC_VERSION
+#  define LZO_CC_ARMCC_ARMCC    __ARMCC_VERSION
+#  define LZO_INFO_CC           "ARM C Compiler"
+#  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__ARMCC_VERSION)
 #elif defined(__AZTEC_C__)
 #  define LZO_CC_AZTECC         1
 #  define LZO_INFO_CC           "Aztec C"
@@ -559,10 +613,23 @@
 #  define LZO_CC_DECC           1
 #  define LZO_INFO_CC           "DEC C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__DECC)
+#elif (defined(__ghs) || defined(__ghs__)) && defined(__GHS_VERSION_NUMBER) && ((__GHS_VERSION_NUMBER-0) > 0)
+#  define LZO_CC_GHS            1
+#  define LZO_INFO_CC           "Green Hills C"
+#  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__GHS_VERSION_NUMBER)
+#  if defined(_MSC_VER) && ((_MSC_VER-0) > 0)
+#    define LZO_CC_GHS_MSC      _MSC_VER
+#  elif defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__VERSION__)
+#    define LZO_CC_GHS_GNUC     (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
+#  endif
 #elif defined(__HIGHC__)
 #  define LZO_CC_HIGHC          1
 #  define LZO_INFO_CC           "MetaWare High C"
 #  define LZO_INFO_CCVER        "unknown"
+#elif defined(__HP_aCC) && ((__HP_aCC-0) > 0)
+#  define LZO_CC_HPACC          __HP_aCC
+#  define LZO_INFO_CC           "HP aCC"
+#  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__HP_aCC)
 #elif defined(__IAR_SYSTEMS_ICC__)
 #  define LZO_CC_IARC           1
 #  define LZO_INFO_CC           "IAR C"
@@ -571,10 +638,14 @@
 #  else
 #    define LZO_INFO_CCVER      "unknown"
 #  endif
-#elif defined(__IBMC__)
-#  define LZO_CC_IBMC           1
+#elif defined(__IBMC__) && ((__IBMC__-0) > 0)
+#  define LZO_CC_IBMC           __IBMC__
 #  define LZO_INFO_CC           "IBM C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__IBMC__)
+#elif defined(__IBMCPP__) && ((__IBMCPP__-0) > 0)
+#  define LZO_CC_IBMC           __IBMCPP__
+#  define LZO_INFO_CC           "IBM C"
+#  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__IBMCPP__)
 #elif defined(__KEIL__) && defined(__C166__)
 #  define LZO_CC_KEILC          1
 #  define LZO_INFO_CC           "Keil C"
@@ -591,16 +662,8 @@
 #  else
 #    define LZO_INFO_CCVER      "unknown"
 #  endif
-#elif defined(_MSC_VER)
-#  define LZO_CC_MSC            1
-#  define LZO_INFO_CC           "Microsoft C"
-#  if defined(_MSC_FULL_VER)
-#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(_MSC_VER) "." LZO_PP_MACRO_EXPAND(_MSC_FULL_VER)
-#  else
-#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(_MSC_VER)
-#  endif
-#elif defined(__MWERKS__)
-#  define LZO_CC_MWERKS         1
+#elif defined(__MWERKS__) && ((__MWERKS__-0) > 0)
+#  define LZO_CC_MWERKS         __MWERKS__
 #  define LZO_INFO_CC           "Metrowerks C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__MWERKS__)
 #elif (defined(__NDPC__) || defined(__NDPX__)) && defined(__i386)
@@ -611,6 +674,15 @@
 #  define LZO_CC_PACIFICC       1
 #  define LZO_INFO_CC           "Pacific C"
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__PACIFIC__)
+#elif defined(__PGI) && defined(__PGIC__) && defined(__PGIC_MINOR__)
+#  if defined(__PGIC_PATCHLEVEL__)
+#    define LZO_CC_PGI          (__PGIC__ * 0x10000L + (__PGIC_MINOR__-0) * 0x100 + (__PGIC_PATCHLEVEL__-0))
+#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(__PGIC__) "." LZO_PP_MACRO_EXPAND(__PGIC_MINOR__) "." LZO_PP_MACRO_EXPAND(__PGIC_PATCHLEVEL__)
+#  else
+#    define LZO_CC_PGI          (__PGIC__ * 0x10000L + (__PGIC_MINOR__-0) * 0x100)
+#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(__PGIC__) "." LZO_PP_MACRO_EXPAND(__PGIC_MINOR__) ".0"
+#  endif
+#  define LZO_INFO_CC           "Portland Group PGI C"
 #elif defined(__PGI) && (defined(__linux__) || defined(__WIN32__))
 #  define LZO_CC_PGI            1
 #  define LZO_INFO_CC           "Portland Group PGI C"
@@ -625,7 +697,7 @@
 #  define LZO_INFO_CCVER        LZO_PP_MACRO_EXPAND(__SC__)
 #elif defined(__SUNPRO_C)
 #  define LZO_INFO_CC           "SunPro C"
-#  if ((__SUNPRO_C)+0 > 0)
+#  if ((__SUNPRO_C-0) > 0)
 #    define LZO_CC_SUNPROC      __SUNPRO_C
 #    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(__SUNPRO_C)
 #  else
@@ -634,7 +706,7 @@
 #  endif
 #elif defined(__SUNPRO_CC)
 #  define LZO_INFO_CC           "SunPro C"
-#  if ((__SUNPRO_CC)+0 > 0)
+#  if ((__SUNPRO_CC-0) > 0)
 #    define LZO_CC_SUNPROC      __SUNPRO_CC
 #    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(__SUNPRO_CC)
 #  else
@@ -660,15 +732,45 @@
 #elif defined(__ZTC__)
 #  define LZO_CC_ZORTECHC       1
 #  define LZO_INFO_CC           "Zortech C"
-#  if (__ZTC__ == 0x310)
+#  if ((__ZTC__-0) == 0x310)
 #    define LZO_INFO_CCVER      "0x310"
 #  else
 #    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(__ZTC__)
 #  endif
+#elif defined(__GNUC__) && defined(__VERSION__)
+#  if defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
+#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100 + (__GNUC_PATCHLEVEL__-0))
+#  elif defined(__GNUC_MINOR__)
+#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L + (__GNUC_MINOR__-0) * 0x100)
+#  else
+#    define LZO_CC_GNUC         (__GNUC__ * 0x10000L)
+#  endif
+#  define LZO_INFO_CC           "gcc"
+#  define LZO_INFO_CCVER        __VERSION__
+#elif defined(_MSC_VER) && ((_MSC_VER-0) > 0)
+#  define LZO_CC_MSC            _MSC_VER
+#  define LZO_INFO_CC           "Microsoft C"
+#  if defined(_MSC_FULL_VER)
+#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(_MSC_VER) "." LZO_PP_MACRO_EXPAND(_MSC_FULL_VER)
+#  else
+#    define LZO_INFO_CCVER      LZO_PP_MACRO_EXPAND(_MSC_VER)
+#  endif
 #else
 #  define LZO_CC_UNKNOWN        1
 #  define LZO_INFO_CC           "unknown"
 #  define LZO_INFO_CCVER        "unknown"
+#endif
+#if (LZO_CC_GNUC) && defined(__OPEN64__)
+#  if defined(__OPENCC__) && defined(__OPENCC_MINOR__) && defined(__OPENCC_PATCHLEVEL__)
+#    define LZO_CC_OPEN64       (__OPENCC__ * 0x10000L + (__OPENCC_MINOR__-0) * 0x100 + (__OPENCC_PATCHLEVEL__-0))
+#    define LZO_CC_OPEN64_GNUC  LZO_CC_GNUC
+#  endif
+#endif
+#if (LZO_CC_GNUC) && defined(__PCC__)
+#  if defined(__PCC__) && defined(__PCC_MINOR__) && defined(__PCC_MINORMINOR__)
+#    define LZO_CC_PCC          (__PCC__ * 0x10000L + (__PCC_MINOR__-0) * 0x100 + (__PCC_MINORMINOR__-0))
+#    define LZO_CC_PCC_GNUC     LZO_CC_GNUC
+#  endif
 #endif
 #if 0 && (LZO_CC_MSC && (_MSC_VER >= 1200)) && !defined(_MSC_FULL_VER)
 #  error "LZO_CC_MSC: _MSC_FULL_VER is not defined"
@@ -687,8 +789,10 @@
 #  define LZO_INFO_ARCH             "generic"
 #elif (LZO_OS_DOS16 || LZO_OS_OS216 || LZO_OS_WIN16)
 #  define LZO_ARCH_I086             1
-#  define LZO_ARCH_IA16             1
 #  define LZO_INFO_ARCH             "i086"
+#elif defined(__aarch64__)
+#  define LZO_ARCH_ARM64            1
+#  define LZO_INFO_ARCH             "arm64"
 #elif defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
 #  define LZO_ARCH_ALPHA            1
 #  define LZO_INFO_ARCH             "alpha"
@@ -704,10 +808,10 @@
 #  define LZO_INFO_ARCH             "arm_thumb"
 #elif defined(__IAR_SYSTEMS_ICC__) && defined(__ICCARM__)
 #  define LZO_ARCH_ARM              1
-#  if defined(__CPU_MODE__) && ((__CPU_MODE__)+0 == 1)
+#  if defined(__CPU_MODE__) && ((__CPU_MODE__-0) == 1)
 #    define LZO_ARCH_ARM_THUMB      1
 #    define LZO_INFO_ARCH           "arm_thumb"
-#  elif defined(__CPU_MODE__) && ((__CPU_MODE__)+0 == 2)
+#  elif defined(__CPU_MODE__) && ((__CPU_MODE__-0) == 2)
 #    define LZO_INFO_ARCH           "arm"
 #  else
 #    define LZO_INFO_ARCH           "arm"
@@ -825,53 +929,147 @@
 #  error "FIXME - missing define for CPU architecture"
 #endif
 #if 1 && (LZO_ARCH_UNKNOWN) && (LZO_OS_WIN32)
-#  error "FIXME - missing WIN32 define for CPU architecture"
+#  error "FIXME - missing LZO_OS_WIN32 define for CPU architecture"
 #endif
 #if 1 && (LZO_ARCH_UNKNOWN) && (LZO_OS_WIN64)
-#  error "FIXME - missing WIN64 define for CPU architecture"
+#  error "FIXME - missing LZO_OS_WIN64 define for CPU architecture"
 #endif
 #if (LZO_OS_OS216 || LZO_OS_WIN16)
 #  define LZO_ARCH_I086PM           1
-#  define LZO_ARCH_IA16PM           1
 #elif 1 && (LZO_OS_DOS16 && defined(BLX286))
 #  define LZO_ARCH_I086PM           1
-#  define LZO_ARCH_IA16PM           1
 #elif 1 && (LZO_OS_DOS16 && defined(DOSX286))
 #  define LZO_ARCH_I086PM           1
-#  define LZO_ARCH_IA16PM           1
 #elif 1 && (LZO_OS_DOS16 && LZO_CC_BORLANDC && defined(__DPMI16__))
 #  define LZO_ARCH_I086PM           1
-#  define LZO_ARCH_IA16PM           1
-#endif
-#if (LZO_ARCH_ARM_THUMB) && !(LZO_ARCH_ARM)
-#  error "this should not happen"
-#endif
-#if (LZO_ARCH_I086PM) && !(LZO_ARCH_I086)
-#  error "this should not happen"
+#endif
+#if (LZO_ARCH_AMD64 && !LZO_ARCH_X64)
+#  define LZO_ARCH_X64              1
+#elif (!LZO_ARCH_AMD64 && LZO_ARCH_X64) && defined(__LZO_ARCH_OVERRIDE)
+#  define LZO_ARCH_AMD64            1
+#endif
+#if (LZO_ARCH_ARM64 && !LZO_ARCH_AARCH64)
+#  define LZO_ARCH_AARCH64          1
+#elif (!LZO_ARCH_ARM64 && LZO_ARCH_AARCH64) && defined(__LZO_ARCH_OVERRIDE)
+#  define LZO_ARCH_ARM64            1
+#endif
+#if (LZO_ARCH_I386 && !LZO_ARCH_X86)
+#  define LZO_ARCH_X86              1
+#elif (!LZO_ARCH_I386 && LZO_ARCH_X86) && defined(__LZO_ARCH_OVERRIDE)
+#  define LZO_ARCH_I386            1
+#endif
+#if (LZO_ARCH_AMD64 && !LZO_ARCH_X64) || (!LZO_ARCH_AMD64 && LZO_ARCH_X64)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM64 && !LZO_ARCH_AARCH64) || (!LZO_ARCH_ARM64 && LZO_ARCH_AARCH64)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_I386 && !LZO_ARCH_X86) || (!LZO_ARCH_I386 && LZO_ARCH_X86)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM_THUMB && !LZO_ARCH_ARM)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM_THUMB1 && !LZO_ARCH_ARM_THUMB)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM_THUMB2 && !LZO_ARCH_ARM_THUMB)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM_THUMB1 && LZO_ARCH_ARM_THUMB2)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_I086PM && !LZO_ARCH_I086)
+#  error "unexpected configuration - check your compiler defines"
 #endif
 #if (LZO_ARCH_I086)
 #  if (UINT_MAX != LZO_0xffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #  if (ULONG_MAX != LZO_0xffffffffL)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #endif
 #if (LZO_ARCH_I386)
 #  if (UINT_MAX != LZO_0xffffL) && defined(__i386_int16__)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #  if (UINT_MAX != LZO_0xffffffffL) && !defined(__i386_int16__)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #  if (ULONG_MAX != LZO_0xffffffffL)
-#    error "this should not happen"
-#  endif
-#endif
-#if !defined(__LZO_MM_OVERRIDE)
+#    error "unexpected configuration - check your compiler defines"
+#  endif
+#endif
+#if (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+#  if !defined(LZO_TARGET_FEATURE_SSE2)
+#    if defined(__SSE2__)
+#      define LZO_TARGET_FEATURE_SSE2       1
+#    elif defined(_MSC_VER) && ((defined(_M_IX86_FP) && ((_M_IX86_FP)+0 >= 2)) || defined(_M_AMD64))
+#      define LZO_TARGET_FEATURE_SSE2       1
+#    endif
+#  endif
+#  if !defined(LZO_TARGET_FEATURE_SSSE3)
+#  if (LZO_TARGET_FEATURE_SSE2)
+#    if defined(__SSSE3__)
+#      define LZO_TARGET_FEATURE_SSSE3      1
+#    elif defined(_MSC_VER) && defined(__AVX__)
+#      define LZO_TARGET_FEATURE_SSSE3      1
+#    endif
+#  endif
+#  endif
+#  if !defined(LZO_TARGET_FEATURE_SSE4_2)
+#  if (LZO_TARGET_FEATURE_SSSE3)
+#    if defined(__SSE4_2__)
+#      define LZO_TARGET_FEATURE_SSE4_2     1
+#    endif
+#  endif
+#  endif
+#  if !defined(LZO_TARGET_FEATURE_AVX)
+#  if (LZO_TARGET_FEATURE_SSSE3)
+#    if defined(__AVX__)
+#      define LZO_TARGET_FEATURE_AVX        1
+#    endif
+#  endif
+#  endif
+#  if !defined(LZO_TARGET_FEATURE_AVX2)
+#  if (LZO_TARGET_FEATURE_AVX)
+#    if defined(__AVX2__)
+#      define LZO_TARGET_FEATURE_AVX2       1
+#    endif
+#  endif
+#  endif
+#endif
+#if (LZO_TARGET_FEATURE_SSSE3 && !(LZO_TARGET_FEATURE_SSE2))
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_TARGET_FEATURE_SSE4_2 && !(LZO_TARGET_FEATURE_SSSE3))
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_TARGET_FEATURE_AVX && !(LZO_TARGET_FEATURE_SSSE3))
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_TARGET_FEATURE_AVX2 && !(LZO_TARGET_FEATURE_AVX))
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if (LZO_ARCH_ARM)
+#  if !defined(LZO_TARGET_FEATURE_NEON)
+#    if defined(__ARM_NEON__)
+#      define LZO_TARGET_FEATURE_NEON       1
+#    endif
+#  endif
+#elif (LZO_ARCH_ARM64)
+#  if !defined(LZO_TARGET_FEATURE_NEON)
+#    if 1
+#      define LZO_TARGET_FEATURE_NEON       1
+#    endif
+#  endif
+#endif
+#if 0
+#elif !defined(__LZO_MM_OVERRIDE)
 #if (LZO_ARCH_I086)
 #if (UINT_MAX != LZO_0xffffL)
-#  error "this should not happen"
+#  error "unexpected configuration - check your compiler defines"
 #endif
 #if defined(__TINY__) || defined(M_I86TM) || defined(_M_I86TM)
 #  define LZO_MM_TINY           1
@@ -898,7 +1096,7 @@
 #elif (LZO_CC_ZORTECHC && defined(__VCM__))
 #  define LZO_MM_LARGE          1
 #else
-#  error "unknown memory model"
+#  error "unknown LZO_ARCH_I086 memory model"
 #endif
 #if (LZO_OS_DOS16 || LZO_OS_OS216 || LZO_OS_WIN16)
 #define LZO_HAVE_MM_HUGE_PTR        1
@@ -921,10 +1119,10 @@
 #endif
 #if (LZO_ARCH_I086PM) && !(LZO_HAVE_MM_HUGE_PTR)
 #  if (LZO_OS_DOS16)
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  elif (LZO_CC_ZORTECHC)
 #  else
-#    error "this should not happen"
+#    error "unexpected configuration - check your compiler defines"
 #  endif
 #endif
 #ifdef __cplusplus
@@ -956,7 +1154,7 @@
 #endif
 #elif (LZO_ARCH_C166)
 #if !defined(__MODEL__)
-#  error "FIXME - C166 __MODEL__"
+#  error "FIXME - LZO_ARCH_C166 __MODEL__"
 #elif ((__MODEL__) == 0)
 #  define LZO_MM_SMALL          1
 #elif ((__MODEL__) == 1)
@@ -970,11 +1168,11 @@
 #elif ((__MODEL__) == 5)
 #  define LZO_MM_XSMALL         1
 #else
-#  error "FIXME - C166 __MODEL__"
+#  error "FIXME - LZO_ARCH_C166 __MODEL__"
 #endif
 #elif (LZO_ARCH_MCS251)
 #if !defined(__MODEL__)
-#  error "FIXME - MCS251 __MODEL__"
+#  error "FIXME - LZO_ARCH_MCS251 __MODEL__"
 #elif ((__MODEL__) == 0)
 #  define LZO_MM_SMALL          1
 #elif ((__MODEL__) == 2)
@@ -986,11 +1184,11 @@
 #elif ((__MODEL__) == 5)
 #  define LZO_MM_XSMALL         1
 #else
-#  error "FIXME - MCS251 __MODEL__"
+#  error "FIXME - LZO_ARCH_MCS251 __MODEL__"
 #endif
 #elif (LZO_ARCH_MCS51)
 #if !defined(__MODEL__)
-#  error "FIXME - MCS51 __MODEL__"
+#  error "FIXME - LZO_ARCH_MCS51 __MODEL__"
 #elif ((__MODEL__) == 1)
 #  define LZO_MM_SMALL          1
 #elif ((__MODEL__) == 2)
@@ -1002,7 +1200,7 @@
 #elif ((__MODEL__) == 5)
 #  define LZO_MM_XSMALL         1
 #else
-#  error "FIXME - MCS51 __MODEL__"
+#  error "FIXME - LZO_ARCH_MCS51 __MODEL__"
 #endif
 #elif (LZO_ARCH_CRAY_PVP)
 #  define LZO_MM_PVP            1
@@ -1029,35 +1227,818 @@
 #  error "unknown memory model"
 #endif
 #endif
+#if !defined(__lzo_gnuc_extension__)
+#if (LZO_CC_GNUC >= 0x020800ul)
+#  define __lzo_gnuc_extension__    __extension__
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_gnuc_extension__    __extension__
+#elif (LZO_CC_IBMC >= 600)
+#  define __lzo_gnuc_extension__    __extension__
+#else
+#endif
+#endif
+#if !defined(__lzo_gnuc_extension__)
+#  define __lzo_gnuc_extension__    /*empty*/
+#endif
+#if !defined(LZO_CFG_USE_NEW_STYLE_CASTS) && defined(__cplusplus) && 0
+#  if (LZO_CC_GNUC && (LZO_CC_GNUC < 0x020800ul))
+#    define LZO_CFG_USE_NEW_STYLE_CASTS 0
+#  elif (LZO_CC_INTELC && (__INTEL_COMPILER < 1200))
+#    define LZO_CFG_USE_NEW_STYLE_CASTS 0
+#  else
+#    define LZO_CFG_USE_NEW_STYLE_CASTS 1
+#  endif
+#endif
+#if !defined(LZO_CFG_USE_NEW_STYLE_CASTS)
+#  define LZO_CFG_USE_NEW_STYLE_CASTS 0
+#endif
+#if !defined(__cplusplus)
+#  if defined(LZO_CFG_USE_NEW_STYLE_CASTS)
+#    undef LZO_CFG_USE_NEW_STYLE_CASTS
+#  endif
+#  define LZO_CFG_USE_NEW_STYLE_CASTS 0
+#endif
+#if !defined(LZO_REINTERPRET_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_REINTERPRET_CAST(t,e)       (reinterpret_cast<t> (e))
+#  endif
+#endif
+#if !defined(LZO_REINTERPRET_CAST)
+#  define LZO_REINTERPRET_CAST(t,e)         ((t) (e))
+#endif
+#if !defined(LZO_STATIC_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_STATIC_CAST(t,e)            (static_cast<t> (e))
+#  endif
+#endif
+#if !defined(LZO_STATIC_CAST)
+#  define LZO_STATIC_CAST(t,e)              ((t) (e))
+#endif
+#if !defined(LZO_STATIC_CAST2)
+#  define LZO_STATIC_CAST2(t1,t2,e)         LZO_STATIC_CAST(t1, LZO_STATIC_CAST(t2, e))
+#endif
+#if !defined(LZO_UNCONST_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_UNCONST_CAST(t,e)           (const_cast<t> (e))
+#  elif (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_UNCONST_CAST(t,e)           ((t) (e))
+#  elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#    define LZO_UNCONST_CAST(t,e)           ((t) ((void *) ((lzo_uintptr_t) ((const void *) (e)))))
+#  endif
+#endif
+#if !defined(LZO_UNCONST_CAST)
+#  define LZO_UNCONST_CAST(t,e)             ((t) ((void *) ((const void *) (e))))
+#endif
+#if !defined(LZO_UNCONST_VOLATILE_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_UNCONST_VOLATILE_CAST(t,e)  (const_cast<t> (e))
+#  elif (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_UNCONST_VOLATILE_CAST(t,e)  ((t) (e))
+#  elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#    define LZO_UNCONST_VOLATILE_CAST(t,e)  ((t) ((volatile void *) ((lzo_uintptr_t) ((volatile const void *) (e)))))
+#  endif
+#endif
+#if !defined(LZO_UNCONST_VOLATILE_CAST)
+#  define LZO_UNCONST_VOLATILE_CAST(t,e)    ((t) ((volatile void *) ((volatile const void *) (e))))
+#endif
+#if !defined(LZO_UNVOLATILE_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_UNVOLATILE_CAST(t,e)        (const_cast<t> (e))
+#  elif (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_UNVOLATILE_CAST(t,e)        ((t) (e))
+#  elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#    define LZO_UNVOLATILE_CAST(t,e)        ((t) ((void *) ((lzo_uintptr_t) ((volatile void *) (e)))))
+#  endif
+#endif
+#if !defined(LZO_UNVOLATILE_CAST)
+#  define LZO_UNVOLATILE_CAST(t,e)          ((t) ((void *) ((volatile void *) (e))))
+#endif
+#if !defined(LZO_UNVOLATILE_CONST_CAST)
+#  if (LZO_CFG_USE_NEW_STYLE_CASTS)
+#    define LZO_UNVOLATILE_CONST_CAST(t,e)  (const_cast<t> (e))
+#  elif (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_UNVOLATILE_CONST_CAST(t,e)  ((t) (e))
+#  elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#    define LZO_UNVOLATILE_CONST_CAST(t,e)  ((t) ((const void *) ((lzo_uintptr_t) ((volatile const void *) (e)))))
+#  endif
+#endif
+#if !defined(LZO_UNVOLATILE_CONST_CAST)
+#  define LZO_UNVOLATILE_CONST_CAST(t,e)    ((t) ((const void *) ((volatile const void *) (e))))
+#endif
+#if !defined(LZO_PCAST)
+#  if (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_PCAST(t,e)                  ((t) (e))
+#  endif
+#endif
+#if !defined(LZO_PCAST)
+#  define LZO_PCAST(t,e)                    LZO_STATIC_CAST(t, LZO_STATIC_CAST(void *, e))
+#endif
+#if !defined(LZO_CCAST)
+#  if (LZO_HAVE_MM_HUGE_PTR)
+#    define LZO_CCAST(t,e)                  ((t) (e))
+#  endif
+#endif
+#if !defined(LZO_CCAST)
+#  define LZO_CCAST(t,e)                    LZO_STATIC_CAST(t, LZO_STATIC_CAST(const void *, e))
+#endif
+#if !defined(LZO_ICONV)
+#  define LZO_ICONV(t,e)                    LZO_STATIC_CAST(t, e)
+#endif
+#if !defined(LZO_ICAST)
+#  define LZO_ICAST(t,e)                    LZO_STATIC_CAST(t, e)
+#endif
+#if !defined(LZO_ITRUNC)
+#  define LZO_ITRUNC(t,e)                   LZO_STATIC_CAST(t, e)
+#endif
+#if !defined(__lzo_cte)
+#  if (LZO_CC_MSC || LZO_CC_WATCOMC)
+#    define __lzo_cte(e)            ((void)0,(e))
+#  elif 1
+#    define __lzo_cte(e)            ((void)0,(e))
+#  endif
+#endif
+#if !defined(__lzo_cte)
+#  define __lzo_cte(e)              (e)
+#endif
+#if !defined(LZO_BLOCK_BEGIN)
+#  define LZO_BLOCK_BEGIN           do {
+#  define LZO_BLOCK_END             } while __lzo_cte(0)
+#endif
+#if !defined(LZO_UNUSED)
+#  if (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0600))
+#    define LZO_UNUSED(var)         ((void) &var)
+#  elif (LZO_CC_BORLANDC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PELLESC || LZO_CC_TURBOC)
+#    define LZO_UNUSED(var)         if (&var) ; else
+#  elif (LZO_CC_CLANG && (LZO_CC_CLANG >= 0x030200ul))
+#    define LZO_UNUSED(var)         ((void) &var)
+#  elif (LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#    define LZO_UNUSED(var)         ((void) var)
+#  elif (LZO_CC_MSC && (_MSC_VER < 900))
+#    define LZO_UNUSED(var)         if (&var) ; else
+#  elif (LZO_CC_KEILC)
+#    define LZO_UNUSED(var)         {LZO_EXTERN_C int lzo_unused__[1-2*!(sizeof(var)>0)];}
+#  elif (LZO_CC_PACIFICC)
+#    define LZO_UNUSED(var)         ((void) sizeof(var))
+#  elif (LZO_CC_WATCOMC) && defined(__cplusplus)
+#    define LZO_UNUSED(var)         ((void) var)
+#  else
+#    define LZO_UNUSED(var)         ((void) &var)
+#  endif
+#endif
+#if !defined(LZO_UNUSED_FUNC)
+#  if (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0600))
+#    define LZO_UNUSED_FUNC(func)   ((void) func)
+#  elif (LZO_CC_BORLANDC || LZO_CC_NDPC || LZO_CC_TURBOC)
+#    define LZO_UNUSED_FUNC(func)   if (func) ; else
+#  elif (LZO_CC_CLANG || LZO_CC_LLVM)
+#    define LZO_UNUSED_FUNC(func)   ((void) &func)
+#  elif (LZO_CC_MSC && (_MSC_VER < 900))
+#    define LZO_UNUSED_FUNC(func)   if (func) ; else
+#  elif (LZO_CC_MSC)
+#    define LZO_UNUSED_FUNC(func)   ((void) &func)
+#  elif (LZO_CC_KEILC || LZO_CC_PELLESC)
+#    define LZO_UNUSED_FUNC(func)   {LZO_EXTERN_C int lzo_unused_func__[1-2*!(sizeof((int)func)>0)];}
+#  else
+#    define LZO_UNUSED_FUNC(func)   ((void) func)
+#  endif
+#endif
+#if !defined(LZO_UNUSED_LABEL)
+#  if (LZO_CC_CLANG >= 0x020800ul)
+#    define LZO_UNUSED_LABEL(l)     (__lzo_gnuc_extension__ ((void) ((const void *) &&l)))
+#  elif (LZO_CC_ARMCC || LZO_CC_CLANG || LZO_CC_INTELC || LZO_CC_WATCOMC)
+#    define LZO_UNUSED_LABEL(l)     if __lzo_cte(0) goto l
+#  else
+#    define LZO_UNUSED_LABEL(l)     switch (0) case 1:goto l
+#  endif
+#endif
+#if !defined(LZO_DEFINE_UNINITIALIZED_VAR)
+#  if 0
+#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var
+#  elif 0 && (LZO_CC_GNUC)
+#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var = var
+#  else
+#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var = init
+#  endif
+#endif
+#if !defined(__lzo_inline)
+#if (LZO_CC_TURBOC && (__TURBOC__ <= 0x0295))
+#elif defined(__cplusplus)
+#  define __lzo_inline          inline
+#elif defined(__STDC_VERSION__) && (__STDC_VERSION__-0 >= 199901L)
+#  define __lzo_inline          inline
+#elif (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0550))
+#  define __lzo_inline          __inline
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CILLY || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
+#  define __lzo_inline          __inline__
+#elif (LZO_CC_DMC)
+#  define __lzo_inline          __inline
+#elif (LZO_CC_GHS)
+#  define __lzo_inline          __inline__
+#elif (LZO_CC_IBMC >= 600)
+#  define __lzo_inline          __inline__
+#elif (LZO_CC_INTELC)
+#  define __lzo_inline          __inline
+#elif (LZO_CC_MWERKS && (__MWERKS__ >= 0x2405))
+#  define __lzo_inline          __inline
+#elif (LZO_CC_MSC && (_MSC_VER >= 900))
+#  define __lzo_inline          __inline
+#elif (LZO_CC_SUNPROC >= 0x5100)
+#  define __lzo_inline          __inline__
+#endif
+#endif
+#if defined(__lzo_inline)
+#  ifndef __lzo_HAVE_inline
+#  define __lzo_HAVE_inline 1
+#  endif
+#else
+#  define __lzo_inline          /*empty*/
+#endif
+#if !defined(__lzo_forceinline)
+#if (LZO_CC_GNUC >= 0x030200ul)
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#elif (LZO_CC_IBMC >= 700)
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#elif (LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 450))
+#  define __lzo_forceinline     __forceinline
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 800))
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#elif (LZO_CC_MSC && (_MSC_VER >= 1200))
+#  define __lzo_forceinline     __forceinline
+#elif (LZO_CC_PGI >= 0x0d0a00ul)
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#elif (LZO_CC_SUNPROC >= 0x5100)
+#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
+#endif
+#endif
+#if defined(__lzo_forceinline)
+#  ifndef __lzo_HAVE_forceinline
+#  define __lzo_HAVE_forceinline 1
+#  endif
+#else
+#  define __lzo_forceinline     __lzo_inline
+#endif
+#if !defined(__lzo_noinline)
+#if 1 && (LZO_ARCH_I386) && (LZO_CC_GNUC >= 0x040000ul) && (LZO_CC_GNUC < 0x040003ul)
+#  define __lzo_noinline        __attribute__((__noinline__,__used__))
+#elif (LZO_CC_GNUC >= 0x030200ul)
+#  define __lzo_noinline        __attribute__((__noinline__))
+#elif (LZO_CC_IBMC >= 700)
+#  define __lzo_noinline        __attribute__((__noinline__))
+#elif (LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 600))
+#  define __lzo_noinline        __declspec(noinline)
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 800))
+#  define __lzo_noinline        __attribute__((__noinline__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_noinline        __attribute__((__noinline__))
+#elif (LZO_CC_MSC && (_MSC_VER >= 1300))
+#  define __lzo_noinline        __declspec(noinline)
+#elif (LZO_CC_MWERKS && (__MWERKS__ >= 0x3200) && (LZO_OS_WIN32 || LZO_OS_WIN64))
+#  if defined(__cplusplus)
+#  else
+#    define __lzo_noinline      __declspec(noinline)
+#  endif
+#elif (LZO_CC_PGI >= 0x0d0a00ul)
+#  define __lzo_noinline        __attribute__((__noinline__))
+#elif (LZO_CC_SUNPROC >= 0x5100)
+#  define __lzo_noinline        __attribute__((__noinline__))
+#endif
+#endif
+#if defined(__lzo_noinline)
+#  ifndef __lzo_HAVE_noinline
+#  define __lzo_HAVE_noinline 1
+#  endif
+#else
+#  define __lzo_noinline        /*empty*/
+#endif
+#if (__lzo_HAVE_forceinline || __lzo_HAVE_noinline) && !(__lzo_HAVE_inline)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if !defined(__lzo_static_inline)
+#if (LZO_CC_IBMC)
+#  define __lzo_static_inline       __lzo_gnuc_extension__ static __lzo_inline
+#endif
+#endif
+#if !defined(__lzo_static_inline)
+#  define __lzo_static_inline       static __lzo_inline
+#endif
+#if !defined(__lzo_static_forceinline)
+#if (LZO_CC_IBMC)
+#  define __lzo_static_forceinline  __lzo_gnuc_extension__ static __lzo_forceinline
+#endif
+#endif
+#if !defined(__lzo_static_forceinline)
+#  define __lzo_static_forceinline  static __lzo_forceinline
+#endif
+#if !defined(__lzo_static_noinline)
+#if (LZO_CC_IBMC)
+#  define __lzo_static_noinline     __lzo_gnuc_extension__ static __lzo_noinline
+#endif
+#endif
+#if !defined(__lzo_static_noinline)
+#  define __lzo_static_noinline     static __lzo_noinline
+#endif
+#if !defined(__lzo_c99_extern_inline)
+#if defined(__GNUC_GNU_INLINE__)
+#  define __lzo_c99_extern_inline   __lzo_inline
+#elif defined(__GNUC_STDC_INLINE__)
+#  define __lzo_c99_extern_inline   extern __lzo_inline
+#elif defined(__STDC_VERSION__) && (__STDC_VERSION__-0 >= 199901L)
+#  define __lzo_c99_extern_inline   extern __lzo_inline
+#endif
+#if !defined(__lzo_c99_extern_inline) && (__lzo_HAVE_inline)
+#  define __lzo_c99_extern_inline   __lzo_inline
+#endif
+#endif
+#if defined(__lzo_c99_extern_inline)
+#  ifndef __lzo_HAVE_c99_extern_inline
+#  define __lzo_HAVE_c99_extern_inline 1
+#  endif
+#else
+#  define __lzo_c99_extern_inline   /*empty*/
+#endif
+#if !defined(__lzo_may_alias)
+#if (LZO_CC_GNUC >= 0x030400ul)
+#  define __lzo_may_alias       __attribute__((__may_alias__))
+#elif (LZO_CC_CLANG >= 0x020900ul)
+#  define __lzo_may_alias       __attribute__((__may_alias__))
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 1210)) && 0
+#  define __lzo_may_alias       __attribute__((__may_alias__))
+#elif (LZO_CC_PGI >= 0x0d0a00ul) && 0
+#  define __lzo_may_alias       __attribute__((__may_alias__))
+#endif
+#endif
+#if defined(__lzo_may_alias)
+#  ifndef __lzo_HAVE_may_alias
+#  define __lzo_HAVE_may_alias 1
+#  endif
+#else
+#  define __lzo_may_alias       /*empty*/
+#endif
+#if !defined(__lzo_noreturn)
+#if (LZO_CC_GNUC >= 0x020700ul)
+#  define __lzo_noreturn        __attribute__((__noreturn__))
+#elif (LZO_CC_IBMC >= 700)
+#  define __lzo_noreturn        __attribute__((__noreturn__))
+#elif (LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 450))
+#  define __lzo_noreturn        __declspec(noreturn)
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 600))
+#  define __lzo_noreturn        __attribute__((__noreturn__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_noreturn        __attribute__((__noreturn__))
+#elif (LZO_CC_MSC && (_MSC_VER >= 1200))
+#  define __lzo_noreturn        __declspec(noreturn)
+#elif (LZO_CC_PGI >= 0x0d0a00ul)
+#  define __lzo_noreturn        __attribute__((__noreturn__))
+#endif
+#endif
+#if defined(__lzo_noreturn)
+#  ifndef __lzo_HAVE_noreturn
+#  define __lzo_HAVE_noreturn 1
+#  endif
+#else
+#  define __lzo_noreturn        /*empty*/
+#endif
+#if !defined(__lzo_nothrow)
+#if (LZO_CC_GNUC >= 0x030300ul)
+#  define __lzo_nothrow         __attribute__((__nothrow__))
+#elif (LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 450)) && defined(__cplusplus)
+#  define __lzo_nothrow         __declspec(nothrow)
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 900))
+#  define __lzo_nothrow         __attribute__((__nothrow__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_nothrow         __attribute__((__nothrow__))
+#elif (LZO_CC_MSC && (_MSC_VER >= 1200)) && defined(__cplusplus)
+#  define __lzo_nothrow         __declspec(nothrow)
+#endif
+#endif
+#if defined(__lzo_nothrow)
+#  ifndef __lzo_HAVE_nothrow
+#  define __lzo_HAVE_nothrow 1
+#  endif
+#else
+#  define __lzo_nothrow         /*empty*/
+#endif
+#if !defined(__lzo_restrict)
+#if (LZO_CC_GNUC >= 0x030400ul)
+#  define __lzo_restrict        __restrict__
+#elif (LZO_CC_IBMC >= 800) && !defined(__cplusplus)
+#  define __lzo_restrict        __restrict__
+#elif (LZO_CC_IBMC >= 1210)
+#  define __lzo_restrict        __restrict__
+#elif (LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 600))
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 600))
+#  define __lzo_restrict        __restrict__
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM)
+#  define __lzo_restrict        __restrict__
+#elif (LZO_CC_MSC && (_MSC_VER >= 1400))
+#  define __lzo_restrict        __restrict
+#elif (LZO_CC_PGI >= 0x0d0a00ul)
+#  define __lzo_restrict        __restrict__
+#endif
+#endif
+#if defined(__lzo_restrict)
+#  ifndef __lzo_HAVE_restrict
+#  define __lzo_HAVE_restrict 1
+#  endif
+#else
+#  define __lzo_restrict        /*empty*/
+#endif
+#if !defined(__lzo_alignof)
+#if (LZO_CC_ARMCC || LZO_CC_CILLY || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
+#  define __lzo_alignof(e)      __alignof__(e)
+#elif (LZO_CC_GHS) && !defined(__cplusplus)
+#  define __lzo_alignof(e)      __alignof__(e)
+#elif (LZO_CC_IBMC >= 600)
+#  define __lzo_alignof(e)      (__lzo_gnuc_extension__ __alignof__(e))
+#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 700))
+#  define __lzo_alignof(e)      __alignof__(e)
+#elif (LZO_CC_MSC && (_MSC_VER >= 1300))
+#  define __lzo_alignof(e)      __alignof(e)
+#elif (LZO_CC_SUNPROC >= 0x5100)
+#  define __lzo_alignof(e)      __alignof__(e)
+#endif
+#endif
+#if defined(__lzo_alignof)
+#  ifndef __lzo_HAVE_alignof
+#  define __lzo_HAVE_alignof 1
+#  endif
+#endif
+#if !defined(__lzo_struct_packed)
+#if   (LZO_CC_CLANG && (LZO_CC_CLANG < 0x020800ul)) && defined(__cplusplus)
+#elif (LZO_CC_GNUC && (LZO_CC_GNUC < 0x020700ul))
+#elif (LZO_CC_GNUC && (LZO_CC_GNUC < 0x020800ul)) && defined(__cplusplus)
+#elif (LZO_CC_PCC && (LZO_CC_PCC < 0x010100ul))
+#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC < 0x5110)) && !defined(__cplusplus)
+#elif (LZO_CC_GNUC >= 0x030400ul) && !(LZO_CC_PCC_GNUC) && (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+#  define __lzo_struct_packed(s)        struct s {
+#  define __lzo_struct_packed_end()     } __attribute__((__gcc_struct__,__packed__));
+#  define __lzo_struct_packed_ma_end()  } __lzo_may_alias __attribute__((__gcc_struct__,__packed__));
+#elif (LZO_CC_ARMCC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || (LZO_CC_PGI >= 0x0d0a00ul) || (LZO_CC_SUNPROC >= 0x5100))
+#  define __lzo_struct_packed(s)        struct s {
+#  define __lzo_struct_packed_end()     } __attribute__((__packed__));
+#  define __lzo_struct_packed_ma_end()  } __lzo_may_alias __attribute__((__packed__));
+#elif (LZO_CC_IBMC >= 700)
+#  define __lzo_struct_packed(s)        __lzo_gnuc_extension__ struct s {
+#  define __lzo_struct_packed_end()     } __attribute__((__packed__));
+#  define __lzo_struct_packed_ma_end()  } __lzo_may_alias __attribute__((__packed__));
+#elif (LZO_CC_INTELC_MSC) || (LZO_CC_MSC && (_MSC_VER >= 1300))
+#  define __lzo_struct_packed(s)        __pragma(pack(push,1)) struct s {
+#  define __lzo_struct_packed_end()     } __pragma(pack(pop));
+#elif (LZO_CC_WATCOMC && (__WATCOMC__ >= 900))
+#  define __lzo_struct_packed(s)        _Packed struct s {
+#  define __lzo_struct_packed_end()     };
+#endif
+#endif
+#if defined(__lzo_struct_packed) && !defined(__lzo_struct_packed_ma)
+#  define __lzo_struct_packed_ma(s)     __lzo_struct_packed(s)
+#endif
+#if defined(__lzo_struct_packed_end) && !defined(__lzo_struct_packed_ma_end)
+#  define __lzo_struct_packed_ma_end()  __lzo_struct_packed_end()
+#endif
+#if !defined(__lzo_byte_struct)
+#if defined(__lzo_struct_packed)
+#  define __lzo_byte_struct(s,n)        __lzo_struct_packed(s) unsigned char a[n]; __lzo_struct_packed_end()
+#  define __lzo_byte_struct_ma(s,n)     __lzo_struct_packed_ma(s) unsigned char a[n]; __lzo_struct_packed_ma_end()
+#elif (LZO_CC_CILLY || LZO_CC_CLANG || LZO_CC_PGI || (LZO_CC_SUNPROC >= 0x5100))
+#  define __lzo_byte_struct(s,n)        struct s { unsigned char a[n]; } __attribute__((__packed__));
+#  define __lzo_byte_struct_ma(s,n)     struct s { unsigned char a[n]; } __lzo_may_alias __attribute__((__packed__));
+#endif
+#endif
+#if defined(__lzo_byte_struct) &&  !defined(__lzo_byte_struct_ma)
+#  define __lzo_byte_struct_ma(s,n)     __lzo_byte_struct(s,n)
+#endif
+#if !defined(__lzo_struct_align16) && (__lzo_HAVE_alignof)
+#if (LZO_CC_GNUC && (LZO_CC_GNUC < 0x030000ul))
+#elif (LZO_CC_CLANG && (LZO_CC_CLANG < 0x020800ul)) && defined(__cplusplus)
+#elif (LZO_CC_CILLY || LZO_CC_PCC)
+#elif (LZO_CC_INTELC_MSC) || (LZO_CC_MSC && (_MSC_VER >= 1300))
+#  define __lzo_struct_align16(s)       struct __declspec(align(16)) s {
+#  define __lzo_struct_align16_end()    };
+#  define __lzo_struct_align32(s)       struct __declspec(align(32)) s {
+#  define __lzo_struct_align32_end()    };
+#  define __lzo_struct_align64(s)       struct __declspec(align(64)) s {
+#  define __lzo_struct_align64_end()    };
+#elif (LZO_CC_ARMCC || LZO_CC_CLANG || LZO_CC_GNUC || (LZO_CC_IBMC >= 700) || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_struct_align16(s)       struct s {
+#  define __lzo_struct_align16_end()    } __attribute__((__aligned__(16)));
+#  define __lzo_struct_align32(s)       struct s {
+#  define __lzo_struct_align32_end()    } __attribute__((__aligned__(32)));
+#  define __lzo_struct_align64(s)       struct s {
+#  define __lzo_struct_align64_end()    } __attribute__((__aligned__(64)));
+#endif
+#endif
+#if !defined(__lzo_union_um)
+#if   (LZO_CC_CLANG && (LZO_CC_CLANG < 0x020800ul)) && defined(__cplusplus)
+#elif (LZO_CC_GNUC && (LZO_CC_GNUC < 0x020700ul))
+#elif (LZO_CC_GNUC && (LZO_CC_GNUC < 0x020800ul)) && defined(__cplusplus)
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER < 810))
+#elif (LZO_CC_PCC && (LZO_CC_PCC < 0x010100ul))
+#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC < 0x5110)) && !defined(__cplusplus)
+#elif (LZO_CC_ARMCC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || (LZO_CC_PGI >= 0x0d0a00ul) || (LZO_CC_SUNPROC >= 0x5100))
+#  define __lzo_union_am(s)             union s {
+#  define __lzo_union_am_end()          } __lzo_may_alias;
+#  define __lzo_union_um(s)             union s {
+#  define __lzo_union_um_end()          } __lzo_may_alias __attribute__((__packed__));
+#elif (LZO_CC_IBMC >= 700)
+#  define __lzo_union_am(s)             __lzo_gnuc_extension__ union s {
+#  define __lzo_union_am_end()          } __lzo_may_alias;
+#  define __lzo_union_um(s)             __lzo_gnuc_extension__ union s {
+#  define __lzo_union_um_end()          } __lzo_may_alias __attribute__((__packed__));
+#elif (LZO_CC_INTELC_MSC) || (LZO_CC_MSC && (_MSC_VER >= 1300))
+#  define __lzo_union_um(s)             __pragma(pack(push,1)) union s {
+#  define __lzo_union_um_end()          } __pragma(pack(pop));
+#elif (LZO_CC_WATCOMC && (__WATCOMC__ >= 900))
+#  define __lzo_union_um(s)             _Packed union s {
+#  define __lzo_union_um_end()          };
+#endif
+#endif
+#if !defined(__lzo_union_am)
+#  define __lzo_union_am(s)             union s {
+#  define __lzo_union_am_end()          };
+#endif
+#if !defined(__lzo_constructor)
+#if (LZO_CC_GNUC >= 0x030400ul)
+#  define __lzo_constructor     __attribute__((__constructor__,__used__))
+#elif (LZO_CC_GNUC >= 0x020700ul)
+#  define __lzo_constructor     __attribute__((__constructor__))
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 800))
+#  define __lzo_constructor     __attribute__((__constructor__,__used__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_constructor     __attribute__((__constructor__))
+#endif
+#endif
+#if defined(__lzo_constructor)
+#  ifndef __lzo_HAVE_constructor
+#  define __lzo_HAVE_constructor 1
+#  endif
+#endif
+#if !defined(__lzo_destructor)
+#if (LZO_CC_GNUC >= 0x030400ul)
+#  define __lzo_destructor      __attribute__((__destructor__,__used__))
+#elif (LZO_CC_GNUC >= 0x020700ul)
+#  define __lzo_destructor      __attribute__((__destructor__))
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 800))
+#  define __lzo_destructor      __attribute__((__destructor__,__used__))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_destructor      __attribute__((__destructor__))
+#endif
+#endif
+#if defined(__lzo_destructor)
+#  ifndef __lzo_HAVE_destructor
+#  define __lzo_HAVE_destructor 1
+#  endif
+#endif
+#if (__lzo_HAVE_destructor) && !(__lzo_HAVE_constructor)
+#  error "unexpected configuration - check your compiler defines"
+#endif
+#if !defined(__lzo_likely) && !defined(__lzo_unlikely)
+#if (LZO_CC_GNUC >= 0x030200ul)
+#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
+#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
+#elif (LZO_CC_IBMC >= 1010)
+#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
+#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
+#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 800))
+#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
+#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
+#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
+#endif
+#endif
+#if defined(__lzo_likely)
+#  ifndef __lzo_HAVE_likely
+#  define __lzo_HAVE_likely 1
+#  endif
+#else
+#  define __lzo_likely(e)       (e)
+#endif
+#if defined(__lzo_unlikely)
+#  ifndef __lzo_HAVE_unlikely
+#  define __lzo_HAVE_unlikely 1
+#  endif
+#else
+#  define __lzo_unlikely(e)     (e)
+#endif
+#if !defined(__lzo_static_unused_void_func)
+#  if 1 && (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || (LZO_CC_GNUC >= 0x020700ul) || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
+#    define __lzo_static_unused_void_func(f)    static void __attribute__((__unused__)) f(void)
+#  else
+#    define __lzo_static_unused_void_func(f)    static __lzo_inline void f(void)
+#  endif
+#endif
+#if !defined(__lzo_loop_forever)
+#  if (LZO_CC_IBMC)
+#    define __lzo_loop_forever()    LZO_BLOCK_BEGIN for (;;) { ; } LZO_BLOCK_END
+#  else
+#    define __lzo_loop_forever()    do { ; } while __lzo_cte(1)
+#  endif
+#endif
+#if !defined(__lzo_unreachable)
+#if (LZO_CC_CLANG && (LZO_CC_CLANG >= 0x020800ul))
+#  define __lzo_unreachable()       __builtin_unreachable();
+#elif (LZO_CC_GNUC >= 0x040500ul)
+#  define __lzo_unreachable()       __builtin_unreachable();
+#elif (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 1300)) && 1
+#  define __lzo_unreachable()       __builtin_unreachable();
+#endif
+#endif
+#if defined(__lzo_unreachable)
+#  ifndef __lzo_HAVE_unreachable
+#  define __lzo_HAVE_unreachable 1
+#  endif
+#else
+#  if 0
+#  define __lzo_unreachable()       ((void)0);
+#  else
+#  define __lzo_unreachable()       __lzo_loop_forever();
+#  endif
+#endif
+#ifndef __LZO_CTA_NAME
+#if (LZO_CFG_USE_COUNTER)
+#  define __LZO_CTA_NAME(a)         LZO_PP_ECONCAT2(a,__COUNTER__)
+#else
+#  define __LZO_CTA_NAME(a)         LZO_PP_ECONCAT2(a,__LINE__)
+#endif
+#endif
+#if !defined(LZO_COMPILE_TIME_ASSERT_HEADER)
+#  if (LZO_CC_AZTECC || LZO_CC_ZORTECHC)
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN extern int __LZO_CTA_NAME(lzo_cta__)[1-!(e)]; LZO_EXTERN_C_END
+#  elif (LZO_CC_DMC || LZO_CC_SYMANTECC)
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN extern int __LZO_CTA_NAME(lzo_cta__)[1u-2*!(e)]; LZO_EXTERN_C_END
+#  elif (LZO_CC_TURBOC && (__TURBOC__ == 0x0295))
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN extern int __LZO_CTA_NAME(lzo_cta__)[1-!(e)]; LZO_EXTERN_C_END
+#  elif (LZO_CC_CLANG && (LZO_CC_CLANG < 0x020900ul)) && defined(__cplusplus)
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN int __LZO_CTA_NAME(lzo_cta_f__)(int [1-2*!(e)]); LZO_EXTERN_C_END
+#  elif (LZO_CC_GNUC) && defined(__CHECKER__) && defined(__SPARSE_CHECKER__)
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN enum {__LZO_CTA_NAME(lzo_cta_e__)=1/!!(e)} __attribute__((__unused__)); LZO_EXTERN_C_END
+#  else
+#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  LZO_EXTERN_C_BEGIN extern int __LZO_CTA_NAME(lzo_cta__)[1-2*!(e)]; LZO_EXTERN_C_END
+#  endif
+#endif
+#if !defined(LZO_COMPILE_TIME_ASSERT)
+#  if (LZO_CC_AZTECC)
+#    define LZO_COMPILE_TIME_ASSERT(e)  {typedef int __LZO_CTA_NAME(lzo_cta_t__)[1-!(e)];}
+#  elif (LZO_CC_DMC || LZO_CC_PACIFICC || LZO_CC_SYMANTECC || LZO_CC_ZORTECHC)
+#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
+#  elif (LZO_CC_GNUC) && defined(__CHECKER__) && defined(__SPARSE_CHECKER__)
+#    define LZO_COMPILE_TIME_ASSERT(e)  {(void) (0/!!(e));}
+#  elif (LZO_CC_GNUC >= 0x040700ul) && (LZO_CFG_USE_COUNTER) && defined(__cplusplus)
+#    define LZO_COMPILE_TIME_ASSERT(e)  {enum {__LZO_CTA_NAME(lzo_cta_e__)=1/!!(e)} __attribute__((__unused__));}
+#  elif (LZO_CC_GNUC >= 0x040700ul)
+#    define LZO_COMPILE_TIME_ASSERT(e)  {typedef int __LZO_CTA_NAME(lzo_cta_t__)[1-2*!(e)] __attribute__((__unused__));}
+#  elif (LZO_CC_MSC && (_MSC_VER < 900))
+#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
+#  elif (LZO_CC_TURBOC && (__TURBOC__ == 0x0295))
+#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
+#  else
+#    define LZO_COMPILE_TIME_ASSERT(e)  {typedef int __LZO_CTA_NAME(lzo_cta_t__)[1-2*!(e)];}
+#  endif
+#endif
+LZO_COMPILE_TIME_ASSERT_HEADER(1 == 1)
+#if defined(__cplusplus)
+extern "C" { LZO_COMPILE_TIME_ASSERT_HEADER(2 == 2) }
+#endif
+LZO_COMPILE_TIME_ASSERT_HEADER(3 == 3)
+#if (LZO_ARCH_I086 || LZO_ARCH_I386) && (LZO_OS_DOS16 || LZO_OS_DOS32 || LZO_OS_OS2 || LZO_OS_OS216 || LZO_OS_WIN16 || LZO_OS_WIN32 || LZO_OS_WIN64)
+#  if (LZO_CC_GNUC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PACIFICC)
+#  elif (LZO_CC_DMC || LZO_CC_SYMANTECC || LZO_CC_ZORTECHC)
+#    define __lzo_cdecl                 __cdecl
+#    define __lzo_cdecl_atexit          /*empty*/
+#    define __lzo_cdecl_main            __cdecl
+#    if (LZO_OS_OS2 && (LZO_CC_DMC || LZO_CC_SYMANTECC))
+#      define __lzo_cdecl_qsort         __pascal
+#    elif (LZO_OS_OS2 && (LZO_CC_ZORTECHC))
+#      define __lzo_cdecl_qsort         _stdcall
+#    else
+#      define __lzo_cdecl_qsort         __cdecl
+#    endif
+#  elif (LZO_CC_WATCOMC)
+#    define __lzo_cdecl                 __cdecl
+#  else
+#    define __lzo_cdecl                 __cdecl
+#    define __lzo_cdecl_atexit          __cdecl
+#    define __lzo_cdecl_main            __cdecl
+#    define __lzo_cdecl_qsort           __cdecl
+#  endif
+#  if (LZO_CC_GNUC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PACIFICC || LZO_CC_WATCOMC)
+#  elif (LZO_OS_OS2 && (LZO_CC_DMC || LZO_CC_SYMANTECC))
+#    define __lzo_cdecl_sighandler      __pascal
+#  elif (LZO_OS_OS2 && (LZO_CC_ZORTECHC))
+#    define __lzo_cdecl_sighandler      _stdcall
+#  elif (LZO_CC_MSC && (_MSC_VER >= 1400)) && defined(_M_CEE_PURE)
+#    define __lzo_cdecl_sighandler      __clrcall
+#  elif (LZO_CC_MSC && (_MSC_VER >= 600 && _MSC_VER < 700))
+#    if defined(_DLL)
+#      define __lzo_cdecl_sighandler    _far _cdecl _loadds
+#    elif defined(_MT)
+#      define __lzo_cdecl_sighandler    _far _cdecl
+#    else
+#      define __lzo_cdecl_sighandler    _cdecl
+#    endif
+#  else
+#    define __lzo_cdecl_sighandler      __cdecl
+#  endif
+#elif (LZO_ARCH_I386) && (LZO_CC_WATCOMC)
+#  define __lzo_cdecl                   __cdecl
+#elif (LZO_ARCH_M68K && LZO_OS_TOS && (LZO_CC_PUREC || LZO_CC_TURBOC))
+#  define __lzo_cdecl                   cdecl
+#endif
+#if !defined(__lzo_cdecl)
+#  define __lzo_cdecl                   /*empty*/
+#endif
+#if !defined(__lzo_cdecl_atexit)
+#  define __lzo_cdecl_atexit            /*empty*/
+#endif
+#if !defined(__lzo_cdecl_main)
+#  define __lzo_cdecl_main              /*empty*/
+#endif
+#if !defined(__lzo_cdecl_qsort)
+#  define __lzo_cdecl_qsort             /*empty*/
+#endif
+#if !defined(__lzo_cdecl_sighandler)
+#  define __lzo_cdecl_sighandler        /*empty*/
+#endif
+#if !defined(__lzo_cdecl_va)
+#  define __lzo_cdecl_va                __lzo_cdecl
+#endif
+#if !(LZO_CFG_NO_WINDOWS_H)
+#if !defined(LZO_HAVE_WINDOWS_H)
+#if (LZO_OS_CYGWIN || (LZO_OS_EMX && defined(__RSXNT__)) || LZO_OS_WIN32 || LZO_OS_WIN64)
+#  if (LZO_CC_WATCOMC && (__WATCOMC__ < 1000))
+#  elif (LZO_OS_WIN32 && LZO_CC_GNUC) && defined(__PW32__)
+#  elif ((LZO_OS_CYGWIN || defined(__MINGW32__)) && (LZO_CC_GNUC && (LZO_CC_GNUC < 0x025f00ul)))
+#  else
+#    define LZO_HAVE_WINDOWS_H 1
+#  endif
+#endif
+#endif
+#endif
+#ifndef LZO_SIZEOF_SHORT
 #if defined(SIZEOF_SHORT)
 #  define LZO_SIZEOF_SHORT          (SIZEOF_SHORT)
-#endif
+#elif defined(__SIZEOF_SHORT__)
+#  define LZO_SIZEOF_SHORT          (__SIZEOF_SHORT__)
+#endif
+#endif
+#ifndef LZO_SIZEOF_INT
 #if defined(SIZEOF_INT)
 #  define LZO_SIZEOF_INT            (SIZEOF_INT)
-#endif
+#elif defined(__SIZEOF_INT__)
+#  define LZO_SIZEOF_INT            (__SIZEOF_INT__)
+#endif
+#endif
+#ifndef LZO_SIZEOF_LONG
 #if defined(SIZEOF_LONG)
 #  define LZO_SIZEOF_LONG           (SIZEOF_LONG)
-#endif
+#elif defined(__SIZEOF_LONG__)
+#  define LZO_SIZEOF_LONG           (__SIZEOF_LONG__)
+#endif
+#endif
+#ifndef LZO_SIZEOF_LONG_LONG
 #if defined(SIZEOF_LONG_LONG)
 #  define LZO_SIZEOF_LONG_LONG      (SIZEOF_LONG_LONG)
-#endif
+#elif defined(__SIZEOF_LONG_LONG__)
+#  define LZO_SIZEOF_LONG_LONG      (__SIZEOF_LONG_LONG__)
+#endif
+#endif
+#ifndef LZO_SIZEOF___INT16
 #if defined(SIZEOF___INT16)
 #  define LZO_SIZEOF___INT16        (SIZEOF___INT16)
 #endif
+#endif
+#ifndef LZO_SIZEOF___INT32
 #if defined(SIZEOF___INT32)
 #  define LZO_SIZEOF___INT32        (SIZEOF___INT32)
 #endif
+#endif
+#ifndef LZO_SIZEOF___INT64
 #if defined(SIZEOF___INT64)
 #  define LZO_SIZEOF___INT64        (SIZEOF___INT64)
 #endif
+#endif
+#ifndef LZO_SIZEOF_VOID_P
 #if defined(SIZEOF_VOID_P)
 #  define LZO_SIZEOF_VOID_P         (SIZEOF_VOID_P)
-#endif
+#elif defined(__SIZEOF_POINTER__)
+#  define LZO_SIZEOF_VOID_P         (__SIZEOF_POINTER__)
+#endif
+#endif
+#ifndef LZO_SIZEOF_SIZE_T
 #if defined(SIZEOF_SIZE_T)
 #  define LZO_SIZEOF_SIZE_T         (SIZEOF_SIZE_T)
-#endif
+#elif defined(__SIZEOF_SIZE_T__)
+#  define LZO_SIZEOF_SIZE_T         (__SIZEOF_SIZE_T__)
+#endif
+#endif
+#ifndef LZO_SIZEOF_PTRDIFF_T
 #if defined(SIZEOF_PTRDIFF_T)
 #  define LZO_SIZEOF_PTRDIFF_T      (SIZEOF_PTRDIFF_T)
+#elif defined(__SIZEOF_PTRDIFF_T__)
+#  define LZO_SIZEOF_PTRDIFF_T      (__SIZEOF_PTRDIFF_T__)
+#endif
 #endif
 #define __LZO_LSR(x,b)    (((x)+0ul) >> (b))
 #if !defined(LZO_SIZEOF_SHORT)
@@ -1079,6 +2060,7 @@
 #    error "LZO_SIZEOF_SHORT"
 #  endif
 #endif
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_SHORT == sizeof(short))
 #if !defined(LZO_SIZEOF_INT)
 #  if (LZO_ARCH_CRAY_PVP)
 #    define LZO_SIZEOF_INT          8
@@ -1100,6 +2082,7 @@
 #    error "LZO_SIZEOF_INT"
 #  endif
 #endif
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_INT == sizeof(int))
 #if !defined(LZO_SIZEOF_LONG)
 #  if (ULONG_MAX == LZO_0xffffffffL)
 #    define LZO_SIZEOF_LONG         4
@@ -1109,6 +2092,8 @@
 #    define LZO_SIZEOF_LONG         2
 #  elif (__LZO_LSR(ULONG_MAX,31) == 1)
 #    define LZO_SIZEOF_LONG         4
+#  elif (__LZO_LSR(ULONG_MAX,39) == 1)
+#    define LZO_SIZEOF_LONG         5
 #  elif (__LZO_LSR(ULONG_MAX,63) == 1)
 #    define LZO_SIZEOF_LONG         8
 #  elif (__LZO_LSR(ULONG_MAX,127) == 1)
@@ -1117,11 +2102,12 @@
 #    error "LZO_SIZEOF_LONG"
 #  endif
 #endif
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_LONG == sizeof(long))
 #if !defined(LZO_SIZEOF_LONG_LONG) && !defined(LZO_SIZEOF___INT64)
 #if (LZO_SIZEOF_LONG > 0 && LZO_SIZEOF_LONG < 8)
 #  if defined(__LONG_MAX__) && defined(__LONG_LONG_MAX__)
 #    if (LZO_CC_GNUC >= 0x030300ul)
-#      if ((__LONG_MAX__)+0 == (__LONG_LONG_MAX__)+0)
+#      if ((__LONG_MAX__-0) == (__LONG_LONG_MAX__-0))
 #        define LZO_SIZEOF_LONG_LONG      LZO_SIZEOF_LONG
 #      elif (__LZO_LSR(__LONG_LONG_MAX__,30) == 1)
 #        define LZO_SIZEOF_LONG_LONG      4
@@ -1135,7 +2121,7 @@
 #if (LZO_ARCH_I086 && LZO_CC_DMC)
 #elif (LZO_CC_CILLY) && defined(__GNUC__)
 #  define LZO_SIZEOF_LONG_LONG      8
-#elif (LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
+#elif (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
 #  define LZO_SIZEOF_LONG_LONG      8
 #elif ((LZO_OS_WIN32 || LZO_OS_WIN64 || defined(_WIN32)) && LZO_CC_MSC && (_MSC_VER >= 1400))
 #  define LZO_SIZEOF_LONG_LONG      8
@@ -1157,11 +2143,13 @@
 #  define LZO_SIZEOF___INT64        8
 #elif (LZO_ARCH_I386 && (LZO_CC_WATCOMC && (__WATCOMC__ >= 1100)))
 #  define LZO_SIZEOF___INT64        8
-#elif (LZO_CC_WATCOMC && defined(_INTEGRAL_MAX_BITS) && (_INTEGRAL_MAX_BITS == 64))
+#elif (LZO_CC_GHS && defined(__LLONG_BIT) && ((__LLONG_BIT-0) == 64))
+#  define LZO_SIZEOF_LONG_LONG      8
+#elif (LZO_CC_WATCOMC && defined(_INTEGRAL_MAX_BITS) && ((_INTEGRAL_MAX_BITS-0) == 64))
 #  define LZO_SIZEOF___INT64        8
 #elif (LZO_OS_OS400 || defined(__OS400__)) && defined(__LLP64_IFC__)
 #  define LZO_SIZEOF_LONG_LONG      8
-#elif (defined(__vms) || defined(__VMS)) && (__INITIAL_POINTER_SIZE+0 == 64)
+#elif (defined(__vms) || defined(__VMS)) && ((__INITIAL_POINTER_SIZE-0) == 64)
 #  define LZO_SIZEOF_LONG_LONG      8
 #elif (LZO_CC_SDCC) && (LZO_SIZEOF_INT == 2)
 #elif 1 && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
@@ -1174,87 +2162,127 @@
 #    undef LZO_SIZEOF_LONG_LONG
 #  endif
 #endif
-#if (LZO_CFG_NO_LONG_LONG) || defined(__NO_LONG_LONG)
+#if (LZO_CFG_NO_LONG_LONG)
 #  undef LZO_SIZEOF_LONG_LONG
+#elif defined(__NO_LONG_LONG)
+#  undef LZO_SIZEOF_LONG_LONG
+#elif defined(_NO_LONGLONG)
+#  undef LZO_SIZEOF_LONG_LONG
+#endif
+#if !defined(LZO_WORDSIZE)
+#if (LZO_ARCH_ALPHA)
+#  define LZO_WORDSIZE              8
+#elif (LZO_ARCH_AMD64)
+#  define LZO_WORDSIZE              8
+#elif (LZO_ARCH_AVR)
+#  define LZO_WORDSIZE              1
+#elif (LZO_ARCH_H8300)
+#  if defined(__NORMAL_MODE__)
+#    define LZO_WORDSIZE            4
+#  elif defined(__H8300H__) || defined(__H8300S__) || defined(__H8300SX__)
+#    define LZO_WORDSIZE            4
+#  else
+#    define LZO_WORDSIZE            2
+#  endif
+#elif (LZO_ARCH_I086)
+#  define LZO_WORDSIZE              2
+#elif (LZO_ARCH_IA64)
+#  define LZO_WORDSIZE              8
+#elif (LZO_ARCH_M16C)
+#  define LZO_WORDSIZE              2
+#elif (LZO_ARCH_SPU)
+#  define LZO_WORDSIZE              4
+#elif (LZO_ARCH_Z80)
+#  define LZO_WORDSIZE              1
+#elif (LZO_SIZEOF_LONG == 8) && ((defined(__mips__) && defined(__R5900__)) || defined(__MIPS_PSX2__))
+#  define LZO_WORDSIZE              8
+#elif (LZO_OS_OS400 || defined(__OS400__))
+#  define LZO_WORDSIZE              8
+#elif (defined(__vms) || defined(__VMS)) && (__INITIAL_POINTER_SIZE+0 == 64)
+#  define LZO_WORDSIZE              8
+#endif
 #endif
 #if !defined(LZO_SIZEOF_VOID_P)
-#if (LZO_ARCH_I086)
-#  define __LZO_WORDSIZE            2
+#if defined(__ILP32__) || defined(__ILP32) || defined(_ILP32)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(int)  == 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(long) == 4)
+#  define LZO_SIZEOF_VOID_P         4
+#elif defined(__ILP64__) || defined(__ILP64) || defined(_ILP64)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(int)  == 8)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(long) == 8)
+#  define LZO_SIZEOF_VOID_P         8
+#elif defined(__LLP64__) || defined(__LLP64) || defined(_LLP64) || defined(_WIN64)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(long) == 4)
+#  define LZO_SIZEOF_VOID_P         8
+#elif defined(__LP64__) || defined(__LP64) || defined(_LP64)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(long) == 8)
+#  define LZO_SIZEOF_VOID_P         8
+#elif (LZO_ARCH_AVR)
+#  define LZO_SIZEOF_VOID_P         2
+#elif (LZO_ARCH_C166 || LZO_ARCH_MCS51 || LZO_ARCH_MCS251 || LZO_ARCH_MSP430)
+#  define LZO_SIZEOF_VOID_P         2
+#elif (LZO_ARCH_H8300)
+#  if defined(__NORMAL_MODE__)
+#    define LZO_SIZEOF_VOID_P       2
+#  elif defined(__H8300H__) || defined(__H8300S__) || defined(__H8300SX__)
+#    define LZO_SIZEOF_VOID_P       4
+#  else
+#    define LZO_SIZEOF_VOID_P       2
+#  endif
+#  if (LZO_CC_GNUC && (LZO_CC_GNUC < 0x040000ul)) && (LZO_SIZEOF_INT == 4)
+#    define LZO_SIZEOF_SIZE_T       LZO_SIZEOF_INT
+#    define LZO_SIZEOF_PTRDIFF_T    LZO_SIZEOF_INT
+#  endif
+#elif (LZO_ARCH_I086)
 #  if (LZO_MM_TINY || LZO_MM_SMALL || LZO_MM_MEDIUM)
 #    define LZO_SIZEOF_VOID_P       2
 #  elif (LZO_MM_COMPACT || LZO_MM_LARGE || LZO_MM_HUGE)
 #    define LZO_SIZEOF_VOID_P       4
 #  else
-#    error "LZO_MM"
-#  endif
-#elif (LZO_ARCH_AVR || LZO_ARCH_Z80)
-#  define __LZO_WORDSIZE            1
-#  define LZO_SIZEOF_VOID_P         2
-#elif (LZO_ARCH_C166 || LZO_ARCH_MCS51 || LZO_ARCH_MCS251 || LZO_ARCH_MSP430)
-#  define LZO_SIZEOF_VOID_P         2
-#elif (LZO_ARCH_H8300)
-#  if defined(__NORMAL_MODE__)
-#    define __LZO_WORDSIZE          4
-#    define LZO_SIZEOF_VOID_P       2
-#  elif defined(__H8300H__) || defined(__H8300S__) || defined(__H8300SX__)
-#    define __LZO_WORDSIZE          4
-#    define LZO_SIZEOF_VOID_P       4
-#  else
-#    define __LZO_WORDSIZE          2
-#    define LZO_SIZEOF_VOID_P       2
-#  endif
-#  if (LZO_CC_GNUC && (LZO_CC_GNUC < 0x040000ul)) && (LZO_SIZEOF_INT == 4)
-#    define LZO_SIZEOF_SIZE_T       LZO_SIZEOF_INT
-#    define LZO_SIZEOF_PTRDIFF_T    LZO_SIZEOF_INT
+#    error "invalid LZO_ARCH_I086 memory model"
 #  endif
 #elif (LZO_ARCH_M16C)
-#  define __LZO_WORDSIZE            2
 #  if defined(__m32c_cpu__) || defined(__m32cm_cpu__)
 #    define LZO_SIZEOF_VOID_P       4
 #  else
 #    define LZO_SIZEOF_VOID_P       2
 #  endif
+#elif (LZO_ARCH_SPU)
+#  define LZO_SIZEOF_VOID_P         4
+#elif (LZO_ARCH_Z80)
+#  define LZO_SIZEOF_VOID_P         2
 #elif (LZO_SIZEOF_LONG == 8) && ((defined(__mips__) && defined(__R5900__)) || defined(__MIPS_PSX2__))
-#  define __LZO_WORDSIZE            8
 #  define LZO_SIZEOF_VOID_P         4
-#elif defined(__LLP64__) || defined(__LLP64) || defined(_LLP64) || defined(_WIN64)
-#  define __LZO_WORDSIZE            8
-#  define LZO_SIZEOF_VOID_P         8
-#elif (LZO_OS_OS400 || defined(__OS400__)) && defined(__LLP64_IFC__)
-#  define LZO_SIZEOF_VOID_P         LZO_SIZEOF_LONG
-#  define LZO_SIZEOF_SIZE_T         LZO_SIZEOF_LONG
-#  define LZO_SIZEOF_PTRDIFF_T      LZO_SIZEOF_LONG
 #elif (LZO_OS_OS400 || defined(__OS400__))
-#  define __LZO_WORDSIZE            LZO_SIZEOF_LONG
-#  define LZO_SIZEOF_VOID_P         16
-#  define LZO_SIZEOF_SIZE_T         LZO_SIZEOF_LONG
-#  define LZO_SIZEOF_PTRDIFF_T      LZO_SIZEOF_LONG
+#  if defined(__LLP64_IFC__)
+#    define LZO_SIZEOF_VOID_P       8
+#    define LZO_SIZEOF_SIZE_T       LZO_SIZEOF_LONG
+#    define LZO_SIZEOF_PTRDIFF_T    LZO_SIZEOF_LONG
+#  else
+#    define LZO_SIZEOF_VOID_P       16
+#    define LZO_SIZEOF_SIZE_T       LZO_SIZEOF_LONG
+#    define LZO_SIZEOF_PTRDIFF_T    LZO_SIZEOF_LONG
+#  endif
 #elif (defined(__vms) || defined(__VMS)) && (__INITIAL_POINTER_SIZE+0 == 64)
 #  define LZO_SIZEOF_VOID_P         8
 #  define LZO_SIZEOF_SIZE_T         LZO_SIZEOF_LONG
 #  define LZO_SIZEOF_PTRDIFF_T      LZO_SIZEOF_LONG
-#elif (LZO_ARCH_SPU)
-# if 0
-#  define __LZO_WORDSIZE            16
-# endif
-#  define LZO_SIZEOF_VOID_P         4
-#else
+#endif
+#endif
+#if !defined(LZO_SIZEOF_VOID_P)
 #  define LZO_SIZEOF_VOID_P         LZO_SIZEOF_LONG
 #endif
-#endif
-#if !defined(LZO_WORDSIZE)
-#  if defined(__LZO_WORDSIZE)
-#    define LZO_WORDSIZE            __LZO_WORDSIZE
-#  else
-#    define LZO_WORDSIZE            LZO_SIZEOF_VOID_P
-#  endif
-#endif
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_VOID_P == sizeof(void *))
 #if !defined(LZO_SIZEOF_SIZE_T)
 #if (LZO_ARCH_I086 || LZO_ARCH_M16C)
 #  define LZO_SIZEOF_SIZE_T         2
-#else
+#endif
+#endif
+#if !defined(LZO_SIZEOF_SIZE_T)
 #  define LZO_SIZEOF_SIZE_T         LZO_SIZEOF_VOID_P
 #endif
+#if defined(offsetof)
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_SIZE_T == sizeof(size_t))
 #endif
 #if !defined(LZO_SIZEOF_PTRDIFF_T)
 #if (LZO_ARCH_I086)
@@ -1267,11 +2295,18 @@
 #      define LZO_SIZEOF_PTRDIFF_T  2
 #    endif
 #  else
-#    error "LZO_MM"
-#  endif
-#else
+#    error "invalid LZO_ARCH_I086 memory model"
+#  endif
+#endif
+#endif
+#if !defined(LZO_SIZEOF_PTRDIFF_T)
 #  define LZO_SIZEOF_PTRDIFF_T      LZO_SIZEOF_SIZE_T
 #endif
+#if defined(offsetof)
+LZO_COMPILE_TIME_ASSERT_HEADER(LZO_SIZEOF_PTRDIFF_T == sizeof(ptrdiff_t))
+#endif
+#if !defined(LZO_WORDSIZE)
+#  define LZO_WORDSIZE              LZO_SIZEOF_VOID_P
 #endif
 #if (LZO_ABI_NEUTRAL_ENDIAN)
 #  undef LZO_ABI_BIG_ENDIAN
@@ -1283,7 +2318,7 @@
 #  define LZO_ABI_LITTLE_ENDIAN     1
 #elif (LZO_ARCH_ALPHA || LZO_ARCH_AMD64 || LZO_ARCH_BLACKFIN || LZO_ARCH_CRIS || LZO_ARCH_I086 || LZO_ARCH_I386 || LZO_ARCH_MSP430)
 #  define LZO_ABI_LITTLE_ENDIAN     1
-#elif (LZO_ARCH_AVR32 || LZO_ARCH_M68K || LZO_ARCH_S390)
+#elif (LZO_ARCH_AVR32 || LZO_ARCH_M68K || LZO_ARCH_S390 || LZO_ARCH_SPU)
 #  define LZO_ABI_BIG_ENDIAN        1
 #elif 1 && defined(__IAR_SYSTEMS_ICC__) && defined(__LITTLE_ENDIAN__)
 #  if (__LITTLE_ENDIAN__ == 1)
@@ -1299,6 +2334,19 @@
 #  define LZO_ABI_BIG_ENDIAN        1
 #elif 1 && (LZO_ARCH_ARM) && defined(__ARMEL__) && !defined(__ARMEB__)
 #  define LZO_ABI_LITTLE_ENDIAN     1
+#elif 1 && (LZO_ARCH_ARM && LZO_CC_ARMCC_ARMCC)
+#  if defined(__BIG_ENDIAN) && defined(__LITTLE_ENDIAN)
+#    error "unexpected configuration - check your compiler defines"
+#  elif defined(__BIG_ENDIAN)
+#    define LZO_ABI_BIG_ENDIAN      1
+#  else
+#    define LZO_ABI_LITTLE_ENDIAN   1
+#  endif
+#  define LZO_ABI_LITTLE_ENDIAN     1
+#elif 1 && (LZO_ARCH_ARM64) && defined(__AARCH64EB__) && !defined(__AARCH64EL__)
+#  define LZO_ABI_BIG_ENDIAN        1
+#elif 1 && (LZO_ARCH_ARM64) && defined(__AARCH64EL__) && !defined(__AARCH64EB__)
+#  define LZO_ABI_LITTLE_ENDIAN     1
 #elif 1 && (LZO_ARCH_MIPS) && defined(__MIPSEB__) && !defined(__MIPSEL__)
 #  define LZO_ABI_BIG_ENDIAN        1
 #elif 1 && (LZO_ARCH_MIPS) && defined(__MIPSEL__) && !defined(__MIPSEB__)
@@ -1306,7 +2354,7 @@
 #endif
 #endif
 #if (LZO_ABI_BIG_ENDIAN) && (LZO_ABI_LITTLE_ENDIAN)
-#  error "this should not happen"
+#  error "unexpected configuration - check your compiler defines"
 #endif
 #if (LZO_ABI_BIG_ENDIAN)
 #  define LZO_INFO_ABI_ENDIAN       "be"
@@ -1321,6 +2369,9 @@
 #elif (LZO_SIZEOF_INT == 2 && LZO_SIZEOF_LONG == 2 && LZO_SIZEOF_VOID_P == 2)
 #  define LZO_ABI_ILP16         1
 #  define LZO_INFO_ABI_PM       "ilp16"
+#elif (LZO_SIZEOF_INT == 2 && LZO_SIZEOF_LONG == 4 && LZO_SIZEOF_VOID_P == 4)
+#  define LZO_ABI_LP32          1
+#  define LZO_INFO_ABI_PM       "lp32"
 #elif (LZO_SIZEOF_INT == 4 && LZO_SIZEOF_LONG == 4 && LZO_SIZEOF_VOID_P == 4)
 #  define LZO_ABI_ILP32         1
 #  define LZO_INFO_ABI_PM       "ilp32"
@@ -1337,7 +2388,8 @@
 #  define LZO_ABI_IP32L64       1
 #  define LZO_INFO_ABI_PM       "ip32l64"
 #endif
-#if !defined(__LZO_LIBC_OVERRIDE)
+#if 0
+#elif !defined(__LZO_LIBC_OVERRIDE)
 #if (LZO_LIBC_NAKED)
 #  define LZO_INFO_LIBC         "naked"
 #elif (LZO_LIBC_FREESTANDING)
@@ -1348,6 +2400,9 @@
 #  define LZO_INFO_LIBC         "isoc90"
 #elif (LZO_LIBC_ISOC99)
 #  define LZO_INFO_LIBC         "isoc99"
+#elif (LZO_CC_ARMCC_ARMCC) && defined(__ARMCLIB_VERSION)
+#  define LZO_LIBC_ISOC90       1
+#  define LZO_INFO_LIBC         "isoc90"
 #elif defined(__dietlibc__)
 #  define LZO_LIBC_DIETLIBC     1
 #  define LZO_INFO_LIBC         "dietlibc"
@@ -1356,13 +2411,13 @@
 #  define LZO_INFO_LIBC         "newlib"
 #elif defined(__UCLIBC__) && defined(__UCLIBC_MAJOR__) && defined(__UCLIBC_MINOR__)
 #  if defined(__UCLIBC_SUBLEVEL__)
-#    define LZO_LIBC_UCLIBC     (__UCLIBC_MAJOR__ * 0x10000L + __UCLIBC_MINOR__ * 0x100 + __UCLIBC_SUBLEVEL__)
+#    define LZO_LIBC_UCLIBC     (__UCLIBC_MAJOR__ * 0x10000L + (__UCLIBC_MINOR__-0) * 0x100 + (__UCLIBC_SUBLEVEL__-0))
 #  else
 #    define LZO_LIBC_UCLIBC     0x00090bL
 #  endif
-#  define LZO_INFO_LIBC         "uclibc"
+#  define LZO_INFO_LIBC         "uc" "libc"
 #elif defined(__GLIBC__) && defined(__GLIBC_MINOR__)
-#  define LZO_LIBC_GLIBC        (__GLIBC__ * 0x10000L + __GLIBC_MINOR__ * 0x100)
+#  define LZO_LIBC_GLIBC        (__GLIBC__ * 0x10000L + (__GLIBC_MINOR__-0) * 0x100)
 #  define LZO_INFO_LIBC         "glibc"
 #elif (LZO_CC_MWERKS) && defined(__MSL__)
 #  define LZO_LIBC_MSL          __MSL__
@@ -1375,436 +2430,7 @@
 #  define LZO_INFO_LIBC         "default"
 #endif
 #endif
-#if !defined(__lzo_gnuc_extension__)
-#if (LZO_CC_GNUC >= 0x020800ul)
-#  define __lzo_gnuc_extension__    __extension__
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_gnuc_extension__    __extension__
-#else
-#  define __lzo_gnuc_extension__    /*empty*/
-#endif
-#endif
-#if !defined(__lzo_ua_volatile)
-#  define __lzo_ua_volatile     volatile
-#endif
-#if !defined(__lzo_alignof)
-#if (LZO_CC_CILLY || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
-#  define __lzo_alignof(e)      __alignof__(e)
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 700))
-#  define __lzo_alignof(e)      __alignof__(e)
-#elif (LZO_CC_MSC && (_MSC_VER >= 1300))
-#  define __lzo_alignof(e)      __alignof(e)
-#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC >= 0x5100))
-#  define __lzo_alignof(e)      __alignof__(e)
-#endif
-#endif
-#if defined(__lzo_alignof)
-#  define __lzo_HAVE_alignof 1
-#endif
-#if !defined(__lzo_constructor)
-#if (LZO_CC_GNUC >= 0x030400ul)
-#  define __lzo_constructor     __attribute__((__constructor__,__used__))
-#elif (LZO_CC_GNUC >= 0x020700ul)
-#  define __lzo_constructor     __attribute__((__constructor__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_constructor     __attribute__((__constructor__))
-#endif
-#endif
-#if defined(__lzo_constructor)
-#  define __lzo_HAVE_constructor 1
-#endif
-#if !defined(__lzo_destructor)
-#if (LZO_CC_GNUC >= 0x030400ul)
-#  define __lzo_destructor      __attribute__((__destructor__,__used__))
-#elif (LZO_CC_GNUC >= 0x020700ul)
-#  define __lzo_destructor      __attribute__((__destructor__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_destructor      __attribute__((__destructor__))
-#endif
-#endif
-#if defined(__lzo_destructor)
-#  define __lzo_HAVE_destructor 1
-#endif
-#if (__lzo_HAVE_destructor) && !(__lzo_HAVE_constructor)
-#  error "this should not happen"
-#endif
-#if !defined(__lzo_inline)
-#if (LZO_CC_TURBOC && (__TURBOC__ <= 0x0295))
-#elif defined(__cplusplus)
-#  define __lzo_inline          inline
-#elif (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0550))
-#  define __lzo_inline          __inline
-#elif (LZO_CC_CILLY || LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
-#  define __lzo_inline          __inline__
-#elif (LZO_CC_DMC)
-#  define __lzo_inline          __inline
-#elif (LZO_CC_INTELC)
-#  define __lzo_inline          __inline
-#elif (LZO_CC_MWERKS && (__MWERKS__ >= 0x2405))
-#  define __lzo_inline          __inline
-#elif (LZO_CC_MSC && (_MSC_VER >= 900))
-#  define __lzo_inline          __inline
-#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC >= 0x5100))
-#  define __lzo_inline          __inline__
-#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
-#  define __lzo_inline          inline
-#endif
-#endif
-#if defined(__lzo_inline)
-#  define __lzo_HAVE_inline 1
-#else
-#  define __lzo_inline          /*empty*/
-#endif
-#if !defined(__lzo_forceinline)
-#if (LZO_CC_GNUC >= 0x030200ul)
-#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 450) && LZO_CC_SYNTAX_MSC)
-#  define __lzo_forceinline     __forceinline
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 800) && LZO_CC_SYNTAX_GNUC)
-#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
-#elif (LZO_CC_MSC && (_MSC_VER >= 1200))
-#  define __lzo_forceinline     __forceinline
-#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC >= 0x5100))
-#  define __lzo_forceinline     __inline__ __attribute__((__always_inline__))
-#endif
-#endif
-#if defined(__lzo_forceinline)
-#  define __lzo_HAVE_forceinline 1
-#else
-#  define __lzo_forceinline     /*empty*/
-#endif
-#if !defined(__lzo_noinline)
-#if 1 && (LZO_ARCH_I386) && (LZO_CC_GNUC >= 0x040000ul) && (LZO_CC_GNUC < 0x040003ul)
-#  define __lzo_noinline        __attribute__((__noinline__,__used__))
-#elif (LZO_CC_GNUC >= 0x030200ul)
-#  define __lzo_noinline        __attribute__((__noinline__))
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 600) && LZO_CC_SYNTAX_MSC)
-#  define __lzo_noinline        __declspec(noinline)
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 800) && LZO_CC_SYNTAX_GNUC)
-#  define __lzo_noinline        __attribute__((__noinline__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_noinline        __attribute__((__noinline__))
-#elif (LZO_CC_MSC && (_MSC_VER >= 1300))
-#  define __lzo_noinline        __declspec(noinline)
-#elif (LZO_CC_MWERKS && (__MWERKS__ >= 0x3200) && (LZO_OS_WIN32 || LZO_OS_WIN64))
-#  if defined(__cplusplus)
-#  else
-#    define __lzo_noinline      __declspec(noinline)
-#  endif
-#elif (LZO_CC_SUNPROC && (LZO_CC_SUNPROC >= 0x5100))
-#  define __lzo_noinline        __attribute__((__noinline__))
-#endif
-#endif
-#if defined(__lzo_noinline)
-#  define __lzo_HAVE_noinline 1
-#else
-#  define __lzo_noinline        /*empty*/
-#endif
-#if (__lzo_HAVE_forceinline || __lzo_HAVE_noinline) && !(__lzo_HAVE_inline)
-#  error "this should not happen"
-#endif
-#if !defined(__lzo_noreturn)
-#if (LZO_CC_GNUC >= 0x020700ul)
-#  define __lzo_noreturn        __attribute__((__noreturn__))
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 450) && LZO_CC_SYNTAX_MSC)
-#  define __lzo_noreturn        __declspec(noreturn)
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 600) && LZO_CC_SYNTAX_GNUC)
-#  define __lzo_noreturn        __attribute__((__noreturn__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_noreturn        __attribute__((__noreturn__))
-#elif (LZO_CC_MSC && (_MSC_VER >= 1200))
-#  define __lzo_noreturn        __declspec(noreturn)
-#endif
-#endif
-#if defined(__lzo_noreturn)
-#  define __lzo_HAVE_noreturn 1
-#else
-#  define __lzo_noreturn        /*empty*/
-#endif
-#if !defined(__lzo_nothrow)
-#if (LZO_CC_GNUC >= 0x030300ul)
-#  define __lzo_nothrow         __attribute__((__nothrow__))
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 450) && LZO_CC_SYNTAX_MSC) && defined(__cplusplus)
-#  define __lzo_nothrow         __declspec(nothrow)
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 900) && LZO_CC_SYNTAX_GNUC)
-#  define __lzo_nothrow         __attribute__((__nothrow__))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_nothrow         __attribute__((__nothrow__))
-#elif (LZO_CC_MSC && (_MSC_VER >= 1200)) && defined(__cplusplus)
-#  define __lzo_nothrow         __declspec(nothrow)
-#endif
-#endif
-#if defined(__lzo_nothrow)
-#  define __lzo_HAVE_nothrow 1
-#else
-#  define __lzo_nothrow         /*empty*/
-#endif
-#if !defined(__lzo_restrict)
-#if (LZO_CC_GNUC >= 0x030400ul)
-#  define __lzo_restrict        __restrict__
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 600) && LZO_CC_SYNTAX_GNUC)
-#  define __lzo_restrict        __restrict__
-#elif (LZO_CC_CLANG || LZO_CC_LLVM)
-#  define __lzo_restrict        __restrict__
-#elif (LZO_CC_MSC && (_MSC_VER >= 1400))
-#  define __lzo_restrict        __restrict
-#endif
-#endif
-#if defined(__lzo_restrict)
-#  define __lzo_HAVE_restrict 1
-#else
-#  define __lzo_restrict        /*empty*/
-#endif
-#if !defined(__lzo_likely) && !defined(__lzo_unlikely)
-#if (LZO_CC_GNUC >= 0x030200ul)
-#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
-#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
-#elif (LZO_CC_INTELC && (__INTEL_COMPILER >= 800))
-#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
-#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
-#elif (LZO_CC_CLANG || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#  define __lzo_likely(e)       (__builtin_expect(!!(e),1))
-#  define __lzo_unlikely(e)     (__builtin_expect(!!(e),0))
-#endif
-#endif
-#if defined(__lzo_likely)
-#  define __lzo_HAVE_likely 1
-#else
-#  define __lzo_likely(e)       (e)
-#endif
-#if defined(__lzo_unlikely)
-#  define __lzo_HAVE_unlikely 1
-#else
-#  define __lzo_unlikely(e)     (e)
-#endif
-#if !defined(LZO_UNUSED)
-#  if (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0600))
-#    define LZO_UNUSED(var)         ((void) &var)
-#  elif (LZO_CC_BORLANDC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PELLESC || LZO_CC_TURBOC)
-#    define LZO_UNUSED(var)         if (&var) ; else
-#  elif (LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#    define LZO_UNUSED(var)         ((void) var)
-#  elif (LZO_CC_MSC && (_MSC_VER < 900))
-#    define LZO_UNUSED(var)         if (&var) ; else
-#  elif (LZO_CC_KEILC)
-#    define LZO_UNUSED(var)         {extern int __lzo_unused[1-2*!(sizeof(var)>0)];}
-#  elif (LZO_CC_PACIFICC)
-#    define LZO_UNUSED(var)         ((void) sizeof(var))
-#  elif (LZO_CC_WATCOMC) && defined(__cplusplus)
-#    define LZO_UNUSED(var)         ((void) var)
-#  else
-#    define LZO_UNUSED(var)         ((void) &var)
-#  endif
-#endif
-#if !defined(LZO_UNUSED_FUNC)
-#  if (LZO_CC_BORLANDC && (__BORLANDC__ >= 0x0600))
-#    define LZO_UNUSED_FUNC(func)   ((void) func)
-#  elif (LZO_CC_BORLANDC || LZO_CC_NDPC || LZO_CC_TURBOC)
-#    define LZO_UNUSED_FUNC(func)   if (func) ; else
-#  elif (LZO_CC_CLANG || LZO_CC_LLVM)
-#    define LZO_UNUSED_FUNC(func)   ((void) &func)
-#  elif (LZO_CC_MSC && (_MSC_VER < 900))
-#    define LZO_UNUSED_FUNC(func)   if (func) ; else
-#  elif (LZO_CC_MSC)
-#    define LZO_UNUSED_FUNC(func)   ((void) &func)
-#  elif (LZO_CC_KEILC || LZO_CC_PELLESC)
-#    define LZO_UNUSED_FUNC(func)   {extern int __lzo_unused[1-2*!(sizeof((int)func)>0)];}
-#  else
-#    define LZO_UNUSED_FUNC(func)   ((void) func)
-#  endif
-#endif
-#if !defined(LZO_UNUSED_LABEL)
-#  if (LZO_CC_WATCOMC) && defined(__cplusplus)
-#    define LZO_UNUSED_LABEL(l)     switch(0) case 1:goto l
-#  elif (LZO_CC_CLANG || LZO_CC_INTELC || LZO_CC_WATCOMC)
-#    define LZO_UNUSED_LABEL(l)     if (0) goto l
-#  else
-#    define LZO_UNUSED_LABEL(l)     switch(0) case 1:goto l
-#  endif
-#endif
-#if !defined(LZO_DEFINE_UNINITIALIZED_VAR)
-#  if 0
-#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var
-#  elif 0 && (LZO_CC_GNUC)
-#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var = var
-#  else
-#    define LZO_DEFINE_UNINITIALIZED_VAR(type,var,init)  type var = init
-#  endif
-#endif
-#if !defined(LZO_UNCONST_CAST)
-#  if 0 && defined(__cplusplus)
-#    define LZO_UNCONST_CAST(t,e)   (const_cast<t> (e))
-#  elif (LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE)
-#    define LZO_UNCONST_CAST(t,e)   ((t) ((void *) ((char *) ((lzo_uintptr_t) ((const void *) (e))))))
-#  else
-#    define LZO_UNCONST_CAST(t,e)   ((t) ((void *) ((char *) ((const void *) (e)))))
-#  endif
-#endif
-#if !defined(LZO_COMPILE_TIME_ASSERT_HEADER)
-#  if (LZO_CC_AZTECC || LZO_CC_ZORTECHC)
-#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  extern int __lzo_cta[1-!(e)];
-#  elif (LZO_CC_DMC || LZO_CC_SYMANTECC)
-#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  extern int __lzo_cta[1u-2*!(e)];
-#  elif (LZO_CC_TURBOC && (__TURBOC__ == 0x0295))
-#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  extern int __lzo_cta[1-!(e)];
-#  else
-#    define LZO_COMPILE_TIME_ASSERT_HEADER(e)  extern int __lzo_cta[1-2*!(e)];
-#  endif
-#endif
-#if !defined(LZO_COMPILE_TIME_ASSERT)
-#  if (LZO_CC_AZTECC)
-#    define LZO_COMPILE_TIME_ASSERT(e)  {typedef int __lzo_cta_t[1-!(e)];}
-#  elif (LZO_CC_DMC || LZO_CC_PACIFICC || LZO_CC_SYMANTECC || LZO_CC_ZORTECHC)
-#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
-#  elif (LZO_CC_MSC && (_MSC_VER < 900))
-#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
-#  elif (LZO_CC_TURBOC && (__TURBOC__ == 0x0295))
-#    define LZO_COMPILE_TIME_ASSERT(e)  switch(0) case 1:case !(e):break;
-#  else
-#    define LZO_COMPILE_TIME_ASSERT(e)  {typedef int __lzo_cta_t[1-2*!(e)];}
-#  endif
-#endif
-#if (LZO_ARCH_I086 || LZO_ARCH_I386) && (LZO_OS_DOS16 || LZO_OS_DOS32 || LZO_OS_OS2 || LZO_OS_OS216 || LZO_OS_WIN16 || LZO_OS_WIN32 || LZO_OS_WIN64)
-#  if (LZO_CC_GNUC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PACIFICC)
-#  elif (LZO_CC_DMC || LZO_CC_SYMANTECC || LZO_CC_ZORTECHC)
-#    define __lzo_cdecl                 __cdecl
-#    define __lzo_cdecl_atexit          /*empty*/
-#    define __lzo_cdecl_main            __cdecl
-#    if (LZO_OS_OS2 && (LZO_CC_DMC || LZO_CC_SYMANTECC))
-#      define __lzo_cdecl_qsort         __pascal
-#    elif (LZO_OS_OS2 && (LZO_CC_ZORTECHC))
-#      define __lzo_cdecl_qsort         _stdcall
-#    else
-#      define __lzo_cdecl_qsort         __cdecl
-#    endif
-#  elif (LZO_CC_WATCOMC)
-#    define __lzo_cdecl                 __cdecl
-#  else
-#    define __lzo_cdecl                 __cdecl
-#    define __lzo_cdecl_atexit          __cdecl
-#    define __lzo_cdecl_main            __cdecl
-#    define __lzo_cdecl_qsort           __cdecl
-#  endif
-#  if (LZO_CC_GNUC || LZO_CC_HIGHC || LZO_CC_NDPC || LZO_CC_PACIFICC || LZO_CC_WATCOMC)
-#  elif (LZO_OS_OS2 && (LZO_CC_DMC || LZO_CC_SYMANTECC))
-#    define __lzo_cdecl_sighandler      __pascal
-#  elif (LZO_OS_OS2 && (LZO_CC_ZORTECHC))
-#    define __lzo_cdecl_sighandler      _stdcall
-#  elif (LZO_CC_MSC && (_MSC_VER >= 1400)) && defined(_M_CEE_PURE)
-#    define __lzo_cdecl_sighandler      __clrcall
-#  elif (LZO_CC_MSC && (_MSC_VER >= 600 && _MSC_VER < 700))
-#    if defined(_DLL)
-#      define __lzo_cdecl_sighandler    _far _cdecl _loadds
-#    elif defined(_MT)
-#      define __lzo_cdecl_sighandler    _far _cdecl
-#    else
-#      define __lzo_cdecl_sighandler    _cdecl
-#    endif
-#  else
-#    define __lzo_cdecl_sighandler      __cdecl
-#  endif
-#elif (LZO_ARCH_I386) && (LZO_CC_WATCOMC)
-#  define __lzo_cdecl                   __cdecl
-#elif (LZO_ARCH_M68K && LZO_OS_TOS && (LZO_CC_PUREC || LZO_CC_TURBOC))
-#  define __lzo_cdecl                   cdecl
-#endif
-#if !defined(__lzo_cdecl)
-#  define __lzo_cdecl                   /*empty*/
-#endif
-#if !defined(__lzo_cdecl_atexit)
-#  define __lzo_cdecl_atexit            /*empty*/
-#endif
-#if !defined(__lzo_cdecl_main)
-#  define __lzo_cdecl_main              /*empty*/
-#endif
-#if !defined(__lzo_cdecl_qsort)
-#  define __lzo_cdecl_qsort             /*empty*/
-#endif
-#if !defined(__lzo_cdecl_sighandler)
-#  define __lzo_cdecl_sighandler        /*empty*/
-#endif
-#if !defined(__lzo_cdecl_va)
-#  define __lzo_cdecl_va                __lzo_cdecl
-#endif
-#if !(LZO_CFG_NO_WINDOWS_H)
-#if (LZO_OS_CYGWIN || (LZO_OS_EMX && defined(__RSXNT__)) || LZO_OS_WIN32 || LZO_OS_WIN64)
-#  if (LZO_CC_WATCOMC && (__WATCOMC__ < 1000))
-#  elif (LZO_OS_WIN32 && LZO_CC_GNUC) && defined(__PW32__)
-#  elif ((LZO_OS_CYGWIN || defined(__MINGW32__)) && (LZO_CC_GNUC && (LZO_CC_GNUC < 0x025f00ul)))
-#  else
-#    define LZO_HAVE_WINDOWS_H 1
-#  endif
-#endif
-#endif
-#if (LZO_ARCH_ALPHA)
-#  define LZO_OPT_AVOID_UINT_INDEX  1
-#  define LZO_OPT_AVOID_SHORT       1
-#  define LZO_OPT_AVOID_USHORT      1
-#elif (LZO_ARCH_AMD64)
-#  define LZO_OPT_AVOID_INT_INDEX   1
-#  define LZO_OPT_AVOID_UINT_INDEX  1
-#  define LZO_OPT_UNALIGNED16       1
-#  define LZO_OPT_UNALIGNED32       1
-#  define LZO_OPT_UNALIGNED64       1
-#elif (LZO_ARCH_ARM && LZO_ARCH_ARM_THUMB)
-#elif (LZO_ARCH_ARM)
-#  define LZO_OPT_AVOID_SHORT       1
-#  define LZO_OPT_AVOID_USHORT      1
-#elif (LZO_ARCH_CRIS)
-#  define LZO_OPT_UNALIGNED16       1
-#  define LZO_OPT_UNALIGNED32       1
-#elif (LZO_ARCH_I386)
-#  define LZO_OPT_UNALIGNED16       1
-#  define LZO_OPT_UNALIGNED32       1
-#elif (LZO_ARCH_IA64)
-#  define LZO_OPT_AVOID_INT_INDEX   1
-#  define LZO_OPT_AVOID_UINT_INDEX  1
-#  define LZO_OPT_PREFER_POSTINC    1
-#elif (LZO_ARCH_M68K)
-#  define LZO_OPT_PREFER_POSTINC    1
-#  define LZO_OPT_PREFER_PREDEC     1
-#  if defined(__mc68020__) && !defined(__mcoldfire__)
-#    define LZO_OPT_UNALIGNED16     1
-#    define LZO_OPT_UNALIGNED32     1
-#  endif
-#elif (LZO_ARCH_MIPS)
-#  define LZO_OPT_AVOID_UINT_INDEX  1
-#elif (LZO_ARCH_POWERPC)
-#  define LZO_OPT_PREFER_PREINC     1
-#  define LZO_OPT_PREFER_PREDEC     1
-#  if (LZO_ABI_BIG_ENDIAN)
-#    define LZO_OPT_UNALIGNED16     1
-#    define LZO_OPT_UNALIGNED32     1
-#  endif
-#elif (LZO_ARCH_S390)
-#  define LZO_OPT_UNALIGNED16       1
-#  define LZO_OPT_UNALIGNED32       1
-#  if (LZO_SIZEOF_SIZE_T == 8)
-#    define LZO_OPT_UNALIGNED64     1
-#  endif
-#elif (LZO_ARCH_SH)
-#  define LZO_OPT_PREFER_POSTINC    1
-#  define LZO_OPT_PREFER_PREDEC     1
-#endif
-#ifndef LZO_CFG_NO_INLINE_ASM
-#if (LZO_CC_LLVM)
-#  define LZO_CFG_NO_INLINE_ASM 1
-#endif
-#endif
-#ifndef LZO_CFG_NO_UNALIGNED
-#if (LZO_ABI_NEUTRAL_ENDIAN) || (LZO_ARCH_GENERIC)
-#  define LZO_CFG_NO_UNALIGNED 1
-#endif
-#endif
-#if (LZO_CFG_NO_UNALIGNED)
-#  undef LZO_OPT_UNALIGNED16
-#  undef LZO_OPT_UNALIGNED32
-#  undef LZO_OPT_UNALIGNED64
-#endif
-#if (LZO_CFG_NO_INLINE_ASM)
-#elif (LZO_ARCH_I386 && (LZO_OS_DOS32 || LZO_OS_WIN32) && (LZO_CC_DMC || LZO_CC_INTELC || LZO_CC_MSC || LZO_CC_PELLESC))
+#if (LZO_ARCH_I386 && (LZO_OS_DOS32 || LZO_OS_WIN32) && (LZO_CC_DMC || LZO_CC_INTELC || LZO_CC_MSC || LZO_CC_PELLESC))
 #  define LZO_ASM_SYNTAX_MSC 1
 #elif (LZO_OS_WIN64 && (LZO_CC_DMC || LZO_CC_INTELC || LZO_CC_MSC || LZO_CC_PELLESC))
 #elif (LZO_ARCH_I386 && LZO_CC_GNUC && (LZO_CC_GNUC == 0x011f00ul))
@@ -1812,15 +2438,161 @@
 #  define LZO_ASM_SYNTAX_GNUC 1
 #elif (LZO_ARCH_AMD64 && (LZO_CC_CLANG || LZO_CC_GNUC || LZO_CC_INTELC || LZO_CC_PATHSCALE))
 #  define LZO_ASM_SYNTAX_GNUC 1
+#elif (LZO_CC_GNUC)
+#  define LZO_ASM_SYNTAX_GNUC 1
 #endif
 #if (LZO_ASM_SYNTAX_GNUC)
 #if (LZO_ARCH_I386 && LZO_CC_GNUC && (LZO_CC_GNUC < 0x020000ul))
-#  define __LZO_ASM_CLOBBER         "ax"
-#elif (LZO_CC_INTELC)
-#  define __LZO_ASM_CLOBBER         "memory"
-#else
-#  define __LZO_ASM_CLOBBER         "cc", "memory"
-#endif
+#  define __LZO_ASM_CLOBBER                     "ax"
+#  define __LZO_ASM_CLOBBER_LIST_CC             /*empty*/
+#  define __LZO_ASM_CLOBBER_LIST_CC_MEMORY      /*empty*/
+#  define __LZO_ASM_CLOBBER_LIST_EMPTY          /*empty*/
+#elif (LZO_CC_INTELC && (__INTEL_COMPILER < 1000))
+#  define __LZO_ASM_CLOBBER                     "memory"
+#  define __LZO_ASM_CLOBBER_LIST_CC             /*empty*/
+#  define __LZO_ASM_CLOBBER_LIST_CC_MEMORY      : "memory"
+#  define __LZO_ASM_CLOBBER_LIST_EMPTY          /*empty*/
+#else
+#  define __LZO_ASM_CLOBBER                     "cc", "memory"
+#  define __LZO_ASM_CLOBBER_LIST_CC             : "cc"
+#  define __LZO_ASM_CLOBBER_LIST_CC_MEMORY      : "cc", "memory"
+#  define __LZO_ASM_CLOBBER_LIST_EMPTY          /*empty*/
+#endif
+#endif
+#if (LZO_ARCH_ALPHA)
+#  define LZO_OPT_AVOID_UINT_INDEX          1
+#elif (LZO_ARCH_AMD64)
+#  define LZO_OPT_AVOID_INT_INDEX           1
+#  define LZO_OPT_AVOID_UINT_INDEX          1
+#  ifndef LZO_OPT_UNALIGNED16
+#  define LZO_OPT_UNALIGNED16               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED32
+#  define LZO_OPT_UNALIGNED32               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED64
+#  define LZO_OPT_UNALIGNED64               1
+#  endif
+#elif (LZO_ARCH_ARM)
+#  if defined(__ARM_FEATURE_UNALIGNED)
+#    ifndef LZO_OPT_UNALIGNED16
+#    define LZO_OPT_UNALIGNED16             1
+#    endif
+#    ifndef LZO_OPT_UNALIGNED32
+#    define LZO_OPT_UNALIGNED32             1
+#    endif
+#  elif defined(__TARGET_ARCH_ARM) && ((__TARGET_ARCH_ARM+0) >= 7)
+#    ifndef LZO_OPT_UNALIGNED16
+#    define LZO_OPT_UNALIGNED16             1
+#    endif
+#    ifndef LZO_OPT_UNALIGNED32
+#    define LZO_OPT_UNALIGNED32             1
+#    endif
+#  elif defined(__TARGET_ARCH_ARM) && ((__TARGET_ARCH_ARM+0) >= 6) && !defined(__TARGET_PROFILE_M)
+#    ifndef LZO_OPT_UNALIGNED16
+#    define LZO_OPT_UNALIGNED16             1
+#    endif
+#    ifndef LZO_OPT_UNALIGNED32
+#    define LZO_OPT_UNALIGNED32             1
+#    endif
+#  endif
+#elif (LZO_ARCH_ARM64)
+#  ifndef LZO_OPT_UNALIGNED16
+#  define LZO_OPT_UNALIGNED16               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED32
+#  define LZO_OPT_UNALIGNED32               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED64
+#  define LZO_OPT_UNALIGNED64               1
+#  endif
+#elif (LZO_ARCH_CRIS)
+#  ifndef LZO_OPT_UNALIGNED16
+#  define LZO_OPT_UNALIGNED16               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED32
+#  define LZO_OPT_UNALIGNED32               1
+#  endif
+#elif (LZO_ARCH_I386)
+#  ifndef LZO_OPT_UNALIGNED16
+#  define LZO_OPT_UNALIGNED16               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED32
+#  define LZO_OPT_UNALIGNED32               1
+#  endif
+#elif (LZO_ARCH_IA64)
+#  define LZO_OPT_AVOID_INT_INDEX           1
+#  define LZO_OPT_AVOID_UINT_INDEX          1
+#  define LZO_OPT_PREFER_POSTINC            1
+#elif (LZO_ARCH_M68K)
+#  define LZO_OPT_PREFER_POSTINC            1
+#  define LZO_OPT_PREFER_PREDEC             1
+#  if defined(__mc68020__) && !defined(__mcoldfire__)
+#    ifndef LZO_OPT_UNALIGNED16
+#    define LZO_OPT_UNALIGNED16             1
+#    endif
+#    ifndef LZO_OPT_UNALIGNED32
+#    define LZO_OPT_UNALIGNED32             1
+#    endif
+#  endif
+#elif (LZO_ARCH_MIPS)
+#  define LZO_OPT_AVOID_UINT_INDEX          1
+#elif (LZO_ARCH_POWERPC)
+#  define LZO_OPT_PREFER_PREINC             1
+#  define LZO_OPT_PREFER_PREDEC             1
+#  if (LZO_ABI_BIG_ENDIAN)
+#    ifndef LZO_OPT_UNALIGNED16
+#    define LZO_OPT_UNALIGNED16             1
+#    endif
+#    ifndef LZO_OPT_UNALIGNED32
+#    define LZO_OPT_UNALIGNED32             1
+#    endif
+#    if (LZO_WORDSIZE == 8)
+#      ifndef LZO_OPT_UNALIGNED64
+#      define LZO_OPT_UNALIGNED64           1
+#      endif
+#    endif
+#  endif
+#elif (LZO_ARCH_S390)
+#  ifndef LZO_OPT_UNALIGNED16
+#  define LZO_OPT_UNALIGNED16               1
+#  endif
+#  ifndef LZO_OPT_UNALIGNED32
+#  define LZO_OPT_UNALIGNED32               1
+#  endif
+#  if (LZO_WORDSIZE == 8)
+#    ifndef LZO_OPT_UNALIGNED64
+#    define LZO_OPT_UNALIGNED64             1
+#    endif
+#  endif
+#elif (LZO_ARCH_SH)
+#  define LZO_OPT_PREFER_POSTINC            1
+#  define LZO_OPT_PREFER_PREDEC             1
+#endif
+#ifndef LZO_CFG_NO_INLINE_ASM
+#if (LZO_ABI_NEUTRAL_ENDIAN) || (LZO_ARCH_GENERIC)
+#  define LZO_CFG_NO_INLINE_ASM 1
+#elif (LZO_CC_LLVM)
+#  define LZO_CFG_NO_INLINE_ASM 1
+#endif
+#endif
+#if (LZO_CFG_NO_INLINE_ASM)
+#  undef LZO_ASM_SYNTAX_MSC
+#  undef LZO_ASM_SYNTAX_GNUC
+#  undef __LZO_ASM_CLOBBER
+#  undef __LZO_ASM_CLOBBER_LIST_CC
+#  undef __LZO_ASM_CLOBBER_LIST_CC_MEMORY
+#  undef __LZO_ASM_CLOBBER_LIST_EMPTY
+#endif
+#ifndef LZO_CFG_NO_UNALIGNED
+#if (LZO_ABI_NEUTRAL_ENDIAN) || (LZO_ARCH_GENERIC)
+#  define LZO_CFG_NO_UNALIGNED 1
+#endif
+#endif
+#if (LZO_CFG_NO_UNALIGNED)
+#  undef LZO_OPT_UNALIGNED16
+#  undef LZO_OPT_UNALIGNED32
+#  undef LZO_OPT_UNALIGNED64
 #endif
 #if defined(__LZO_INFOSTR_MM)
 #elif (LZO_MM_FLAT) && (defined(__LZO_INFOSTR_PM) || defined(LZO_INFO_ABI_PM))
@@ -1865,6 +2637,381 @@
 #define LZO_INFO_STRING \
     LZO_INFO_ARCH __LZO_INFOSTR_MM __LZO_INFOSTR_PM __LZO_INFOSTR_ENDIAN \
     " " __LZO_INFOSTR_OSNAME __LZO_INFOSTR_LIBC " " LZO_INFO_CC __LZO_INFOSTR_CCVER
+#if !(LZO_CFG_SKIP_LZO_TYPES)
+#if (!(LZO_SIZEOF_SHORT+0 > 0 && LZO_SIZEOF_INT+0 > 0 && LZO_SIZEOF_LONG+0 > 0))
+#  error "missing defines for sizes"
+#endif
+#if (!(LZO_SIZEOF_PTRDIFF_T+0 > 0 && LZO_SIZEOF_SIZE_T+0 > 0 && LZO_SIZEOF_VOID_P+0 > 0))
+#  error "missing defines for sizes"
+#endif
+#if !defined(lzo_llong_t)
+#if (LZO_SIZEOF_LONG_LONG+0 > 0)
+__lzo_gnuc_extension__ typedef long long lzo_llong_t__;
+__lzo_gnuc_extension__ typedef unsigned long long lzo_ullong_t__;
+#  define lzo_llong_t               lzo_llong_t__
+#  define lzo_ullong_t              lzo_ullong_t__
+#endif
+#endif
+#if !defined(lzo_int16e_t)
+#if (LZO_SIZEOF_LONG == 2)
+#  define lzo_int16e_t              long
+#  define lzo_uint16e_t             unsigned long
+#elif (LZO_SIZEOF_INT == 2)
+#  define lzo_int16e_t              int
+#  define lzo_uint16e_t             unsigned int
+#elif (LZO_SIZEOF_SHORT == 2)
+#  define lzo_int16e_t              short int
+#  define lzo_uint16e_t             unsigned short int
+#elif 1 && !(LZO_CFG_TYPE_NO_MODE_HI) && (LZO_CC_CLANG || (LZO_CC_GNUC >= 0x025f00ul) || LZO_CC_LLVM)
+   typedef int lzo_int16e_hi_t__ __attribute__((__mode__(__HI__)));
+   typedef unsigned int lzo_uint16e_hi_t__ __attribute__((__mode__(__HI__)));
+#  define lzo_int16e_t              lzo_int16e_hi_t__
+#  define lzo_uint16e_t             lzo_uint16e_hi_t__
+#elif (LZO_SIZEOF___INT16 == 2)
+#  define lzo_int16e_t              __int16
+#  define lzo_uint16e_t             unsigned __int16
+#else
+#endif
+#endif
+#if defined(lzo_int16e_t)
+#  define LZO_SIZEOF_LZO_INT16E_T   2
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int16e_t) == 2)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int16e_t) == LZO_SIZEOF_LZO_INT16E_T)
+#endif
+#if !defined(lzo_int32e_t)
+#if (LZO_SIZEOF_LONG == 4)
+#  define lzo_int32e_t              long int
+#  define lzo_uint32e_t             unsigned long int
+#elif (LZO_SIZEOF_INT == 4)
+#  define lzo_int32e_t              int
+#  define lzo_uint32e_t             unsigned int
+#elif (LZO_SIZEOF_SHORT == 4)
+#  define lzo_int32e_t              short int
+#  define lzo_uint32e_t             unsigned short int
+#elif (LZO_SIZEOF_LONG_LONG == 4)
+#  define lzo_int32e_t              lzo_llong_t
+#  define lzo_uint32e_t             lzo_ullong_t
+#elif 1 && !(LZO_CFG_TYPE_NO_MODE_SI) && (LZO_CC_CLANG || (LZO_CC_GNUC >= 0x025f00ul) || LZO_CC_LLVM) && (__INT_MAX__+0 > 2147483647L)
+   typedef int lzo_int32e_si_t__ __attribute__((__mode__(__SI__)));
+   typedef unsigned int lzo_uint32e_si_t__ __attribute__((__mode__(__SI__)));
+#  define lzo_int32e_t              lzo_int32e_si_t__
+#  define lzo_uint32e_t             lzo_uint32e_si_t__
+#elif 1 && !(LZO_CFG_TYPE_NO_MODE_SI) && (LZO_CC_GNUC >= 0x025f00ul) && defined(__AVR__) && (__LONG_MAX__+0 == 32767L)
+   typedef int lzo_int32e_si_t__ __attribute__((__mode__(__SI__)));
+   typedef unsigned int lzo_uint32e_si_t__ __attribute__((__mode__(__SI__)));
+#  define lzo_int32e_t              lzo_int32e_si_t__
+#  define lzo_uint32e_t             lzo_uint32e_si_t__
+#  define LZO_INT32_C(c)            (c##LL)
+#  define LZO_UINT32_C(c)           (c##ULL)
+#elif (LZO_SIZEOF___INT32 == 4)
+#  define lzo_int32e_t              __int32
+#  define lzo_uint32e_t             unsigned __int32
+#else
+#endif
+#endif
+#if defined(lzo_int32e_t)
+#  define LZO_SIZEOF_LZO_INT32E_T   4
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32e_t) == 4)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32e_t) == LZO_SIZEOF_LZO_INT32E_T)
+#endif
+#if !defined(lzo_int64e_t)
+#if (LZO_SIZEOF___INT64 == 8)
+#  if (LZO_CC_BORLANDC) && !(LZO_CFG_TYPE_PREFER___INT64)
+#    define LZO_CFG_TYPE_PREFER___INT64 1
+#  endif
+#endif
+#if (LZO_SIZEOF_INT == 8) && (LZO_SIZEOF_INT < LZO_SIZEOF_LONG)
+#  define lzo_int64e_t              int
+#  define lzo_uint64e_t             unsigned int
+#  define LZO_SIZEOF_LZO_INT64E_T   LZO_SIZEOF_INT
+#elif (LZO_SIZEOF_LONG == 8)
+#  define lzo_int64e_t              long int
+#  define lzo_uint64e_t             unsigned long int
+#  define LZO_SIZEOF_LZO_INT64E_T   LZO_SIZEOF_LONG
+#elif (LZO_SIZEOF_LONG_LONG == 8) && !(LZO_CFG_TYPE_PREFER___INT64)
+#  define lzo_int64e_t              lzo_llong_t
+#  define lzo_uint64e_t             lzo_ullong_t
+#  if (LZO_CC_BORLANDC)
+#    define LZO_INT64_C(c)          ((c) + 0ll)
+#    define LZO_UINT64_C(c)         ((c) + 0ull)
+#  elif 0
+#    define LZO_INT64_C(c)          (__lzo_gnuc_extension__ (c##LL))
+#    define LZO_UINT64_C(c)         (__lzo_gnuc_extension__ (c##ULL))
+#  else
+#    define LZO_INT64_C(c)          (c##LL)
+#    define LZO_UINT64_C(c)         (c##ULL)
+#  endif
+#  define LZO_SIZEOF_LZO_INT64E_T   LZO_SIZEOF_LONG_LONG
+#elif (LZO_SIZEOF___INT64 == 8)
+#  define lzo_int64e_t              __int64
+#  define lzo_uint64e_t             unsigned __int64
+#  if (LZO_CC_BORLANDC)
+#    define LZO_INT64_C(c)          ((c) + 0i64)
+#    define LZO_UINT64_C(c)         ((c) + 0ui64)
+#  else
+#    define LZO_INT64_C(c)          (c##i64)
+#    define LZO_UINT64_C(c)         (c##ui64)
+#  endif
+#  define LZO_SIZEOF_LZO_INT64E_T   LZO_SIZEOF___INT64
+#else
+#endif
+#endif
+#if defined(lzo_int64e_t)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64e_t) == 8)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64e_t) == LZO_SIZEOF_LZO_INT64E_T)
+#endif
+#if !defined(lzo_int32l_t)
+#if defined(lzo_int32e_t)
+#  define lzo_int32l_t              lzo_int32e_t
+#  define lzo_uint32l_t             lzo_uint32e_t
+#  define LZO_SIZEOF_LZO_INT32L_T   LZO_SIZEOF_LZO_INT32E_T
+#elif (LZO_SIZEOF_INT >= 4) && (LZO_SIZEOF_INT < LZO_SIZEOF_LONG)
+#  define lzo_int32l_t              int
+#  define lzo_uint32l_t             unsigned int
+#  define LZO_SIZEOF_LZO_INT32L_T   LZO_SIZEOF_INT
+#elif (LZO_SIZEOF_LONG >= 4)
+#  define lzo_int32l_t              long int
+#  define lzo_uint32l_t             unsigned long int
+#  define LZO_SIZEOF_LZO_INT32L_T   LZO_SIZEOF_LONG
+#else
+#  error "lzo_int32l_t"
+#endif
+#endif
+#if 1
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32l_t) >= 4)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32l_t) == LZO_SIZEOF_LZO_INT32L_T)
+#endif
+#if !defined(lzo_int64l_t)
+#if defined(lzo_int64e_t)
+#  define lzo_int64l_t              lzo_int64e_t
+#  define lzo_uint64l_t             lzo_uint64e_t
+#  define LZO_SIZEOF_LZO_INT64L_T   LZO_SIZEOF_LZO_INT64E_T
+#else
+#endif
+#endif
+#if defined(lzo_int64l_t)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64l_t) >= 8)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64l_t) == LZO_SIZEOF_LZO_INT64L_T)
+#endif
+#if !defined(lzo_int32f_t)
+#if (LZO_SIZEOF_SIZE_T >= 8)
+#  define lzo_int32f_t              lzo_int64l_t
+#  define lzo_uint32f_t             lzo_uint64l_t
+#  define LZO_SIZEOF_LZO_INT32F_T   LZO_SIZEOF_LZO_INT64L_T
+#else
+#  define lzo_int32f_t              lzo_int32l_t
+#  define lzo_uint32f_t             lzo_uint32l_t
+#  define LZO_SIZEOF_LZO_INT32F_T   LZO_SIZEOF_LZO_INT32L_T
+#endif
+#endif
+#if 1
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32f_t) >= 4)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32f_t) == LZO_SIZEOF_LZO_INT32F_T)
+#endif
+#if !defined(lzo_int64f_t)
+#if defined(lzo_int64l_t)
+#  define lzo_int64f_t              lzo_int64l_t
+#  define lzo_uint64f_t             lzo_uint64l_t
+#  define LZO_SIZEOF_LZO_INT64F_T   LZO_SIZEOF_LZO_INT64L_T
+#else
+#endif
+#endif
+#if defined(lzo_int64f_t)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64f_t) >= 8)
+   LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64f_t) == LZO_SIZEOF_LZO_INT64F_T)
+#endif
+#if !defined(lzo_intptr_t)
+#if 1 && (LZO_OS_OS400 && (LZO_SIZEOF_VOID_P == 16))
+#  define __LZO_INTPTR_T_IS_POINTER 1
+   typedef char*                    lzo_intptr_t;
+   typedef char*                    lzo_uintptr_t;
+#  define lzo_intptr_t              lzo_intptr_t
+#  define lzo_uintptr_t             lzo_uintptr_t
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_VOID_P
+#elif (LZO_CC_MSC && (_MSC_VER >= 1300) && (LZO_SIZEOF_VOID_P == 4) && (LZO_SIZEOF_INT == 4))
+   typedef __w64 int                lzo_intptr_t;
+   typedef __w64 unsigned int       lzo_uintptr_t;
+#  define lzo_intptr_t              lzo_intptr_t
+#  define lzo_uintptr_t             lzo_uintptr_t
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_INT
+#elif (LZO_SIZEOF_SHORT == LZO_SIZEOF_VOID_P) && (LZO_SIZEOF_INT > LZO_SIZEOF_VOID_P)
+#  define lzo_intptr_t              short
+#  define lzo_uintptr_t             unsigned short
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_SHORT
+#elif (LZO_SIZEOF_INT >= LZO_SIZEOF_VOID_P) && (LZO_SIZEOF_INT < LZO_SIZEOF_LONG)
+#  define lzo_intptr_t              int
+#  define lzo_uintptr_t             unsigned int
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_INT
+#elif (LZO_SIZEOF_LONG >= LZO_SIZEOF_VOID_P)
+#  define lzo_intptr_t              long
+#  define lzo_uintptr_t             unsigned long
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_LONG
+#elif (LZO_SIZEOF_LZO_INT64L_T >= LZO_SIZEOF_VOID_P)
+#  define lzo_intptr_t              lzo_int64l_t
+#  define lzo_uintptr_t             lzo_uint64l_t
+#  define LZO_SIZEOF_LZO_INTPTR_T   LZO_SIZEOF_LZO_INT64L_T
+#else
+#  error "lzo_intptr_t"
+#endif
+#endif
+#if 1
+    LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_intptr_t) >= sizeof(void *))
+    LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_intptr_t) == sizeof(lzo_uintptr_t))
+#endif
+#if !defined(lzo_word_t)
+#if defined(LZO_WORDSIZE) && (LZO_WORDSIZE+0 > 0)
+#if (LZO_WORDSIZE == LZO_SIZEOF_LZO_INTPTR_T) && !(__LZO_INTPTR_T_IS_POINTER)
+#  define lzo_word_t                lzo_uintptr_t
+#  define lzo_sword_t               lzo_intptr_t
+#  define LZO_SIZEOF_LZO_WORD_T LZO_SIZEOF_LZO_INTPTR_T
+#elif (LZO_WORDSIZE == LZO_SIZEOF_LONG)
+#  define lzo_word_t                unsigned long
+#  define lzo_sword_t               long
+#  define LZO_SIZEOF_LZO_WORD_T LZO_SIZEOF_LONG
+#elif (LZO_WORDSIZE == LZO_SIZEOF_INT)
+#  define lzo_word_t                unsigned int
+#  define lzo_sword_t               int
+#  define LZO_SIZEOF_LZO_WORD_T LZO_SIZEOF_INT
+#elif (LZO_WORDSIZE == LZO_SIZEOF_SHORT)
+#  define lzo_word_t                unsigned short
+#  define lzo_sword_t               short
+#  define LZO_SIZEOF_LZO_WORD_T LZO_SIZEOF_SHORT
+#elif (LZO_WORDSIZE == 1)
+#  define lzo_word_t                unsigned char
+#  define lzo_sword_t               signed char
+#  define LZO_SIZEOF_LZO_WORD_T 1
+#elif (LZO_WORDSIZE == LZO_SIZEOF_LZO_INT64L_T)
+#  define lzo_word_t                lzo_uint64l_t
+#  define lzo_sword_t               lzo_int64l_t
+#  define LZO_SIZEOF_LZO_WORD_T LZO_SIZEOF_LZO_INT64L_T
+#elif (LZO_ARCH_SPU) && (LZO_CC_GNUC)
+#if 0
+   typedef unsigned lzo_word_t  __attribute__((__mode__(__V16QI__)));
+   typedef int      lzo_sword_t __attribute__((__mode__(__V16QI__)));
+#  define lzo_word_t                lzo_word_t
+#  define lzo_sword_t               lzo_sword_t
+#  define LZO_SIZEOF_LZO_WORD_T     16
+#endif
+#else
+#  error "lzo_word_t"
+#endif
+#endif
+#endif
+#if 1 && defined(lzo_word_t)
+    LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_word_t)  == LZO_WORDSIZE)
+    LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_sword_t) == LZO_WORDSIZE)
+#endif
+#if 1
+#define lzo_int8_t                  signed char
+#define lzo_uint8_t                 unsigned char
+#define LZO_SIZEOF_LZO_INT8_T       1
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int8_t) == 1)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int8_t) == sizeof(lzo_uint8_t))
+#endif
+#if defined(lzo_int16e_t)
+#define lzo_int16_t                 lzo_int16e_t
+#define lzo_uint16_t                lzo_uint16e_t
+#define LZO_SIZEOF_LZO_INT16_T      LZO_SIZEOF_LZO_INT16E_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int16_t) == 2)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int16_t) == sizeof(lzo_uint16_t))
+#endif
+#if defined(lzo_int32e_t)
+#define lzo_int32_t                 lzo_int32e_t
+#define lzo_uint32_t                lzo_uint32e_t
+#define LZO_SIZEOF_LZO_INT32_T      LZO_SIZEOF_LZO_INT32E_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32_t) == 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32_t) == sizeof(lzo_uint32_t))
+#endif
+#if defined(lzo_int64e_t)
+#define lzo_int64_t                 lzo_int64e_t
+#define lzo_uint64_t                lzo_uint64e_t
+#define LZO_SIZEOF_LZO_INT64_T      LZO_SIZEOF_LZO_INT64E_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64_t) == 8)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64_t) == sizeof(lzo_uint64_t))
+#endif
+#if 1
+#define lzo_int_least32_t           lzo_int32l_t
+#define lzo_uint_least32_t          lzo_uint32l_t
+#define LZO_SIZEOF_LZO_INT_LEAST32_T LZO_SIZEOF_LZO_INT32L_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_least32_t) >= 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_least32_t) == sizeof(lzo_uint_least32_t))
+#endif
+#if defined(lzo_int64l_t)
+#define lzo_int_least64_t           lzo_int64l_t
+#define lzo_uint_least64_t          lzo_uint64l_t
+#define LZO_SIZEOF_LZO_INT_LEAST64_T LZO_SIZEOF_LZO_INT64L_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_least64_t) >= 8)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_least64_t) == sizeof(lzo_uint_least64_t))
+#endif
+#if 1
+#define lzo_int_fast32_t           lzo_int32f_t
+#define lzo_uint_fast32_t          lzo_uint32f_t
+#define LZO_SIZEOF_LZO_INT_FAST32_T LZO_SIZEOF_LZO_INT32F_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_fast32_t) >= 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_fast32_t) == sizeof(lzo_uint_fast32_t))
+#endif
+#if defined(lzo_int64f_t)
+#define lzo_int_fast64_t           lzo_int64f_t
+#define lzo_uint_fast64_t          lzo_uint64f_t
+#define LZO_SIZEOF_LZO_INT_FAST64_T LZO_SIZEOF_LZO_INT64F_T
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_fast64_t) >= 8)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int_fast64_t) == sizeof(lzo_uint_fast64_t))
+#endif
+#if !defined(LZO_INT16_C)
+#  if (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_INT >= 2)
+#    define LZO_INT16_C(c)          ((c) + 0)
+#    define LZO_UINT16_C(c)         ((c) + 0U)
+#  elif (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_LONG >= 2)
+#    define LZO_INT16_C(c)          ((c) + 0L)
+#    define LZO_UINT16_C(c)         ((c) + 0UL)
+#  elif (LZO_SIZEOF_INT >= 2)
+#    define LZO_INT16_C(c)          (c)
+#    define LZO_UINT16_C(c)         (c##U)
+#  elif (LZO_SIZEOF_LONG >= 2)
+#    define LZO_INT16_C(c)          (c##L)
+#    define LZO_UINT16_C(c)         (c##UL)
+#  else
+#    error "LZO_INT16_C"
+#  endif
+#endif
+#if !defined(LZO_INT32_C)
+#  if (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_INT >= 4)
+#    define LZO_INT32_C(c)          ((c) + 0)
+#    define LZO_UINT32_C(c)         ((c) + 0U)
+#  elif (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_LONG >= 4)
+#    define LZO_INT32_C(c)          ((c) + 0L)
+#    define LZO_UINT32_C(c)         ((c) + 0UL)
+#  elif (LZO_SIZEOF_INT >= 4)
+#    define LZO_INT32_C(c)          (c)
+#    define LZO_UINT32_C(c)         (c##U)
+#  elif (LZO_SIZEOF_LONG >= 4)
+#    define LZO_INT32_C(c)          (c##L)
+#    define LZO_UINT32_C(c)         (c##UL)
+#  elif (LZO_SIZEOF_LONG_LONG >= 4)
+#    define LZO_INT32_C(c)          (c##LL)
+#    define LZO_UINT32_C(c)         (c##ULL)
+#  else
+#    error "LZO_INT32_C"
+#  endif
+#endif
+#if !defined(LZO_INT64_C) && defined(lzo_int64l_t)
+#  if (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_INT >= 8)
+#    define LZO_INT64_C(c)          ((c) + 0)
+#    define LZO_UINT64_C(c)         ((c) + 0U)
+#  elif (LZO_BROKEN_INTEGRAL_CONSTANTS) && (LZO_SIZEOF_LONG >= 8)
+#    define LZO_INT64_C(c)          ((c) + 0L)
+#    define LZO_UINT64_C(c)         ((c) + 0UL)
+#  elif (LZO_SIZEOF_INT >= 8)
+#    define LZO_INT64_C(c)          (c)
+#    define LZO_UINT64_C(c)         (c##U)
+#  elif (LZO_SIZEOF_LONG >= 8)
+#    define LZO_INT64_C(c)          (c##L)
+#    define LZO_UINT64_C(c)         (c##UL)
+#  else
+#    error "LZO_INT64_C"
+#  endif
+#endif
+#endif
 
 #endif
 
@@ -1873,7 +3020,7 @@
 #undef LZO_HAVE_CONFIG_H
 #include "minilzo.h"
 
-#if !defined(MINILZO_VERSION) || (MINILZO_VERSION != 0x2040)
+#if !defined(MINILZO_VERSION) || (MINILZO_VERSION != 0x2070)
 #  error "version mismatch in miniLZO source files"
 #endif
 
@@ -1885,23 +3032,9 @@
 #define __LZO_CONF_H 1
 
 #if !defined(__LZO_IN_MINILZO)
-#if (LZO_CFG_FREESTANDING)
+#if defined(LZO_CFG_FREESTANDING) && (LZO_CFG_FREESTANDING)
 #  define LZO_LIBC_FREESTANDING 1
 #  define LZO_OS_FREESTANDING 1
-#  define ACC_LIBC_FREESTANDING 1
-#  define ACC_OS_FREESTANDING 1
-#endif
-#if (LZO_CFG_NO_UNALIGNED)
-#  define ACC_CFG_NO_UNALIGNED 1
-#endif
-#if (LZO_ARCH_GENERIC)
-#  define ACC_ARCH_GENERIC 1
-#endif
-#if (LZO_ABI_NEUTRAL_ENDIAN)
-#  define ACC_ABI_NEUTRAL_ENDIAN 1
-#endif
-#if (LZO_HAVE_CONFIG_H)
-#  define ACC_CONFIG_NO_HEADER 1
 #endif
 #if defined(LZO_CFG_EXTRA_CONFIG_HEADER)
 #  include LZO_CFG_EXTRA_CONFIG_HEADER
@@ -1910,22 +3043,27 @@
 #  error "include this file first"
 #endif
 #include "lzo/lzoconf.h"
-#endif
-
-#if (LZO_VERSION < 0x02000) || !defined(__LZOCONF_H_INCLUDED)
+#if defined(LZO_CFG_EXTRA_CONFIG_HEADER2)
+#  include LZO_CFG_EXTRA_CONFIG_HEADER2
+#endif
+#endif
+
+#if (LZO_VERSION < 0x2070) || !defined(__LZOCONF_H_INCLUDED)
 #  error "version mismatch"
 #endif
 
-#if (LZO_CC_BORLANDC && LZO_ARCH_I086)
-#  pragma option -h
-#endif
-
+#if (LZO_CC_MSC && (_MSC_VER >= 1000 && _MSC_VER < 1100))
+#  pragma warning(disable: 4702)
+#endif
 #if (LZO_CC_MSC && (_MSC_VER >= 1000))
 #  pragma warning(disable: 4127 4701)
+#  pragma warning(disable: 4514 4710 4711)
 #endif
 #if (LZO_CC_MSC && (_MSC_VER >= 1300))
 #  pragma warning(disable: 4820)
-#  pragma warning(disable: 4514 4710 4711)
+#endif
+#if (LZO_CC_MSC && (_MSC_VER >= 1800))
+#  pragma warning(disable: 4746)
 #endif
 
 #if (LZO_CC_SUNPROC)
@@ -1936,48 +3074,15 @@
 #endif
 #endif
 
-#if (__LZO_MMODEL_HUGE) && !(LZO_HAVE_MM_HUGE_PTR)
-#  error "this should not happen - check defines for __huge"
-#endif
-
-#if defined(__LZO_IN_MINILZO) || defined(LZO_CFG_FREESTANDING)
-#elif (LZO_OS_DOS16 || LZO_OS_OS216 || LZO_OS_WIN16)
-#  define ACC_WANT_ACC_INCD_H 1
-#  define ACC_WANT_ACC_INCE_H 1
-#  define ACC_WANT_ACC_INCI_H 1
+#if defined(__LZO_IN_MINILZO) || (LZO_CFG_FREESTANDING)
 #elif 1
 #  include <string.h>
 #else
-#  define ACC_WANT_ACC_INCD_H 1
-#endif
-
-#if (LZO_ARCH_I086)
-#  define ACC_MM_AHSHIFT        LZO_MM_AHSHIFT
-#  define ACC_PTR_FP_OFF(x)     (((const unsigned __far*)&(x))[0])
-#  define ACC_PTR_FP_SEG(x)     (((const unsigned __far*)&(x))[1])
-#  define ACC_PTR_MK_FP(s,o)    ((void __far*)(((unsigned long)(s)<<16)+(unsigned)(o)))
-#endif
-
-#if !defined(lzo_uintptr_t)
-#  if defined(__LZO_MMODEL_HUGE)
-#    define lzo_uintptr_t       unsigned long
-#  elif 1 && defined(LZO_OS_OS400) && (LZO_SIZEOF_VOID_P == 16)
-#    define __LZO_UINTPTR_T_IS_POINTER 1
-     typedef char*              lzo_uintptr_t;
-#    define lzo_uintptr_t       lzo_uintptr_t
-#  elif (LZO_SIZEOF_SIZE_T == LZO_SIZEOF_VOID_P)
-#    define lzo_uintptr_t       size_t
-#  elif (LZO_SIZEOF_LONG == LZO_SIZEOF_VOID_P)
-#    define lzo_uintptr_t       unsigned long
-#  elif (LZO_SIZEOF_INT == LZO_SIZEOF_VOID_P)
-#    define lzo_uintptr_t       unsigned int
-#  elif (LZO_SIZEOF_LONG_LONG == LZO_SIZEOF_VOID_P)
-#    define lzo_uintptr_t       unsigned long long
-#  else
-#    define lzo_uintptr_t       size_t
-#  endif
-#endif
-LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uintptr_t) >= sizeof(lzo_voidp))
+#  define LZO_WANT_ACC_INCD_H 1
+#endif
+#if defined(LZO_HAVE_CONFIG_H)
+#  define LZO_CFG_NO_CONFIG_HEADER 1
+#endif
 
 #if 1 && !defined(LZO_CFG_FREESTANDING)
 #if 1 && !defined(HAVE_STRING_H)
@@ -1999,6 +3104,23 @@
 
 #if 1 && defined(HAVE_STRING_H)
 #include <string.h>
+#endif
+
+#if 1 || defined(lzo_int8_t) || defined(lzo_uint8_t)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int8_t)  == 1)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint8_t) == 1)
+#endif
+#if 1 || defined(lzo_int16_t) || defined(lzo_uint16_t)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int16_t)  == 2)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint16_t) == 2)
+#endif
+#if 1 || defined(lzo_int32_t) || defined(lzo_uint32_t)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int32_t)  == 4)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint32_t) == 4)
+#endif
+#if defined(lzo_int64_t) || defined(lzo_uint64_t)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_int64_t)  == 8)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint64_t) == 8)
 #endif
 
 #if (LZO_CFG_FREESTANDING)
@@ -2011,28 +3133,28 @@
 #if !(HAVE_MEMCMP)
 #  undef memcmp
 #  define memcmp(a,b,c)         lzo_memcmp(a,b,c)
-#elif !(__LZO_MMODEL_HUGE)
+#else
 #  undef lzo_memcmp
 #  define lzo_memcmp(a,b,c)     memcmp(a,b,c)
 #endif
 #if !(HAVE_MEMCPY)
 #  undef memcpy
 #  define memcpy(a,b,c)         lzo_memcpy(a,b,c)
-#elif !(__LZO_MMODEL_HUGE)
+#else
 #  undef lzo_memcpy
 #  define lzo_memcpy(a,b,c)     memcpy(a,b,c)
 #endif
 #if !(HAVE_MEMMOVE)
 #  undef memmove
 #  define memmove(a,b,c)        lzo_memmove(a,b,c)
-#elif !(__LZO_MMODEL_HUGE)
+#else
 #  undef lzo_memmove
 #  define lzo_memmove(a,b,c)    memmove(a,b,c)
 #endif
 #if !(HAVE_MEMSET)
 #  undef memset
 #  define memset(a,b,c)         lzo_memset(a,b,c)
-#elif !(__LZO_MMODEL_HUGE)
+#else
 #  undef lzo_memset
 #  define lzo_memset(a,b,c)     memset(a,b,c)
 #endif
@@ -2057,26 +3179,28 @@
 #  define BOUNDS_CHECKING_OFF_IN_EXPR(expr)     (expr)
 #endif
 
-#if !defined(__lzo_inline)
-#  define __lzo_inline              /*empty*/
-#endif
-#if !defined(__lzo_forceinline)
-#  define __lzo_forceinline         /*empty*/
-#endif
-#if !defined(__lzo_noinline)
-#  define __lzo_noinline            /*empty*/
-#endif
-
 #if (LZO_CFG_PGO)
-#  undef __acc_likely
-#  undef __acc_unlikely
 #  undef __lzo_likely
 #  undef __lzo_unlikely
-#  define __acc_likely(e)       (e)
-#  define __acc_unlikely(e)     (e)
 #  define __lzo_likely(e)       (e)
 #  define __lzo_unlikely(e)     (e)
 #endif
+
+#undef _
+#undef __
+#undef ___
+#undef ____
+#undef _p0
+#undef _p1
+#undef _p2
+#undef _p3
+#undef _p4
+#undef _s0
+#undef _s1
+#undef _s2
+#undef _s3
+#undef _s4
+#undef _ww
 
 #if 1
 #  define LZO_BYTE(x)       ((unsigned char) (x))
@@ -2096,48 +3220,548 @@
 #define LZO_SIZE(bits)      (1u << (bits))
 #define LZO_MASK(bits)      (LZO_SIZE(bits) - 1)
 
-#define LZO_LSIZE(bits)     (1ul << (bits))
-#define LZO_LMASK(bits)     (LZO_LSIZE(bits) - 1)
-
 #define LZO_USIZE(bits)     ((lzo_uint) 1 << (bits))
 #define LZO_UMASK(bits)     (LZO_USIZE(bits) - 1)
 
 #if !defined(DMUL)
 #if 0
 
-#  define DMUL(a,b) ((lzo_xint) ((lzo_uint32)(a) * (lzo_uint32)(b)))
+#  define DMUL(a,b) ((lzo_xint) ((lzo_uint32_t)(a) * (lzo_uint32_t)(b)))
 #else
 #  define DMUL(a,b) ((lzo_xint) ((a) * (b)))
 #endif
 #endif
 
-#if 1 && !(LZO_CFG_NO_UNALIGNED)
-#if 1 && (LZO_ARCH_AMD64 || LZO_ARCH_I386 || LZO_ARCH_POWERPC)
-#  if (LZO_SIZEOF_SHORT == 2)
-#    define LZO_UNALIGNED_OK_2 1
-#  endif
-#  if (LZO_SIZEOF_INT == 4)
-#    define LZO_UNALIGNED_OK_4 1
-#  endif
-#endif
-#endif
-
-#if defined(LZO_UNALIGNED_OK_2)
-  LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(short) == 2)
-#endif
-#if defined(LZO_UNALIGNED_OK_4)
-  LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint32) == 4)
-#elif defined(LZO_ALIGNED_OK_4)
-  LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(lzo_uint32) == 4)
-#endif
-
-#undef COPY4
-#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
-#  if 1 && defined(ACC_UA_COPY32)
-#    define COPY4(d,s)  ACC_UA_COPY32(d,s)
-#  else
-#    define COPY4(d,s)  (* (__lzo_ua_volatile lzo_uint32p)(__lzo_ua_volatile lzo_voidp)(d) = * (__lzo_ua_volatile const lzo_uint32p)(__lzo_ua_volatile const lzo_voidp)(s))
-#  endif
+#ifndef __LZO_FUNC_H
+#define __LZO_FUNC_H 1
+
+#if !defined(LZO_BITOPS_USE_ASM_BITSCAN) && !defined(LZO_BITOPS_USE_GNUC_BITSCAN) && !defined(LZO_BITOPS_USE_MSC_BITSCAN)
+#if 1 && (LZO_ARCH_AMD64) && (LZO_CC_GNUC && (LZO_CC_GNUC < 0x040000ul)) && (LZO_ASM_SYNTAX_GNUC)
+#define LZO_BITOPS_USE_ASM_BITSCAN 1
+#elif (LZO_CC_CLANG || (LZO_CC_GNUC >= 0x030400ul) || (LZO_CC_INTELC_GNUC && (__INTEL_COMPILER >= 1000)) || (LZO_CC_LLVM && (!defined(__llvm_tools_version__) || (__llvm_tools_version__+0 >= 0x010500ul))))
+#define LZO_BITOPS_USE_GNUC_BITSCAN 1
+#elif (LZO_OS_WIN32 || LZO_OS_WIN64) && ((LZO_CC_INTELC_MSC && (__INTEL_COMPILER >= 1010)) || (LZO_CC_MSC && (_MSC_VER >= 1400)))
+#define LZO_BITOPS_USE_MSC_BITSCAN 1
+#if (LZO_CC_MSC) && (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+#include <intrin.h>
+#endif
+#if (LZO_CC_MSC) && (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+#pragma intrinsic(_BitScanReverse)
+#pragma intrinsic(_BitScanForward)
+#endif
+#if (LZO_CC_MSC) && (LZO_ARCH_AMD64)
+#pragma intrinsic(_BitScanReverse64)
+#pragma intrinsic(_BitScanForward64)
+#endif
+#endif
+#endif
+
+__lzo_static_forceinline unsigned lzo_bitops_ctlz32_func(lzo_uint32_t v)
+{
+#if (LZO_BITOPS_USE_MSC_BITSCAN) && (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+    unsigned long r; (void) _BitScanReverse(&r, v); return (unsigned) r ^ 31;
+#define lzo_bitops_ctlz32(v)    lzo_bitops_ctlz32_func(v)
+#elif (LZO_BITOPS_USE_ASM_BITSCAN) && (LZO_ARCH_AMD64 || LZO_ARCH_I386) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_uint32_t r;
+    __asm__("bsr %1,%0" : "=r" (r) : "rm" (v) __LZO_ASM_CLOBBER_LIST_CC);
+    return (unsigned) r ^ 31;
+#define lzo_bitops_ctlz32(v)    lzo_bitops_ctlz32_func(v)
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_INT == 4)
+    unsigned r; r = (unsigned) __builtin_clz(v); return r;
+#define lzo_bitops_ctlz32(v)    ((unsigned) __builtin_clz(v))
+#else
+    LZO_UNUSED(v); return 0;
+#endif
+}
+
+#if defined(lzo_uint64_t)
+__lzo_static_forceinline unsigned lzo_bitops_ctlz64_func(lzo_uint64_t v)
+{
+#if (LZO_BITOPS_USE_MSC_BITSCAN) && (LZO_ARCH_AMD64)
+    unsigned long r; (void) _BitScanReverse64(&r, v); return (unsigned) r ^ 63;
+#define lzo_bitops_ctlz64(v)    lzo_bitops_ctlz64_func(v)
+#elif (LZO_BITOPS_USE_ASM_BITSCAN) && (LZO_ARCH_AMD64) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_uint64_t r;
+    __asm__("bsr %1,%0" : "=r" (r) : "rm" (v) __LZO_ASM_CLOBBER_LIST_CC);
+    return (unsigned) r ^ 63;
+#define lzo_bitops_ctlz64(v)    lzo_bitops_ctlz64_func(v)
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_LONG == 8) && (LZO_WORDSIZE >= 8)
+    unsigned r; r = (unsigned) __builtin_clzl(v); return r;
+#define lzo_bitops_ctlz64(v)    ((unsigned) __builtin_clzl(v))
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_LONG_LONG == 8) && (LZO_WORDSIZE >= 8)
+    unsigned r; r = (unsigned) __builtin_clzll(v); return r;
+#define lzo_bitops_ctlz64(v)    ((unsigned) __builtin_clzll(v))
+#else
+    LZO_UNUSED(v); return 0;
+#endif
+}
+#endif
+
+__lzo_static_forceinline unsigned lzo_bitops_cttz32_func(lzo_uint32_t v)
+{
+#if (LZO_BITOPS_USE_MSC_BITSCAN) && (LZO_ARCH_AMD64 || LZO_ARCH_I386)
+    unsigned long r; (void) _BitScanForward(&r, v); return (unsigned) r;
+#define lzo_bitops_cttz32(v)    lzo_bitops_cttz32_func(v)
+#elif (LZO_BITOPS_USE_ASM_BITSCAN) && (LZO_ARCH_AMD64 || LZO_ARCH_I386) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_uint32_t r;
+    __asm__("bsf %1,%0" : "=r" (r) : "rm" (v) __LZO_ASM_CLOBBER_LIST_CC);
+    return (unsigned) r;
+#define lzo_bitops_cttz32(v)    lzo_bitops_cttz32_func(v)
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_INT >= 4)
+    unsigned r; r = (unsigned) __builtin_ctz(v); return r;
+#define lzo_bitops_cttz32(v)    ((unsigned) __builtin_ctz(v))
+#else
+    LZO_UNUSED(v); return 0;
+#endif
+}
+
+#if defined(lzo_uint64_t)
+__lzo_static_forceinline unsigned lzo_bitops_cttz64_func(lzo_uint64_t v)
+{
+#if (LZO_BITOPS_USE_MSC_BITSCAN) && (LZO_ARCH_AMD64)
+    unsigned long r; (void) _BitScanForward64(&r, v); return (unsigned) r;
+#define lzo_bitops_cttz64(v)    lzo_bitops_cttz64_func(v)
+#elif (LZO_BITOPS_USE_ASM_BITSCAN) && (LZO_ARCH_AMD64) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_uint64_t r;
+    __asm__("bsf %1,%0" : "=r" (r) : "rm" (v) __LZO_ASM_CLOBBER_LIST_CC);
+    return (unsigned) r;
+#define lzo_bitops_cttz64(v)    lzo_bitops_cttz64_func(v)
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_LONG >= 8) && (LZO_WORDSIZE >= 8)
+    unsigned r; r = (unsigned) __builtin_ctzl(v); return r;
+#define lzo_bitops_cttz64(v)    ((unsigned) __builtin_ctzl(v))
+#elif (LZO_BITOPS_USE_GNUC_BITSCAN) && (LZO_SIZEOF_LONG_LONG >= 8) && (LZO_WORDSIZE >= 8)
+    unsigned r; r = (unsigned) __builtin_ctzll(v); return r;
+#define lzo_bitops_cttz64(v)    ((unsigned) __builtin_ctzll(v))
+#else
+    LZO_UNUSED(v); return 0;
+#endif
+}
+#endif
+
+#if 1 && (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || (LZO_CC_GNUC >= 0x020700ul) || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
+static void __attribute__((__unused__))
+#else
+__lzo_static_forceinline void
+#endif
+lzo_bitops_unused_funcs(void)
+{
+    LZO_UNUSED_FUNC(lzo_bitops_ctlz32_func);
+    LZO_UNUSED_FUNC(lzo_bitops_cttz32_func);
+#if defined(lzo_uint64_t)
+    LZO_UNUSED_FUNC(lzo_bitops_ctlz64_func);
+    LZO_UNUSED_FUNC(lzo_bitops_cttz64_func);
+#endif
+    LZO_UNUSED_FUNC(lzo_bitops_unused_funcs);
+}
+
+#if defined(__lzo_alignof) && !(LZO_CFG_NO_UNALIGNED)
+#ifndef __lzo_memops_tcheck
+#define __lzo_memops_tcheck(t,a,b) ((void)0, sizeof(t) == (a) && __lzo_alignof(t) == (b))
+#endif
+#endif
+#ifndef lzo_memops_TU0p
+#define lzo_memops_TU0p void __LZO_MMODEL *
+#endif
+#ifndef lzo_memops_TU1p
+#define lzo_memops_TU1p unsigned char __LZO_MMODEL *
+#endif
+#ifndef lzo_memops_TU2p
+#if (LZO_OPT_UNALIGNED16)
+typedef lzo_uint16_t __lzo_may_alias lzo_memops_TU2;
+#define lzo_memops_TU2p volatile lzo_memops_TU2 *
+#elif defined(__lzo_byte_struct)
+__lzo_byte_struct(lzo_memops_TU2_struct,2)
+typedef struct lzo_memops_TU2_struct lzo_memops_TU2;
+#else
+struct lzo_memops_TU2_struct { unsigned char a[2]; } __lzo_may_alias;
+typedef struct lzo_memops_TU2_struct lzo_memops_TU2;
+#endif
+#ifndef lzo_memops_TU2p
+#define lzo_memops_TU2p lzo_memops_TU2 *
+#endif
+#endif
+#ifndef lzo_memops_TU4p
+#if (LZO_OPT_UNALIGNED32)
+typedef lzo_uint32_t __lzo_may_alias lzo_memops_TU4;
+#define lzo_memops_TU4p volatile lzo_memops_TU4 __LZO_MMODEL *
+#elif defined(__lzo_byte_struct)
+__lzo_byte_struct(lzo_memops_TU4_struct,4)
+typedef struct lzo_memops_TU4_struct lzo_memops_TU4;
+#else
+struct lzo_memops_TU4_struct { unsigned char a[4]; } __lzo_may_alias;
+typedef struct lzo_memops_TU4_struct lzo_memops_TU4;
+#endif
+#ifndef lzo_memops_TU4p
+#define lzo_memops_TU4p lzo_memops_TU4 __LZO_MMODEL *
+#endif
+#endif
+#ifndef lzo_memops_TU8p
+#if (LZO_OPT_UNALIGNED64)
+typedef lzo_uint64_t __lzo_may_alias lzo_memops_TU8;
+#define lzo_memops_TU8p volatile lzo_memops_TU8 __LZO_MMODEL *
+#elif defined(__lzo_byte_struct)
+__lzo_byte_struct(lzo_memops_TU8_struct,8)
+typedef struct lzo_memops_TU8_struct lzo_memops_TU8;
+#else
+struct lzo_memops_TU8_struct { unsigned char a[8]; } __lzo_may_alias;
+typedef struct lzo_memops_TU8_struct lzo_memops_TU8;
+#endif
+#ifndef lzo_memops_TU8p
+#define lzo_memops_TU8p lzo_memops_TU8 __LZO_MMODEL *
+#endif
+#endif
+#ifndef lzo_memops_set_TU1p
+#define lzo_memops_set_TU1p     volatile lzo_memops_TU1p
+#endif
+#ifndef lzo_memops_move_TU1p
+#define lzo_memops_move_TU1p    lzo_memops_TU1p
+#endif
+#define LZO_MEMOPS_SET1(dd,cc) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_set_TU1p d__1 = (lzo_memops_set_TU1p) (lzo_memops_TU0p) (dd); \
+    d__1[0] = LZO_BYTE(cc); \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_SET2(dd,cc) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_set_TU1p d__2 = (lzo_memops_set_TU1p) (lzo_memops_TU0p) (dd); \
+    d__2[0] = LZO_BYTE(cc); d__2[1] = LZO_BYTE(cc); \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_SET3(dd,cc) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_set_TU1p d__3 = (lzo_memops_set_TU1p) (lzo_memops_TU0p) (dd); \
+    d__3[0] = LZO_BYTE(cc); d__3[1] = LZO_BYTE(cc); d__3[2] = LZO_BYTE(cc); \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_SET4(dd,cc) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_set_TU1p d__4 = (lzo_memops_set_TU1p) (lzo_memops_TU0p) (dd); \
+    d__4[0] = LZO_BYTE(cc); d__4[1] = LZO_BYTE(cc); d__4[2] = LZO_BYTE(cc); d__4[3] = LZO_BYTE(cc); \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_MOVE1(dd,ss) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_move_TU1p d__1 = (lzo_memops_move_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_move_TU1p s__1 = (const lzo_memops_move_TU1p) (const lzo_memops_TU0p) (ss); \
+    d__1[0] = s__1[0]; \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_MOVE2(dd,ss) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_move_TU1p d__2 = (lzo_memops_move_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_move_TU1p s__2 = (const lzo_memops_move_TU1p) (const lzo_memops_TU0p) (ss); \
+    d__2[0] = s__2[0]; d__2[1] = s__2[1]; \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_MOVE3(dd,ss) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_move_TU1p d__3 = (lzo_memops_move_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_move_TU1p s__3 = (const lzo_memops_move_TU1p) (const lzo_memops_TU0p) (ss); \
+    d__3[0] = s__3[0]; d__3[1] = s__3[1]; d__3[2] = s__3[2]; \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_MOVE4(dd,ss) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_move_TU1p d__4 = (lzo_memops_move_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_move_TU1p s__4 = (const lzo_memops_move_TU1p) (const lzo_memops_TU0p) (ss); \
+    d__4[0] = s__4[0]; d__4[1] = s__4[1]; d__4[2] = s__4[2]; d__4[3] = s__4[3]; \
+    LZO_BLOCK_END
+#define LZO_MEMOPS_MOVE8(dd,ss) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_move_TU1p d__8 = (lzo_memops_move_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_move_TU1p s__8 = (const lzo_memops_move_TU1p) (const lzo_memops_TU0p) (ss); \
+    d__8[0] = s__8[0]; d__8[1] = s__8[1]; d__8[2] = s__8[2]; d__8[3] = s__8[3]; \
+    d__8[4] = s__8[4]; d__8[5] = s__8[5]; d__8[6] = s__8[6]; d__8[7] = s__8[7]; \
+    LZO_BLOCK_END
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(*(lzo_memops_TU1p)0)==1)
+#define LZO_MEMOPS_COPY1(dd,ss) LZO_MEMOPS_MOVE1(dd,ss)
+#if (LZO_OPT_UNALIGNED16)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(*(lzo_memops_TU2p)0)==2)
+#define LZO_MEMOPS_COPY2(dd,ss) \
+    * (lzo_memops_TU2p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU2p) (const lzo_memops_TU0p) (ss)
+#elif defined(__lzo_memops_tcheck)
+#define LZO_MEMOPS_COPY2(dd,ss) \
+    LZO_BLOCK_BEGIN if (__lzo_memops_tcheck(lzo_memops_TU2,2,1)) { \
+        * (lzo_memops_TU2p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU2p) (const lzo_memops_TU0p) (ss); \
+    } else { LZO_MEMOPS_MOVE2(dd,ss); } LZO_BLOCK_END
+#else
+#define LZO_MEMOPS_COPY2(dd,ss) LZO_MEMOPS_MOVE2(dd,ss)
+#endif
+#if (LZO_OPT_UNALIGNED32)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(*(lzo_memops_TU4p)0)==4)
+#define LZO_MEMOPS_COPY4(dd,ss) \
+    * (lzo_memops_TU4p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU4p) (const lzo_memops_TU0p) (ss)
+#elif defined(__lzo_memops_tcheck)
+#define LZO_MEMOPS_COPY4(dd,ss) \
+    LZO_BLOCK_BEGIN if (__lzo_memops_tcheck(lzo_memops_TU4,4,1)) { \
+        * (lzo_memops_TU4p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU4p) (const lzo_memops_TU0p) (ss); \
+    } else { LZO_MEMOPS_MOVE4(dd,ss); } LZO_BLOCK_END
+#else
+#define LZO_MEMOPS_COPY4(dd,ss) LZO_MEMOPS_MOVE4(dd,ss)
+#endif
+#if (LZO_WORDSIZE != 8)
+#define LZO_MEMOPS_COPY8(dd,ss) \
+    LZO_BLOCK_BEGIN LZO_MEMOPS_COPY4(dd,ss); LZO_MEMOPS_COPY4((lzo_memops_TU1p)(lzo_memops_TU0p)(dd)+4,(const lzo_memops_TU1p)(const lzo_memops_TU0p)(ss)+4); LZO_BLOCK_END
+#else
+#if (LZO_OPT_UNALIGNED64)
+LZO_COMPILE_TIME_ASSERT_HEADER(sizeof(*(lzo_memops_TU8p)0)==8)
+#define LZO_MEMOPS_COPY8(dd,ss) \
+    * (lzo_memops_TU8p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU8p) (const lzo_memops_TU0p) (ss)
+#elif (LZO_OPT_UNALIGNED32)
+#define LZO_MEMOPS_COPY8(dd,ss) \
+    LZO_BLOCK_BEGIN LZO_MEMOPS_COPY4(dd,ss); LZO_MEMOPS_COPY4((lzo_memops_TU1p)(lzo_memops_TU0p)(dd)+4,(const lzo_memops_TU1p)(const lzo_memops_TU0p)(ss)+4); LZO_BLOCK_END
+#elif defined(__lzo_memops_tcheck)
+#define LZO_MEMOPS_COPY8(dd,ss) \
+    LZO_BLOCK_BEGIN if (__lzo_memops_tcheck(lzo_memops_TU8,8,1)) { \
+        * (lzo_memops_TU8p) (lzo_memops_TU0p) (dd) = * (const lzo_memops_TU8p) (const lzo_memops_TU0p) (ss); \
+    } else { LZO_MEMOPS_MOVE8(dd,ss); } LZO_BLOCK_END
+#else
+#define LZO_MEMOPS_COPY8(dd,ss) LZO_MEMOPS_MOVE8(dd,ss)
+#endif
+#endif
+#define LZO_MEMOPS_COPYN(dd,ss,nn) \
+    LZO_BLOCK_BEGIN \
+    lzo_memops_TU1p d__n = (lzo_memops_TU1p) (lzo_memops_TU0p) (dd); \
+    const lzo_memops_TU1p s__n = (const lzo_memops_TU1p) (const lzo_memops_TU0p) (ss); \
+    lzo_uint n__n = (nn); \
+    while ((void)0, n__n >= 8) { LZO_MEMOPS_COPY8(d__n, s__n); d__n += 8; s__n += 8; n__n -= 8; } \
+    if ((void)0, n__n >= 4) { LZO_MEMOPS_COPY4(d__n, s__n); d__n += 4; s__n += 4; n__n -= 4; } \
+    if ((void)0, n__n > 0) do { *d__n++ = *s__n++; } while (--n__n > 0); \
+    LZO_BLOCK_END
+
+__lzo_static_forceinline lzo_uint16_t lzo_memops_get_le16(const lzo_voidp ss)
+{
+    lzo_uint16_t v;
+#if (LZO_ABI_LITTLE_ENDIAN)
+    LZO_MEMOPS_COPY2(&v, ss);
+#elif (LZO_OPT_UNALIGNED16 && LZO_ARCH_POWERPC && LZO_ABI_BIG_ENDIAN) && (LZO_ASM_SYNTAX_GNUC)
+    const lzo_memops_TU2p s = (const lzo_memops_TU2p) ss;
+    unsigned long vv;
+    __asm__("lhbrx %0,0,%1" : "=r" (vv) : "r" (s), "m" (*s));
+    v = (lzo_uint16_t) vv;
+#else
+    const lzo_memops_TU1p s = (const lzo_memops_TU1p) ss;
+    v = (lzo_uint16_t) (((lzo_uint16_t)s[0]) | ((lzo_uint16_t)s[1] << 8));
+#endif
+    return v;
+}
+#if (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
+#define LZO_MEMOPS_GET_LE16(ss)    * (const lzo_memops_TU2p) (const lzo_memops_TU0p) (ss)
+#else
+#define LZO_MEMOPS_GET_LE16(ss)    lzo_memops_get_le16(ss)
+#endif
+
+__lzo_static_forceinline lzo_uint32_t lzo_memops_get_le32(const lzo_voidp ss)
+{
+    lzo_uint32_t v;
+#if (LZO_ABI_LITTLE_ENDIAN)
+    LZO_MEMOPS_COPY4(&v, ss);
+#elif (LZO_OPT_UNALIGNED32 && LZO_ARCH_POWERPC && LZO_ABI_BIG_ENDIAN) && (LZO_ASM_SYNTAX_GNUC)
+    const lzo_memops_TU4p s = (const lzo_memops_TU4p) ss;
+    unsigned long vv;
+    __asm__("lwbrx %0,0,%1" : "=r" (vv) : "r" (s), "m" (*s));
+    v = (lzo_uint32_t) vv;
+#else
+    const lzo_memops_TU1p s = (const lzo_memops_TU1p) ss;
+    v = (lzo_uint32_t) (((lzo_uint32_t)s[0] << 24) | ((lzo_uint32_t)s[1] << 16) | ((lzo_uint32_t)s[2] << 8) | ((lzo_uint32_t)s[3]));
+#endif
+    return v;
+}
+#if (LZO_OPT_UNALIGNED32) && (LZO_ABI_LITTLE_ENDIAN)
+#define LZO_MEMOPS_GET_LE32(ss)    * (const lzo_memops_TU4p) (const lzo_memops_TU0p) (ss)
+#else
+#define LZO_MEMOPS_GET_LE32(ss)    lzo_memops_get_le32(ss)
+#endif
+
+#if (LZO_OPT_UNALIGNED64) && (LZO_ABI_LITTLE_ENDIAN)
+#define LZO_MEMOPS_GET_LE64(ss)    * (const lzo_memops_TU8p) (const lzo_memops_TU0p) (ss)
+#endif
+
+__lzo_static_forceinline lzo_uint16_t lzo_memops_get_ne16(const lzo_voidp ss)
+{
+    lzo_uint16_t v;
+    LZO_MEMOPS_COPY2(&v, ss);
+    return v;
+}
+#if (LZO_OPT_UNALIGNED16)
+#define LZO_MEMOPS_GET_NE16(ss)    * (const lzo_memops_TU2p) (const lzo_memops_TU0p) (ss)
+#else
+#define LZO_MEMOPS_GET_NE16(ss)    lzo_memops_get_ne16(ss)
+#endif
+
+__lzo_static_forceinline lzo_uint32_t lzo_memops_get_ne32(const lzo_voidp ss)
+{
+    lzo_uint32_t v;
+    LZO_MEMOPS_COPY4(&v, ss);
+    return v;
+}
+#if (LZO_OPT_UNALIGNED32)
+#define LZO_MEMOPS_GET_NE32(ss)    * (const lzo_memops_TU4p) (const lzo_memops_TU0p) (ss)
+#else
+#define LZO_MEMOPS_GET_NE32(ss)    lzo_memops_get_ne32(ss)
+#endif
+
+#if (LZO_OPT_UNALIGNED64)
+#define LZO_MEMOPS_GET_NE64(ss)    * (const lzo_memops_TU8p) (const lzo_memops_TU0p) (ss)
+#endif
+
+__lzo_static_forceinline void lzo_memops_put_le16(lzo_voidp dd, lzo_uint16_t vv)
+{
+#if (LZO_ABI_LITTLE_ENDIAN)
+    LZO_MEMOPS_COPY2(dd, &vv);
+#elif (LZO_OPT_UNALIGNED16 && LZO_ARCH_POWERPC && LZO_ABI_BIG_ENDIAN) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_memops_TU2p d = (lzo_memops_TU2p) dd;
+    unsigned long v = vv;
+    __asm__("sthbrx %2,0,%1" : "=m" (*d) : "r" (d), "r" (v));
+#else
+    lzo_memops_TU1p d = (lzo_memops_TU1p) dd;
+    d[0] = LZO_BYTE((vv      ) & 0xff);
+    d[1] = LZO_BYTE((vv >>  8) & 0xff);
+#endif
+}
+#if (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
+#define LZO_MEMOPS_PUT_LE16(dd,vv) (* (lzo_memops_TU2p) (lzo_memops_TU0p) (dd) = (vv))
+#else
+#define LZO_MEMOPS_PUT_LE16(dd,vv) lzo_memops_put_le16(dd,vv)
+#endif
+
+__lzo_static_forceinline void lzo_memops_put_le32(lzo_voidp dd, lzo_uint32_t vv)
+{
+#if (LZO_ABI_LITTLE_ENDIAN)
+    LZO_MEMOPS_COPY4(dd, &vv);
+#elif (LZO_OPT_UNALIGNED32 && LZO_ARCH_POWERPC && LZO_ABI_BIG_ENDIAN) && (LZO_ASM_SYNTAX_GNUC)
+    lzo_memops_TU4p d = (lzo_memops_TU4p) dd;
+    unsigned long v = vv;
+    __asm__("stwbrx %2,0,%1" : "=m" (*d) : "r" (d), "r" (v));
+#else
+    lzo_memops_TU1p d = (lzo_memops_TU1p) dd;
+    d[0] = LZO_BYTE((vv      ) & 0xff);
+    d[1] = LZO_BYTE((vv >>  8) & 0xff);
+    d[2] = LZO_BYTE((vv >> 16) & 0xff);
+    d[3] = LZO_BYTE((vv >> 24) & 0xff);
+#endif
+}
+#if (LZO_OPT_UNALIGNED32) && (LZO_ABI_LITTLE_ENDIAN)
+#define LZO_MEMOPS_PUT_LE32(dd,vv) (* (lzo_memops_TU4p) (lzo_memops_TU0p) (dd) = (vv))
+#else
+#define LZO_MEMOPS_PUT_LE32(dd,vv) lzo_memops_put_le32(dd,vv)
+#endif
+
+__lzo_static_forceinline void lzo_memops_put_ne16(lzo_voidp dd, lzo_uint16_t vv)
+{
+    LZO_MEMOPS_COPY2(dd, &vv);
+}
+#if (LZO_OPT_UNALIGNED16)
+#define LZO_MEMOPS_PUT_NE16(dd,vv) (* (lzo_memops_TU2p) (lzo_memops_TU0p) (dd) = (vv))
+#else
+#define LZO_MEMOPS_PUT_NE16(dd,vv) lzo_memops_put_ne16(dd,vv)
+#endif
+
+__lzo_static_forceinline void lzo_memops_put_ne32(lzo_voidp dd, lzo_uint32_t vv)
+{
+    LZO_MEMOPS_COPY4(dd, &vv);
+}
+#if (LZO_OPT_UNALIGNED32)
+#define LZO_MEMOPS_PUT_NE32(dd,vv) (* (lzo_memops_TU4p) (lzo_memops_TU0p) (dd) = (vv))
+#else
+#define LZO_MEMOPS_PUT_NE32(dd,vv) lzo_memops_put_ne32(dd,vv)
+#endif
+
+#if 1 && (LZO_CC_ARMCC_GNUC || LZO_CC_CLANG || (LZO_CC_GNUC >= 0x020700ul) || LZO_CC_INTELC_GNUC || LZO_CC_LLVM || LZO_CC_PATHSCALE || LZO_CC_PGI)
+static void __attribute__((__unused__))
+#else
+__lzo_static_forceinline void
+#endif
+lzo_memops_unused_funcs(void)
+{
+    LZO_UNUSED_FUNC(lzo_memops_get_le16);
+    LZO_UNUSED_FUNC(lzo_memops_get_le32);
+    LZO_UNUSED_FUNC(lzo_memops_get_ne16);
+    LZO_UNUSED_FUNC(lzo_memops_get_ne32);
+    LZO_UNUSED_FUNC(lzo_memops_put_le16);
+    LZO_UNUSED_FUNC(lzo_memops_put_le32);
+    LZO_UNUSED_FUNC(lzo_memops_put_ne16);
+    LZO_UNUSED_FUNC(lzo_memops_put_ne32);
+    LZO_UNUSED_FUNC(lzo_memops_unused_funcs);
+}
+
+#endif
+
+#ifndef UA_SET1
+#define UA_SET1             LZO_MEMOPS_SET1
+#endif
+#ifndef UA_SET2
+#define UA_SET2             LZO_MEMOPS_SET2
+#endif
+#ifndef UA_SET3
+#define UA_SET3             LZO_MEMOPS_SET3
+#endif
+#ifndef UA_SET4
+#define UA_SET4             LZO_MEMOPS_SET4
+#endif
+#ifndef UA_MOVE1
+#define UA_MOVE1            LZO_MEMOPS_MOVE1
+#endif
+#ifndef UA_MOVE2
+#define UA_MOVE2            LZO_MEMOPS_MOVE2
+#endif
+#ifndef UA_MOVE3
+#define UA_MOVE3            LZO_MEMOPS_MOVE3
+#endif
+#ifndef UA_MOVE4
+#define UA_MOVE4            LZO_MEMOPS_MOVE4
+#endif
+#ifndef UA_MOVE8
+#define UA_MOVE8            LZO_MEMOPS_MOVE8
+#endif
+#ifndef UA_COPY1
+#define UA_COPY1            LZO_MEMOPS_COPY1
+#endif
+#ifndef UA_COPY2
+#define UA_COPY2            LZO_MEMOPS_COPY2
+#endif
+#ifndef UA_COPY3
+#define UA_COPY3            LZO_MEMOPS_COPY3
+#endif
+#ifndef UA_COPY4
+#define UA_COPY4            LZO_MEMOPS_COPY4
+#endif
+#ifndef UA_COPY8
+#define UA_COPY8            LZO_MEMOPS_COPY8
+#endif
+#ifndef UA_COPYN
+#define UA_COPYN            LZO_MEMOPS_COPYN
+#endif
+#ifndef UA_COPYN_X
+#define UA_COPYN_X          LZO_MEMOPS_COPYN
+#endif
+#ifndef UA_GET_LE16
+#define UA_GET_LE16         LZO_MEMOPS_GET_LE16
+#endif
+#ifndef UA_GET_LE32
+#define UA_GET_LE32         LZO_MEMOPS_GET_LE32
+#endif
+#ifdef LZO_MEMOPS_GET_LE64
+#ifndef UA_GET_LE64
+#define UA_GET_LE64         LZO_MEMOPS_GET_LE64
+#endif
+#endif
+#ifndef UA_GET_NE16
+#define UA_GET_NE16         LZO_MEMOPS_GET_NE16
+#endif
+#ifndef UA_GET_NE32
+#define UA_GET_NE32         LZO_MEMOPS_GET_NE32
+#endif
+#ifdef LZO_MEMOPS_GET_NE64
+#ifndef UA_GET_NE64
+#define UA_GET_NE64         LZO_MEMOPS_GET_NE64
+#endif
+#endif
+#ifndef UA_PUT_LE16
+#define UA_PUT_LE16         LZO_MEMOPS_PUT_LE16
+#endif
+#ifndef UA_PUT_LE32
+#define UA_PUT_LE32         LZO_MEMOPS_PUT_LE32
+#endif
+#ifndef UA_PUT_NE16
+#define UA_PUT_NE16         LZO_MEMOPS_PUT_NE16
+#endif
+#ifndef UA_PUT_NE32
+#define UA_PUT_NE32         LZO_MEMOPS_PUT_NE32
 #endif
 
 #define MEMCPY8_DS(dest,src,len) \
@@ -2158,25 +3782,10 @@
 extern "C" {
 #endif
 
-#if !defined(lzo_uintptr_t)
-#  if (__LZO_MMODEL_HUGE)
-#    define lzo_uintptr_t   unsigned long
-#  else
-#    define lzo_uintptr_t   acc_uintptr_t
-#    ifdef __ACC_INTPTR_T_IS_POINTER
-#      define __LZO_UINTPTR_T_IS_POINTER 1
-#    endif
-#  endif
-#endif
-
 #if (LZO_ARCH_I086)
-#define PTR(a)              ((lzo_bytep) (a))
-#define PTR_ALIGNED_4(a)    ((ACC_PTR_FP_OFF(a) & 3) == 0)
-#define PTR_ALIGNED2_4(a,b) (((ACC_PTR_FP_OFF(a) | ACC_PTR_FP_OFF(b)) & 3) == 0)
+#error "LZO_ARCH_I086 is unsupported"
 #elif (LZO_MM_PVP)
-#define PTR(a)              ((lzo_bytep) (a))
-#define PTR_ALIGNED_8(a)    ((((lzo_uintptr_t)(a)) >> 61) == 0)
-#define PTR_ALIGNED2_8(a,b) ((((lzo_uintptr_t)(a)|(lzo_uintptr_t)(b)) >> 61) == 0)
+#error "LZO_MM_PVP is unsupported"
 #else
 #define PTR(a)              ((lzo_uintptr_t) (a))
 #define PTR_LINEAR(a)       PTR(a)
@@ -2206,20 +3815,28 @@
     unsigned long   a_ulong;
     lzo_int         a_lzo_int;
     lzo_uint        a_lzo_uint;
-    lzo_int32       a_lzo_int32;
-    lzo_uint32      a_lzo_uint32;
+    lzo_xint        a_lzo_xint;
+    lzo_int16_t     a_lzo_int16_t;
+    lzo_uint16_t    a_lzo_uint16_t;
+    lzo_int32_t     a_lzo_int32_t;
+    lzo_uint32_t    a_lzo_uint32_t;
+#if defined(lzo_uint64_t)
+    lzo_int64_t     a_lzo_int64_t;
+    lzo_uint64_t    a_lzo_uint64_t;
+#endif
+    size_t          a_size_t;
     ptrdiff_t       a_ptrdiff_t;
     lzo_uintptr_t   a_lzo_uintptr_t;
+    void *          a_void_p;
+    char *          a_char_p;
+    unsigned char * a_uchar_p;
+    const void *          a_c_void_p;
+    const char *          a_c_char_p;
+    const unsigned char * a_c_uchar_p;
     lzo_voidp       a_lzo_voidp;
-    void *          a_void_p;
     lzo_bytep       a_lzo_bytep;
-    lzo_bytepp      a_lzo_bytepp;
-    lzo_uintp       a_lzo_uintp;
-    lzo_uint *      a_lzo_uint_p;
-    lzo_uint32p     a_lzo_uint32p;
-    lzo_uint32 *    a_lzo_uint32_p;
-    unsigned char * a_uchar_p;
-    char *          a_char_p;
+    const lzo_voidp a_c_lzo_voidp;
+    const lzo_bytep a_c_lzo_bytep;
 }
 lzo_full_align_t;
 
@@ -2229,19 +3846,20 @@
 
 #endif
 
+#ifndef LZO_DETERMINISTIC
 #define LZO_DETERMINISTIC 1
-
+#endif
+
+#ifndef LZO_DICT_USE_PTR
 #define LZO_DICT_USE_PTR 1
-#if 0 && (LZO_ARCH_I086)
-#  undef LZO_DICT_USE_PTR
 #endif
 
 #if (LZO_DICT_USE_PTR)
 #  define lzo_dict_t    const lzo_bytep
-#  define lzo_dict_p    lzo_dict_t __LZO_MMODEL *
+#  define lzo_dict_p    lzo_dict_t *
 #else
 #  define lzo_dict_t    lzo_uint
-#  define lzo_dict_p    lzo_dict_t __LZO_MMODEL *
+#  define lzo_dict_p    lzo_dict_t *
 #endif
 
 #endif
@@ -2254,10 +3872,9 @@
     lzo_uintptr_t p;
 
 #if (LZO_ARCH_I086)
-    p = (((lzo_uintptr_t)(ACC_PTR_FP_SEG(ptr))) << (16 - ACC_MM_AHSHIFT)) + (ACC_PTR_FP_OFF(ptr));
+#error "LZO_ARCH_I086 is unsupported"
 #elif (LZO_MM_PVP)
-    p = (lzo_uintptr_t) (ptr);
-    p = (p << 3) | (p >> 61);
+#error "LZO_MM_PVP is unsupported"
 #else
     p = (lzo_uintptr_t) PTR_LINEAR(ptr);
 #endif
@@ -2268,9 +3885,8 @@
 LZO_PUBLIC(unsigned)
 __lzo_align_gap(const lzo_voidp ptr, lzo_uint size)
 {
-#if defined(__LZO_UINTPTR_T_IS_POINTER)
-    size_t n = (size_t) ptr;
-    n = (((n + size - 1) / size) * size) - n;
+#if (__LZO_UINTPTR_T_IS_POINTER)
+#error "__LZO_UINTPTR_T_IS_POINTER is unsupported"
 #else
     lzo_uintptr_t p, n;
     p = __lzo_ptr_linear(ptr);
@@ -2296,7 +3912,7 @@
 #else
     "\r\n\n"
     "LZO data compression library.\n"
-    "$Copyright: LZO Copyright (C) 1996-2010 Markus Franz Xaver Johannes Oberhumer\n"
+    "$Copyright: LZO Copyright (C) 1996-2014 Markus Franz Xaver Johannes Oberhumer\n"
     "<markus@oberhumer.com>\n"
     "http://www.oberhumer.com $\n\n"
     "$Id: patch-libvncserver_minilzo.c,v 1.1 2014/08/11 21:22:15 markd Exp $\n"
@@ -2306,11 +3922,7 @@
 LZO_PUBLIC(const lzo_bytep)
 lzo_copyright(void)
 {
-#if (LZO_OS_DOS16 && LZO_CC_TURBOC)
-    return (lzo_voidp) __lzo_copyright;
-#else
     return (const lzo_bytep) __lzo_copyright;
-#endif
 }
 
 LZO_PUBLIC(unsigned)
@@ -2352,11 +3964,11 @@
 #define LZO_DO8(buf,i)  LZO_DO4(buf,i); LZO_DO4(buf,i+4);
 #define LZO_DO16(buf,i) LZO_DO8(buf,i); LZO_DO8(buf,i+8);
 
-LZO_PUBLIC(lzo_uint32)
-lzo_adler32(lzo_uint32 adler, const lzo_bytep buf, lzo_uint len)
+LZO_PUBLIC(lzo_uint32_t)
+lzo_adler32(lzo_uint32_t adler, const lzo_bytep buf, lzo_uint len)
 {
-    lzo_uint32 s1 = adler & 0xffff;
-    lzo_uint32 s2 = (adler >> 16) & 0xffff;
+    lzo_uint32_t s1 = adler & 0xffff;
+    lzo_uint32_t s2 = (adler >> 16) & 0xffff;
     unsigned k;
 
     if (buf == NULL)
@@ -2413,8 +4025,8 @@
 LZOLIB_PUBLIC(int, lzo_hmemcmp) (const lzo_hvoid_p s1, const lzo_hvoid_p s2, lzo_hsize_t len)
 {
 #if (LZO_HAVE_MM_HUGE_PTR) || !(HAVE_MEMCMP)
-    const lzo_hbyte_p p1 = (const lzo_hbyte_p) s1;
-    const lzo_hbyte_p p2 = (const lzo_hbyte_p) s2;
+    const lzo_hbyte_p p1 = LZO_STATIC_CAST(const lzo_hbyte_p, s1);
+    const lzo_hbyte_p p2 = LZO_STATIC_CAST(const lzo_hbyte_p, s2);
     if __lzo_likely(len > 0) do
     {
         int d = *p1 - *p2;
@@ -2430,8 +4042,8 @@
 LZOLIB_PUBLIC(lzo_hvoid_p, lzo_hmemcpy) (lzo_hvoid_p dest, const lzo_hvoid_p src, lzo_hsize_t len)
 {
 #if (LZO_HAVE_MM_HUGE_PTR) || !(HAVE_MEMCPY)
-    lzo_hbyte_p p1 = (lzo_hbyte_p) dest;
-    const lzo_hbyte_p p2 = (const lzo_hbyte_p) src;
+    lzo_hbyte_p p1 = LZO_STATIC_CAST(lzo_hbyte_p, dest);
+    const lzo_hbyte_p p2 = LZO_STATIC_CAST(const lzo_hbyte_p, src);
     if (!(len > 0) || p1 == p2)
         return dest;
     do
@@ -2445,8 +4057,8 @@
 LZOLIB_PUBLIC(lzo_hvoid_p, lzo_hmemmove) (lzo_hvoid_p dest, const lzo_hvoid_p src, lzo_hsize_t len)
 {
 #if (LZO_HAVE_MM_HUGE_PTR) || !(HAVE_MEMMOVE)
-    lzo_hbyte_p p1 = (lzo_hbyte_p) dest;
-    const lzo_hbyte_p p2 = (const lzo_hbyte_p) src;
+    lzo_hbyte_p p1 = LZO_STATIC_CAST(lzo_hbyte_p, dest);
+    const lzo_hbyte_p p2 = LZO_STATIC_CAST(const lzo_hbyte_p, src);
     if (!(len > 0) || p1 == p2)
         return dest;
     if (p1 < p2)
@@ -2468,16 +4080,17 @@
     return memmove(dest, src, len);
 #endif
 }
-LZOLIB_PUBLIC(lzo_hvoid_p, lzo_hmemset) (lzo_hvoid_p s, int c, lzo_hsize_t len)
+LZOLIB_PUBLIC(lzo_hvoid_p, lzo_hmemset) (lzo_hvoid_p s, int cc, lzo_hsize_t len)
 {
 #if (LZO_HAVE_MM_HUGE_PTR) || !(HAVE_MEMSET)
-    lzo_hbyte_p p = (lzo_hbyte_p) s;
+    lzo_hbyte_p p = LZO_STATIC_CAST(lzo_hbyte_p, s);
+    unsigned char c = LZO_ITRUNC(unsigned char, cc);
     if __lzo_likely(len > 0) do
-        *p++ = (unsigned char) c;
+        *p++ = c;
     while __lzo_likely(--len > 0);
     return s;
 #else
-    return memset(s, c, len);
+    return memset(s, cc, len);
 #endif
 }
 #undef LZOLIB_PUBLIC
@@ -2486,29 +4099,28 @@
 
 #if !defined(__LZO_IN_MINILZO)
 
-#define ACC_WANT_ACC_CHK_CH 1
-#undef ACCCHK_ASSERT
-
-    ACCCHK_ASSERT_IS_SIGNED_T(lzo_int)
-    ACCCHK_ASSERT_IS_UNSIGNED_T(lzo_uint)
-
-    ACCCHK_ASSERT_IS_SIGNED_T(lzo_int32)
-    ACCCHK_ASSERT_IS_UNSIGNED_T(lzo_uint32)
-    ACCCHK_ASSERT((LZO_UINT32_C(1) << (int)(8*sizeof(LZO_UINT32_C(1))-1)) > 0)
-    ACCCHK_ASSERT(sizeof(lzo_uint32) >= 4)
-
-#if !defined(__LZO_UINTPTR_T_IS_POINTER)
-    ACCCHK_ASSERT_IS_UNSIGNED_T(lzo_uintptr_t)
-#endif
-    ACCCHK_ASSERT(sizeof(lzo_uintptr_t) >= sizeof(lzo_voidp))
-
-    ACCCHK_ASSERT_IS_UNSIGNED_T(lzo_xint)
-    ACCCHK_ASSERT(sizeof(lzo_xint) >= sizeof(lzo_uint32))
-    ACCCHK_ASSERT(sizeof(lzo_xint) >= sizeof(lzo_uint))
-    ACCCHK_ASSERT(sizeof(lzo_xint) == sizeof(lzo_uint32) || sizeof(lzo_xint) == sizeof(lzo_uint))
-
-#endif
-#undef ACCCHK_ASSERT
+#define LZO_WANT_ACC_CHK_CH 1
+#undef LZOCHK_ASSERT
+
+    LZOCHK_ASSERT((LZO_UINT32_C(1) << (int)(8*sizeof(LZO_UINT32_C(1))-1)) > 0)
+    LZOCHK_ASSERT_IS_SIGNED_T(lzo_int)
+    LZOCHK_ASSERT_IS_UNSIGNED_T(lzo_uint)
+#if !(__LZO_UINTPTR_T_IS_POINTER)
+    LZOCHK_ASSERT_IS_UNSIGNED_T(lzo_uintptr_t)
+#endif
+    LZOCHK_ASSERT(sizeof(lzo_uintptr_t) >= sizeof(lzo_voidp))
+    LZOCHK_ASSERT_IS_UNSIGNED_T(lzo_xint)
+
+#endif
+#undef LZOCHK_ASSERT
+
+union lzo_config_check_union {
+    lzo_uint a[2];
+    unsigned char b[2*LZO_MAX(8,sizeof(lzo_uint))];
+#if defined(lzo_uint64_t)
+    lzo_uint64_t c[2];
+#endif
+};
 
 #if 0
 #define u2p(ptr,off) ((lzo_voidp) (((lzo_bytep)(lzo_voidp)(ptr)) + (off)))
@@ -2522,40 +4134,85 @@
 LZO_PUBLIC(int)
 _lzo_config_check(void)
 {
-    lzo_bool r = 1;
-    union {
-        lzo_xint a[2]; unsigned char b[2*sizeof(lzo_xint)];
-        unsigned short x[2]; lzo_uint32 y[2]; lzo_uint z[2];
-    } u;
+#if (LZO_CC_CLANG && (LZO_CC_CLANG >= 0x030100ul && LZO_CC_CLANG < 0x030300ul))
+# if 0
+    volatile
+# endif
+#endif
+    union lzo_config_check_union u;
     lzo_voidp p;
+    unsigned r = 1;
 
     u.a[0] = u.a[1] = 0;
     p = u2p(&u, 0);
     r &= ((* (lzo_bytep) p) == 0);
-#if !defined(LZO_CFG_NO_CONFIG_CHECK)
-#if defined(LZO_ABI_BIG_ENDIAN)
+#if !(LZO_CFG_NO_CONFIG_CHECK)
+#if (LZO_ABI_BIG_ENDIAN)
     u.a[0] = u.a[1] = 0; u.b[sizeof(lzo_uint) - 1] = 128;
     p = u2p(&u, 0);
     r &= ((* (lzo_uintp) p) == 128);
 #endif
-#if defined(LZO_ABI_LITTLE_ENDIAN)
+#if (LZO_ABI_LITTLE_ENDIAN)
     u.a[0] = u.a[1] = 0; u.b[0] = 128;
     p = u2p(&u, 0);
     r &= ((* (lzo_uintp) p) == 128);
 #endif
-#if defined(LZO_UNALIGNED_OK_2)
     u.a[0] = u.a[1] = 0;
-    u.b[0] = 1; u.b[sizeof(unsigned short) + 1] = 2;
+    u.b[0] = 1; u.b[3] = 2;
     p = u2p(&u, 1);
-    r &= ((* (lzo_ushortp) p) == 0);
-#endif
-#if defined(LZO_UNALIGNED_OK_4)
+    r &= UA_GET_NE16(p) == 0;
+    r &= UA_GET_LE16(p) == 0;
+    u.b[1] = 128;
+    r &= UA_GET_LE16(p) == 128;
     u.a[0] = u.a[1] = 0;
-    u.b[0] = 3; u.b[sizeof(lzo_uint32) + 1] = 4;
+    u.b[0] = 3; u.b[5] = 4;
     p = u2p(&u, 1);
-    r &= ((* (lzo_uint32p) p) == 0);
-#endif
-#endif
+    r &= UA_GET_NE32(p) == 0;
+    r &= UA_GET_LE32(p) == 0;
+    u.b[1] = 128;
+    r &= UA_GET_LE32(p) == 128;
+#if defined(UA_GET_NE64)
+    u.c[0] = u.c[1] = 0;
+    u.b[0] = 5; u.b[9] = 6;
+    p = u2p(&u, 1);
+    u.c[0] = u.c[1] = 0;
+    r &= UA_GET_NE64(p) == 0;
+#if defined(UA_GET_LE64)
+    r &= UA_GET_LE64(p) == 0;
+    u.b[1] = 128;
+    r &= UA_GET_LE64(p) == 128;
+#endif
+#endif
+#if defined(lzo_bitops_ctlz32)
+    { unsigned i = 0; lzo_uint32_t v;
+    for (v = 1; v != 0 && r == 1; v <<= 1, i++) {
+        r &= lzo_bitops_ctlz32(v) == 31 - i;
+        r &= lzo_bitops_ctlz32_func(v) == 31 - i;
+    }}
+#endif
+#if defined(lzo_bitops_ctlz64)
+    { unsigned i = 0; lzo_uint64_t v;
+    for (v = 1; v != 0 && r == 1; v <<= 1, i++) {
+        r &= lzo_bitops_ctlz64(v) == 63 - i;
+        r &= lzo_bitops_ctlz64_func(v) == 63 - i;
+    }}
+#endif
+#if defined(lzo_bitops_cttz32)
+    { unsigned i = 0; lzo_uint32_t v;
+    for (v = 1; v != 0 && r == 1; v <<= 1, i++) {
+        r &= lzo_bitops_cttz32(v) == i;
+        r &= lzo_bitops_cttz32_func(v) == i;
+    }}
+#endif
+#if defined(lzo_bitops_cttz64)
+    { unsigned i = 0; lzo_uint64_t v;
+    for (v = 1; v != 0 && r == 1; v <<= 1, i++) {
+        r &= lzo_bitops_cttz64(v) == i;
+        r &= lzo_bitops_cttz64_func(v) == i;
+    }}
+#endif
+#endif
+    LZO_UNUSED_FUNC(lzo_bitops_unused_funcs);
 
     return r == 1 ? LZO_E_OK : LZO_E_ERROR;
 }
@@ -2569,11 +4226,11 @@
 #if defined(__LZO_IN_MINILZO)
 #elif (LZO_CC_MSC && ((_MSC_VER) < 700))
 #else
-#define ACC_WANT_ACC_CHK_CH 1
-#undef ACCCHK_ASSERT
-#define ACCCHK_ASSERT(expr)  LZO_COMPILE_TIME_ASSERT(expr)
-#endif
-#undef ACCCHK_ASSERT
+#define LZO_WANT_ACC_CHK_CH 1
+#undef LZOCHK_ASSERT
+#define LZOCHK_ASSERT(expr)  LZO_COMPILE_TIME_ASSERT(expr)
+#endif
+#undef LZOCHK_ASSERT
 
     if (v == 0)
         return LZO_E_ERROR;
@@ -2581,7 +4238,7 @@
     r = (s1 == -1 || s1 == (int) sizeof(short)) &&
         (s2 == -1 || s2 == (int) sizeof(int)) &&
         (s3 == -1 || s3 == (int) sizeof(long)) &&
-        (s4 == -1 || s4 == (int) sizeof(lzo_uint32)) &&
+        (s4 == -1 || s4 == (int) sizeof(lzo_uint32_t)) &&
         (s5 == -1 || s5 == (int) sizeof(lzo_uint)) &&
         (s6 == -1 || s6 == (int) lzo_sizeof_dict_t) &&
         (s7 == -1 || s7 == (int) sizeof(char *)) &&
@@ -2624,10 +4281,24 @@
 
 #if !defined(MINILZO_CFG_SKIP_LZO1X_1_COMPRESS)
 
+#if 1 && defined(UA_GET_LE32)
+#undef  LZO_DICT_USE_PTR
+#define LZO_DICT_USE_PTR 0
+#undef  lzo_dict_t
+#define lzo_dict_t lzo_uint16_t
+#endif
+
 #define LZO_NEED_DICT_H 1
+#ifndef D_BITS
 #define D_BITS          14
+#endif
 #define D_INDEX1(d,p)       d = DM(DMUL(0x21,DX3(p,5,5,6)) >> 5)
 #define D_INDEX2(d,p)       d = (d & (D_MASK & 0x7ff)) ^ (D_HIGH | 0x1f)
+#if 1
+#define DINDEX(dv,p)        DM(((DMUL(0x1824429d,dv)) >> (32-D_BITS)))
+#else
+#define DINDEX(dv,p)        DM((dv) + ((dv) >> (32-D_BITS)))
+#endif
 
 #ifndef __LZO_CONFIG1X_H
 #define __LZO_CONFIG1X_H 1
@@ -2845,11 +4516,11 @@
 #endif
 #endif
 
-#if defined(LZO_DICT_USE_PTR)
+#if (LZO_DICT_USE_PTR)
 #  define DENTRY(p,in)                          (p)
 #  define GINDEX(m_pos,m_off,dict,dindex,in)    m_pos = dict[dindex]
 #else
-#  define DENTRY(p,in)                          ((lzo_uint) ((p)-(in)))
+#  define DENTRY(p,in)                          ((lzo_dict_t) pd(p, in))
 #  define GINDEX(m_pos,m_off,dict,dindex,in)    m_off = dict[dindex]
 #endif
 
@@ -2870,7 +4541,7 @@
 
 #endif
 
-#if defined(LZO_DICT_USE_PTR)
+#if (LZO_DICT_USE_PTR)
 
 #define LZO_CHECK_MPOS_DET(m_pos,m_off,in,ip,max_offset) \
         (m_pos == NULL || (m_off = pd(ip, m_pos)) > max_offset)
@@ -2896,7 +4567,7 @@
 
 #endif
 
-#if defined(LZO_DETERMINISTIC)
+#if (LZO_DETERMINISTIC)
 #  define LZO_CHECK_MPOS    LZO_CHECK_MPOS_DET
 #else
 #  define LZO_CHECK_MPOS    LZO_CHECK_MPOS_NON_DET
@@ -2912,22 +4583,25 @@
 
 #endif
 
-#define do_compress     _lzo1x_1_do_compress
+#define LZO_DETERMINISTIC !(LZO_DICT_USE_PTR)
+
+#ifndef DO_COMPRESS
 #define DO_COMPRESS     lzo1x_1_compress
+#endif
 
 #if 1 && defined(DO_COMPRESS) && !defined(do_compress)
-#  define do_compress       LZO_CPP_ECONCAT2(DO_COMPRESS,_core)
+#  define do_compress       LZO_PP_ECONCAT2(DO_COMPRESS,_core)
 #endif
 
 static __lzo_noinline lzo_uint
 do_compress ( const lzo_bytep in , lzo_uint  in_len,
                     lzo_bytep out, lzo_uintp out_len,
-                    lzo_voidp wrkmem )
+                    lzo_uint  ti,  lzo_voidp wrkmem)
 {
-    register const lzo_bytep ip;
+    const lzo_bytep ip;
     lzo_bytep op;
     const lzo_bytep const in_end = in + in_len;
-    const lzo_bytep const ip_end = in + in_len - M2_MAX_LEN - 5;
+    const lzo_bytep const ip_end = in + in_len - 20;
     const lzo_bytep ii;
     lzo_dict_p const dict = (lzo_dict_p) wrkmem;
 
@@ -2935,14 +4609,17 @@
     ip = in;
     ii = ip;
 
-    ip += 4;
+    ip += ti < 4 ? 4 - ti : 0;
     for (;;)
     {
-        register const lzo_bytep m_pos;
+        const lzo_bytep m_pos;
+#if !(LZO_DETERMINISTIC)
         LZO_DEFINE_UNINITIALIZED_VAR(lzo_uint, m_off, 0);
         lzo_uint m_len;
         lzo_uint dindex;
-
+next:
+        if __lzo_unlikely(ip >= ip_end)
+            break;
         DINDEX1(dindex,ip);
         GINDEX(m_pos,m_off,dict,dindex,in);
         if (LZO_CHECK_MPOS_NON_DET(m_pos,m_off,in,ip,M4_MAX_OFFSET))
@@ -2960,200 +4637,247 @@
         goto literal;
 
 try_match:
-#if 1 && defined(LZO_UNALIGNED_OK_2)
-        if (* (const lzo_ushortp) (const lzo_voidp) m_pos != * (const lzo_ushortp) (const lzo_voidp) ip)
-#else
-        if (m_pos[0] != ip[0] || m_pos[1] != ip[1])
+#if (LZO_OPT_UNALIGNED32)
+        if (UA_GET_NE32(m_pos) != UA_GET_NE32(ip))
+#else
+        if (m_pos[0] != ip[0] || m_pos[1] != ip[1] || m_pos[2] != ip[2] || m_pos[3] != ip[3])
 #endif
         {
+literal:
+            UPDATE_I(dict,0,dindex,ip,in);
+            ip += 1 + ((ip - ii) >> 5);
+            continue;
+        }
+        UPDATE_I(dict,0,dindex,ip,in);
+#else
+        lzo_uint m_off;
+        lzo_uint m_len;
+        {
+        lzo_uint32_t dv;
+        lzo_uint dindex;
+literal:
+        ip += 1 + ((ip - ii) >> 5);
+next:
+        if __lzo_unlikely(ip >= ip_end)
+            break;
+        dv = UA_GET_LE32(ip);
+        dindex = DINDEX(dv,ip);
+        GINDEX(m_off,m_pos,in+dict,dindex,in);
+        UPDATE_I(dict,0,dindex,ip,in);
+        if __lzo_unlikely(dv != UA_GET_LE32(m_pos))
+            goto literal;
+        }
+#endif
+
+        ii -= ti; ti = 0;
+        {
+        lzo_uint t = pd(ip,ii);
+        if (t != 0)
+        {
+            if (t <= 3)
+            {
+                op[-2] = LZO_BYTE(op[-2] | t);
+#if (LZO_OPT_UNALIGNED32)
+                UA_COPY4(op, ii);
+                op += t;
+#else
+                { do *op++ = *ii++; while (--t > 0); }
+#endif
+            }
+#if (LZO_OPT_UNALIGNED32) || (LZO_OPT_UNALIGNED64)
+            else if (t <= 16)
+            {
+                *op++ = LZO_BYTE(t - 3);
+                UA_COPY8(op, ii);
+                UA_COPY8(op+8, ii+8);
+                op += t;
+            }
+#endif
+            else
+            {
+                if (t <= 18)
+                    *op++ = LZO_BYTE(t - 3);
+                else
+                {
+                    lzo_uint tt = t - 18;
+                    *op++ = 0;
+                    while __lzo_unlikely(tt > 255)
+                    {
+                        tt -= 255;
+                        UA_SET1(op, 0);
+                        op++;
+                    }
+                    assert(tt > 0);
+                    *op++ = LZO_BYTE(tt);
+                }
+#if (LZO_OPT_UNALIGNED32) || (LZO_OPT_UNALIGNED64)
+                do {
+                    UA_COPY8(op, ii);
+                    UA_COPY8(op+8, ii+8);
+                    op += 16; ii += 16; t -= 16;
+                } while (t >= 16); if (t > 0)
+#endif
+                { do *op++ = *ii++; while (--t > 0); }
+            }
+        }
+        }
+        m_len = 4;
+        {
+#if (LZO_OPT_UNALIGNED64)
+        lzo_uint64_t v;
+        v = UA_GET_NE64(ip + m_len) ^ UA_GET_NE64(m_pos + m_len);
+        if __lzo_unlikely(v == 0) {
+            do {
+                m_len += 8;
+                v = UA_GET_NE64(ip + m_len) ^ UA_GET_NE64(m_pos + m_len);
+                if __lzo_unlikely(ip + m_len >= ip_end)
+                    goto m_len_done;
+            } while (v == 0);
+        }
+#if (LZO_ABI_BIG_ENDIAN) && defined(lzo_bitops_ctlz64)
+        m_len += lzo_bitops_ctlz64(v) / CHAR_BIT;
+#elif (LZO_ABI_BIG_ENDIAN)
+        if ((v >> (64 - CHAR_BIT)) == 0) do {
+            v <<= CHAR_BIT;
+            m_len += 1;
+        } while ((v >> (64 - CHAR_BIT)) == 0);
+#elif (LZO_ABI_LITTLE_ENDIAN) && defined(lzo_bitops_cttz64)
+        m_len += lzo_bitops_cttz64(v) / CHAR_BIT;
+#elif (LZO_ABI_LITTLE_ENDIAN)
+        if ((v & UCHAR_MAX) == 0) do {
+            v >>= CHAR_BIT;
+            m_len += 1;
+        } while ((v & UCHAR_MAX) == 0);
+#else
+        if (ip[m_len] == m_pos[m_len]) do {
+            m_len += 1;
+        } while (ip[m_len] == m_pos[m_len]);
+#endif
+#elif (LZO_OPT_UNALIGNED32)
+        lzo_uint32_t v;
+        v = UA_GET_NE32(ip + m_len) ^ UA_GET_NE32(m_pos + m_len);
+        if __lzo_unlikely(v == 0) {
+            do {
+                m_len += 4;
+                v = UA_GET_NE32(ip + m_len) ^ UA_GET_NE32(m_pos + m_len);
+                if (v != 0)
+                    break;
+                m_len += 4;
+                v = UA_GET_NE32(ip + m_len) ^ UA_GET_NE32(m_pos + m_len);
+                if __lzo_unlikely(ip + m_len >= ip_end)
+                    goto m_len_done;
+            } while (v == 0);
+        }
+#if (LZO_ABI_BIG_ENDIAN) && defined(lzo_bitops_ctlz32)
+        m_len += lzo_bitops_ctlz32(v) / CHAR_BIT;
+#elif (LZO_ABI_BIG_ENDIAN)
+        if ((v >> (32 - CHAR_BIT)) == 0) do {
+            v <<= CHAR_BIT;
+            m_len += 1;
+        } while ((v >> (32 - CHAR_BIT)) == 0);
+#elif (LZO_ABI_LITTLE_ENDIAN) && defined(lzo_bitops_cttz32)
+        m_len += lzo_bitops_cttz32(v) / CHAR_BIT;
+#elif (LZO_ABI_LITTLE_ENDIAN)
+        if ((v & UCHAR_MAX) == 0) do {
+            v >>= CHAR_BIT;
+            m_len += 1;
+        } while ((v & UCHAR_MAX) == 0);
+#else
+        if (ip[m_len] == m_pos[m_len]) do {
+            m_len += 1;
+        } while (ip[m_len] == m_pos[m_len]);
+#endif
+#else
+        if __lzo_unlikely(ip[m_len] == m_pos[m_len]) {
+            do {
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if (ip[m_len] != m_pos[m_len])
+                    break;
+                m_len += 1;
+                if __lzo_unlikely(ip + m_len >= ip_end)
+                    goto m_len_done;
+            } while (ip[m_len] == m_pos[m_len]);
+        }
+#endif
+        }
+m_len_done:
+        m_off = pd(ip,m_pos);
+        ip += m_len;
+        ii = ip;
+        if (m_len <= M2_MAX_LEN && m_off <= M2_MAX_OFFSET)
+        {
+            m_off -= 1;
+#if defined(LZO1X)
+            *op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
+            *op++ = LZO_BYTE(m_off >> 3);
+#elif defined(LZO1Y)
+            *op++ = LZO_BYTE(((m_len + 1) << 4) | ((m_off & 3) << 2));
+            *op++ = LZO_BYTE(m_off >> 2);
+#endif
+        }
+        else if (m_off <= M3_MAX_OFFSET)
+        {
+            m_off -= 1;
+            if (m_len <= M3_MAX_LEN)
+                *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
+            else
+            {
+                m_len -= M3_MAX_LEN;
+                *op++ = M3_MARKER | 0;
+                while __lzo_unlikely(m_len > 255)
+                {
+                    m_len -= 255;
+                    UA_SET1(op, 0);
+                    op++;
+                }
+                *op++ = LZO_BYTE(m_len);
+            }
+            *op++ = LZO_BYTE(m_off << 2);
+            *op++ = LZO_BYTE(m_off >> 6);
         }
         else
         {
-            if __lzo_likely(m_pos[2] == ip[2])
-            {
-#if 0
-                if (m_off <= M2_MAX_OFFSET)
-                    goto match;
-                if (lit <= 3)
-                    goto match;
-                if (lit == 3)
-                {
-                    assert(op - 2 > out); op[-2] |= LZO_BYTE(3);
-                    *op++ = *ii++; *op++ = *ii++; *op++ = *ii++;
-                    goto code_match;
-                }
-                if (m_pos[3] == ip[3])
-#endif
-                    goto match;
-            }
+            m_off -= 0x4000;
+            if (m_len <= M4_MAX_LEN)
+                *op++ = LZO_BYTE(M4_MARKER | ((m_off >> 11) & 8) | (m_len - 2));
             else
             {
-#if 0
-#if 0
-                if (m_off <= M1_MAX_OFFSET && lit > 0 && lit <= 3)
-#else
-                if (m_off <= M1_MAX_OFFSET && lit == 3)
-#endif
+                m_len -= M4_MAX_LEN;
+                *op++ = LZO_BYTE(M4_MARKER | ((m_off >> 11) & 8));
+                while __lzo_unlikely(m_len > 255)
                 {
-                    register lzo_uint t;
-
-                    t = lit;
-                    assert(op - 2 > out); op[-2] |= LZO_BYTE(t);
-                    do *op++ = *ii++; while (--t > 0);
-                    assert(ii == ip);
-                    m_off -= 1;
-                    *op++ = LZO_BYTE(M1_MARKER | ((m_off & 3) << 2));
-                    *op++ = LZO_BYTE(m_off >> 2);
-                    ip += 2;
-                    goto match_done;
+                    m_len -= 255;
+                    UA_SET1(op, 0);
+                    op++;
                 }
-#endif
+                *op++ = LZO_BYTE(m_len);
             }
-        }
-
-literal:
-        UPDATE_I(dict,0,dindex,ip,in);
-        ++ip;
-        if __lzo_unlikely(ip >= ip_end)
-            break;
-        continue;
-
-match:
-        UPDATE_I(dict,0,dindex,ip,in);
-        if (pd(ip,ii) > 0)
-        {
-            register lzo_uint t = pd(ip,ii);
-
-            if (t <= 3)
-            {
-                assert(op - 2 > out);
-                op[-2] |= LZO_BYTE(t);
-            }
-            else if (t <= 18)
-                *op++ = LZO_BYTE(t - 3);
-            else
-            {
-                register lzo_uint tt = t - 18;
-
-                *op++ = 0;
-                while (tt > 255)
-                {
-                    tt -= 255;
-                    *op++ = 0;
-                }
-                assert(tt > 0);
-                *op++ = LZO_BYTE(tt);
-            }
-            do *op++ = *ii++; while (--t > 0);
-        }
-
-        assert(ii == ip);
-        ip += 3;
-        if (m_pos[3] != *ip++ || m_pos[4] != *ip++ || m_pos[5] != *ip++ ||
-            m_pos[6] != *ip++ || m_pos[7] != *ip++ || m_pos[8] != *ip++
-#ifdef LZO1Y
-            || m_pos[ 9] != *ip++ || m_pos[10] != *ip++ || m_pos[11] != *ip++
-            || m_pos[12] != *ip++ || m_pos[13] != *ip++ || m_pos[14] != *ip++
-#endif
-           )
-        {
-            --ip;
-            m_len = pd(ip, ii);
-            assert(m_len >= 3); assert(m_len <= M2_MAX_LEN);
-
-            if (m_off <= M2_MAX_OFFSET)
-            {
-                m_off -= 1;
-#if defined(LZO1X)
-                *op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
-                *op++ = LZO_BYTE(m_off >> 3);
-#elif defined(LZO1Y)
-                *op++ = LZO_BYTE(((m_len + 1) << 4) | ((m_off & 3) << 2));
-                *op++ = LZO_BYTE(m_off >> 2);
-#endif
-            }
-            else if (m_off <= M3_MAX_OFFSET)
-            {
-                m_off -= 1;
-                *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
-                goto m3_m4_offset;
-            }
-            else
-#if defined(LZO1X)
-            {
-                m_off -= 0x4000;
-                assert(m_off > 0); assert(m_off <= 0x7fff);
-                *op++ = LZO_BYTE(M4_MARKER |
-                                 ((m_off & 0x4000) >> 11) | (m_len - 2));
-                goto m3_m4_offset;
-            }
-#elif defined(LZO1Y)
-                goto m4_match;
-#endif
-        }
-        else
-        {
-            {
-                const lzo_bytep end = in_end;
-                const lzo_bytep m = m_pos + M2_MAX_LEN + 1;
-                while (ip < end && *m == *ip)
-                    m++, ip++;
-                m_len = pd(ip, ii);
-            }
-            assert(m_len > M2_MAX_LEN);
-
-            if (m_off <= M3_MAX_OFFSET)
-            {
-                m_off -= 1;
-                if (m_len <= 33)
-                    *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
-                else
-                {
-                    m_len -= 33;
-                    *op++ = M3_MARKER | 0;
-                    goto m3_m4_len;
-                }
-            }
-            else
-            {
-#if defined(LZO1Y)
-m4_match:
-#endif
-                m_off -= 0x4000;
-                assert(m_off > 0); assert(m_off <= 0x7fff);
-                if (m_len <= M4_MAX_LEN)
-                    *op++ = LZO_BYTE(M4_MARKER |
-                                     ((m_off & 0x4000) >> 11) | (m_len - 2));
-                else
-                {
-                    m_len -= M4_MAX_LEN;
-                    *op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11));
-m3_m4_len:
-                    while (m_len > 255)
-                    {
-                        m_len -= 255;
-                        *op++ = 0;
-                    }
-                    assert(m_len > 0);
-                    *op++ = LZO_BYTE(m_len);
-                }
-            }
-
-m3_m4_offset:
-            *op++ = LZO_BYTE((m_off & 63) << 2);
+            *op++ = LZO_BYTE(m_off << 2);
             *op++ = LZO_BYTE(m_off >> 6);
         }
-
-#if 0
-match_done:
-#endif
-        ii = ip;
-        if __lzo_unlikely(ip >= ip_end)
-            break;
+        goto next;
     }
 
     *out_len = pd(op, out);
-    return pd(in_end,ii);
+    return pd(in_end,ii-ti);
 }
 
 LZO_PUBLIC(int)
@@ -3161,16 +4885,30 @@
                          lzo_bytep out, lzo_uintp out_len,
                          lzo_voidp wrkmem )
 {
+    const lzo_bytep ip = in;
     lzo_bytep op = out;
-    lzo_uint t;
-
-    if __lzo_unlikely(in_len <= M2_MAX_LEN + 5)
-        t = in_len;
-    else
+    lzo_uint l = in_len;
+    lzo_uint t = 0;
+
+    while (l > 20)
     {
-        t = do_compress(in,in_len,op,out_len,wrkmem);
+        lzo_uint ll = l;
+        lzo_uintptr_t ll_end;
+#if 0 || (LZO_DETERMINISTIC)
+        ll = LZO_MIN(ll, 49152);
+#endif
+        ll_end = (lzo_uintptr_t)ip + ll;
+        if ((ll_end + ((t + ll) >> 5)) <= ll_end || (const lzo_bytep)(ll_end + ((t + ll) >> 5)) <= ip + ll)
+            break;
+#if (LZO_DETERMINISTIC)
+        lzo_memset(wrkmem, 0, ((lzo_uint)1 << D_BITS) * sizeof(lzo_dict_t));
+#endif
+        t = do_compress(ip,ll,op,out_len,t,wrkmem);
+        ip += ll;
         op += *out_len;
+        l  -= ll;
     }
+    t += l;
 
     if (t > 0)
     {
@@ -3179,7 +4917,7 @@
         if (op == out && t <= 238)
             *op++ = LZO_BYTE(17 + t);
         else if (t <= 3)
-            op[-2] |= LZO_BYTE(t);
+            op[-2] = LZO_BYTE(op[-2] | t);
         else if (t <= 18)
             *op++ = LZO_BYTE(t - 3);
         else
@@ -3190,12 +4928,14 @@
             while (tt > 255)
             {
                 tt -= 255;
-                *op++ = 0;
+                UA_SET1(op, 0);
+                op++;
             }
             assert(tt > 0);
             *op++ = LZO_BYTE(tt);
         }
-        do *op++ = *ii++; while (--t > 0);
+        UA_COPYN(op, ii, t);
+        op += t;
     }
 
     *op++ = M4_MARKER | 1;
@@ -3232,10 +4972,13 @@
 
 #undef TEST_IP
 #undef TEST_OP
+#undef TEST_IP_AND_TEST_OP
 #undef TEST_LB
 #undef TEST_LBO
 #undef NEED_IP
 #undef NEED_OP
+#undef TEST_IV
+#undef TEST_OV
 #undef HAVE_TEST_IP
 #undef HAVE_TEST_OP
 #undef HAVE_NEED_IP
@@ -3250,6 +4993,7 @@
 #  if (LZO_TEST_OVERRUN_INPUT >= 2)
 #    define NEED_IP(x) \
             if ((lzo_uint)(ip_end - ip) < (lzo_uint)(x))  goto input_overrun
+#    define TEST_IV(x)          if ((x) >  (lzo_uint)0 - (511)) goto input_overrun
 #  endif
 #endif
 
@@ -3261,12 +5005,13 @@
 #    undef TEST_OP
 #    define NEED_OP(x) \
             if ((lzo_uint)(op_end - op) < (lzo_uint)(x))  goto output_overrun
+#    define TEST_OV(x)          if ((x) >  (lzo_uint)0 - (511)) goto output_overrun
 #  endif
 #endif
 
 #if defined(LZO_TEST_OVERRUN_LOOKBEHIND)
-#  define TEST_LB(m_pos)        if (m_pos < out || m_pos >= op) goto lookbehind_overrun
-#  define TEST_LBO(m_pos,o)     if (m_pos < out || m_pos >= op - (o)) goto lookbehind_overrun
+#  define TEST_LB(m_pos)        if (PTR_LT(m_pos,out) || PTR_GE(m_pos,op)) goto lookbehind_overrun
+#  define TEST_LBO(m_pos,o)     if (PTR_LT(m_pos,out) || PTR_GE(m_pos,op-(o))) goto lookbehind_overrun
 #else
 #  define TEST_LB(m_pos)        ((void) 0)
 #  define TEST_LBO(m_pos,o)     ((void) 0)
@@ -3287,15 +5032,27 @@
 #  define TEST_OP               1
 #endif
 
+#if defined(HAVE_TEST_IP) && defined(HAVE_TEST_OP)
+#  define TEST_IP_AND_TEST_OP   (TEST_IP && TEST_OP)
+#elif defined(HAVE_TEST_IP)
+#  define TEST_IP_AND_TEST_OP   TEST_IP
+#elif defined(HAVE_TEST_OP)
+#  define TEST_IP_AND_TEST_OP   TEST_OP
+#else
+#  define TEST_IP_AND_TEST_OP   1
+#endif
+
 #if defined(NEED_IP)
 #  define HAVE_NEED_IP 1
 #else
 #  define NEED_IP(x)            ((void) 0)
+#  define TEST_IV(x)            ((void) 0)
 #endif
 #if defined(NEED_OP)
 #  define HAVE_NEED_OP 1
 #else
 #  define NEED_OP(x)            ((void) 0)
+#  define TEST_OV(x)            ((void) 0)
 #endif
 
 #if defined(HAVE_TEST_IP) || defined(HAVE_NEED_IP)
@@ -3312,14 +5069,14 @@
                        lzo_voidp wrkmem )
 #endif
 {
-    register lzo_bytep op;
-    register const lzo_bytep ip;
-    register lzo_uint t;
+    lzo_bytep op;
+    const lzo_bytep ip;
+    lzo_uint t;
 #if defined(COPY_DICT)
     lzo_uint m_off;
     const lzo_bytep dict_end;
 #else
-    register const lzo_bytep m_pos;
+    const lzo_bytep m_pos;
 #endif
 
     const lzo_bytep const ip_end = in + in_len;
@@ -3354,46 +5111,65 @@
     op = out;
     ip = in;
 
+    NEED_IP(1);
     if (*ip > 17)
     {
         t = *ip++ - 17;
         if (t < 4)
             goto match_next;
-        assert(t > 0); NEED_OP(t); NEED_IP(t+1);
+        assert(t > 0); NEED_OP(t); NEED_IP(t+3);
         do *op++ = *ip++; while (--t > 0);
         goto first_literal_run;
     }
 
-    while (TEST_IP && TEST_OP)
+    for (;;)
     {
+        NEED_IP(3);
         t = *ip++;
         if (t >= 16)
             goto match;
         if (t == 0)
         {
-            NEED_IP(1);
             while (*ip == 0)
             {
                 t += 255;
                 ip++;
+                TEST_IV(t);
                 NEED_IP(1);
             }
             t += 15 + *ip++;
         }
-        assert(t > 0); NEED_OP(t+3); NEED_IP(t+4);
-#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
-#if !defined(LZO_UNALIGNED_OK_4)
+        assert(t > 0); NEED_OP(t+3); NEED_IP(t+6);
+#if (LZO_OPT_UNALIGNED64) && (LZO_OPT_UNALIGNED32)
+        t += 3;
+        if (t >= 8) do
+        {
+            UA_COPY8(op,ip);
+            op += 8; ip += 8; t -= 8;
+        } while (t >= 8);
+        if (t >= 4)
+        {
+            UA_COPY4(op,ip);
+            op += 4; ip += 4; t -= 4;
+        }
+        if (t > 0)
+        {
+            *op++ = *ip++;
+            if (t > 1) { *op++ = *ip++; if (t > 2) { *op++ = *ip++; } }
+        }
+#elif (LZO_OPT_UNALIGNED32) || (LZO_ALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         if (PTR_ALIGNED2_4(op,ip))
         {
 #endif
-        COPY4(op,ip);
+        UA_COPY4(op,ip);
         op += 4; ip += 4;
         if (--t > 0)
         {
             if (t >= 4)
             {
                 do {
-                    COPY4(op,ip);
+                    UA_COPY4(op,ip);
                     op += 4; ip += 4; t -= 4;
                 } while (t >= 4);
                 if (t > 0) do *op++ = *ip++; while (--t > 0);
@@ -3401,12 +5177,12 @@
             else
                 do *op++ = *ip++; while (--t > 0);
         }
-#if !defined(LZO_UNALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         }
         else
 #endif
 #endif
-#if !defined(LZO_UNALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         {
             *op++ = *ip++; *op++ = *ip++; *op++ = *ip++;
             do *op++ = *ip++; while (--t > 0);
@@ -3442,7 +5218,7 @@
 #endif
         goto match_done;
 
-        do {
+        for (;;) {
 match:
             if (t >= 64)
             {
@@ -3502,14 +5278,15 @@
                 t &= 31;
                 if (t == 0)
                 {
-                    NEED_IP(1);
                     while (*ip == 0)
                     {
                         t += 255;
                         ip++;
+                        TEST_OV(t);
                         NEED_IP(1);
                     }
                     t += 31 + *ip++;
+                    NEED_IP(2);
                 }
 #if defined(COPY_DICT)
 #if defined(LZO1Z)
@@ -3525,9 +5302,9 @@
                     m_pos = op - off;
                     last_m_off = off;
                 }
-#elif defined(LZO_UNALIGNED_OK_2) && defined(LZO_ABI_LITTLE_ENDIAN)
+#elif (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
                 m_pos = op - 1;
-                m_pos -= (* (const lzo_ushortp) (const lzo_voidp) ip) >> 2;
+                m_pos -= UA_GET_LE16(ip) >> 2;
 #else
                 m_pos = op - 1;
                 m_pos -= (ip[0] >> 2) + (ip[1] << 6);
@@ -3546,14 +5323,15 @@
                 t &= 7;
                 if (t == 0)
                 {
-                    NEED_IP(1);
                     while (*ip == 0)
                     {
                         t += 255;
                         ip++;
+                        TEST_OV(t);
                         NEED_IP(1);
                     }
                     t += 7 + *ip++;
+                    NEED_IP(2);
                 }
 #if defined(COPY_DICT)
 #if defined(LZO1Z)
@@ -3571,8 +5349,8 @@
 #else
 #if defined(LZO1Z)
                 m_pos -= (ip[0] << 6) + (ip[1] >> 2);
-#elif defined(LZO_UNALIGNED_OK_2) && defined(LZO_ABI_LITTLE_ENDIAN)
-                m_pos -= (* (const lzo_ushortp) (const lzo_voidp) ip) >> 2;
+#elif (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
+                m_pos -= UA_GET_LE16(ip) >> 2;
 #else
                 m_pos -= (ip[0] >> 2) + (ip[1] << 6);
 #endif
@@ -3620,8 +5398,29 @@
 #else
 
             TEST_LB(m_pos); assert(t > 0); NEED_OP(t+3-1);
-#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
-#if !defined(LZO_UNALIGNED_OK_4)
+#if (LZO_OPT_UNALIGNED64) && (LZO_OPT_UNALIGNED32)
+            if (op - m_pos >= 8)
+            {
+                t += (3 - 1);
+                if (t >= 8) do
+                {
+                    UA_COPY8(op,m_pos);
+                    op += 8; m_pos += 8; t -= 8;
+                } while (t >= 8);
+                if (t >= 4)
+                {
+                    UA_COPY4(op,m_pos);
+                    op += 4; m_pos += 4; t -= 4;
+                }
+                if (t > 0)
+                {
+                    *op++ = m_pos[0];
+                    if (t > 1) { *op++ = m_pos[1]; if (t > 2) { *op++ = m_pos[2]; } }
+                }
+            }
+            else
+#elif (LZO_OPT_UNALIGNED32) || (LZO_ALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
             if (t >= 2 * 4 - (3 - 1) && PTR_ALIGNED2_4(op,m_pos))
             {
                 assert((op - m_pos) >= 4);
@@ -3629,10 +5428,10 @@
             if (t >= 2 * 4 - (3 - 1) && (op - m_pos) >= 4)
             {
 #endif
-                COPY4(op,m_pos);
+                UA_COPY4(op,m_pos);
                 op += 4; m_pos += 4; t -= 4 - (3 - 1);
                 do {
-                    COPY4(op,m_pos);
+                    UA_COPY4(op,m_pos);
                     op += 4; m_pos += 4; t -= 4;
                 } while (t >= 4);
                 if (t > 0) do *op++ = *m_pos++; while (--t > 0);
@@ -3657,7 +5456,7 @@
                 break;
 
 match_next:
-            assert(t > 0); assert(t < 4); NEED_OP(t); NEED_IP(t+1);
+            assert(t > 0); assert(t < 4); NEED_OP(t); NEED_IP(t+3);
 #if 0
             do *op++ = *ip++; while (--t > 0);
 #else
@@ -3665,16 +5464,10 @@
             if (t > 1) { *op++ = *ip++; if (t > 2) { *op++ = *ip++; } }
 #endif
             t = *ip++;
-        } while (TEST_IP && TEST_OP);
+        }
     }
 
-#if defined(HAVE_TEST_IP) || defined(HAVE_TEST_OP)
-    *out_len = pd(op, out);
-    return LZO_E_EOF_NOT_FOUND;
-#endif
-
 eof_found:
-    assert(t == 1);
     *out_len = pd(op, out);
     return (ip == ip_end ? LZO_E_OK :
            (ip < ip_end  ? LZO_E_INPUT_NOT_CONSUMED : LZO_E_INPUT_OVERRUN));
@@ -3720,10 +5513,13 @@
 
 #undef TEST_IP
 #undef TEST_OP
+#undef TEST_IP_AND_TEST_OP
 #undef TEST_LB
 #undef TEST_LBO
 #undef NEED_IP
 #undef NEED_OP
+#undef TEST_IV
+#undef TEST_OV
 #undef HAVE_TEST_IP
 #undef HAVE_TEST_OP
 #undef HAVE_NEED_IP
@@ -3738,6 +5534,7 @@
 #  if (LZO_TEST_OVERRUN_INPUT >= 2)
 #    define NEED_IP(x) \
             if ((lzo_uint)(ip_end - ip) < (lzo_uint)(x))  goto input_overrun
+#    define TEST_IV(x)          if ((x) >  (lzo_uint)0 - (511)) goto input_overrun
 #  endif
 #endif
 
@@ -3749,12 +5546,13 @@
 #    undef TEST_OP
 #    define NEED_OP(x) \
             if ((lzo_uint)(op_end - op) < (lzo_uint)(x))  goto output_overrun
+#    define TEST_OV(x)          if ((x) >  (lzo_uint)0 - (511)) goto output_overrun
 #  endif
 #endif
 
 #if defined(LZO_TEST_OVERRUN_LOOKBEHIND)
-#  define TEST_LB(m_pos)        if (m_pos < out || m_pos >= op) goto lookbehind_overrun
-#  define TEST_LBO(m_pos,o)     if (m_pos < out || m_pos >= op - (o)) goto lookbehind_overrun
+#  define TEST_LB(m_pos)        if (PTR_LT(m_pos,out) || PTR_GE(m_pos,op)) goto lookbehind_overrun
+#  define TEST_LBO(m_pos,o)     if (PTR_LT(m_pos,out) || PTR_GE(m_pos,op-(o))) goto lookbehind_overrun
 #else
 #  define TEST_LB(m_pos)        ((void) 0)
 #  define TEST_LBO(m_pos,o)     ((void) 0)
@@ -3775,15 +5573,27 @@
 #  define TEST_OP               1
 #endif
 
+#if defined(HAVE_TEST_IP) && defined(HAVE_TEST_OP)
+#  define TEST_IP_AND_TEST_OP   (TEST_IP && TEST_OP)
+#elif defined(HAVE_TEST_IP)
+#  define TEST_IP_AND_TEST_OP   TEST_IP
+#elif defined(HAVE_TEST_OP)
+#  define TEST_IP_AND_TEST_OP   TEST_OP
+#else
+#  define TEST_IP_AND_TEST_OP   1
+#endif
+
 #if defined(NEED_IP)
 #  define HAVE_NEED_IP 1
 #else
 #  define NEED_IP(x)            ((void) 0)
+#  define TEST_IV(x)            ((void) 0)
 #endif
 #if defined(NEED_OP)
 #  define HAVE_NEED_OP 1
 #else
 #  define NEED_OP(x)            ((void) 0)
+#  define TEST_OV(x)            ((void) 0)
 #endif
 
 #if defined(HAVE_TEST_IP) || defined(HAVE_NEED_IP)
@@ -3800,14 +5610,14 @@
                        lzo_voidp wrkmem )
 #endif
 {
-    register lzo_bytep op;
-    register const lzo_bytep ip;
-    register lzo_uint t;
+    lzo_bytep op;
+    const lzo_bytep ip;
+    lzo_uint t;
 #if defined(COPY_DICT)
     lzo_uint m_off;
     const lzo_bytep dict_end;
 #else
-    register const lzo_bytep m_pos;
+    const lzo_bytep m_pos;
 #endif
 
     const lzo_bytep const ip_end = in + in_len;
@@ -3842,46 +5652,65 @@
     op = out;
     ip = in;
 
+    NEED_IP(1);
     if (*ip > 17)
     {
         t = *ip++ - 17;
         if (t < 4)
             goto match_next;
-        assert(t > 0); NEED_OP(t); NEED_IP(t+1);
+        assert(t > 0); NEED_OP(t); NEED_IP(t+3);
         do *op++ = *ip++; while (--t > 0);
         goto first_literal_run;
     }
 
-    while (TEST_IP && TEST_OP)
+    for (;;)
     {
+        NEED_IP(3);
         t = *ip++;
         if (t >= 16)
             goto match;
         if (t == 0)
         {
-            NEED_IP(1);
             while (*ip == 0)
             {
                 t += 255;
                 ip++;
+                TEST_IV(t);
                 NEED_IP(1);
             }
             t += 15 + *ip++;
         }
-        assert(t > 0); NEED_OP(t+3); NEED_IP(t+4);
-#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
-#if !defined(LZO_UNALIGNED_OK_4)
+        assert(t > 0); NEED_OP(t+3); NEED_IP(t+6);
+#if (LZO_OPT_UNALIGNED64) && (LZO_OPT_UNALIGNED32)
+        t += 3;
+        if (t >= 8) do
+        {
+            UA_COPY8(op,ip);
+            op += 8; ip += 8; t -= 8;
+        } while (t >= 8);
+        if (t >= 4)
+        {
+            UA_COPY4(op,ip);
+            op += 4; ip += 4; t -= 4;
+        }
+        if (t > 0)
+        {
+            *op++ = *ip++;
+            if (t > 1) { *op++ = *ip++; if (t > 2) { *op++ = *ip++; } }
+        }
+#elif (LZO_OPT_UNALIGNED32) || (LZO_ALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         if (PTR_ALIGNED2_4(op,ip))
         {
 #endif
-        COPY4(op,ip);
+        UA_COPY4(op,ip);
         op += 4; ip += 4;
         if (--t > 0)
         {
             if (t >= 4)
             {
                 do {
-                    COPY4(op,ip);
+                    UA_COPY4(op,ip);
                     op += 4; ip += 4; t -= 4;
                 } while (t >= 4);
                 if (t > 0) do *op++ = *ip++; while (--t > 0);
@@ -3889,12 +5718,12 @@
             else
                 do *op++ = *ip++; while (--t > 0);
         }
-#if !defined(LZO_UNALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         }
         else
 #endif
 #endif
-#if !defined(LZO_UNALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
         {
             *op++ = *ip++; *op++ = *ip++; *op++ = *ip++;
             do *op++ = *ip++; while (--t > 0);
@@ -3930,7 +5759,7 @@
 #endif
         goto match_done;
 
-        do {
+        for (;;) {
 match:
             if (t >= 64)
             {
@@ -3990,14 +5819,15 @@
                 t &= 31;
                 if (t == 0)
                 {
-                    NEED_IP(1);
                     while (*ip == 0)
                     {
                         t += 255;
                         ip++;
+                        TEST_OV(t);
                         NEED_IP(1);
                     }
                     t += 31 + *ip++;
+                    NEED_IP(2);
                 }
 #if defined(COPY_DICT)
 #if defined(LZO1Z)
@@ -4013,9 +5843,9 @@
                     m_pos = op - off;
                     last_m_off = off;
                 }
-#elif defined(LZO_UNALIGNED_OK_2) && defined(LZO_ABI_LITTLE_ENDIAN)
+#elif (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
                 m_pos = op - 1;
-                m_pos -= (* (const lzo_ushortp) (const lzo_voidp) ip) >> 2;
+                m_pos -= UA_GET_LE16(ip) >> 2;
 #else
                 m_pos = op - 1;
                 m_pos -= (ip[0] >> 2) + (ip[1] << 6);
@@ -4034,14 +5864,15 @@
                 t &= 7;
                 if (t == 0)
                 {
-                    NEED_IP(1);
                     while (*ip == 0)
                     {
                         t += 255;
                         ip++;
+                        TEST_OV(t);
                         NEED_IP(1);
                     }
                     t += 7 + *ip++;
+                    NEED_IP(2);
                 }
 #if defined(COPY_DICT)
 #if defined(LZO1Z)
@@ -4059,8 +5890,8 @@
 #else
 #if defined(LZO1Z)
                 m_pos -= (ip[0] << 6) + (ip[1] >> 2);
-#elif defined(LZO_UNALIGNED_OK_2) && defined(LZO_ABI_LITTLE_ENDIAN)
-                m_pos -= (* (const lzo_ushortp) (const lzo_voidp) ip) >> 2;
+#elif (LZO_OPT_UNALIGNED16) && (LZO_ABI_LITTLE_ENDIAN)
+                m_pos -= UA_GET_LE16(ip) >> 2;
 #else
                 m_pos -= (ip[0] >> 2) + (ip[1] << 6);
 #endif
@@ -4108,8 +5939,29 @@
 #else
 
             TEST_LB(m_pos); assert(t > 0); NEED_OP(t+3-1);
-#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
-#if !defined(LZO_UNALIGNED_OK_4)
+#if (LZO_OPT_UNALIGNED64) && (LZO_OPT_UNALIGNED32)
+            if (op - m_pos >= 8)
+            {
+                t += (3 - 1);
+                if (t >= 8) do
+                {
+                    UA_COPY8(op,m_pos);
+                    op += 8; m_pos += 8; t -= 8;
+                } while (t >= 8);
+                if (t >= 4)
+                {
+                    UA_COPY4(op,m_pos);
+                    op += 4; m_pos += 4; t -= 4;
+                }
+                if (t > 0)
+                {
+                    *op++ = m_pos[0];
+                    if (t > 1) { *op++ = m_pos[1]; if (t > 2) { *op++ = m_pos[2]; } }
+                }
+            }
+            else
+#elif (LZO_OPT_UNALIGNED32) || (LZO_ALIGNED_OK_4)
+#if !(LZO_OPT_UNALIGNED32)
             if (t >= 2 * 4 - (3 - 1) && PTR_ALIGNED2_4(op,m_pos))
             {
                 assert((op - m_pos) >= 4);
@@ -4117,10 +5969,10 @@
             if (t >= 2 * 4 - (3 - 1) && (op - m_pos) >= 4)
             {
 #endif
-                COPY4(op,m_pos);
+                UA_COPY4(op,m_pos);
                 op += 4; m_pos += 4; t -= 4 - (3 - 1);
                 do {
-                    COPY4(op,m_pos);
+                    UA_COPY4(op,m_pos);
                     op += 4; m_pos += 4; t -= 4;
                 } while (t >= 4);
                 if (t > 0) do *op++ = *m_pos++; while (--t > 0);
@@ -4145,7 +5997,7 @@
                 break;
 
 match_next:
-            assert(t > 0); assert(t < 4); NEED_OP(t); NEED_IP(t+1);
+            assert(t > 0); assert(t < 4); NEED_OP(t); NEED_IP(t+3);
 #if 0
             do *op++ = *ip++; while (--t > 0);
 #else
@@ -4153,16 +6005,10 @@
             if (t > 1) { *op++ = *ip++; if (t > 2) { *op++ = *ip++; } }
 #endif
             t = *ip++;
-        } while (TEST_IP && TEST_OP);
+        }
     }
 
-#if defined(HAVE_TEST_IP) || defined(HAVE_TEST_OP)
-    *out_len = pd(op, out);
-    return LZO_E_EOF_NOT_FOUND;
-#endif
-
 eof_found:
-    assert(t == 1);
     *out_len = pd(op, out);
     return (ip == ip_end ? LZO_E_OK :
            (ip < ip_end  ? LZO_E_INPUT_NOT_CONSUMED : LZO_E_INPUT_OVERRUN));

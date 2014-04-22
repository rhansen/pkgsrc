# $NetBSD: buildlink3.mk,v 1.1 2014/04/22 20:46:41 ryoon Exp $

BUILDLINK_TREE+=	gcc48-cc++

.if !defined(GCC48_CC++_BUILDLINK3_MK)
GCC48_CC++_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc48-cc+++=	gcc48-cc++>=${_GCC_REQD}
BUILDLINK_PKGSRCDIR.gcc48-cc++?=	../../lang/gcc48-cc++

BUILDLINK_GCC48_LIBDIRS=		gcc48/lib
BUILDLINK_LIBDIRS.gcc48-cc+++=		${BUILDLINK_GCC48_LIBDIRS}
BUILDLINK_DEPMETHOD.gcc48-cc++?=	build
.endif	# GCC48_CC++_BUILDLINK3_MK

BUILDLINK_TREE+=	-gcc48-cc++

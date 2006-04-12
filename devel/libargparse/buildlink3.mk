# $NetBSD: buildlink3.mk,v 1.4 2006/04/12 10:27:09 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBARGPARSE_BUILDLINK3_MK:=	${LIBARGPARSE_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libargparse
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibargparse}
BUILDLINK_PACKAGES+=	libargparse

.if !empty(LIBARGPARSE_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libargparse+=	libargparse>=0.1.0000
BUILDLINK_ABI_DEPENDS.libargparse+=	libargparse>=0.1.0000nb1
BUILDLINK_PKGSRCDIR.libargparse?=	../../devel/libargparse
.endif	# LIBARGPARSE_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

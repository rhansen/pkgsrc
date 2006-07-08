# $NetBSD: buildlink3.mk,v 1.6 2006/07/08 23:10:36 jlam Exp $
#

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBDTS_BUILDLINK3_MK:=	${LIBDTS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libdca
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibdca}
BUILDLINK_PACKAGES+=	libdca
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libdca

.if !empty(LIBDTS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libdca+=	libdca>=0.0.2
BUILDLINK_PKGSRCDIR.libdca?=	../../audio/libdca
BUILDLINK_DEPMETHOD.libdca?=	build
.endif	# LIBDTS_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

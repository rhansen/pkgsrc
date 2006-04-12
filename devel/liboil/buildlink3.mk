# $NetBSD: buildlink3.mk,v 1.3 2006/04/12 10:27:11 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBOIL_BUILDLINK3_MK:=	${LIBOIL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	liboil
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nliboil}
BUILDLINK_PACKAGES+=	liboil

.if !empty(LIBOIL_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.liboil+=	liboil>=0.3.6
BUILDLINK_PKGSRCDIR.liboil?=	../../devel/liboil
.endif	# LIBOIL_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

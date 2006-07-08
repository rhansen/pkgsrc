# $NetBSD: buildlink3.mk,v 1.5 2006/07/08 23:10:50 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
EXIV2_BUILDLINK3_MK:=	${EXIV2_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	exiv2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nexiv2}
BUILDLINK_PACKAGES+=	exiv2
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}exiv2

.if ${EXIV2_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.exiv2+=	exiv2>=0.10
BUILDLINK_PKGSRCDIR.exiv2?=	../../graphics/exiv2
.endif	# EXIV2_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

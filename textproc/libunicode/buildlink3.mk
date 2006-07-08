# $NetBSD: buildlink3.mk,v 1.7 2006/07/08 23:11:11 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBUNICODE_BUILDLINK3_MK:=	${LIBUNICODE_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libunicode
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibunicode}
BUILDLINK_PACKAGES+=	libunicode
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libunicode

.if !empty(LIBUNICODE_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libunicode+=		libunicode>=0.4
BUILDLINK_ABI_DEPENDS.libunicode+=	libunicode>=0.4nb1
BUILDLINK_PKGSRCDIR.libunicode?=	../../textproc/libunicode
.endif	# LIBUNICODE_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

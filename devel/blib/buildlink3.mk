# $NetBSD: buildlink3.mk,v 1.9 2006/07/08 23:10:41 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
BLIB_BUILDLINK3_MK:=	${BLIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	blib
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nblib}
BUILDLINK_PACKAGES+=	blib
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}blib

.if !empty(BLIB_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.blib+=	blib>=1.0.2nb1
BUILDLINK_ABI_DEPENDS.blib+=	blib>=1.0.2nb5
BUILDLINK_PKGSRCDIR.blib?=	../../devel/blib
.endif	# BLIB_BUILDLINK3_MK

.include "../../x11/gtk2/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

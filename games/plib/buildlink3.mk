# $NetBSD: buildlink3.mk,v 1.2 2006/02/05 23:09:21 joerg Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PLIB_BUILDLINK3_MK:=	${PLIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	plib
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nplib}
BUILDLINK_PACKAGES+=	plib

.if !empty(PLIB_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.plib+=	plib>=1.6.0
BUILDLINK_RECOMMENDED.plib?=	plib>=1.6.0nb3
BUILDLINK_PKGSRCDIR.plib?=	../../games/plib
BUILDLINK_DEPMETHOD.plib?=	build
.endif	# PLIB_BUILDLINK3_MK

.include "../../graphics/Mesa/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.1 2004/01/24 21:24:09 recht Exp $
#

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
SPREAD_BUILDLINK3_MK:=	${SPREAD_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	spread
.endif

.if !empty(SPREAD_BUILDLINK3_MK:M+)
BUILDLINK_PACKAGES+=			spread
BUILDLINK_DEPENDS.spread?=		spread>=3.17.1nb1
BUILDLINK_PKGSRCDIR.spread?=		../../net/spread

.endif # SPREAD_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

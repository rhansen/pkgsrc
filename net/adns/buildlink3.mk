# $NetBSD: buildlink3.mk,v 1.1 2004/04/25 08:01:15 snj Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
ADNS_BUILDLINK3_MK:=	${ADNS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	adns
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nadns}
BUILDLINK_PACKAGES+=	adns

.if !empty(ADNS_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.adns+=	adns>=1.0
BUILDLINK_PKGSRCDIR.adns?=	../../net/adns
.endif	# ADNS_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

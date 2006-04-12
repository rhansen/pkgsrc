# $NetBSD: buildlink3.mk,v 1.4 2006/04/12 10:27:26 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
SLATEC_BUILDLINK3_MK:=	${SLATEC_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	slatec
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nslatec}
BUILDLINK_PACKAGES+=	slatec

.if !empty(SLATEC_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.slatec+=	slatec>=4.1nb1
BUILDLINK_ABI_DEPENDS.slatec+=	slatec>=4.1nb2
BUILDLINK_PKGSRCDIR.slatec?=	../../math/slatec
.endif	# SLATEC_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

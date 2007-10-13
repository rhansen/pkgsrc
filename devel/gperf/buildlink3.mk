# $NetBSD: buildlink3.mk,v 1.8 2007/10/13 18:35:35 adam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
GPERF_BUILDLINK3_MK:=	${GPERF_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	gperf
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ngperf}
BUILDLINK_PACKAGES+=	gperf
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}gperf

.if !empty(GPERF_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.gperf+=	gperf>=3.0.1
BUILDLINK_PKGSRCDIR.gperf?=	../../devel/gperf
BUILDLINK_DEPMETHOD.gperf?=	build
.endif	# GPERF_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

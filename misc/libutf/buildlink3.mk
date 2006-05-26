# $NetBSD: buildlink3.mk,v 1.5 2006/05/26 21:13:01 agc Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBUTF_BUILDLINK3_MK:=	${LIBUTF_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	libutf
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibutf}
BUILDLINK_PACKAGES+=	libutf

.if ${LIBUTF_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.libutf+=	libutf>=3.0
BUILDLINK_PKGSRCDIR.libutf?=	../../misc/libutf
.endif	# LIBUTF_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

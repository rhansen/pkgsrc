# $NetBSD: buildlink3.mk,v 1.1.1.1 2005/01/22 13:21:43 peter Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
TLS_BUILDLINK3_MK:=	${TLS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	tls
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ntls}
BUILDLINK_PACKAGES+=	tls

.if !empty(TLS_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.tls+=	tls>=1.5.0
BUILDLINK_PKGSRCDIR.tls?=	../../security/tls
.endif	# TLS_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

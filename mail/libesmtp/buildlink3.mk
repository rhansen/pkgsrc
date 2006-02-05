# $NetBSD: buildlink3.mk,v 1.7 2006/02/05 23:09:55 joerg Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBESMTP_BUILDLINK3_MK:=	${LIBESMTP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libesmtp
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibesmtp}
BUILDLINK_PACKAGES+=	libesmtp

.if !empty(LIBESMTP_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libesmtp+=	libesmtp>=1.0rc1nb1
BUILDLINK_RECOMMENDED.libesmtp?=	libesmtp>=1.0.3nb2
BUILDLINK_PKGSRCDIR.libesmtp?=	../../mail/libesmtp

LIBESMTP=	-lesmtp

CONFIGURE_ENV+=	LIBESMTP=${LIBESMTP:Q}
MAKE_ENV+=	LIBESMTP=${LIBESMTP:Q}

.endif	# LIBESMTP_BUILDLINK3_MK

.include "../../security/openssl/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

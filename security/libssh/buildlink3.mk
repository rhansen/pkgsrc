# $NetBSD: buildlink3.mk,v 1.7 2006/07/08 23:11:07 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBSSH_BUILDLINK3_MK:=	${NETWIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libssh
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibssh}
BUILDLINK_PACKAGES+=	libssh
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libssh

.if !empty(LIBSSH_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libssh+=	libssh>=0.11
BUILDLINK_PKGSRCDIR.libssh?=	../../security/libssh
.endif	# LIBSSH_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.5 2006/04/12 10:27:33 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBSSH_BUILDLINK3_MK:=	${NETWIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libssh
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibssh}
BUILDLINK_PACKAGES+=	libssh

.if !empty(LIBSSH_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libssh+=	libssh>=0.11
BUILDLINK_PKGSRCDIR.libssh?=	../../security/libssh
.endif	# LIBSSH_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

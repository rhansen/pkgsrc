# $NetBSD: buildlink3.mk,v 1.3 2005/04/01 19:50:42 drochner Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBOSIP2_BUILDLINK3_MK:=	${LIBOSIP2_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libosip2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibosip2}
BUILDLINK_PACKAGES+=	libosip2

.if !empty(LIBOSIP2_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libosip2+=	libosip2>=2.2.0
BUILDLINK_RECOMMENDED.libosip2+=	libosip2>=2.2.0
BUILDLINK_PKGSRCDIR.libosip2?=	../../devel/libosip
.endif	# LIBOSIP2_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.5 2006/02/05 18:55:22 adam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBTLEN_BUILDLINK3_MK:=	${LIBTLEN_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libtlen
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibtlen}
BUILDLINK_PACKAGES+=	libtlen

.if !empty(LIBTLEN_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libtlen+=	libtlen>=20040212
BUILDLINK_RECOMMENDED.libtlen+=	libtlen>=20040212nb1
BUILDLINK_PKGSRCDIR.libtlen?=	../../chat/libtlen
.endif	# LIBTLEN_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

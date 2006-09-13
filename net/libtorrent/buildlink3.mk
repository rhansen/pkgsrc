# $NetBSD: buildlink3.mk,v 1.11 2006/09/13 21:04:19 tron Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBTORRENT_BUILDLINK3_MK:=	${LIBTORRENT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libtorrent
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibtorrent}
BUILDLINK_PACKAGES+=	libtorrent
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libtorrent

.if !empty(LIBTORRENT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libtorrent+=	libtorrent>=0.10.0
BUILDLINK_ABI_DEPENDS.libtorrent+=	libtorrent>=0.10.0
BUILDLINK_PKGSRCDIR.libtorrent?=	../../net/libtorrent
.endif	# LIBTORRENT_BUILDLINK3_MK

.include "../../devel/libsigc++2/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

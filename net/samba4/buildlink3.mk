# $NetBSD: buildlink3.mk,v 1.2 2019/01/03 19:36:45 adam Exp $

BUILDLINK_TREE+=	samba

.if !defined(SAMBA_BUILDLINK3_MK)
SAMBA_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.samba+=	samba>=4.9.4
BUILDLINK_PKGSRCDIR.samba?=	../../net/samba4

.include "../../archivers/libarchive/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../databases/lmdb/buildlink3.mk"
.include "../../databases/tdb/buildlink3.mk"
.include "../../devel/cmocka/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/popt/buildlink3.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../devel/talloc/buildlink3.mk"
.include "../../devel/tevent/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../textproc/jansson/buildlink3.mk"
.endif	# SAMBA_BUILDLINK3_MK

BUILDLINK_TREE+=	-samba

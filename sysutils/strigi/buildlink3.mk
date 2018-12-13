# $NetBSD: buildlink3.mk,v 1.14 2018/12/13 19:51:37 adam Exp $

BUILDLINK_TREE+=	strigi

.if !defined(STRIGI_BUILDLINK3_MK)
STRIGI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.strigi+=	strigi>=0.6.2
BUILDLINK_ABI_DEPENDS.strigi?=	strigi>=0.7.8nb25
BUILDLINK_PKGSRCDIR.strigi?=	../../sysutils/strigi

.include "../../archivers/bzip2/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../textproc/libclucene/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../sysutils/dbus/buildlink3.mk"
.endif # STRIGI_BUILDLINK3_MK

BUILDLINK_TREE+=	-strigi

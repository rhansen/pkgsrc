# $NetBSD: buildlink3.mk,v 1.18 2015/09/10 00:54:47 dsainty Exp $

BUILDLINK_TREE+=	libgphoto2

.if !defined(LIBGPHOTO2_BUILDLINK3_MK)
LIBGPHOTO2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libgphoto2+=		libgphoto2>=2.1.2
BUILDLINK_ABI_DEPENDS.libgphoto2+=	libgphoto2>=2.4.7nb3
BUILDLINK_PKGSRCDIR.libgphoto2?=	../../devel/libgphoto2

.include "../../mk/bsd.fast.prefs.mk"
.include "../../devel/libusb/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libltdl/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../graphics/libexif/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif # LIBGPHOTO2_BUILDLINK3_MK

BUILDLINK_TREE+=	-libgphoto2

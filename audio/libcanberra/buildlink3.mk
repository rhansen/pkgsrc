# $NetBSD: buildlink3.mk,v 1.25 2014/05/05 00:47:37 ryoon Exp $

BUILDLINK_TREE+=	libcanberra

.if !defined(LIBCANBERRA_BUILDLINK3_MK)
LIBCANBERRA_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libcanberra+=	libcanberra>=0.10
BUILDLINK_ABI_DEPENDS.libcanberra+=	libcanberra>=0.27nb4
BUILDLINK_PKGSRCDIR.libcanberra?=	../../audio/libcanberra

pkgbase := libcanberra
.include "../../mk/pkg-build-options.mk"

.if !empty(PKG_BUILD_OPTIONS.libcanberra:Mgtk)
.include "../../x11/gtk2/buildlink3.mk"
.endif
.if !empty(PKG_BUILD_OPTIONS.libcanberra:Mgtk3)
.include "../../x11/gtk3/buildlink3.mk"
.endif
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../devel/libltdl/buildlink3.mk"
.endif # LIBCANBERRA_BUILDLINK3_MK

BUILDLINK_TREE+=	-libcanberra

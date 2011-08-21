# $NetBSD: buildlink3.mk,v 1.1.1.1 2011/08/21 13:29:32 obache Exp $

BUILDLINK_TREE+=	webkit-gtk3

.if !defined(WEBKIT_GTK3_BUILDLINK3_MK)
WEBKIT_GTK3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.webkit-gtk3+=	webkit-gtk3>=1.4.2
BUILDLINK_PKGSRCDIR.webkit-gtk3?=	../../www/webkit-gtk3

.include "../../databases/sqlite3/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../multimedia/gstreamer0.10/buildlink3.mk"
.include "../../multimedia/gst-plugins0.10-base/buildlink3.mk"
.include "../../net/libsoup24/buildlink3.mk"
.include "../../textproc/enchant/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../textproc/libxslt/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.endif # WEBKIT_GTK3_BUILDLINK3_MK

BUILDLINK_TREE+=	-webkit-gtk3

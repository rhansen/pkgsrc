# $NetBSD: buildlink3.mk,v 1.54 2017/02/12 06:24:53 ryoon Exp $

BUILDLINK_TREE+=	gnome-sharp

.if !defined(GNOME_SHARP_BUILDLINK3_MK)
GNOME_SHARP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gnome-sharp+=	gnome-sharp>=2.24.0
BUILDLINK_ABI_DEPENDS.gnome-sharp+=	gnome-sharp>=2.24.2nb43
BUILDLINK_PKGSRCDIR.gnome-sharp?=	../../x11/gnome-sharp

.include "../../devel/libgnomeui/buildlink3.mk"
.include "../../graphics/libart/buildlink3.mk"
.include "../../graphics/libgnomecanvas/buildlink3.mk"
.include "../../lang/mono/buildlink3.mk"
.include "../../sysutils/gnome-vfs/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/gtk-sharp/buildlink3.mk"
.endif # GNOME_SHARP_BUILDLINK3_MK

BUILDLINK_TREE+=	-gnome-sharp

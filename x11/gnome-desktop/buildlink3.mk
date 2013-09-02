# $NetBSD: buildlink3.mk,v 1.49 2013/09/02 19:50:46 adam Exp $

BUILDLINK_TREE+=	gnome-desktop

.if !defined(GNOME_DESKTOP_BUILDLINK3_MK)
GNOME_DESKTOP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gnome-desktop+=	gnome-desktop>=2.30.0
BUILDLINK_ABI_DEPENDS.gnome-desktop+=	gnome-desktop>=2.32.1nb19
BUILDLINK_PKGSRCDIR.gnome-desktop?=	../../x11/gnome-desktop

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/startup-notification/buildlink3.mk"
.endif # GNOME_DESKTOP_BUILDLINK3_MK

BUILDLINK_TREE+=	-gnome-desktop

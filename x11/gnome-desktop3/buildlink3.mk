# $NetBSD: buildlink3.mk,v 1.9 2013/06/03 10:06:12 wiz Exp $

BUILDLINK_TREE+=	gnome-desktop3

.if !defined(GNOME_DESKTOP3_BUILDLINK3_MK)
GNOME_DESKTOP3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gnome-desktop3+=	gnome-desktop3>=3.4.2
BUILDLINK_ABI_DEPENDS.gnome-desktop3+=	gnome-desktop3>=3.6.2nb2
BUILDLINK_PKGSRCDIR.gnome-desktop3?=	../../x11/gnome-desktop3

.include "../../x11/gtk3/buildlink3.mk"
.include "../../x11/libxkbfile/buildlink3.mk"
.include "../../x11/startup-notification/buildlink3.mk"
.endif # GNOME_DESKTOP_BUILDLINK3_MK

BUILDLINK_TREE+=	-gnome-desktop3

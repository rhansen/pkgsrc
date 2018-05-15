# $NetBSD: buildlink3.mk,v 1.42 2018/05/15 22:25:31 youri Exp $

BUILDLINK_TREE+=	xfce4-thunar

.if !defined(XFCE4_THUNAR_BUILDLINK3_MK)
XFCE4_THUNAR_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-thunar+=	xfce4-thunar>=1.6.6
BUILDLINK_ABI_DEPENDS.xfce4-thunar+=	xfce4-thunar>=1.6.11nb3
BUILDLINK_PKGSRCDIR.xfce4-thunar?=	../../sysutils/xfce4-thunar

.include "../../graphics/libexif/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/buildlink3.mk"
.include "../../x11/libxfce4util/buildlink3.mk"
.include "../../x11/xfce4-exo/buildlink3.mk"
.include "../../x11/xfce4-panel/buildlink3.mk"
.endif	# XFCE4_THUNAR_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-thunar

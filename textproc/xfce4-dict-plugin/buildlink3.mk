# $NetBSD: buildlink3.mk,v 1.11 2012/02/06 12:41:45 wiz Exp $

BUILDLINK_TREE+=	xfce4-dict-plugin

.if !defined(XFCE4_DICT_PLUGIN_BUILDLINK3_MK)
XFCE4_DICT_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-dict-plugin+=	xfce4-dict-plugin>=0.2.1
BUILDLINK_ABI_DEPENDS.xfce4-dict-plugin?=	xfce4-dict-plugin>=0.2.1nb8
BUILDLINK_PKGSRCDIR.xfce4-dict-plugin?=	../../textproc/xfce4-dict-plugin

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_DICT_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-dict-plugin

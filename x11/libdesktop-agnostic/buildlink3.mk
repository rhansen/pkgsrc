# $NetBSD: buildlink3.mk,v 1.10 2013/06/03 10:06:20 wiz Exp $

BUILDLINK_TREE+=	libdesktop-agnostic

.if !defined(LIBDESKTOP_AGNOSTIC_BUILDLINK3_MK)
LIBDESKTOP_AGNOSTIC_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libdesktop-agnostic+=	libdesktop-agnostic>=0.3.92
BUILDLINK_ABI_DEPENDS.libdesktop-agnostic+=	libdesktop-agnostic>=0.3.92nb9
BUILDLINK_PKGSRCDIR.libdesktop-agnostic?=	../../x11/libdesktop-agnostic

.include "../../lang/vala014/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/GConf/buildlink3.mk"
.include "../../devel/py-gobject/buildlink3.mk"
.include "../../devel/gobject-introspection/buildlink3.mk"
.endif	# LIBDESKTOP_AGNOSTIC_BUILDLINK3_MK

BUILDLINK_TREE+=	-libdesktop-agnostic

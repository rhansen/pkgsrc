# $NetBSD: buildlink3.mk,v 1.3 2009/08/26 19:57:01 sno Exp $
#

BUILDLINK_TREE+=	goocanvas

.if !defined(GOOCANVAS_BUILDLINK3_MK)
GOOCANVAS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.goocanvas+=	goocanvas>=0.12
BUILDLINK_ABI_DEPENDS.goocanvas?=	goocanvas>=0.15nb1
BUILDLINK_PKGSRCDIR.goocanvas?=	../../graphics/goocanvas

.include "../../devel/glib2/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # GOOCANVAS_BUILDLINK3_MK

BUILDLINK_TREE+=	-goocanvas

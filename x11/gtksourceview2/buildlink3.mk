# $NetBSD: buildlink3.mk,v 1.26 2013/09/02 19:50:43 adam Exp $

BUILDLINK_TREE+=	gtksourceview2

.if !defined(GTKSOURCEVIEW2_BUILDLINK3_MK)
GTKSOURCEVIEW2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gtksourceview2+=	gtksourceview2>=2.0.2<3
BUILDLINK_ABI_DEPENDS.gtksourceview2+=	gtksourceview2>=2.10.5nb19
BUILDLINK_PKGSRCDIR.gtksourceview2?=	../../x11/gtksourceview2

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/pango/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # GTKSOURCEVIEW2_BUILDLINK3_MK

BUILDLINK_TREE+=	-gtksourceview2

# $NetBSD: buildlink3.mk,v 1.32 2013/10/09 17:39:02 wiz Exp $

BUILDLINK_TREE+=	gdl

.if !defined(GDL_BUILDLINK3_MK)
GDL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gdl+=	gdl>=3.10
BUILDLINK_ABI_DEPENDS.gdl?=	gdl>=3.10.0nb1
BUILDLINK_PKGSRCDIR.gdl?=	../../devel/gdl

.include "../../devel/libglade/buildlink3.mk"
.include "../../devel/libgnomeui/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # GDL_BUILDLINK3_MK

BUILDLINK_TREE+=	-gdl

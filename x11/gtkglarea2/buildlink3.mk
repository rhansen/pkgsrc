# $NetBSD: buildlink3.mk,v 1.17 2012/05/07 01:54:09 dholland Exp $

BUILDLINK_TREE+=	gtkglarea2

.if !defined(GTKGLAREA2_BUILDLINK3_MK)
GTKGLAREA2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gtkglarea2+=	gtkglarea2>=2.0.1
BUILDLINK_ABI_DEPENDS.gtkglarea2+=	gtkglarea2>=2.0.1nb5
BUILDLINK_PKGSRCDIR.gtkglarea2?=	../../x11/gtkglarea2

.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif	# GTKGLAREA2_BUILDLINK3_MK

BUILDLINK_TREE+=	-gtkglarea2

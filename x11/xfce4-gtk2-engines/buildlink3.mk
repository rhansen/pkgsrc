# $NetBSD: buildlink3.mk,v 1.5 2005/03/18 07:59:09 martti Exp $

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH}+
XFCE4_GTK2_ENGINE_BUILDLINK3_MK:=	${XFCE4_GTK2_ENGINE_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	xfce4-gtk2-engine
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxfce4-gtk2-engine}
BUILDLINK_PACKAGES+=	xfce4-gtk2-engine

.if !empty(XFCE4_GTK2_ENGINE_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.xfce4-gtk2-engine+=	xfce4-gtk2-engine>=2.2.6
BUILDLINK_PKGSRCDIR.xfce4-gtk2-engine?=	../../x11/xfce4-gtk2-engines
.endif	# XFCE4_GTK2_ENGINE_BUILDLINK3_MK

.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

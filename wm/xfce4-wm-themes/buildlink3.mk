# $NetBSD: buildlink3.mk,v 1.6 2005/03/18 07:59:09 martti Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
XFCE4_WM_THEMES_BUILDLINK3_MK:=	${XFCE4_WM_THEMES_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	xfce4-wm-themes
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxfce4-wm-themes}
BUILDLINK_PACKAGES+=	xfce4-wm-themes

.if !empty(XFCE4_WM_THEMES_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.xfce4-wm-themes+=	xfce4-wm-themes>=4.2.1
BUILDLINK_PKGSRCDIR.xfce4-wm-themes?=	../../wm/xfce4-wm-themes
.endif	# XFCE4_WM_THEMES_BUILDLINK3_MK

.include "../../wm/xfce4-wm/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

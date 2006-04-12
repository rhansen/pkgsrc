# $NetBSD: buildlink3.mk,v 1.13 2006/04/12 10:27:44 rillig Exp $

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH}+
XFCE4_MCS_PLUGINS_BUILDLINK3_MK:=	${XFCE4_MCS_PLUGINS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	xfce4-mcs-plugins
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxfce4-mcs-plugins}
BUILDLINK_PACKAGES+=	xfce4-mcs-plugins

.if !empty(XFCE4_MCS_PLUGINS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.xfce4-mcs-plugins+=	xfce4-mcs-plugins>=4.2.3
BUILDLINK_ABI_DEPENDS.xfce4-mcs-plugins?=	xfce4-mcs-plugins>=4.2.3nb2
BUILDLINK_PKGSRCDIR.xfce4-mcs-plugins?=	../../x11/xfce4-mcs-plugins
.endif	# XFCE4_MCS_PLUGINS_BUILDLINK3_MK

.include "../../x11/xfce4-mcs-manager/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.2 2004/03/18 09:12:14 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
XFCE4_PRINT_BUILDLINK3_MK:=	${XFCE4_PRINT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	xfce4-print
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxfce4-print}
BUILDLINK_PACKAGES+=	xfce4-print

.if !empty(XFCE4_PRINT_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.xfce4-print+=	xfce4-print>=4.0.4nb1
BUILDLINK_PKGSRCDIR.xfce4-print?=	../../print/xfce4-print
.endif	# XFCE4_PRINT_BUILDLINK3_MK

.include "../../x11/xfce4-mcs-plugins/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

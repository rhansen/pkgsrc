# $NetBSD: buildlink3.mk,v 1.2 2004/01/04 23:34:07 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
XRANDR_BUILDLINK3_MK:=	${XRANDR_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	Xrandr
.endif

BUILDLINK_IS_BUILTIN.Xrender?=	no

.if !empty(XRANDR_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.Xrandr?=	Xrandr>=1.0.1
BUILDLINK_PKGSRCDIR.Xrandr?=	../../x11/Xrandr
BUILDLINK_PACKAGES+=		Xrandr
.endif	# XRANDR_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:C/\+$//}

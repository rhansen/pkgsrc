# $NetBSD: buildlink3.mk,v 1.2 2004/08/17 15:34:23 minskim Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY23PTH_XLIB_BUILDLINK3_MK:=	${PY23PTH_XLIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	py23pth-Xlib
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npy23pth-Xlib}
BUILDLINK_PACKAGES+=	py23pth-Xlib

.if !empty(PY23PTH_XLIB_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.py23pth-Xlib+=	py23pth-Xlib>=0.12
BUILDLINK_PKGSRCDIR.py23pth-Xlib?=	../../x11/py-Xlib
.endif	# PY23PTH_XLIB_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

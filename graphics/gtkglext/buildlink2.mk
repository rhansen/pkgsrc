# $NetBSD: buildlink2.mk,v 1.4 2003/03/12 22:07:28 jschauma Exp $
#
# This Makefile fragment is included by packages that use gtkglext.
#
# This file was created automatically using createbuildlink 2.4.
#

.if !defined(GTKGLEXT_BUILDLINK2_MK)
GTKGLEXT_BUILDLINK2_MK=	# defined

BUILDLINK_PACKAGES+=			gtkglext
BUILDLINK_DEPENDS.gtkglext?=		gtkglext>=0.6.1
BUILDLINK_PKGSRCDIR.gtkglext?=		../../graphics/gtkglext

EVAL_PREFIX+=	BUILDLINK_PREFIX.gtkglext=gtkglext
BUILDLINK_PREFIX.gtkglext_DEFAULT=	${LOCALBASE}
BUILDLINK_FILES.gtkglext+=	include/gtkglext-1.0/gdk/*.h
BUILDLINK_FILES.gtkglext+=	include/gtkglext-1.0/gdk/GL/*.h
BUILDLINK_FILES.gtkglext+=	include/gtkglext-1.0/gdk/x11/*.h
BUILDLINK_FILES.gtkglext+=	include/gtkglext-1.0/gtk/*.h
BUILDLINK_FILES.gtkglext+=	lib/gtkglext-1.0/include/gdkglext-config.h
BUILDLINK_FILES.gtkglext+=	lib/libgdkglext-x11-1.0.*
BUILDLINK_FILES.gtkglext+=	lib/libgtkglext-x11-1.0.*
BUILDLINK_FILES.gtkglext+=	lib/pkgconfig/gdkglext-1.0.pc
BUILDLINK_FILES.gtkglext+=	lib/pkgconfig/gdkglext-x11-1.0.pc
BUILDLINK_FILES.gtkglext+=	lib/pkgconfig/gtkglext-1.0.pc
BUILDLINK_FILES.gtkglext+=	lib/pkgconfig/gtkglext-x11-1.0.pc

.include "../../textproc/gtk-doc/buildlink2.mk"
.include "../../devel/pkgconfig/buildlink2.mk"
.include "../../graphics/MesaLib/buildlink2.mk"
.include "../../x11/gtk2/buildlink2.mk"

BUILDLINK_TARGETS+=	gtkglext-buildlink

gtkglext-buildlink: _BUILDLINK_USE

.endif	# GTKGLEXT_BUILDLINK2_MK

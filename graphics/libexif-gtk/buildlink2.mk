# $NetBSD: buildlink2.mk,v 1.5 2004/01/03 18:49:43 reed Exp $
#

.if !defined(LIBEXIF_GTK_BUILDLINK2_MK)
LIBEXIF_GTK_BUILDLINK2_MK=	# defined

BUILDLINK_PACKAGES+=			libexif-gtk
BUILDLINK_DEPENDS.libexif-gtk?=		libexif-gtk>=0.3.3nb7
BUILDLINK_PKGSRCDIR.libexif-gtk?=	../../graphics/libexif-gtk

EVAL_PREFIX+=	BUILDLINK_PREFIX.libexif-gtk=libexif-gtk
BUILDLINK_PREFIX.libexif-gtk_DEFAULT=	${LOCALBASE}
BUILDLINK_FILES.libexif-gtk+=	include/libexif-gtk/*.h
BUILDLINK_FILES.libexif-gtk+=	lib/libexif-gtk.*

.include "../../devel/gettext-lib/buildlink2.mk"
.include "../../graphics/libexif/buildlink2.mk"
.include "../../x11/gtk2/buildlink2.mk"

BUILDLINK_TARGETS+=	libexif-gtk-buildlink

libexif-gtk-buildlink: _BUILDLINK_USE

.endif	# LIBEXIF_GTK_BUILDLINK2_MK

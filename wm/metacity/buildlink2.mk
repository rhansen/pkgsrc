# $NetBSD: buildlink2.mk,v 1.9 2004/01/03 18:49:54 reed Exp $
#
# This Makefile fragment is included by packages that use metacity.
#
# This file was created automatically using createbuildlink 2.4.
#

.if !defined(METACITY_BUILDLINK2_MK)
METACITY_BUILDLINK2_MK=	# defined

BUILDLINK_PACKAGES+=			metacity
BUILDLINK_DEPENDS.metacity?=		metacity>=2.6.3nb1
BUILDLINK_PKGSRCDIR.metacity?=		../../wm/metacity

EVAL_PREFIX+=	BUILDLINK_PREFIX.metacity=metacity
BUILDLINK_PREFIX.metacity_DEFAULT=	${LOCALBASE}
BUILDLINK_FILES.metacity+=	include/metacity-1/metacity-private/*
BUILDLINK_FILES.metacity+=	lib/libmetacity-private.*

.include "../../devel/gettext-lib/buildlink2.mk"
.include "../../devel/libglade2/buildlink2.mk"
.include "../../net/ORBit2/buildlink2.mk"
.include "../../x11/startup-notification/buildlink2.mk"

BUILDLINK_TARGETS+=	metacity-buildlink

metacity-buildlink: _BUILDLINK_USE

.endif	# METACITY_BUILDLINK2_MK

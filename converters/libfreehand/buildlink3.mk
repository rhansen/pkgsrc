# $NetBSD: buildlink3.mk,v 1.2 2014/07/22 10:53:30 wiz Exp $

BUILDLINK_TREE+=	libfreehand

.if !defined(LIBFREEHAND_BUILDLINK3_MK)
LIBFREEHAND_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libfreehand+=	libfreehand>=0.0.0
BUILDLINK_ABI_DEPENDS.libfreehand?=	libfreehand>=0.1.0nb1
BUILDLINK_PKGSRCDIR.libfreehand?=	../../converters/libfreehand

.include "../../converters/libwpd/buildlink3.mk"
.include "../../converters/libwpg/buildlink3.mk"
.endif	# LIBFREEHAND_BUILDLINK3_MK

BUILDLINK_TREE+=	-libfreehand

# $NetBSD: buildlink3.mk,v 1.1 2012/03/19 19:44:01 markd Exp $

BUILDLINK_TREE+=	kactivities

.if !defined(KACTIVITIES_BUILDLINK3_MK)
KACTIVITIES_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.kactivities+=	kactivities>=4.7.95
BUILDLINK_ABI_DEPENDS.kactivities?=	kactivities>=4.7.95
BUILDLINK_PKGSRCDIR.kactivities?=	../../x11/kactivities

.include "../../x11/kdelibs4/buildlink3.mk"
.endif # KACTIVITIES_BUILDLINK3_MK

BUILDLINK_TREE+=	-kactivities

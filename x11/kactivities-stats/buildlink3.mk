# $NetBSD: buildlink3.mk,v 1.17 2020/08/18 17:57:32 leot Exp $

BUILDLINK_TREE+=	kactivities-stats

.if !defined(KACTIVITIES_STATS_BUILDLINK3_MK)
KACTIVITIES_STATS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.kactivities-stats+=	kactivities-stats>=5.41.0
BUILDLINK_ABI_DEPENDS.kactivities-stats?=	kactivities-stats>=5.70.0nb2
BUILDLINK_PKGSRCDIR.kactivities-stats?=		../../x11/kactivities-stats

.include "../../x11/kactivities5/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# KACTIVITIES_STATS_BUILDLINK3_MK

BUILDLINK_TREE+=	-kactivities-stats

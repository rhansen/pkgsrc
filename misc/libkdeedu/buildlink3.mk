# $NetBSD: buildlink3.mk,v 1.19 2014/08/22 11:24:26 wiz Exp $

BUILDLINK_TREE+=	libkdeedu

.if !defined(LIBKDEEDU_BUILDLINK3_MK)
LIBKDEEDU_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libkdeedu+=	libkdeedu>=4.8.0
BUILDLINK_ABI_DEPENDS.libkdeedu?=	libkdeedu>=4.11.5nb4
BUILDLINK_PKGSRCDIR.libkdeedu?=	../../misc/libkdeedu

.include "../../x11/kdelibs4/buildlink3.mk"
.endif	# LIBKDEEDU_BUILDLINK3_MK

BUILDLINK_TREE+=	-libkdeedu

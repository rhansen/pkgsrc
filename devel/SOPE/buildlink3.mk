# $NetBSD: buildlink3.mk,v 1.3 2015/06/03 12:21:31 taca Exp $

BUILDLINK_TREE+=	SOPE

.if !defined(SOPE_BUILDLINK3_MK)
SOPE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.SOPE+=	SOPE>=2.3.0
BUILDLINK_ABI_DEPENDS.SOPE+=	SOPE>=2.3.0
BUILDLINK_PKGSRCDIR.SOPE?=	../../devel/SOPE
.endif # SOPE_BUILDLINK3_MK

BUILDLINK_TREE+=	-SOPE

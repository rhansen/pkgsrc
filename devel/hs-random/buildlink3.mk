# $NetBSD: buildlink3.mk,v 1.2 2014/08/29 14:08:39 szptvlfn Exp $

BUILDLINK_TREE+=	hs-random

.if !defined(HS_RANDOM_BUILDLINK3_MK)
HS_RANDOM_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-random+=	hs-random>=1.0.1
BUILDLINK_ABI_DEPENDS.hs-random+=	hs-random>=1.0.1.3
BUILDLINK_PKGSRCDIR.hs-random?=	../../devel/hs-random
.endif	# HS_RANDOM_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-random

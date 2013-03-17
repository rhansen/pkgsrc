# $NetBSD: buildlink3.mk,v 1.1 2013/03/17 19:37:19 markd Exp $

BUILDLINK_TREE+=	eigen3

.if !defined(EIGEN3_BUILDLINK3_MK)
EIGEN3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.eigen3+=	eigen3>=3.1.2
BUILDLINK_PKGSRCDIR.eigen3?=	../../math/eigen3
BUILDLINK_DEPMETHOD.eigen3?=	build
.endif # EIGEN3_BUILDLINK3_MK

BUILDLINK_TREE+=	-eigen3

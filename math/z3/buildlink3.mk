# $NetBSD: buildlink3.mk,v 1.2 2018/03/13 00:34:02 khorben Exp $

BUILDLINK_TREE+=	z3

.if !defined(Z3_BUILDLINK3_MK)
Z3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.z3+=	z3>=4.5.0
BUILDLINK_PKGSRCDIR.z3?=	../../math/z3

.endif  # Z3_BUILDLINK3_MK

BUILDLINK_TREE+=	-z3

# $NetBSD: buildlink3.mk,v 1.1 2017/02/23 16:55:07 kleink Exp $

BUILDLINK_TREE+=	argon2

.if !defined(ARGON2_BUILDLINK3_MK)
ARGON2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.argon2+=	argon2>=20161029nb1
BUILDLINK_ABI_DEPENDS.argon2+=	argon2>=20161029nb1
BUILDLINK_PKGSRCDIR.argon2?=	../../security/argon2
.endif # ARGON2_BUILDLINK3_MK

BUILDLINK_TREE+=	-argon2

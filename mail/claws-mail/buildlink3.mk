# $NetBSD: buildlink3.mk,v 1.8 2012/02/06 12:40:47 wiz Exp $

BUILDLINK_TREE+=	claws-mail

.if !defined(CLAWS_MAIL_BUILDLINK3_MK)
CLAWS_MAIL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.claws-mail+= claws-mail>=3.7.0
BUILDLINK_ABI_DEPENDS.claws-mail?=	claws-mail>=3.7.10nb3
BUILDLINK_PKGSRCDIR.claws-mail?=	../../mail/claws-mail

.include "../../textproc/enchant/buildlink3.mk"
.endif # CLAWS_MAIL_BUILDLINK3_MK

BUILDLINK_TREE+=	-claws-mail

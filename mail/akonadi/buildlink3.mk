# $NetBSD: buildlink3.mk,v 1.23 2013/06/03 10:05:28 wiz Exp $

BUILDLINK_TREE+=	akonadi

.if !defined(AKONADI_BUILDLINK3_MK)
AKONADI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.akonadi+=	akonadi>=0.82.0
BUILDLINK_ABI_DEPENDS.akonadi+=	akonadi>=1.9.1nb2
BUILDLINK_PKGSRCDIR.akonadi?=	../../mail/akonadi

.include "../../x11/qt4-libs/buildlink3.mk"
.include "../../x11/qt4-qdbus/buildlink3.mk"
.endif # AKONADI_BUILDLINK3_MK

BUILDLINK_TREE+=	-akonadi

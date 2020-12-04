# $NetBSD: buildlink3.mk,v 1.6 2020/12/04 04:56:18 riastradh Exp $

BUILDLINK_TREE+=	lxqt-globalkeys

.if !defined(LXQT_GLOBALKEYS_BUILDLINK3_MK)
LXQT_GLOBALKEYS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.lxqt-globalkeys+=	lxqt-globalkeys>=0.15.0
BUILDLINK_ABI_DEPENDS.lxqt-globalkeys?=	lxqt-globalkeys>=0.15.0nb4
BUILDLINK_PKGSRCDIR.lxqt-globalkeys?=	../../x11/lxqt-globalkeys

.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../x11/liblxqt/buildlink3.mk"
.endif	# LXQT_GLOBALKEYS_BUILDLINK3_MK

BUILDLINK_TREE+=	-lxqt-globalkeys

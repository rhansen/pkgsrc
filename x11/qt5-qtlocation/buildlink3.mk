# $NetBSD: buildlink3.mk,v 1.21 2018/04/14 07:34:07 adam Exp $

BUILDLINK_TREE+=	qt5-qtlocation

.if !defined(QT5_QTLOCATION_BUILDLINK3_MK)
QT5_QTLOCATION_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.qt5-qtlocation+=	qt5-qtlocation>=5.9.1
BUILDLINK_ABI_DEPENDS.qt5-qtlocation+=	qt5-qtlocation>=5.10.1nb3
BUILDLINK_PKGSRCDIR.qt5-qtlocation?=	../../x11/qt5-qtlocation

BUILDLINK_INCDIRS.qt5-qtlocation+=	qt5/include
BUILDLINK_LIBDIRS.qt5-qtlocation+=	qt5/lib
BUILDLINK_LIBDIRS.qt5-qtlocation+=	qt5/plugins

.include "../../x11/qt5-qtdeclarative/buildlink3.mk"
.endif	# QT5_QTLOCATION_BUILDLINK3_MK

BUILDLINK_TREE+=	-qt5-qtlocation

# $NetBSD: buildlink3.mk,v 1.16 2014/04/10 06:21:19 obache Exp $

BUILDLINK_TREE+=	libkipi

.if !defined(LIBKIPI_BUILDLINK3_MK)
LIBKIPI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libkipi+=	libkipi>=0.1.5<4.0
BUILDLINK_ABI_DEPENDS.libkipi+=	libkipi>=0.1.6nb26
BUILDLINK_PKGSRCDIR.libkipi?=	../../graphics/libkipi-kde3

.include "../../x11/kdelibs3/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.endif # LIBKIPI_BUILDLINK3_MK

BUILDLINK_TREE+=	-libkipi

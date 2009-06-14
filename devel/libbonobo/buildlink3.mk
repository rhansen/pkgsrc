# $NetBSD: buildlink3.mk,v 1.18 2009/06/14 22:58:00 joerg Exp $

BUILDLINK_TREE+=	libbonobo

.if !defined(LIBBONOBO_BUILDLINK3_MK)
LIBBONOBO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libbonobo+=	libbonobo>=2.8.0
BUILDLINK_ABI_DEPENDS.libbonobo+=	libbonobo>=2.10.1nb2
BUILDLINK_PKGSRCDIR.libbonobo?=	../../devel/libbonobo

BUILDLINK_FILES.libbonobo+=	share/idl/bonobo-2.0/*
BUILDLINK_FILES.libbonobo+=	share/idl/bonobo-activation-2.0/*

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/popt/buildlink3.mk"
.include "../../net/ORBit2/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif # LIBBONOBO_BUILDLINK3_MK

BUILDLINK_TREE+=	-libbonobo

# $NetBSD: buildlink3.mk,v 1.1 2014/10/13 12:51:09 mef Exp $

BUILDLINK_TREE+=	gnuradio-default

.if !defined(GNURADIO_DEFAULT_BUILDLINK3_MK)
GNURADIO_DEFAULT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gnuradio-default+=	gnuradio-default>=3.7.5
BUILDLINK_ABI_DEPENDS.gnuradio-default+=	gnuradio-default>=3.7.5
BUILDLINK_PKGSRCDIR.gnuradio-default?=	../../ham/gnuradio-default
.endif # GNURADIO_DEFAULT_BUILDLINK3_MK

BUILDLINK_TREE+=	-gnuradio-default

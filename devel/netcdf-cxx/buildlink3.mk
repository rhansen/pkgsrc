# $NetBSD: buildlink3.mk,v 1.1 2015/08/30 10:26:44 markd Exp $

BUILDLINK_TREE+=	netcdf-cxx

.if !defined(NETCDF_CXX_BUILDLINK3_MK)
NETCDF_CXX_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.netcdf-cxx+=	netcdf-cxx>=4.2
BUILDLINK_ABI_DEPENDS.netcdf-cxx?=	netcdf-cxx>=4.2
BUILDLINK_PKGSRCDIR.netcdf-cxx?=	../../devel/netcdf-cxx

.include "../../devel/netcdf/buildlink3.mk"
.endif	# NETCDF_CXX_BUILDLINK3_MK

BUILDLINK_TREE+=	-netcdf-cxx

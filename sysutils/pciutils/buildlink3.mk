# $NetBSD: buildlink3.mk,v 1.1 2004/04/26 10:21:26 cube Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PCIUTILS_BUILDLINK3_MK:=	${PCIUTILS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pciutils
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npciutils}
BUILDLINK_PACKAGES+=	pciutils

.if !empty(PCIUTILS_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.pciutils+=	pciutils>=2.1.11
BUILDLINK_PKGSRCDIR.pciutils?=	../../sysutils/pciutils
BUILDLINK_DEPMETHOD.pciutils?=	build
.endif	# PCIUTILS_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

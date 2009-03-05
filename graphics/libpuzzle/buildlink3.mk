# $NetBSD: buildlink3.mk,v 1.1 2009/03/05 00:23:46 imil Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBPUZZLE_BUILDLINK3_MK:=	${LIBPUZZLE_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	libpuzzle
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibpuzzle}
BUILDLINK_PACKAGES+=	libpuzzle
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libpuzzle

.if ${LIBPUZZLE_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.libpuzzle+=	libpuzzle>=0.9
BUILDLINK_PKGSRCDIR.libpuzzle?=	../../graphics/libpuzzle
.endif	# LIBPUZZLE_BUILDLINK3_MK

.include "../../graphics/gd/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.3 2004/02/10 20:45:01 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBMAD_BUILDLINK3_MK:=		${LIBMAD_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libmad
.endif

.if !empty(LIBMAD_BUILDLINK3_MK:M+)
BUILDLINK_PACKAGES+=		libmad
BUILDLINK_DEPENDS.libmad+=	libmad>=0.15.0b
BUILDLINK_PKGSRCDIR.libmad?=	../../audio/libmad
.endif	# LIBMAD_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

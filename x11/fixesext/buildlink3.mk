# $NetBSD: buildlink3.mk,v 1.5 2006/04/12 10:27:40 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
FIXESEXT_BUILDLINK3_MK:=	${FIXESEXT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	fixesext
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nfixesext}
BUILDLINK_PACKAGES+=	fixesext

.if !empty(FIXESEXT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.fixesext+=	fixesext>=2.0
BUILDLINK_ABI_DEPENDS.fixesext?=	fixesext>=2.0.1nb1
BUILDLINK_PKGSRCDIR.fixesext?=	../../x11/fixesext
.endif	# FIXESEXT_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

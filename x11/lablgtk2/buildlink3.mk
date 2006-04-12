# $NetBSD: buildlink3.mk,v 1.9 2006/04/12 10:27:41 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LABLGTK2_BUILDLINK3_MK:=	${LABLGTK2_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	lablgtk2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlablgtk2}
BUILDLINK_PACKAGES+=	lablgtk2

.if !empty(LABLGTK2_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.lablgtk2+=	lablgtk2>=2.6.0nb3
BUILDLINK_ABI_DEPENDS.lablgtk2?=	lablgtk2>=2.6.0nb5
BUILDLINK_PKGSRCDIR.lablgtk2?=	../../x11/lablgtk2
.endif	# LABLGTK2_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

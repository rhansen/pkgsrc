# $NetBSD: buildlink3.mk,v 1.14 2007/05/12 13:53:11 ghen Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
FIREFOX_GTK2_BUILDLINK3_MK:=	${FIREFOX_GTK2_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	firefox-gtk1
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nfirefox-gtk1}
BUILDLINK_PACKAGES+=	firefox-gtk1
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}firefox-gtk1

.if !empty(FIREFOX_GTK2_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.firefox-gtk1+=	firefox-gtk1>=2.0
BUILDLINK_ABI_DEPENDS.firefox-gtk1+=	firefox-gtk1>=2.0.0.3nb1
BUILDLINK_PKGSRCDIR.firefox-gtk1?=	../../www/firefox-gtk1
.endif	# FIREFOX_GTK2_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

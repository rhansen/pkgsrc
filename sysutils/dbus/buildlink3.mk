# $NetBSD: buildlink3.mk,v 1.1.1.1 2004/10/11 17:45:27 jmmv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
DBUS_BUILDLINK3_MK:=	${DBUS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	dbus
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ndbus}
BUILDLINK_PACKAGES+=	dbus

.if !empty(DBUS_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.dbus+=	dbus>=0.22
BUILDLINK_PKGSRCDIR.dbus?=	../../sysutils/dbus
.endif	# DBUS_BUILDLINK3_MK

.include "../../textproc/expat/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.1 2004/05/01 23:57:00 snj Exp $
# XXX	BUILDLINK_DEPMETHOD.kdebase?=	build

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
KDEBASE_BUILDLINK3_MK:=	${KDEBASE_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	kdebase
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nkdebase}
BUILDLINK_PACKAGES+=	kdebase

.if !empty(KDEBASE_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.kdebase+=	kdebase>=2.2.2nb4
BUILDLINK_RECOMMENDED.kdebase2?=kdebase>=2.2.2nb6
BUILDLINK_PKGSRCDIR.kdebase?=	../../x11/kdebase2
.endif	# KDEBASE_BUILDLINK3_MK

.include "../../x11/kdelibs2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.2 2009/03/20 19:25:40 joerg Exp $

BUILDLINK_DEPMETHOD.evieext?=	build

BUILDLINK_TREE+=	evieext

.if !defined(EVIEEXT_BUILDLINK3_MK)
EVIEEXT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.evieext+=	evieext>=1.0.2
BUILDLINK_PKGSRCDIR.evieext?=	../../x11/evieext
.endif # EVIEEXT_BUILDLINK3_MK

BUILDLINK_TREE+=	-evieext

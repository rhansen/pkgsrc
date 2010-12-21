# $NetBSD: buildlink3.mk,v 1.1.1.1 2010/12/21 11:27:57 obache Exp $
#

BUILDLINK_TREE+=	cutter

.if !defined(CUTTER_BUILDLINK3_MK)
CUTTER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.cutter+=	cutter>=1.1.3
BUILDLINK_DEPMETHOD.cutter?=	build
BUILDLINK_PKGSRCDIR.cutter?=	../../devel/cutter

.include "../../devel/glib2/buildlink3.mk"
.endif	# CUTTER_BUILDLINK3_MK

BUILDLINK_TREE+=	-cutter

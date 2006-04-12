# $NetBSD: buildlink3.mk,v 1.8 2006/04/12 10:27:13 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PHYSFS_BUILDLINK3_MK:=	${PHYSFS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	physfs
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nphysfs}
BUILDLINK_PACKAGES+=	physfs

.if !empty(PHYSFS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.physfs+=	physfs>=1.0.0
BUILDLINK_ABI_DEPENDS.physfs+=	physfs>=1.0.1
BUILDLINK_PKGSRCDIR.physfs?=	../../devel/physfs
.endif	# PHYSFS_BUILDLINK3_MK

.include "../../devel/readline/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.6 2006/02/05 23:09:16 joerg Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
KDEGAMES_BUILDLINK3_MK:=	${KDEGAMES_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	kdegames
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nkdegames}
BUILDLINK_PACKAGES+=	kdegames

.if !empty(KDEGAMES_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.kdegames+=	kdegames>=3.5.0nb1
BUILDLINK_RECOMMENDED.kdegames?=	kdegames>=3.5.1nb1
BUILDLINK_PKGSRCDIR.kdegames?=	../../games/kdegames3
.endif	# KDEGAMES_BUILDLINK3_MK

.include "../../x11/kdebase3/buildlink3.mk"
.include "../../x11/kdelibs3/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

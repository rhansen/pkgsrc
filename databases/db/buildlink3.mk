# $NetBSD: buildlink3.mk,v 1.11 2004/03/10 18:06:07 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
DB_BUILDLINK3_MK:=	${DB_BUILDLINK3_MK}+

.include "../../mk/bsd.prefs.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	db2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ndb2}
BUILDLINK_PACKAGES+=	db2

.if !empty(DB_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.db2+=		db>=2.7.3
BUILDLINK_PKGSRCDIR.db2?=	../../databases/db

.if defined(USE_DB185)
BUILDLINK_INCDIRS.db2?=	include/db2
BUILDLINK_TRANSFORM+=	l:db:db2
.endif

.endif	# DB_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

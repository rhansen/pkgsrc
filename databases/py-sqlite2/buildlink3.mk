# $NetBSD: buildlink3.mk,v 1.1 2007/01/10 10:39:18 drochner Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY_SQLITE2_BUILDLINK3_MK:=	${PY_SQLITE2_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	py-sqlite2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npy-sqlite2}
BUILDLINK_PACKAGES+=	py-sqlite2
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}py-sqlite2

.if ${PY_SQLITE2_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.py-sqlite2+=	${PYPKGPREFIX}-sqlite2>=2.3.2
BUILDLINK_PKGSRCDIR.py-sqlite2?=	../../databases/py-sqlite2
.endif	# PY_SQLITE2_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

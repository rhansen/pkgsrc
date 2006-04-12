# $NetBSD: buildlink3.mk,v 1.7 2006/04/12 10:27:05 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PY_ZODB_BUILDLINK3_MK:=	${PY_ZODB_BUILDLINK3_MK}+

.include "../../lang/python/pyversion.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pyZODB
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NpyZODB}
BUILDLINK_PACKAGES+=	pyZODB

.if !empty(PY_ZODB_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.pyZODB+=	${PYPKGPREFIX}-ZODB>=3.2nb1
BUILDLINK_ABI_DEPENDS.pyZODB?=	${PYPKGPREFIX}-ZODB>=3.2.1nb2
BUILDLINK_PKGSRCDIR.pyZODB?=	../../databases/py-ZODB
.endif	# PY_ZODB_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

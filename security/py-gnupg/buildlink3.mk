# $NetBSD: buildlink3.mk,v 1.2 2009/03/20 17:30:12 joerg Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY_GNUPG_BUILDLINK3_MK:=	${PY_GNUPG_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	py-gnupg
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npy-gnupg}
BUILDLINK_PACKAGES+=	py-gnupg
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}py-gnupg

.if !empty(PY_GNUPG_BUILDLINK3_MK:M+)
.  include "../../lang/python/pyversion.mk"

BUILDLINK_API_DEPENDS.py-gnupg+=	${PYPKGPREFIX}-gnupg-[0-9]*
BUILDLINK_ABI_DEPENDS.py-gnupg+=	${PYPKGPREFIX}-gnupg>=0.3.2
BUILDLINK_PKGSRCDIR.py-gnupg?=		../../security/py-gnupg
.endif	# PY_GNUPG_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

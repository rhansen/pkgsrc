# $NetBSD: buildlink3.mk,v 1.6 2006/04/12 10:27:19 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
SANE_BACKENDS_BUILDLINK3_MK:=	${SANE_BACKENDS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	sane-backends
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nsane-backends}
BUILDLINK_PACKAGES+=	sane-backends

.if !empty(SANE_BACKENDS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.sane-backends+=	sane-backends>=1.0.3
BUILDLINK_ABI_DEPENDS.sane-backends+=	sane-backends>=1.0.17nb1
BUILDLINK_PKGSRCDIR.sane-backends?=	../../graphics/sane-backends
.endif	# SANE_BACKENDS_BUILDLINK3_MK

.include "../../mk/bsd.prefs.mk"

.if (${OPSYS} != "SunOS")
. include "../../devel/libusb/buildlink3.mk"
.endif
.include "../../graphics/jpeg/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.14 2006/04/17 13:46:06 wiz Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
KDEMULTIMEDIA_BUILDLINK3_MK:=	${KDEMULTIMEDIA_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	kdemultimedia
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nkdemultimedia}
BUILDLINK_PACKAGES+=	kdemultimedia

.if !empty(KDEMULTIMEDIA_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.kdemultimedia+=	kdemultimedia>=3.5.0nb2
BUILDLINK_ABI_DEPENDS.kdemultimedia?=	kdemultimedia>=3.5.2nb2
BUILDLINK_PKGSRCDIR.kdemultimedia?=	../../multimedia/kdemultimedia3
.endif	# KDEMULTIMEDIA_BUILDLINK3_MK

.include "../../audio/arts/buildlink3.mk"
.include "../../audio/lame/buildlink3.mk"
.include "../../audio/musicbrainz/buildlink3.mk"
.include "../../audio/libtunepimp/buildlink3.mk"
.include "../../audio/taglib/buildlink3.mk"
.if defined(PTHREAD_TYPE) && ${PTHREAD_TYPE} == "pth"
.include "../../devel/pthread-sem/buildlink3.mk"
.endif
.include "../../multimedia/xine-lib/buildlink3.mk"
.include "../../x11/kdebase3/buildlink3.mk"
.include "../../x11/kdelibs3/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

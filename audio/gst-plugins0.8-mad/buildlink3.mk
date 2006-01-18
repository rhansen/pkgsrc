# $NetBSD: buildlink3.mk,v 1.1 2006/01/18 12:44:01 jmmv Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
GST_PLUGINS0.8_MAD_BUILDLINK3_MK:=	${GST_PLUGINS0.8_MAD_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	gst-plugins0.8-mad
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ngst-plugins0.8-mad}
BUILDLINK_PACKAGES+=	gst-plugins0.8-mad

.if !empty(GST_PLUGINS0.8_MAD_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.gst-plugins0.8-mad+=	gst-plugins0.8-mad>=0.8.11
BUILDLINK_PKGSRCDIR.gst-plugins0.8-mad?=	../../audio/gst-plugins0.8-mad
.endif	# GST_PLUGINS0.8_MAD_BUILDLINK3_MK

.include "../../audio/libid3tag/buildlink3.mk"
.include "../../audio/libmad/buildlink3.mk"
.include "../../multimedia/gst-plugins0.8/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

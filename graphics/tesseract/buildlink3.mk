# $NetBSD: buildlink3.mk,v 1.1 2018/04/29 10:16:20 adam Exp $

BUILDLINK_TREE+=	tesseract

.if !defined(TESSERACT_BUILDLINK3_MK)
TESSERACT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.tesseract+=	tesseract>=3.05.01nb6
BUILDLINK_PKGSRCDIR.tesseract?=		../../graphics/tesseract

.include "../../graphics/leptonica/buildlink3.mk"
.endif	# TESSERACT_BUILDLINK3_MK

BUILDLINK_TREE+=	-tesseract

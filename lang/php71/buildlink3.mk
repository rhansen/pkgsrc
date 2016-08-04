# $NetBSD: buildlink3.mk,v 1.1 2016/08/04 14:09:03 jdolecek Exp $

BUILDLINK_TREE+=	php

.if !defined(PHP_BUILDLINK3_MK)
PHP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php+=	php>=7.1.0<7.2
BUILDLINK_ABI_DEPENDS.php+=	php>=7.1.0<7.2
BUILDLINK_PKGSRCDIR.php?=	../../lang/php71

.include "../../textproc/libxml2/buildlink3.mk"
.endif # PHP_BUILDLINK3_MK

BUILDLINK_TREE+=	-php

# $NetBSD: buildlink3.mk,v 1.37 2014/02/12 23:18:39 tron Exp $

BUILDLINK_TREE+=	gkrellm

.if !defined(GKRELLM_BUILDLINK3_MK)
GKRELLM_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gkrellm+=	gkrellm>=2.1.22
BUILDLINK_ABI_DEPENDS.gkrellm+=	gkrellm>=2.2.10nb22
BUILDLINK_PKGSRCDIR.gkrellm?=	../../sysutils/gkrellm

.include "../../devel/glib2/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # GKRELLM_BUILDLINK3_MK

BUILDLINK_TREE+=	-gkrellm

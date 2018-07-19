# $NetBSD: buildlink3.mk,v 1.3 2018/07/19 13:01:34 jaapb Exp $

BUILDLINK_TREE+=	ocaml-ppx_tools_versioned

.if !defined(OCAML_PPX_TOOLS_VERSIONED_BUILDLINK3_MK)
OCAML_PPX_TOOLS_VERSIONED_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-ppx_tools_versioned+=	ocaml-ppx_tools_versioned>=5.0.1
BUILDLINK_ABI_DEPENDS.ocaml-ppx_tools_versioned+=	ocaml-ppx_tools_versioned>=5.2
BUILDLINK_PKGSRCDIR.ocaml-ppx_tools_versioned?=		../../devel/ocaml-ppx_tools_versioned
.endif	# OCAML_PPX_TOOLS_VERSIONED_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-ppx_tools_versioned

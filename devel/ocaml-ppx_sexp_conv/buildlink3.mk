# $NetBSD: buildlink3.mk,v 1.9 2019/03/05 18:06:23 jaapb Exp $

BUILDLINK_TREE+=	ocaml-ppx_sexp_conv

.if !defined(OCAML_PPX_SEXP_CONV_BUILDLINK3_MK)
OCAML_PPX_SEXP_CONV_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-ppx_sexp_conv+=	ocaml-ppx_sexp_conv>=0.9.0
BUILDLINK_ABI_DEPENDS.ocaml-ppx_sexp_conv+=	ocaml-ppx_sexp_conv>=0.12.0
BUILDLINK_PKGSRCDIR.ocaml-ppx_sexp_conv?=	../../devel/ocaml-ppx_sexp_conv

#.include "../../devel/ocaml-ppx_core/buildlink3.mk"
#.include "../../devel/ocaml-ppx_type_conv/buildlink3.mk"
.endif	# OCAML_PPX_SEXP_CONV_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-ppx_sexp_conv

# $NetBSD: buildlink3.mk,v 1.4 2019/03/05 17:51:42 jaapb Exp $

BUILDLINK_TREE+=	ocaml-parsexp

.if !defined(OCAML_PARSEXP_BUILDLINK3_MK)
OCAML_PARSEXP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-parsexp+=	ocaml-parsexp>=0.11.0
BUILDLINK_ABI_DEPENDS.ocaml-parsexp+=	ocaml-parsexp>=0.12.0
BUILDLINK_PKGSRCDIR.ocaml-parsexp?=	../../devel/ocaml-parsexp

.endif	# OCAML_PARSEXP_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-parsexp

# $NetBSD: buildlink3.mk,v 1.1 2019/03/12 18:09:29 jaapb Exp $

BUILDLINK_TREE+=	ocaml-bigstringaf

.if !defined(OCAML_BIGSTRINGAF_BUILDLINK3_MK)
OCAML_BIGSTRINGAF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-bigstringaf+=	ocaml-bigstringaf>=0.4.0
BUILDLINK_PKGSRCDIR.ocaml-bigstringaf?=	../../devel/ocaml-bigstringaf

.endif	# OCAML_BIGSTRINGAF_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-bigstringaf

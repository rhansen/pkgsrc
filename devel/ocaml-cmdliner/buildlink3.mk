# $NetBSD: buildlink3.mk,v 1.3 2015/06/30 11:52:56 jaapb Exp $

BUILDLINK_TREE+=	ocaml-cmdliner

.if !defined(OCAML_CMDLINER_BUILDLINK3_MK)
OCAML_CMDLINER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-cmdliner+=	ocaml-cmdliner>=0.9.4
BUILDLINK_ABI_DEPENDS.ocaml-cmdliner?=	ocaml-cmdliner>=0.9.4nb2
BUILDLINK_PKGSRCDIR.ocaml-cmdliner?=	../../devel/ocaml-cmdliner

.include "../../devel/ocaml-findlib/buildlink3.mk"
.include "../../lang/ocaml/buildlink3.mk"
.endif	# OCAML_CMDLINER_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-cmdliner

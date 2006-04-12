# $NetBSD: buildlink3.mk,v 1.4 2006/04/12 10:27:31 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
TCL_SCOTTY_BUILDLINK3_MK:=	${TCL_SCOTTY_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	tcl-scotty
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ntcl-scotty}
BUILDLINK_PACKAGES+=	tcl-scotty

.if !empty(TCL_SCOTTY_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.tcl-scotty+=	tcl-scotty>=2.1.11
BUILDLINK_ABI_DEPENDS.tcl-scotty+=	tcl-scotty>=2.1.11nb4
BUILDLINK_PKGSRCDIR.tcl-scotty?=	../../net/tcl-scotty
.endif	# TCL_SCOTTY_BUILDLINK3_MK

.include "../../lang/tcl/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

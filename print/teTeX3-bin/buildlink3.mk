# $NetBSD: buildlink3.mk,v 1.12 2008/12/07 06:40:47 minskim Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
TETEX_BIN_BUILDLINK3_MK:=	${TETEX_BIN_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	teTeX-bin
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NteTeX-bin}
BUILDLINK_PACKAGES+=	teTeX-bin
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}teTeX-bin

.if !empty(TETEX_BIN_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.teTeX-bin+=	teTeX-bin>=3.0nb2
BUILDLINK_ABI_DEPENDS.teTeX-bin?=	teTeX-bin>=3.0nb7
BUILDLINK_PKGSRCDIR.teTeX-bin?=	../../print/teTeX3-bin
.endif	# TETEX_BIN_BUILDLINK3_MK

TEXMFDIST=	${PREFIX}/share/texmf-dist
PLIST_SUBST+=	TEXMFDIST=${TEXMFDIST:C|^${PREFIX}/||}

TEX=etex
PDFTEX=pdfetex
#PKG_TEXMFPREFIX=	${PREFIX}/share/texmf-dist
PKG_TEXMFPREFIX=	${PREFIX}/share/texmf
PKG_LOCALTEXMFPREFIX=	${PREFIX}/share/texmf-local
PLIST_SUBST+=	PKG_TEXMFPREFIX=${PKG_TEXMFPREFIX:C|^${PREFIX}/||}
PLIST_SUBST+=	PKG_LOCALTEXMFPREFIX=${PKG_LOCALTEXMFPREFIX:C|^${PREFIX}/||}

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

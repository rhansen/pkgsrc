# $NetBSD: options.mk,v 1.9 2011/01/31 10:21:41 wiz Exp $

.include "../../mk/bsd.prefs.mk"

PKG_OPTIONS_VAR=	PKG_OPTIONS.imlib2
PKG_SUPPORTED_OPTIONS=	x11
PKG_SUGGESTED_OPTIONS=	x11
.if ${MACHINE_ARCH} == "i386"
PKG_SUPPORTED_OPTIONS+=	mmx
.elif ${MACHINE_ARCH} == "x86_64"
PKG_SUPPORTED_OPTIONS+=	imlib2-amd64
PKG_SUGGESTED_OPTIONS+=	imlib2-amd64
.endif

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mmmx)
CONFIGURE_ARGS+=	--enable-mmx
.endif

.if !empty(PKG_OPTIONS:Mimlib2-amd64)
CONFIGURE_ARGS+=	--enable-amd64
.endif

PLIST_VARS+=		x11

.if !empty(PKG_OPTIONS:Mx11)
.include "../../x11/xextproto/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
PLIST.x11=		yes
.else
CONFIGURE_ARGS+=	--without-x
.endif

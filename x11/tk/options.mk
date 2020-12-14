# $NetBSD: options.mk,v 1.9 2020/12/14 08:46:56 dbj Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.tk
PKG_SUPPORTED_OPTIONS=	threads debug xft2
PKG_SUGGESTED_OPTIONS=	threads

.include "../../mk/bsd.prefs.mk"

PLIST_VARS+=	aqua

.if ${OPSYS} != "Darwin"
PKG_SUGGESTED_OPTIONS+=	xft2
.else
PKG_SUPPORTED_OPTIONS+=	aqua
.endif

.include "../../mk/bsd.options.mk"

# IMPORTANT: This option should be enabled on a system without X11.
# Otherwise some X11 headers are installed and will break X11 compatibility.
.if !empty(PKG_OPTIONS:Maqua)
CONFIGURE_ARGS+=	--enable-aqua
CONFIGURE_ARGS+=	--without-x
PLIST.aqua=		yes
.else
CONFIGURE_ARGS+=	--x-includes=${X11BASE}/include
CONFIGURE_ARGS+=	--x-libraries=${X11BASE}/lib${LIBABISUFFIX:Q}
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXScrnSaver/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mdebug)
CONFIGURE_ARGS+=	--enable-symbols
.endif

.if !empty(PKG_OPTIONS:Mthreads)
CONFIGURE_ARGS+=	--enable-threads
PTHREAD_OPTS+=		require
.include "../../mk/pthread.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-threads
.endif

.if !empty(PKG_OPTIONS:Mxft2)
CONFIGURE_ARGS+=	--enable-xft
USE_TOOLS+=		pkg-config
.include "../../x11/libXft/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-xft
.endif

# $NetBSD: options.mk,v 1.6 2015/10/26 19:03:59 adam Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.qt5
PKG_SUPPORTED_OPTIONS=	cups debug gtk2

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		cups

.if !empty(PKG_OPTIONS:Mcups)
.  include "../../print/cups15/buildlink3.mk"
CONFIGURE_ARGS+=	-cups
PLIST.cups=		yes
.else
CONFIGURE_ARGS+=	-no-cups
.endif

.if !empty(PKG_OPTIONS:Mgtk2)
.  include "../../x11/gtk2/buildlink3.mk"
CONFIGURE_ARGS+=	-gtkstyle
.else
CONFIGURE_ARGS+=	-no-gtkstyle
.endif

.if !empty(PKG_OPTIONS:Mdebug)
# this does not work - builds libQtBoostracp_debug
CC+=			-ggdb
CXX+=			-ggdb
CONFIGURE_ARGS+=	-debug
INSTALL_UNSTRIPPED=	yes
.else
CONFIGURE_ARGS+=	-release
CONFIGURE_ARGS+=	-no-debug
.endif

# $NetBSD: Makefile,v 1.1 2020/08/30 23:53:23 wiz Exp $

PKGNAME=		${DISTNAME:S/pinentry-/pinentry-gnome3-/}
COMMENT=		Applications for entering PINs or Passphrases, GNOME 3 enabled

.include		"../../security/pinentry/Makefile.common"

USE_TOOLS+=		pkg-config
CONFIGURE_ARGS+=	--disable-pinentry-gtk2
CONFIGURE_ARGS+=	--disable-pinentry-qt
CONFIGURE_ARGS+=	--disable-pinentry-curses
CONFIGURE_ARGS+=	--disable-pinentry-emacs
#CONFIGURE_ARGS+=	--disable-fallback-curses
CONFIGURE_ARGS+=	--enable-pinentry-gnome3
CONFIGURE_ARGS+=	--disable-pinentry-fltk
CONFIGURE_ARGS+=	--disable-libsecret

INSTALL_DIRS=		gnome3

.include "../../security/gcr/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

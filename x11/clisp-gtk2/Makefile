# $NetBSD: Makefile,v 1.34 2020/08/17 20:20:24 leot Exp $
#

CLISP_MODULE=	gtk2

PKGNAME=	clisp-${CLISP_MODULE}-${CLISP_VERSION}
PKGREVISION=	32
CATEGORIES=	x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=clisp/}

MAINTAINER=	asau@inbox.ru
HOMEPAGE=	http://clisp.cons.org/
COMMENT=	CLISP GIMP Toolkit v2 (GTK2) module

MAKE_JOBS_SAFE=	no

.include "../../lang/clisp/module.mk"

USE_TOOLS+=	pkg-config

.include "../../devel/libglade/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

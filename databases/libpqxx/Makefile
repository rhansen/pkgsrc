# $NetBSD: Makefile,v 1.36 2020/09/15 09:48:26 prlw1 Exp $

DISTNAME=		libpqxx-7.1.2
CATEGORIES=		databases
MASTER_SITES=		${MASTER_SITE_GITHUB:=jtv/}
GITHUB_PROJECT=		libpqxx

MAINTAINER=		is@NetBSD.org
HOMEPAGE=		http://pqxx.org/development/libpqxx/
COMMENT=		C++ interface to postgresql-lib
LICENSE=		modified-bsd

USE_LANGUAGES=		c++17
USE_LIBTOOL=		yes
PKGCONFIG_OVERRIDE+=	libpqxx.pc.in
GNU_CONFIGURE=		yes
USE_TOOLS+=		gmake pkg-config

PYTHON_FOR_BUILD_ONLY=	yes
REPLACE_PYTHON+=	tools/m4esc.py
REPLACE_PYTHON+=	tools/splitconfig

.include "options.mk"

.include "../../lang/python/application.mk"
.include "../../mk/pgsql.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

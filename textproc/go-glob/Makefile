# $NetBSD: Makefile,v 1.22 2020/09/03 07:29:51 bsiegert Exp $

DISTNAME=	glob-0.2.3
PKGNAME=	go-${DISTNAME}
PKGREVISION=	19
MASTER_SITES=	${MASTER_SITE_GITHUB:=gobwas/}
CATEGORIES=	textproc
GITHUB_PROJECT=	${PKGBASE:S/^go-//}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	minskim@NetBSD.org
HOMEPAGE=	https://github.com/gobwas/glob
COMMENT=	Go glob
LICENSE=	mit

GO_DIST_BASE=	${DISTNAME}
GO_SRCPATH=	${HOMEPAGE:S,https://,,}

REPLACE_SH+=	bench.sh

.include "../../lang/go/go-package.mk"
.include "../../mk/bsd.pkg.mk"

# $NetBSD: Makefile,v 1.30 2020/08/31 18:06:30 wiz Exp $

DISTNAME=		superlu-5.2.1
PKGREVISION=		1
CATEGORIES=		math
MASTER_SITES=		${MASTER_SITE_GITHUB:=xiaoyeli/}
GITHUB_TAG=		v${PKGVERSION_NOREV}

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://portal.nersc.gov/project/sparse/superlu/
COMMENT=		Library for solving large, sparse, nonsymmetric systems of linear equations

DEPENDS+=		blas-[0-9]*:../../math/blas

USE_CMAKE=		yes
USE_LANGUAGES=		c fortran
TEST_TARGET=		test

.include "../../mk/bsd.pkg.mk"

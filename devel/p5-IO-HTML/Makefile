# $NetBSD: Makefile,v 1.15 2020/08/31 18:08:10 wiz Exp $

DISTNAME=	IO-HTML-1.001
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	6
CATEGORIES=	devel perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=IO/}

MAINTAINER=	wen@NetBSD.org
HOMEPAGE=	https://metacpan.org/release/IO-HTML
COMMENT=	Open an HTML file with automatic charset detection
LICENSE=	${PERL5_LICENSE}

PERL5_PACKLIST=		auto/IO/HTML/.packlist

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"

# $NetBSD: dist.mk,v 1.9 2012/11/15 09:48:30 is Exp $
#
# used by devel/xulrunner10/Makefile
# used by www/firefox10/Makefile

DISTNAME=	firefox-${FIREFOX_VER}esr.source
FIREFOX_VER=	${MOZ_BRANCH}${MOZ_BRANCH_MINOR}
MOZ_BRANCH=	10.0
MOZ_BRANCH_MINOR=	.10
MASTER_SITES=	${MASTER_SITE_MOZILLA_ESR:=firefox/releases/${FIREFOX_VER}esr/source/}
EXTRACT_SUFX=	.tar.bz2

DISTINFO_FILE=	${.CURDIR}/../../devel/xulrunner10/distinfo
PATCHDIR=	${.CURDIR}/../../devel/xulrunner10/patches

WRKSRC=		${WRKDIR}/mozilla-esr10

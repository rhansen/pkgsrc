# $NetBSD: options.mk,v 1.5 2008/10/12 13:05:01 taca Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.drupal-translations

# Select official release or beta versions which contains correct
# directory structure.
#
# Broken directory structure: eo vi
# Development version only: ar fr nn pt th tr
# Empty, LICENSE.it.txt only: it
DL_SUPPORTED_LANGUAGES=	cs da de el es fi gu he hu ja lt nb nl pl pt-br ro \
			sk sv uk-ua zh-cn zh-tw

DL_TRANSLATIONS.cs=	cs-6.x-1.9.tar.gz
DL_TRANSLATIONS.da=	da-6.x-1.0.tar.gz
DL_TRANSLATIONS.de=	de-6.x-1.0-rc1.tar.gz
DL_TRANSLATIONS.el=	el-6.x-1.0-beta1.tar.gz
DL_TRANSLATIONS.es=	es-6.x-1.0.tar.gz
DL_TRANSLATIONS.fi=	fi-6.x-1.0.tar.gz
DL_TRANSLATIONS.gu=	gu-6.x-1.0.tar.gz
DL_TRANSLATIONS.he=	he-6.x-1.0.tar.gz
DL_TRANSLATIONS.hu=	hu-6.x-1.0.tar.gz
DL_TRANSLATIONS.ja=	ja-6.x-1.2.tar.gz
DL_TRANSLATIONS.lt=	lt-6.x-1.2.tar.gz
DL_TRANSLATIONS.nb=	nb-6.x-1.0.tar.gz
DL_TRANSLATIONS.nl=	nl-6.x-1.1.tar.gz
DL_TRANSLATIONS.pl=	pl-6.x-0.3.tar.gz
DL_TRANSLATIONS.pt-br=	pt-br-6.x-1.0-rc5.tar.gz
DL_TRANSLATIONS.ro=	ro-6.x-1.1.tar.gz
DL_TRANSLATIONS.sk=	sk-6.x-1.0.tar.gz
DL_TRANSLATIONS.sv=	sv-6.x-1.1.tar.gz
DL_TRANSLATIONS.uk-ua=	uk-ua-6.x-1.2-beta3.tar.gz
DL_TRANSLATIONS.zh-cn=	zh-hans-6.x-1.0.tar.gz
DL_TRANSLATIONS.zh-tw=	zh-hant-6.x-1.1.tar.gz

.for l in ${DL_SUPPORTED_LANGUAGES}
PKG_SUPPORTED_OPTIONS+=	lang-${l}
PKG_SUGGESTED_OPTIONS+=	lang-${l}
.endfor

.include "../../mk/bsd.options.mk"

.for l in ${PKG_OPTIONS:Mlang-*}
DL_LANGUAGES+=	${l:S/^lang-//1}
.endfor

.for l in ${DL_LANGUAGES}
DL_DISTFILES+=	${DL_TRANSLATIONS.${l}}
PLIST_SRC+=	PLIST.${l}
.endfor
PLIST_SRC+=	PLIST.common_end

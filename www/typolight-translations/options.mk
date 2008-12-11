# $NetBSD: options.mk,v 1.9 2008/12/11 02:30:22 taca Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.typolight-translations

TL_SUPPORTED_LANGUAGES=	af bg ca da es fa fr is it ja lt lv nl no \
			pl pt ro ru sk sq sr sv th tr uk zh

TL_TRANSLATIONS.af=	TYPOlight-Afrikaans-v1.zip	# 2008/01/15
TL_TRANSLATIONS.bg=	TYPOlight-Bulgarian-v12.zip	# 2008/12/09
TL_TRANSLATIONS.ca=	TYPOlight-Catalan-v4.zip	# 2008/09/24
TL_TRANSLATIONS.da=	TYPOlight-Danish-v5.zip		# 2008/04/28
TL_TRANSLATIONS.es=	TYPOlight-Spanish-v10.zip	# 2008/07/15
TL_TRANSLATIONS.fa=	TYPOlight-Persian-v2.zip	# 2008/06/05
TL_TRANSLATIONS.fr=	TYPOlight-French-v34.zip	# 2008/12/08
TL_TRANSLATIONS.is=	TYPOlight-Icelandic-v2.zip	# 2008/01/31
TL_TRANSLATIONS.it=	TYPOlight-Italian-v8.zip	# 2008/11/02
TL_TRANSLATIONS.ja=	TYPOlight-Japanese-v10.zip	# 2008/11/06
TL_TRANSLATIONS.lt=	TYPOlight-Lithuanian-v2.zip	# 2008/04/25
TL_TRANSLATIONS.lv=	TYPOlight-Latvian-v16.zip	# 2008/12/09
TL_TRANSLATIONS.nl=	TYPOlight-Dutch-v25.zip		# 2008/11/04
TL_TRANSLATIONS.no=	TYPOlight-Norwegian-v8.zip	# 2008/09/02
TL_TRANSLATIONS.pl=	TYPOlight-Polish-v19.zip	# 2008/09/21
TL_TRANSLATIONS.pt=	TYPOlight-Portuguese-v3.zip	# 2008/10/15
TL_TRANSLATIONS.ro=	TYPOlight-Romanian-v6.zip	# 2008/12/02
TL_TRANSLATIONS.ru=	TYPOlight-Russian-v18.zip	# 2008/11/09
TL_TRANSLATIONS.sk=	TYPOlight-Slovak-v1.zip		# 2008/08/28
TL_TRANSLATIONS.sq=	TYPOlight-Albanian-v3.zip	# 2008/10/28
TL_TRANSLATIONS.sr=	TYPOlight-Serbian-v4.zip	# 2008/11/09
TL_TRANSLATIONS.sv=	TYPOlight-Swedish-v25.zip	# 2008/11/28
TL_TRANSLATIONS.th=	TYPOlight-Thai-v2.zip		# 2008/11/23
TL_TRANSLATIONS.tr=	TYPOlight-Turkish-v1.zip	# 2008/10/14
TL_TRANSLATIONS.uk=	TYPOlight-Ukrainian-v5.zip	# 2008/10/14
TL_TRANSLATIONS.zh=	TYPOlight-Chinese-v19.zip	# 2008/12/02

.for l in ${TL_SUPPORTED_LANGUAGES}
PKG_SUPPORTED_OPTIONS+=	lang-${l}
PKG_SUGGESTED_OPTIONS+=	lang-${l}
.endfor

.include "../../mk/bsd.options.mk"

.for l in ${PKG_OPTIONS:Mlang-*}
TL_LANGUAGES+=	${l:S/^lang-//1}
.endfor

.for l in ${TL_LANGUAGES}
TL_DISTFILES+=	${TL_TRANSLATIONS.${l}}
SITES.${TL_TRANSLATIONS.${l}}= \
	http://www.typolight.org/download-translations.html?iso=${l}&file=tl_files/languages/${l}/
PLIST_SRC+=	PLIST.${l}
.endfor

# $NetBSD: options.mk,v 1.4 2017/04/17 08:41:30 wiz Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.fuppes
PKG_SUPPORTED_OPTIONS=	mp4v2 mysql
PKG_SUGGESTED_OPTIONS=	mp4v2

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		${PKG_SUPPORTED_OPTIONS}

.if !empty(PKG_OPTIONS:Mmp4v2)
.include "../../multimedia/libmp4v2/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mmysql)
PLIST.mysql=		yes
.include "../../mk/mysql.buildlink3.mk"
.else
CONFIGURE_ENV+=		ac_cv_path_MYSQL_CONFIG=no
.endif

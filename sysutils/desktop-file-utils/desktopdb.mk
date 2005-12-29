# $NetBSD: desktopdb.mk,v 1.3 2005/12/29 06:22:17 jlam Exp $
#
# This Makefile fragment is intended to be included by packages that install
# desktop entries.  It takes care of registering them in the global database.
#

.if !defined(DESKTOP_FILE_UTILS_MIMEDB_MK)
DESKTOP_FILE_UTILS_MIMEDB_MK=	# defined

.include "../../mk/bsd.prefs.mk"

INSTALL_EXTRA_TMPL+=	${.CURDIR}/../../sysutils/desktop-file-utils/files/install.tmpl
DEINSTALL_EXTRA_TMPL+=	${.CURDIR}/../../sysutils/desktop-file-utils/files/install.tmpl

FILES_SUBST+=		APPLICATIONS_PATH="${BUILDLINK_PREFIX.desktop-file-utils}/share/applications"
FILES_SUBST+=		UPDATE_DESKTOPDB="${BUILDLINK_PREFIX.desktop-file-utils}/bin/update-desktop-database"

PRINT_PLIST_AWK+=	/^share\/applications\/mimeinfo.cache$$/ { next }

.include "../../sysutils/desktop-file-utils/buildlink3.mk"

.endif	# DESKTOP_FILE_UTILS_MIMEDB_MK

# $NetBSD: buildlink3.mk,v 1.7 2004/01/04 23:34:06 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
FREETYPE2_BUILDLINK3_MK:=	${FREETYPE2_BUILDLINK3_MK}+

.if !empty(FREETYPE2_BUILDLINK3_MK:M+)
.  include "../../mk/bsd.prefs.mk"

BUILDLINK_DEPENDS.freetype2?=	freetype2>=2.0.1
BUILDLINK_PKGSRCDIR.freetype2?=	../../graphics/freetype2
.endif	# FREETYPE2_BUILDLINK3_MK

BUILDLINK_CHECK_BUILTIN.freetype2?=	NO

_FREETYPE2_FREETYPE_H=	${X11BASE}/include/freetype2/freetype/freetype.h
_X11_TMPL=		${X11BASE}/lib/X11/config/X11.tmpl

.if !defined(BUILDLINK_IS_BUILTIN.freetype2)
BUILDLINK_IS_BUILTIN.freetype2=	NO
.  if exists(${_FREETYPE2_FREETYPE_H}) && exists(${_X11_TMPL})
BUILDLINK_IS_BUILTIN.freetype2!=					\
	if ${GREP} -q BuildFreetype2Library ${_X11_TMPL}; then		\
		${ECHO} YES;						\
	else								\
		${ECHO} NO;						\
	fi
.  endif
MAKEFLAGS+=	BUILDLINK_IS_BUILTIN.freetype2=${BUILDLINK_IS_BUILTIN.freetype2}
.endif

.if !empty(BUILDLINK_CHECK_BUILTIN.freetype2:M[yY][eE][sS])
_NEED_FREETYPE2=	NO
.endif

.if !defined(_NEED_FREETYPE2)
.  if !empty(BUILDLINK_IS_BUILTIN.freetype2:M[nN][oO])
_NEED_FREETYPE2=	YES
.  else
#
# Create an appropriate package name for the built-in freetype2 distributed
# with the system.  This package name can be used to check against
# BUILDLINK_DEPENDS.<pkg> to see if we need to install the pkgsrc version
# or if the built-in one is sufficient.
#
_FREETYPE2_MAJOR!=	\
	${AWK} '/\#define[ 	]*FREETYPE_MAJOR/ { print $$3 }' ${_FREETYPE2_FREETYPE_H}
_FREETYPE2_MINOR!=	\
	${AWK} '/\#define[ 	]*FREETYPE_MINOR/ { print "."$$3 }' ${_FREETYPE2_FREETYPE_H}
_FREETYPE2_PATCH!=	\
	${AWK} 'BEGIN { patch=0; } /\#define[ 	]*FREETYPE_PATCH/ { patch=$$3; } END { print "."patch; }' ${_FREETYPE2_FREETYPE_H}
_FREETYPE2_VERSION=	${_FREETYPE2_MAJOR}${_FREETYPE2_MINOR}${_FREETYPE2_PATCH}
_FREETYPE2_PKG=		freetype2-${_FREETYPE2_VERSION}
_FREETYPE2_DEPENDS=	${BUILDLINK_DEPENDS.freetype2}
_NEED_FREETYPE2!=	\
	if ${PKG_ADMIN} pmatch '${_FREETYPE2_DEPENDS}' ${_FREETYPE2_PKG}; then \
		${ECHO} "NO";						\
	else								\
		${ECHO} "YES";						\
	fi
.  endif
MAKEFLAGS+=	_NEED_FREETYPE2="${_NEED_FREETYPE2}"
.endif

.if ${_NEED_FREETYPE2} == "YES"
#
# If we depend on the package, depend on the latest version with a library
# major number bump.
#
BUILDLINK_DEPENDS.freetype2=	freetype2>=2.1.3
.  if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=		freetype2
.  endif
.endif

.if !empty(FREETYPE2_BUILDLINK3_MK:M+)
.  if ${_NEED_FREETYPE2} == "YES"
BUILDLINK_PACKAGES+=		freetype2
.  else
BUILDLINK_PREFIX.freetype2=	${X11BASE}
.  endif

FREETYPE_CONFIG?=	${BUILDLINK_PREFIX.freetype2}/bin/freetype-config
CONFIGURE_ENV+=		FREETYPE_CONFIG="${FREETYPE_CONFIG}"
.endif	# FREETYPE2_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:C/\+$//}

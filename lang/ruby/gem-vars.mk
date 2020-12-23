# $NetBSD: gem-vars.mk,v 1.10 2020/12/19 14:41:16 taca Exp $
#
# This Makefile fragment defines various make(1) variables for Ruby gems
# support.
#
.if !defined(_RUBYGEM_VARS_MK)
_RUBYGEM_VARS_MK=	# defined

# Specify GEM_PATH
GEM_PATH?=	${PREFIX}/${GEM_HOME}

# Base directory for Gems
MAKE_ENV+=	GEM_PATH=${GEM_PATH}

RUBYGEM_LANG?=	en_US.UTF-8
RUBYGEM_ENV?=	LANG=${RUBYGEM_LANG} LC_CTYPE=${RUBYGEM_LANG}

RUBYGEM=	${LOCALBASE}/bin/${RUBYGEM_NAME}

GEM_EXTSDIR_NEEDS_SUBDIR?=	yes

.if exists(${RUBYGEM})
RUBY_GEM_ARCH!=	${RUBYGEM} environment platform | ${SED} -e 's|.*:||'

GEM_EXTSBASE=	${GEM_HOME}/extensions

.  if !empty(GEM_EXTSDIR_NEEDS_SUBDIR:M[nN][oO])
GEM_EXTSDIR=	${GEM_EXTSBASE}/${RUBY_GEM_ARCH}/${RUBY_VER_DIR}
.  else
GEM_EXTSDIR=	${GEM_EXTSBASE}/${RUBY_GEM_ARCH}/${RUBY_VER_DIR}/${GEM_NAME}
.  endif

.  if !empty(GEM_EXTSDIR)
PLIST_SUBST+=		GEM_EXTSDIR=${GEM_EXTSDIR}
.  else
PLIST_SUBST+=		GEM_EXTSDIR="@comment "
.  endif
.endif

.endif

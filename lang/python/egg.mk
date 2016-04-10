# $NetBSD: egg.mk,v 1.21 2016/04/10 16:39:28 joerg Exp $
#
# Common logic to handle Python Eggs
#
.include "../../mk/bsd.fast.prefs.mk"
.include "../../lang/python/pyversion.mk"

# This file should be included to package python "distributions" which
# use setuptools to create an egg.  Some distributions use distutils,
# which creates an egg-info file; those should use distutils.mk

EGG_NAME?=	${DISTNAME:C/-([^0-9])/_\1/g}
EGG_INFODIR?=	${EGG_NAME}-py${PYVERSSUFFIX}.egg-info

PYDISTUTILSPKG=	yes
PY_PATCHPLIST=	yes

# True eggs always have an egg-info directory, and thus there is no
# PLIST conditional (as in distutils.mk for old versions of python).
# Note that we substitute EGG_INFODIR rather than EGG_FILE, because
# the egg information in an egg comprises multiple files in an
# egg-info directory.

# The PLIST substitution of EGG_NAME is not necessary. However, it
# is convenient. See lang/ruby/gem.mk and PLIST files for ruby gem
# packages to understand other examples of this feature in non-python
# packages.

PLIST_SUBST+=	EGG_NAME=${EGG_NAME}-py${PYVERSSUFFIX}
PLIST_SUBST+=	EGG_INFODIR=${EGG_INFODIR}
PRINT_PLIST_AWK+=	{ gsub(/${EGG_NAME}-py${PYVERSSUFFIX}.egg-info/, \
			       "$${EGG_INFODIR}") }
PRINT_PLIST_AWK+=	{ gsub(/${EGG_NAME}-py${PYVERSSUFFIX}-nspkg.pth/, \
			       "$${EGG_NAME}-nspkg.pth") }

_PYSETUPTOOLSINSTALLARGS=	--single-version-externally-managed

DEPENDS+=	${PYPKGPREFIX}-setuptools>=0.8:../../devel/py-setuptools

INSTALLATION_DIRS+=	${PYSITELIB}

.include "../../lang/python/extension.mk"

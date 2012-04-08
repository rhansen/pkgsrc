# $NetBSD: distutils.mk,v 1.3 2012/04/08 20:17:10 wiz Exp $
#
# Common logic for python distributions that use distutils.
#
.include "../../mk/bsd.fast.prefs.mk"

.include "../../lang/python/pyversion.mk"

# This file should be included to package python "distributions" which
# use distutils.  See egg.mk for distributions that use setuptools and
# extensions.mk for ad hoc cases.

# Some day, hoist the PYDISTUTILSPKG code in extension.mk to here,
# after all distutils-using packages use this.
PYDISTUTILSPKG=	yes

# We expect distutils to create an egg-info file if Python distutils
# can do so, and provide support for a PLIST entry that represents
# this norm and will work with all python versions.  (If the package
# set PY_NO_EGG, respect that choice, but PLIST.eggfile is still set.)

# Set the egg file basename.
EGG_NAME?=	${DISTNAME}

PLIST_VARS+=	eggfile
# Python distutils will create an eggfile.
PLIST.eggfile=	yes
PY_NO_EGG?=	no

# Egg files have the version encoded, so generalize in PLIST, and provide
# our conditional.
PLIST_SUBST+=	EGG_FILE=${EGG_NAME}-py${PYVERSSUFFIX}.egg-info
# PYSITELIB is already de-expanded
PRINT_PLIST_AWK+=	{ gsub("[$$]{PYSITELIB}/${EGG_NAME}-py${PYVERSSUFFIX}.egg-info", \
				"$${PLIST.eggfile}$${PYSITELIB}/$${EGG_FILE}") }

.include "../../lang/python/extension.mk"

# $NetBSD: hacks.mk,v 1.2 2016/04/12 13:25:21 ryoon Exp $

.if !defined(EMACS_HACKS_MK)
EMACS_HACKS_MK=	defined

.include "../../mk/compiler.mk"

### On NetBSD/amd64 7.99.26, gcc optimisation, at least for version 5.3,
### produces, a "temacs" binary which segfaults.
###
.  if !empty(MACHINE_PLATFORM:MNetBSD-*-x86_64)
.    if !empty(CC_VERSION:Mgcc-5.3.*)
PKG_HACKS+=		optimisation
BUILDLINK_TRANSFORM+=	opt:-O2:-O0
.    endif
.  endif

### PaX is enabled, bootstrap-emacs command dumps core with segfault.
### emacs-24.5/src/Makefile.in does not support NetBSD paxctl(8) syntax.
###
.  if !empty(MACHINE_PLATFORM:MNetBSD-*-x86_64)
.    if exists(/usr/sbin/paxctl)
SUBST_CLASSES+=			paxctl
SUBST_STAGE.paxctl=		pre-configure
SUBST_MESSAGE.paxctl=		Setting paxctl command
SUBST_FILES.paxctl+=		src/Makefile.in
SUBST_SED.paxctl+=		-e 's,test "X$$(PAXCTL)" = X || $$(PAXCTL) -zex,/usr/sbin/paxctl +a,g'
SUBST_SED.paxctl+=		-e 's,test "X$$(PAXCTL)" = X || $$(PAXCTL) -r,/usr/sbin/paxctl +a,g'
.    endif
.  endif

.endif  # EMACS_HACKS_MK

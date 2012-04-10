# $NetBSD: hacks.mk,v 1.2 2012/04/10 14:12:50 tsutsui Exp $

.if !defined(RUBY19_BASE_HACKS_MK)
RUBY19_BASE_HACKS_MK=	defined

.include "../../mk/compiler.mk"

### [ Sun Jun  5 10:05:39 CEST 2005 : seb ]
### On NetBSD/sparc64, gcc optimisation, at least for version 3.3.3,
### produces segmentation faulting miniruby binary.
### Also note that `-O' level optimisation produces a miniruby
### binary that loops while running the installation scripts.
###
.if !empty(MACHINE_PLATFORM:MNetBSD-*-sparc64)
.  if !empty(CC_VERSION:Mgcc-3.3.*)
PKG_HACKS+=		optimisation
BUILDLINK_TRANSFORM+=	rm:-O[0-9]*
.  endif
.endif

# On NetBSD/sh3el 6.0, the default -Os causes an error on compiling node.c:
#  {standard input}: Assembler messages: {standard input}:1458: \
#  Error: pcrel too far
# and -O1 works around.
.if !empty(MACHINE_PLATFORM:MNetBSD-*-sh3*) && !empty(CC_VERSION:Mgcc-4.5.*)
PKG_HACKS+=		optimisation
BUILDLINK_TRANSFORM+=	rename:-Os:-O1 rm:-freorder-blocks
.endif

.endif	# RUBY19_BASE_HACKS_MK

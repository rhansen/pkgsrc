# $NetBSD: buildlink3.mk,v 1.35 2009/03/20 19:24:04 joerg Exp $

BUILDLINK_TREE+=	db4

.if !defined(DB4_BUILDLINK3_MK)
DB4_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.db4+=	db4>=4.7.25.1
BUILDLINK_ABI_DEPENDS.db4?=	db4>=4.7.25.1
BUILDLINK_PKGSRCDIR.db4?=	../../databases/db4
BUILDLINK_INCDIRS.db4?=		include/db4
BUILDLINK_LDADD.db4=		-ldb4
BUILDLINK_TRANSFORM+=		l:db-4:db4

.  include "../../mk/bsd.fast.prefs.mk"
.  if defined(USE_DB185) && !empty(USE_DB185:M[yY][eE][sS])
BUILDLINK_LIBS.db4=		${BUILDLINK_LDADD.db4}
BUILDLINK_TRANSFORM+=		l:db:db4
.  endif

.  include "../../mk/compiler.mk"
.  if empty(PKGSRC_COMPILER:Mgcc)
PTHREAD_OPTS+=	native
.    include "../../mk/pthread.buildlink3.mk"
.  endif
.endif # DB4_BUILDLINK3_MK

BUILDLINK_TREE+=	-db4

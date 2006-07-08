# $NetBSD: buildlink3.mk,v 1.11 2006/07/08 23:10:42 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
BUILDTOOL_BUILDLINK3_MK:=	${BUILDTOOL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	buildtool
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nbuildtool}
BUILDLINK_PACKAGES+=	buildtool
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}buildtool

.if !empty(BUILDTOOL_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.buildtool+=	buildtool>=0.16
BUILDLINK_PKGSRCDIR.buildtool?=	../../devel/buildtool
BUILDLINK_DEPMETHOD.buildtool?=	build

BUILDTOOL=		${BUILDLINK_PREFIX.buildtool}/bin/buildtool
USE_TOOLS+=		m4

HAS_CONFIGURE=		yes
CONFIGURE_SCRIPT=	${BUILDTOOL} config
CONFIGURE_ENV+=		BT_FLAGS_CC=${CFLAGS:M*:Q}
CONFIGURE_ENV+=		BT_FLAGS_CPP=${CPPFLAGS:M*:Q}
CONFIGURE_ENV+=		BT_FLAGS_CXX=${CXXFLAGS:M*:Q}
CONFIGURE_ENV+=		BT_FLAGS_LD=${LDFLAGS:M*:Q}
CONFIGURE_ENV+=		BT_PROG_AWK=${TOOLS_AWK:Q}
CONFIGURE_ENV+=		BT_PROG_CC=${CC:Q}
CONFIGURE_ENV+=		BT_PROG_CXX=${CXX:Q}
CONFIGURE_ENV+=		BT_PROG_LD=${LD:Q}
CONFIGURE_ENV+=		BT_PROG_M4=${TOOLS_M4:Q}
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q}

.if !target(do-build)
do-build:
	${_PKG_SILENT}${_PKG_DEBUG}${_ULIMIT_CMD}cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} ${BUILDTOOL} build
.endif

.if !target(do-install)
do-install:
	${_PKG_SILENT}${_PKG_DEBUG}${_ULIMIT_CMD}cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} ${BUILDTOOL} install
.endif

.endif	# BUILDTOOL_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

# $NetBSD: buildlink3.mk,v 1.13 2011/11/08 15:30:44 taca Exp $

BUILDLINK_TREE+=	${RUBY_PKGPREFIX}-rdtool

.if !defined(RUBY_RDTOOL_BUILDLINK3_MK)
RUBY_RDTOOL_BUILDLINK3_MK:=

RUBY_RD=		rd2
RUBY_RD_VERSION =	0.6.18
RUBY_RD_REQD=		0.6.14

BUILDLINK_FILES.${RUBY_PKGPREFIX}-rdtool+=	bin/rd2
BUILDLINK_DEPMETHOD.${RUBY_PKGPREFIX}-rdtool?=	build
BUILDLINK_API_DEPENDS.${RUBY_PKGPREFIX}-rdtool+=${RUBY_PKGPREFIX}-rdtool>=0.6.14
BUILDLINK_PKGSRCDIR.${RUBY_PKGPREFIX}-rdtool?=	../../textproc/ruby-rdtool

.endif # RUBY_RDTOOL_BUILDLINK3_MK

BUILDLINK_TREE+=	-${RUBY_PKGPREFIX}-rdtool

# $NetBSD: buildlink3.mk,v 1.4 2006/02/05 23:08:53 joerg Exp $

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH}+
RUBY_GNOME2_PANGO_BUILDLINK3_MK:=	${RUBY_GNOME2_PANGO_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	ruby-gnome2-pango
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nruby-gnome2-pango}
BUILDLINK_PACKAGES+=	ruby-gnome2-pango

.if !empty(RUBY_GNOME2_PANGO_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.ruby-gnome2-pango+=	ruby-gnome2-pango>=0.14.1
BUILDLINK_RECOMMENDED.ruby-gnome2-pango?=	ruby-gnome2-pango>=0.14.1nb2
BUILDLINK_PKGSRCDIR.ruby-gnome2-pango?=	../../devel/ruby-gnome2-pango
.endif	# RUBY_GNOME2_PANGO_BUILDLINK3_MK


BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

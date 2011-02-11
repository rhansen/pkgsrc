# $NetBSD: buildlink3.mk,v 1.22 2011/02/11 12:11:26 adam Exp $

.include "../../mk/bsd.fast.prefs.mk"

BUILDLINK_TREE+=	libpcap

.if !defined(LIBPCAP_BUILDLINK3_MK)
LIBPCAP_BUILDLINK3_MK:=

# XXX?
BUILDLINK_API_DEPENDS.libpcap+=	libpcap>=0.5.0
BUILDLINK_PKGSRCDIR.libpcap?=	../../net/libpcap

# on Solaris, we always need libnsl and libsocket because libpcap.a
# references symbols in them.
.if ${OPSYS} == "SunOS"
BUILDLINK_LDADD.libpcap+=	-lnsl -lsocket
BUILDLINK_LDFLAGS.libpcap?=	${BUILDLINK_LDADD.libpcap}
.endif
.endif # LIBPCAP_BUILDLINK3_MK

BUILDLINK_TREE+=	-libpcap

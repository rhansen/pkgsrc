# $NetBSD: buildlink3.mk,v 1.2 2004/06/05 16:35:51 xtraeme Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
WONKA_BUILDLINK3_MK:=	${WONKA_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	wonka
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nwonka}
BUILDLINK_PACKAGES+=	wonka

.if !empty(WONKA_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.wonka+=	wonka-[0-9]*
BUILDLINK_PKGSRCDIR.wonka?=	../../lang/wonka
BUILDLINK_JAVA_PREFIX.wonka=	${PREFIX}/java/wonka
BUILDLINK_CPPFLAGS.wonka=						\
	-I${BUILDLINK_JAVA_PREFIX.wonka}/include			\
	-I${BUILDLINK_JAVA_PREFIX.wonka}/include/wonka
.endif	# WONKA_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}

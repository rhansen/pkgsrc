# $NetBSD: buildlink3.mk,v 1.3 2006/04/12 10:27:20 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
BLACKDOWN_JRE13_BUILDLINK3_MK:=	${BLACKDOWN_JRE13_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	blackdown-jre13
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nblackdown-jre13}
BUILDLINK_PACKAGES+=	blackdown-jre13

.if !empty(BLACKDOWN_JRE13_BUILDLINK3_MK:M+)

BUILDLINK_API_DEPENDS.blackdown-jre13+=	blackdown-jre13-[0-9]*
BUILDLINK_PKGSRCDIR.blackdown-jre13?=	../../lang/blackdown-jre13
EVAL_PREFIX+=   BUILDLINK_JAVA_PREFIX.blackdown-jre13=blackdown-jre13
BUILDLINK_JAVA_PREFIX.blackdown-jre13=	\
	${BUILDLINK_PREFIX.blackdown-jre13}/java/sun-1.3.1

.endif	# BLACKDOWN_JRE13_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}

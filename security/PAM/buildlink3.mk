# $NetBSD: buildlink3.mk,v 1.15 2004/11/16 07:46:57 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PAM_BUILDLINK3_MK:=	${PAM_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pam
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npam}
BUILDLINK_PACKAGES+=	pam

.if !empty(PAM_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.pam+=		PAM>=0.75
BUILDLINK_RECOMMENDED.pam+=	PAM>=0.77nb3
BUILDLINK_PKGSRCDIR.pam?=	../../security/PAM
.endif	# PAM_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}

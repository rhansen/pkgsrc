#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: unrealircd.sh,v 1.3 2019/02/09 15:23:15 nia Exp $
#
# PROVIDE: unrealircd
# REQUIRE: DAEMON
# KEYWORD: shutdown
#

if [ -f /etc/rc.subr ]
then
	. /etc/rc.subr
fi

name="unrealircd"
rcvar=${name}
command="@PREFIX@/bin/unrealircd"
required_files="@PKG_SYSCONFDIR@/unrealircd/unrealircd.conf"
pidfile="@PREFIX@/unrealircd/ircd.pid"
unrealircd_user="@UIRCD_USER@"
unrealircd_group="@UIRCD_GROUP@"
extra_commands="rehash"
rehash_cmd="unrealircd_rehash"

unrealircd_rehash()
{
	kill -1 `@CAT@ $pidfile`
}

load_rc_config $name
run_rc_command "$1"

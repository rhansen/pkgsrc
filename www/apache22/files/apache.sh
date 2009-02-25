#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: apache.sh,v 1.3 2009/02/25 15:39:38 tron Exp $
#
# PROVIDE: apache
# REQUIRE: DAEMON
# KEYWORD: shutdown
#
# You will need to set some variables in /etc/rc.conf to start Apache:
#
# apache=YES
# apache_start="start"	# set to "startssl" to allow HTTPS connections;
#			# this variable is optional

name="apache"

if [ -f /etc/rc.subr ]
then
	. /etc/rc.subr

	rcvar=$name
	command="@PREFIX@/sbin/httpd"
	command_args="-k start"
	pidfile="@VARBASE@/run/httpd.pid"
	required_files="@PKG_SYSCONFDIR@/httpd.conf"
	extra_commands="reload"
	reload_cmd="$command -k graceful"

	load_rc_config $name
	run_rc_command "$1"
else
	ctl_command="@PREFIX@/sbin/apachectl"

	if [ ! -x ${ctl_command} ]; then
		return
	fi

	case "$1" in
	start)
		@ECHO@ "Starting ${name}."
		${ctl_command} start
		;;
	stop)
		@ECHO@ "Stopping ${name}."
		${ctl_command} stop
		;;
	reload)
		${ctl_command} graceful
		;;
	restart)
		"$0" stop
		sleep 10
		"$0" start
		;;
	*)
		${ctl_command} "$1"
		;;
	esac
fi

#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: dspam.sh,v 1.3 2005/10/12 20:22:55 xtraeme Exp $
#

# PROVIDE: dspam
# REQUIRE: SERVERS
# BEFORE:  DAEMON

if [ -f /etc/rc.subr ]; then
	. /etc/rc.subr
fi

name="dspam"
rcvar="${name}"
command="@PREFIX@/bin/${name}"
pidfile="@DSPAM_PIDDIR@/${name}.pid"
command_args="--daemon > /dev/null 2>&1 &"
dspam_user="@DSPAM_USER@"
dspam_group="@DSPAM_GROUP@"
start_precmd="dspam_precmd"

dspam_precmd()
{
    if [ ! -d @DSPAM_PIDDIR@ ]; then
	@MKDIR@ @DSPAM_PIDDIR@
	@CHMOD@ 0700 @DSPAM_PIDDIR@
	@CHOWN@ @DSPAM_USER@ @DSPAM_PIDDIR@
    fi
}

if [ -f /etc/rc.subr -a -f /etc/rc.conf -a -f /etc/rc.d/DAEMON ]; then
	load_rc_config $name
	run_rc_command "$1"
else
	case ${1:-start} in
	start)
		dspam_precmd
		if [ -x ${command} ]; then
			echo "Starting ${name}."
			eval ${command} ${dspam_flags} ${command_args}
		fi
		;;
	stop)
		if [ -f ${pidfile} ]; then
			pid=`/bin/head -1 ${pidfile}`
			echo "Stopping ${name}."
			kill -TERM ${pid}
		else
			echo "${name} not running?"
		fi
		;;
	restart)
		( $0 stop )
		sleep 1
		$0 start
		;;
	status)
		if [ -f ${pidfile} ]; then
			pid=`/bin/head -1 ${pidfile}`
			echo "${name} is running as pid ${pid}."
		else
			echo "${name} is not running."
		fi
		;;
		esac
fi

if checkyesno "${rcvar}" && [ "$1" != "stop" -o "$1" != "status" ]; then
	echo $(check_process $command) > $pidfile
fi

#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: pubhttpd.sh,v 1.1 2015/01/27 23:01:31 schmonz Exp $
#
# @PKGNAME@ script to control publicfile httpd (HTTP server)
#

# PROVIDE: pubhttpd
# REQUIRE: NETWORKING mountcritremote syslogd
# BEFORE:  DAEMON

name="pubhttpd"

# User-settable rc.conf variables and their default values:
: ${pubhttpd_root:="@VARBASE@/public"}
: ${pubhttpd_postenv:=""}
: ${pubhttpd_datalimit:="50000"}
: ${pubhttpd_localname:="0"}
: ${pubhttpd_backlog:="50"}
: ${pubhttpd_conlimit:="100"}
: ${pubhttpd_host:="0"}
: ${pubhttpd_port:="80"}
: ${pubhttpd_log:="YES"}
: ${pubhttpd_logcmd:="logger -t nb${name} -p ftp.info"}
: ${pubhttpd_nologcmd:="@DAEMONTOOLS_PREFIX@/bin/multilog -*"}

if [ -f /etc/rc.subr ]; then
	. /etc/rc.subr
fi

rcvar=${name}
required_dirs="${pubhttpd_root}"
command="@UCSPI_TCP_PREFIX@/bin/tcpserver"
procname=${name}
start_precmd="pubhttpd_precmd"

pubhttpd_precmd()
{
	# tcpserver(1) is akin to inetd(8), but runs one service per process.
	# We want to signal only the tcpserver process responsible for the HTTP
	# service.  Use argv0(1) to set the process name to "pubhttpd".
	if [ -f /etc/rc.subr ]; then
		checkyesno pubhttpd_log || pubhttpd_logcmd=${pubhttpd_nologcmd}
	fi
 	command="@SETENV@ - ${pubhttpd_postenv} @DAEMONTOOLS_PREFIX@/bin/envuidgid pubhttp @DAEMONTOOLS_PREFIX@/bin/softlimit -o20 -d${pubhttpd_datalimit} @UCSPI_TCP_PREFIX@/bin/argv0 @UCSPI_TCP_PREFIX@/bin/tcpserver ${name} -vDRH -l${pubhttpd_localname} -b${pubhttpd_backlog} -c${pubhttpd_conlimit} ${pubhttpd_host} ${pubhttpd_port} @PUBLICFILE_PREFIX@/publicfile/bin/httpd ${pubhttpd_root} 2>&1 | @DAEMONTOOLS_PREFIX@/bin/setuidgid publog ${pubhttpd_logcmd}"
	command_args="&"
	rc_flags=""
}

if [ -f /etc/rc.subr ]; then
	load_rc_config $name
	run_rc_command "$1"
else
	@ECHO_N@ " ${name}"
	pubhttpd_precmd
	eval ${command} ${pubhttpd_flags} ${command_args}
fi

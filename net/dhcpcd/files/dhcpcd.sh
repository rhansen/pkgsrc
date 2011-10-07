#!@RCD_SCRIPTS_SHELL@

# PROVIDE: dhcpcd
# REQUIRE: network mountcritlocal
# BEFORE:  NETWORKING

$_rc_subr_loaded . /etc/rc.subr

name="dhcpcd"
rcvar=$name
command="@PREFIX@/sbin/${name}"
pidfile="@VARBASE@/run/${name}.pid"

load_rc_config $name
run_rc_command "$1"

#!/bin/sh

### BEGIN INIT INFO
# Provides:        pixelboard-server
# Required-Start:  $network $syslog
# Required-Stop:   $network $syslog
# Default-Start:   2 3 4 5
# Default-Stop: 
# Short-Description: Start pixelboard-server daemon
### END INIT INFO

PATH=/sbin:/bin:/usr/sbin:/usr/bin

DAEMON=/usr/local/bin/pixelboard-server
PIDFILE=/var/run/pixelboard-server.pid
LOGFILE=/var/log/pixelboard-server.log

test -x $DAEMON || exit 5

. /lib/lsb/init-functions

case $1 in
	start)
		log_daemon_msg "Starting pixelboard-server" "pixelboard-server"
    start-stop-daemon --start --background --make-pidfile --pidfile $PIDFILE --startas $DAEMON -C >> $LOGFILE 2>&1
		status=$?
		log_end_msg $status
  		;;
	stop)
		log_daemon_msg "Stopping pixelboard-server" "pixelboard-server"
    pkill -P `cat $PIDFILE 2> /dev/null` > /dev/null 2>&1
		log_end_msg $?
		rm -f $PIDFILE > /dev/null 2>&1
  		;;
	restart|force-reload)
		$0 stop && sleep 2 && $0 start
  		;;
	status)
		status_of_proc $DAEMON "pixelboard-server"
		;;
	*)
		echo "Usage: $0 {start|stop|restart|status}"
		exit 2
		;;
esac

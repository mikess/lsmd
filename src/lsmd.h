/*
 * svdefine.h - header with some static configuration variables
 */

#define PROCDIR		"/proc"

#define SVC_SERVICES	"/etc/svcs"

#define SVC_CONF	"/etc/lsmd/lsmd.conf"


/* Default place for services */
#define SVCROOT	"/run/svc"
#define SVC_STAT "/run/svc/current"

#define SVC_TYPE_SYS    1
#define SVC_SYS         "system"
#define SVC_TYPE_MGMT   2
#define SVC_MGMT        "management"
#define SVC_TYPE_NET    3
#define SVC_NET         "network"
#define SVC_TYPE_APP    4
#define SVC_APP         "applications"
#define SVC_TYPE_USER   5
#define SVC_USER        "user"


/*
 * Define of service status.
 */
#define SVC_STATUS_ONLINE	1	/* Service is started */

#define SVC_STATUS_OFFILNE	0	/* Service not started */

#define SVC_STATUS_FAULT	-1	/* Service not started due to errors */

#define SVC_STATUS_UNCONF	-2	/* Service cannot be started
					   because is unconfigured */




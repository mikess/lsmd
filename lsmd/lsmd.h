/*
 * svdefine.h - header with some static configuration variables
 */

#define PROCDIR		"/proc"

#define SVC_SERVICES	"/run/svc/services/"
#define SVC_CONF	"/etc/lsmd/lsmd.conf"


/* Default place for services */
#define SVCROOT	"/run/svc/"
#define SVC_STAT "/run/svc/current/"
#define SVC_S

/*
 * sinst_s	- service instance structure
 * 
 * @sid		- service parent ID
 * @iname	- instance name
 * @ipath	- path to status
 * @fpid	- path to pidfile
 * @fsock	- path to socket
struct sinst_s {
	int sid;
	char *name;
	char *ipath;
	char *fpid;
	char *fsock;
	char *factivator;
};

 *  svcs_s	- structure for services
 *
 *  @sid	- service ID
 *  @sname	- service name
 *  @instances 	- service instances sinst_s
struct ssvc_s {

};
*/


#define LSM_TRACE_ON	1
#define LSM_TRACE_OFF	0


/*
 * lsmd_process_check() return 1 if process exists,
 * 0 if not running and -1 if PID is smaller then 1
 */

int lsmd_process_check(pid_t pid);


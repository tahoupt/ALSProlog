#define MinorOSStr		"djgpp2"

#undef  STDC_HEADERS
#define STDC_HEADERS		1

#define ISCOFF(x)	((x) == 0x14c)

#define HAVE_BRK		1
#define HAVE_DIRENT_H		1
#define HAVE_FCNTL_H		1
#define HAVE_MEMORY_H		1
#define HAVE_REGEX_H		1
#define HAVE_STDARG_H		1
#define HAVE_STDDEF_H		1
#define HAVE_STDLIB_H		1
#define HAVE_STRING_H		1
#define HAVE_SYS_PARAM_H	1
#define HAVE_SYS_STAT_H		1
#define HAVE_SYS_TIME_H		1
#define HAVE_SYS_TIMES_H	1
#define HAVE_SYS_WAIT_H		1
#define HAVE_UNISTD_H		1
#define RETSIGTYPE		void
#define SIGT			RETSIGTYPE
#define SIGRET			/*do nothing*/
#define MODE_T			INT
#define UID_T			INT
#define GID_T			INT
#define SETVBUF_REVERSED	1
#define ST_BLKSIZE		1
#define ST_RDEV			1
#define TIME_WITH_SYS_TIME	1
#define LIBM			1
#define UNIX			1
#define HAVE_BCOPY		1
#define HAVE_GETCWD		1
#define HAVE_GETPAGESIZE	1
#define HAVE_GETWD		1
#define HAVE_MEMOVE		1
#define HAVE_MKDIR		1
#define HAVE_REGCMP		1
#define HAVE_SIGACTION		1
#define HAVE_SRAND		1
#define HAVE_SRANDOM		1
#define HAVE_STRCSPN		1
#define HAVE_STRDUP		1
#define HAVE_STRSPN		1
#define HAVE_STRTOK		1
#define HAVE_SYSCONF		1
#define HAVE_TEMPNAM		1
#define HAVE_TIME		1
#define HAVE_VFPRINTF		1
#define MISSING_EXTERN_ACCEPT	1
#define MISSING_EXTERN_BIND	1
#define MISSING_EXTERN_CONNECT	1
#define MISSING_EXTERN_GETPGRP	1
#define MISSING_EXTERN_GETSOCKNAME	1
#define MISSING_EXTERN_LDOPEN	1
#define MISSING_EXTERN_MPROTECT	1
#define MISSING_EXTERN_RECVFROM	1
#define MISSING_EXTERN_REGCMP	1
#define MISSING_EXTERN_REGEX	1
#define MISSING_EXTERN_REXEC	1
#define MISSING_EXTERN_SELECT	1
#define MISSING_EXTERN_SENDTO	1
#define MISSING_EXTERN_SETITIMER	1
#define MISSING_EXTERN_SETPGRP	1
#define MISSING_EXTERN_SHUTDOWN	1
#define MISSING_EXTERN_SIGSTACK	1
#define MISSING_EXTERN_TIMES	1

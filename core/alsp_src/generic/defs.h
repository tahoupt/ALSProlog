/*=====================================================================*
 |			defs.h	
 |		Copyright (c) 1990-1995 by Applied Logic Systems, Inc.
 |
 |			-- Common definitions and configuration parameters
 |
 | Creation: 9/27/90 (originally config.h)
 | Authors: K.Hughes, K.Buettner, P.Raman, K.Bowen
 |
 | This file contains common configuration parameters.  Certain assumptions
 | are made in this file about the architecture and machine on which
 | Prolog will be built for.  aconfig.h and mconfig, the architecture and
 | machine dependent configuration files can override these assumptions if
 | they are wrong.  Certain other parameters will simply not be defined here
 | because they will be different for every platform.  In this case, these
 | parameters will be defined in either aconfig.h or mconfig.h.
 | 
 *=====================================================================*/
#ifndef _DEFS_H_INCLUDED_
#define _DEFS_H_INCLUDED_ 1

/*---------------------------------------------------------------------*
 | Environment & Operating System:
 |
 |		THIS IS NO LONGER TRUE:
 | We start from the assumption HERE that some variant of unix is the 
 | operating system.  One modifies or overides this this assumption 
 | or any of its details in an architecture-specific configuration
 | file(s) aconfig.h, or (even more refined control) in a machine-
 | specific configuration file mconfig.h.
 |		NOW: the particular system is configured in a combination
 |	of this file with the files:
 |		aconfig.h - architecture (e.g. in alsp_src/sparc)
 |		mconfig.h - machine (e.g. in alsp_src/sparc)
 |		tconfig.h - os (e.g., in alsp_src/sparc/sunos4, or alsp_src/port/djgpp)
 |			(and dfltsys.h, which is included in tconfig.h by default)
 |		config.h (generated by configure or configur.bat, etc.)
 |
 |	[#define UNIX 1 is now set in the appropriate tconfig.h files]
 |
 | We now longer explicitly distiguish inside the sources between variants 
 | of unix.  Instead, we test for specific features in the configuration 
 | script instead, and configure appropriately inside the sources.
 *---------------------------------------------------------------------*/

	/* #define SysName "ALS Prolog" -- now computed in blt_shl.pro */
#define SysManufacturer "generic"

/* Like UNIX and OSStr above, assume that the OS has a brk() call. */

#ifdef MacOS
#define HAVE_BRK
#else
/*** #define HAVE_BRK  ***/
#endif

/*---------------------------------------------------------------------*
 | SlowCut needs to be defined at the present time in order for our interrupt
 | mechanism to work properly.  It is unfortunate that this is the case.
 | SlowCut indicates that code for performing cut is not expanded inline;
 | that is, it is a goal like any other goal.  There are some ways to
 | properly get cut inlined and also allow interrupts to work which might
 | be explored in the future.
 *---------------------------------------------------------------------*/

#define SlowCut 1

/*---------------------------------------------------------------------*
 | NewMath indicates that goals performing arithmetic are totally expanded.
 | InMath and FMath must also be defined if NewMath is defined.
 | Define NewMath if math code totally expanded; InMath and FMath must also
 | be defined if NewMath is defined.
 *---------------------------------------------------------------------*/

#define NewMath 1
#define InMath 1	/* Inline math */
#define FMath 1		/* Inline floating math */

/*---------------------------------------------------------------------* 
 | It may be useful to turn off the following configuration parameters when
 | porting to a new platform.  Otherwise, they should be left alone.
 |
 | CodeGC	-- code space garbage collection
 | AutoIndexing	-- stable procedures generate indexing for themselves
 | SPY		-- support for spy points
 | OBP		-- support for .obp files
 | Indexing	-- generate first argument indexing
 | BigStruct	-- structures with arities larger than ESCAPE_ARITY are 
 |		   supported.  ESCAPE_ARITY is 255 on most platforms (see
 |		   mtypes.h).  Assembly versions of functor, arg, mangle,
 |		   and the unifier need to be modified in order to support
 |		   big structures.  The garbage collector and other C code
 |		   should use ifdef BigStruct to handle big structures.
 *---------------------------------------------------------------------*/

#define CodeGC		1
#define AutoIndexing	1
#define SPY		1
#define OBP		1
#define Indexing	1
#define BigStruct	1

/*---------------------------------------------------------------------*
 | Other Parameters which are not defined by default; these should be defined
 | in either mconfig.h or aconfig.h if needed.
 |
 | DoubleType	-- floating point types are implemented in a direct fashion
 |		(similar to UIA's).  They are more compact and more easily
 |		decoded.  If DoubleType is not defined, floats and doubles
 |		are represented as '$double'(D1,D2,D3,D4) where D1-D4 are
 |		sixteen bit pieces of the double.
 |
 | MotorolaMath	-- defined if the Motorola math builtins implemented by
 |		Sam Daniel's group are supported.
 |
 | PACKAGE	-- defined if the application packaging system is to be
 |		included
 |
 | CMeta	-- certain meta-builtins are written in C
 |
 | SIO_ASM 	-- certain of the stream I/O primitives are implemented
 |		in assembly language
 |
 *---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*
 | Include the architecture and machine specific configuration files.  The
 | machine specific file is included after the architecture specific file so
 | that it may override certain architecture defined parameters in much the
 | same manner in which both of these files may override the paramters defined
 | in this file before this point.
 *---------------------------------------------------------------------*/

#if   defined(UNIX)
#include "unix_config.h"
#elif defined(MACOS)
#include "macos_config.h"
#elif defined(MSWIN32)
#include "mswin32_config.h"
#elif defined(ALS_ANSI)
#include "ansi_config.h"
#else
#error
#endif

#if   defined(PORT)
#include "port_config.h"
#else
#error
#endif

#if defined(__MWERKS__) && defined(WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
/*---------------------------------------------------------------------*
 | Macros concerned with constraints, intervals, freeze, etc.
 |
 | INTCONSTR -- support interval constraints
 |
 | FREEZE -- suport freeze/delay
 |
 *---------------------------------------------------------------------*/

#if (defined(INTCONSTR) && !defined(FREEZE))
#define FREEZE 1
#endif

#if (defined(INTCONSTR) && !defined(TRAILVALS))
#define TRAILVALS 1
#endif

/*---------------------------------------------------------------------*
 | 
 *---------------------------------------------------------------------*/

#ifdef Bytecode
#undef Threaded
#endif

#if defined(HAVE_VM_ALLOCATE) && defined(HAVE_VM_PROTECT)
#define MACH_SUBSTRATE 1
#undef HAVE_MMAP
#endif /* HAVE_VM_ALLOCATE && HAVE_VM_PROTECT */


#if HAVE_LIBC_H		/* NeXT has this */
#include <libc.h>	/* Get prototypes for C library */
#endif /* HAVE_LIBC_H */

#ifdef PURE_ANSI
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#define HAVE_STRCSPN
#define HAVE_STRTOK
#define HAVE_STRSPN
#else
#include <stdlib.h>


/* Defined EXIT_ERROR for reporting invalid options, etc. */
#define EXIT_ERROR 2

#include <stdio.h>

#include <stdarg.h>

#include <stddef.h>

#include <string.h>
#if HAVE_STRINGS_H
#include <strings.h>
  /* memory.h and strings.h conflict on some systems */
#endif		/* HAVE_STRINGS_H */

#endif /* PURE_ANSI */


#ifdef UNIX
			/* include some standard files */
#include <sys/types.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif		/* HAVE_SYS_TIME_H */
#ifdef HAVE_SYS_TIMES_H
#include <sys/times.h>
#endif		/* HAVE_SYS_TIMES_H */
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif		/* HAVE_SYS_STAT */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif		/* HAVE_UNISTD_H */
#include <signal.h>


/*---------------------------------------------------------------------*
 | Don't use sigaction if implementation of sigaction is immature.
 *---------------------------------------------------------------------*/
#if defined(HAVE_SIGACTION) && !defined(SA_SIGINFO)
#undef HAVE_SIGACTION
#endif	/* HAVE_SIGACTION && !SA_SIGINFO */

#include "missing.h"		/* extern decls missing from header files */

#define BERKELEY_SOCKETS 1

#endif	/* UNIX */

/*---------------------------------------------------------------------*
 *---------------------------------------------------------------------*/

#if (defined(__sgi) && defined(__mips))
#define __BIT_TYPES_DEFINED__ 1
#endif

/*---------------------------------------------------------------------*
 | IEEEP FP Stuff
 *---------------------------------------------------------------------*/

#if (defined(SOLARIS) || (defined(__sgi) && defined(__mips)))
#define HAVE_IEEE_FP 1
#endif

/*---------------------------------------------------------------------*
 | Define the system dependent directory and path separators for parsing path
 | lists
 |
 |			UNIX	VMS	DOS	Atari	Mac
 | Path Separator:	:	,	;	,	,
 | Dir Separator:	/	]	\	\	:
 *---------------------------------------------------------------------*/

#if	defined(UNIX)
#if defined(__GO32__) || defined(OS2)
#define PATH_SEPARATOR	';'
#else
#define PATH_SEPARATOR	':'
#endif	/* __GO32__||OS2 */
#define DIR_SEPARATOR	'/'

#elif	defined(VMS)
#define PATH_SEPERATOR	','
#define DIR_SEPARATOR	']'

#elif	defined(DOS) || defined(MSWin32)
#define	PATH_SEPARATOR	';'
#define DIR_SEPARATOR	'\\'

#elif	defined(AtariOS)
#define PATH_SEPARATOR	','
#define DIR_SEPARATOR	'\\'

#elif	defined(MacOS)
#define PATH_SEPARATOR	','
#define DIR_SEPARATOR	':'

#endif

/*---------------------------------------------------------------------*
 |	System-Level Debugging 
 *---------------------------------------------------------------------*/

#ifdef DEBUGSYS
#include "debugsys.h"
#endif

/*---------------------------------------------------------------------*
 | Stuff from memory.h:
 |
 | Some systems still use bcopy so define memmove in terms of bcopy if
 | we have to.
 *---------------------------------------------------------------------*/

#if !defined(HAVE_MEMMOVE) && defined(HAVE_BCOPY)
#define memmove(s1,s2,n) bcopy(s2,s1,n)
#endif

/*---------------------------------------------------------------------*
 | Include commonly needed Generic include files
 *---------------------------------------------------------------------*/

// THREAD defines

void gensym_init(void);

#ifdef UNIX
#error
#elif WIN32
#define MUTEX CRITICAL_SECTION
#define INIT_MUTEX(m)	InitializeCriticalSection(&m)
#define LOCK_MUTEX(m)	EnterCriticalSection(&m);
#define UNLOCK_MUTEX(m)	LeaveCriticalSection(&m);
#endif

struct prolog_engine_struct;

#define PE struct prolog_engine_struct *hpe

/* #include "wd_size.h"	 */
#include "mtypes.h"	/* not generic, but every platform has one */

#include "alstypes.h"
#include "alloc.h"
#include "fileio.h"	/* candidate for eventual elimination */
#include "parser.h"
#include "newtokens.h"

#include "engine.h"
#include "cexception.h"
#include "cassert.h"


#include "sig.h"
#include "winter.h"
#include "fatal.h"
#include "alspi.h"
#include "chpt.h"
#include "built.h"

#include "security.h"
/*---------------------------------------------------------------------*
 | If string.h doesn't exist or is lacking certain functions, we provide
 | our own replacements for the functions declared therein...
 *---------------------------------------------------------------------*/
#ifndef HAVE_STRTOK
extern char *strtok ( char *s1, const char *s2 );
#endif 		/* HAVE_STRTOK */
#ifndef HAVE_STRDUP
extern char *strdup ( const char *s1 );
#endif 		/* HAVE_STRDUP */
#ifndef HAVE_STRSPN
extern size_t strspn ( const char *s1, const char *s2 );
#endif 		/* HAVE_STRSPN */
#ifndef HAVE_STRCSPN
extern size_t strcspn ( const char *s1, const char *s2 );
#endif 		/* HAVE_STRCSPN */

/*---------------------------------------------------------------------*
 | Declare the als memory allocation function and associated helpers
 *---------------------------------------------------------------------*/
extern	int	als_mem_init	( PE, const char *file, long offset );
extern	long *	ss_pmalloc	( PE, size_t size, int fe_num, long *asizep );
extern	long *	ss_malloc	( PE, size_t size, int fe_num );
extern	void	ss_register_global (PE,  long *addr );
extern	long	ss_image_offset	(const char *);
extern	int	ss_save_image_with_state (PE, const char * );
extern	int	ss_attach_state_to_file (PE, const char *file_name);
extern	int	ss_save_state	(PE, const char *, long );
extern	void	protect_bottom_stack_page ( void );
extern	long *	ss_fmalloc_start ( void );
extern	long *	ss_fmalloc	( size_t );

/*---------------------------------------------------------------------*
 | Declare prototypes of other functions which have no obvious header file.
 *---------------------------------------------------------------------*/

/* ----------   arith.c ----------   */

void make_ieee_nan  (PE, PWord *, int *);
void make_ieee_inf  (PE, PWord *, int *);

/* os routines. */
int os_copy_file(const char *from_file, const char *to_file);
void os_init_time(void);
double os_cputime(void);
double os_realtime(void);

int os_set_timer(double initial, double interval);

/* ----------   main.c ----------   */
#ifdef MSWin32
extern	char	*MinorOSStr;
extern	int	win32s_system;
#endif
#ifdef MacOS
extern	int	MPW_Tool;
#endif

extern	void	als_exit	( int );
extern	void	heap_overflow	( PE );

#define IMAGEDIR_MAX	1024
extern char library_path[IMAGEDIR_MAX];
extern char library_dir[IMAGEDIR_MAX];
extern char executable_path[IMAGEDIR_MAX];

void	locate_library_executable(int argc, char *argv[]);

/* ----------   disassem.c ----------   */
extern	void	list_asm	(PE,  Code *, int );

/* ----------   loadfile.c ----------   */
/* extern	void	fix_MAGIC	( void ); */
extern	void	f_icode		(PE, int, long, long, long, long );
extern	int	obp_open	(PE, char * );
extern	void	obp_close	( PE );
extern	int	f_load		(PE,  const char * );
extern	int	load_file	(PE, char *, int );
#ifdef MacOS
extern	int	obpres_load	(PE, const char *fname);
#endif
extern	void	obp_push	( PE );
extern	void	obp_pop		( PE );

/* ----------   sig.c ----------   */
extern	void	deathwatch	( void );
extern	void	reissue_cntrlc	( PE );

/* ----------   vprintf.c ----------   */
extern	void	PI_oprintf	( const char *, ... );
extern	void	PI_oputchar	( int );

/* ----------   fsdos.c, fsmac.c, fsunix.c, or fsvms.c ----------   */
extern	void	init_fsutils	( PE );

extern	int	pgetcwd		( PE );
extern	int	pchdir		( PE );
extern	int	punlink		( PE );

#ifdef FSACCESS
extern	int	getDirEntries	( PE );
extern	int	getFileStatus	( PE );
extern	int	read_link	( PE );
extern	int	make_symlink	( PE );
extern	int	pcmp_fs		( PE );
extern	int	prmdir		( PE );
extern	int	pmkdir		( PE );
extern	char *	canonical_pathname ( char *, char ** );
extern	int	canonicalize_pathname ( PE );
extern	int	pgetpid		( PE );
#endif /* FSACCESS */

#if (!defined(__DJGPP__) && !defined(__GO32__))
extern	long	get_file_modified_time	(const char * );
extern	int	isdir			(const char * );
#endif

#if MacOS
extern	int	absolute_pathname	(const char *name);
extern	char *	re_comp			(const char *pattern);
extern	int	re_exec			(const char *s);
#ifndef HAVE_GUSI
extern  int	access			(const char *, int x);
extern  int	chdir			(const char *dirname);
extern  char *	getcwd			(char *, int);
#endif
#endif

typedef struct {
    void *start;
    unsigned long length;
} mem_file_info;

extern void *open_memory_file(const char *file_name, mem_file_info *info);
extern void close_memory_file(mem_file_info *info);

/* ----------  bsio.c ------------*/
extern long standard_console_read(char *buf, long n);
extern long standard_console_write(char *buf, long n);
extern long standard_console_error(char *buf, long n);
extern void init_bsio(void);

/* ----------   sig.c ----------   */
extern	void	init_sigint	( void );
extern	void	reset_sigint	( void );

/* ----------   cinterf.c ----------   */
extern	void	cinterf_init	( void );

/* ----------   from either assembly code or wam.c ----------   */
extern	void	wm_exec		(PE, Code * );
extern	int	wm_rungoal	(PE, PWord, PWord );

/* ----------   foreign.c ----------   */
extern	int	load_foreign	( char *, char *, char * );

#ifdef DynamicForeign
/* ----------   lforeign.c ----------   */
extern	void (*	load_object	( char *, char *, char * ) ) (void);
extern	void	foreign_shutdown ( void );
#endif /* DynamicForeign */

#ifdef Portable
extern	void	wam_init	( PE );
#endif /* Portable */

/* ----------   icode1.c ----------   */
extern	int	init_icode_buf	( int );

#ifdef MacOS
extern	void	init_math		( void );
#endif

#ifdef MaxFunc
/*
 * max returns the greater of its two parameters
 * 	-- We are using a macro for "max" -- Ilyas, Raman 5/17/90 
 */

int
max(x, y)
    int   x, y;
{
    return (x < y) ? y : x;
}
#else  /* MaxFunc */
#ifndef max
#define max(a,b) ((a)<(b) ? (b) : (a))
#endif
#endif /* MaxFunc */

/* Define the ASCII values for carrage returns and line feeds.
   We cannot use '\r' and '\n' because these values are compiler dependant. */
#define CR	0x0d
#define LF	0x0a
#define CRSTR	"\x0d"
#define LFSTR	"\x0a"
#define CRLFSTR	"\x0d\x0a"




#endif /* _DEFS_H_INCLUDED_ */

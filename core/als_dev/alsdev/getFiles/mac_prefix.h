/*
 * MW_TclHeader.pch --
 *
 *  This file is the source for a pre-compilied header that gets used
 *  for all files in the Tcl projects.  This make compilies go a bit
 *  faster.  This file is only intended to be used in the MetroWerks
 *  CodeWarrior environment.  It essentially acts as a place to set 
 *  compiler flags.  See MetroWerks documention for more details.
 *
 * Copyright (c) 1995-1997 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * SCCS: @(#) MW_TclHeader.pch 1.24 97/07/30 16:44:37
 */

/*
 * To use the compilied header you need to set the "Prefix file" in
 * the "C/C++ Language" preference panel to point to the created
 * compilied header.  The name of the header depends on the
 * architecture we are compiling for (see the code below).  For
 * example, for a 68k app the prefix file should be: MW_TclHeader68K.
 */
#if __POWERPC__
#pragma precompile_target "MW_ExampleHeaderPPC"
#elif __CFM68K__
#pragma precompile_target "MW_ExampleHeaderCFM68K"
#endif

/*
 * Macintosh Tcl must be compiled with certain compiler options to
 * ensure that it will work correctly.  The following pragmas are 
 * used to ensure that those options are set correctly.  An error
 * will occur at compile time if they are not set correctly.
 */

#if !__option(enumsalwaysint)
#error Tcl requires the Metrowerks setting "Enums always ints".
#endif

#if !defined(__POWERPC__)
#if !__option(far_data)
#error Tcl requires the Metrowerks setting "Far data".
#endif
#endif

#if !defined(__POWERPC__)
#if !__option(fourbyteints)
#error Tcl requires the Metrowerks setting "4 byte ints".
#endif
#endif

#if !defined(__POWERPC__)
#if !__option(IEEEdoubles)
#error Tcl requires the Metrowerks setting "8 byte doubles".
#endif
#endif

/*
 * The define is used most everywhere to tell Tcl (or any Tcl
 * extensions) that we are compiling for the Macintosh platform.
 */

#define MAC_TCL

/*
 * The following defines control the behavior of the Macintosh
 * Universial Headers.
 */

#define SystemSevenOrLater 1
#define STRICT_CONTROLS 1
#define STRICT_WINDOWS  1

/*
 * Define the following symbol if you want
 * comprehensive debugging turned on.
 */

/* #define TCL_DEBUG */

#ifdef TCL_DEBUG
#   define TCL_MEM_DEBUG
#   define TCL_TEST
#endif

/*
 * Place any includes below that will are needed by the majority of the
 * and is OK to be in any file in the system.  The pragma's are used
 * to control what functions are exported from shared library.  In this
 * case, the header file example.h contains the one symbol we export.
 */

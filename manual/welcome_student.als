      Welcome to ALS Prolog (Student Edition)!
      ========================================

Contents:
   - LICENSE
   - WARRANTY
   - CD ORGANIZATION
   - MANUAL
   - HELP SYSTEM
   - COPYING ALS

LICENSE
=======
Applied Logic Systems, Inc., provides this program and licenses 
its use.  Use of this program is prohibited without a valid 
license.  You may:
a)  Use this program on a single machine at any given time;
    (To install this program on a server, you must obtain a 
     separate server license from Applied Logic Systems.)
b)  Copy the program for backup purposes;
c)  Transfer the program and license to another person if the 
    other person agrees to accept the terms of this license.
No other uses of program are permitted.  

WARRANTY
========
This program is provided "as is " without warranty of any kind, 
either expressed or implied, including, but not limited to, 
implied warranties of merchantability and fitness for a 
particular purpose.  You assume the entire risk as to the 
selection of this program to achieve your intended results and 
for the installation, use, performance, and results obtained 
through the use of this program.

CD ORGANIZATION
===============
The ALS Prolog Student Edition CD contains the following file 
and directories:

     ALS Student Prolog 3.1 Installer 
     Acrobat Reader Installer
	 Welcome - this file

On Macintosh and Windows, ALS Student Prolog 3.1 Installer is a standard
system installer (on Windows, it is ALS Student Prolog 3.1 Installer.EXE).
Simply double-click on the icon for

	ALS Student Prolog 3.1 Installer, 

and follow the simple directions to install ALS Prolog on your 
hard drive.

On Unix, ALS Student Prolog 3.1 Installer is a gzipped tar file whose name
is of the form

	als-student-prolog-<ARCH>.tgz

where <ARCH> is your target OS (e.g., solaris, hpux, irix, linux).
Choose the directory in which you want to install ALS Prolog, and
copy als-student-prolog-<ARCH>.tgz to that directory.  Then perform:

	gzip -d als-student-prolog-<ARCH>.tgz
	tar -xf ./als-student-prolog-<ARCH>.tar

If you do not have gzip on your system, a copy is included on the
CD for your convenience.

After installation on Unix, set your search paths appropriately.

MANUAL
======
The manual for the student edition of ALS Prolog is provided
by the file

    Student Manual.pdf (student-manual.pdf on Unix)

in the installation directory ALS Student Prolog.  This is an Adobe 
Acrobat(r) file.  A copy of an installer for Acrobat is included in 
the Acrobat directory.  The installer is named:

	Macintosh: Reader 3.02 Installer 
	Windows:   ar302.exe
	Unix:      ar302XXX.tar.Z  (XXX appropriate for the platform)

To install Acrobat:
	On Windows and Macintosh, double click on the icon for the
	Acrobat Installer, and follow the simple directions.

	On Unix, choose a temporary directory, and copy ar302XXX.tar.Z to
	that directory.  Then perform:

		gzip -d ar302XXX.tar.Z
		tar -xf ar302XXX.tar

	Then execute


	and follow the simple directions.

To read the ALS Student Prolog manual:  
	After Acrobat has been installed, on Windows and Macintosh, simply 
	double-click on the icon for

    	ALS Prolog Manual.pdf

	On Unix, execute

		acroread

	and then open student-manual.pdf.  If <MP> is a path to the directory 
	containing the manual, then executing

		acroread <MP>/student-manual.pdf

	will start the Acrobat Reader and automatically load the manual.

HELP SYSTEM
===========

The Reference Manual for ALS Prolog is implemented as an HTML-based HELP system.
You will need fairly recent versions of the Netscape or Internet Explorer browsers
to read the help files, as follows:

	Macintosh:  Netscape Navigator 4.0+
	---------   { IE exibits difficulties on Macintosh }

	Windows:    Netscape Navigator 4.06+
	-------     Internet Explorer 4.0+

	Unix:       Netscape Navigator 4.07+
	----

After the installation is complete, the ALS Prolog HELP system is contained in the

	help

directory inside the installation directory.  It consists of a large number of
*.htm and *.gif files, together with a number of additonal files.  In addition,
there is one file

	als_help.htm 

in the installation directory.  To view the ALS Prolog Help system, simply open the 
file

	als_help.htm

in your browser.  PLEASE NOTE that the start-up of the help system is rather
slow, since the browsers must fire up Java and other components.  However,
once the contents for the system have appeared, it performs quite nicely

COPYING ALS
===========
Most of the source files distributed with ALS Prolog are governed
by the license contained in the file "COPYING ALS" which 
is included with this distribution.  

   = = = = = = = = = = = = = = = = = = = = = = = = = = = =

       Applied Logic Systems, Inc.
       PO Box 400175, Cambridge, MA 02140 USA
	   Web: http://www.als.com
       Email: support@als.com   
       Fax: (617) 497-3963 Tel: (617) 497-0100   


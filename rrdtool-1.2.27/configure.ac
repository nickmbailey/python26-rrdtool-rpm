dnl RRDtool AutoConf script ... 
dnl ---------------------------
dnl
dnl Created by Jeff Allen, Tobi Oetiker, Blair Zajac
dnl
dnl Inspiration from http://autoconf-archive.cryp.to
 
dnl tell automake the this script is for rrdtool
dnl the official version number is
dnl a.b.c
AC_INIT([rrdtool],[1.2.27])
dnl for testing a numberical version number comes handy
dnl the released version are
dnl a.bccc
dnl the devl versions will be something like
dnl a.b999yymmddhh 
NUMVERS=1.2027
AC_SUBST(NUMVERS)
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([rrd_config.h])

dnl all our local stuff like install scripts and include files
dnl is in there


dnl determine the type of system we are running on

AC_SUBST(VERSION)

AC_PREFIX_DEFAULT( /usr/local/rrdtool-$PACKAGE_VERSION )

dnl Minimum Autoconf version required.
AC_PREREQ(2.59)

dnl At the TOP of the HEADER

AH_TOP([

#ifndef RRD_CONFIG_H
#define RRD_CONFIG_H
/* IEEE can be prevented from raising signals with fpsetmask(0) */
#undef MUST_DISABLE_FPMASK

/* IEEE math only works if SIGFPE gets actively set to IGNORE */

#undef MUST_DISABLE_SIGFPE

/* realloc does not support NULL as argument */
#undef NO_NULL_REALLOC

/* lets enable madvise defines in NetBSD */
#if defined(__NetBSD__)
# if !defined(_NETBSD_SOURCE)
#  define _NETBSD_SOURCE
# endif
#endif

 ])

AH_BOTTOM([
#ifdef HAVE_FEATURES_H
#define _XOPEN_SOURCE 600
#undef _BSD_SOURCE /* comment to prevent configure from modifying this line */   
#define _BSD_SOURCE 1
# include <features.h>
#endif

#ifdef HAVE_ERRNO_H
# include <errno.h>
#endif

#if defined(HAVE_SYS_MMAN_H)
#include <sys/mman.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif
#ifndef MAXPATH
# ifdef PATH_MAX
#  define MAXPATH PATH_MAX
# endif
#endif
#ifndef MAXPATH
/* else try the BSD variant */
# ifdef MAXPATHLEN
#  define MAXPATH MAXPATHLEN
# endif
#endif

#if !defined HAVE_MADVISE && defined HAVE_POSIX_MADVISE
/* use posix_madvise family */
# define madvise posix_madvise
# define MADV_NORMAL POSIX_MADV_NORMAL
# define MADV_RANDOM POSIX_MADV_RANDOM
# define MADV_SEQUENTIAL POSIX_MADV_SEQUENTIAL
# define MADV_WILLNEED POSIX_MADV_WILLNEED
# define MADV_DONTNEED POSIX_MADV_DONTNEED
#endif

#if defined POSIX_MADV_RANDOM && !defined MADV_RANDOM
#define MADV_RANDOM POSIX_MADV_RANDOM
#endif



#if defined HAVE_MADVISE || defined HAVE_POSIX_MADVISE
# define USE_MADVISE 1
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef HAVE_SYS_TIMES_H
# include <sys/times.h>
#endif

#ifdef HAVE_SYS_RESOURCE_H
# include <sys/resource.h>
#if (defined(__svr4__) && defined(__sun__))
/* Solaris headers (pre 2.6) don't have a getrusage prototype.
   Use this instead. */
extern int getrusage(int, struct rusage *);
#endif /* __svr4__ && __sun__ */
#endif

/* define strrchr, strchr and memcpy, memmove in terms of bsd funcs
   make sure you are NOT using bcopy, index or rindex in the code */
      
#ifdef STDC_HEADERS
# include <string.h>
#else
# ifndef HAVE_STRCHR
#  define strchr index
#  define strrchr rindex
# endif
char *strchr (), *strrchr ();
# ifndef HAVE_MEMMOVE
#  define memcpy(d, s, n) bcopy ((s), (d), (n))
#  define memmove(d, s, n) bcopy ((s), (d), (n))
# endif
#endif

#ifdef NO_NULL_REALLOC
# define rrd_realloc(a,b) ( (a) == NULL ? malloc( (b) ) : realloc( (a) , (b) ))
#else
# define rrd_realloc(a,b) realloc((a), (b))
#endif

#ifdef NEED_MALLOC_MALLOC_H
#  include <malloc/malloc.h>
#endif

#ifdef HAVE_MATH_H
#  include <math.h>
#endif

#ifdef HAVE_FLOAT_H
#  include <float.h>
#endif

#ifdef HAVE_IEEEFP_H
#  include <ieeefp.h>
#endif

#ifdef HAVE_FP_CLASS_H
#  include <fp_class.h>
#endif

/* for Solaris */
#if (! defined(HAVE_ISINF) && defined(HAVE_FPCLASS))
#  define HAVE_ISINF 1
#  ifdef isinf
#  undef isinf /* confuse autoconf */
#  endif
#  define isinf(a) (fpclass(a) == FP_NINF || fpclass(a) == FP_PINF)
#endif

/* solaris 10 it defines isnan such that only forte can compile it ... bad bad  */
#if (defined(HAVE_ISNAN) && defined(isnan) && defined(HAVE_FPCLASS))
#  undef isnan  /* confuse autoconf to NOT remove this */
#  define isnan(a) (fpclass(a) == FP_SNAN || fpclass(a) == FP_QNAN)
#endif

/* for OSF1 Digital Unix */
#if (! defined(HAVE_ISINF) && defined(HAVE_FP_CLASS) && defined(HAVE_FP_CLASS_H))
#  define HAVE_ISINF 1
#  define isinf(a) (fp_class(a) == FP_NEG_INF || fp_class(a) == FP_POS_INF)
#endif

#if (! defined(HAVE_ISINF) && defined(HAVE_FPCLASSIFY) && defined(FP_PLUS_INF) && defined(FP_MINUS_INF))
#  define HAVE_ISINF 1
#  define isinf(a) (fpclassify(a) == FP_MINUS_INF || fpclassify(a) == FP_PLUS_INF)
#endif

#if (! defined(HAVE_ISINF) && defined(HAVE_FPCLASSIFY) && defined(FP_INFINITE))
#  define HAVE_ISINF 1
#  define isinf(a) (fpclassify(a) == FP_INFINITE)
#endif

/* for AIX */
#if (! defined(HAVE_ISINF) && defined(HAVE_CLASS))
#  define HAVE_ISINF 1
#  define isinf(a) (class(a) == FP_MINUS_INF || class(a) == FP_PLUS_INF)
#endif

#if (! defined (HAVE_FINITE) && defined (HAVE_ISFINITE))
#  define HAVE_FINITE 1
#  define finite(a) isfinite(a)
#endif

#if (! defined(HAVE_FINITE) && defined(HAVE_ISNAN) && defined(HAVE_ISINF))
#  define HAVE_FINITE 1
#  define finite(a) (! isnan(a) && ! isinf(a))
#endif

#ifndef HAVE_FINITE
#error "Can't compile without finite function"
#endif

#ifndef HAVE_ISINF
#error "Can't compile without isinf function"
#endif

#endif /* RRD_CONFIG_H */
])

dnl Process Special Options
dnl -----------------------------------

dnl How the vertical axis label is printed
AC_ARG_VAR(RRDGRAPH_YLEGEND_ANGLE, 
 [Vertical label angle: 90.0 (default) or 270.0])
AC_DEFINE_UNQUOTED(RRDGRAPH_YLEGEND_ANGLE,${RRDGRAPH_YLEGEND_ANGLE:-90.0},
 [Vertical label angle: 90.0 (default) or 270.0])

AC_ARG_ENABLE(rrdcgi,[  --disable-rrdcgi        disable building of rrdcgi],
[],[enable_rrdcgi=yes])

dnl Check if we run on a system that has fonts
AC_ARG_WITH(rrd-default-font,
[  --with-rrd-default-font=[OPTIONS]  set the full path to your default font.],
[RRD_DEFAULT_FONT=$withval],[
  if test -d ${WINDIR:-nodir}/cour.ttf ; then
	RRD_DEFAULT_FONT=`cd $WINDIR;pwd`/cour.ttf
  else
	RRD_DEFAULT_FONT='$(fontsdir)/$(fonts_DATA)'
  fi
])

dnl Use mmap in rrd_update instead of seek+write
AC_ARG_ENABLE([mmap],
[  --disable-mmap          disable mmap in rrd_update, use seek+write instead],
[],
[enable_mmap=yes])


 AC_ARG_ENABLE(pthread,[  --disable-pthread       disable multithread support],
[],[enable_pthread=yes])



CONFIGURE_PART(Audit Compilation Environment)


dnl Check for the compiler and static/shared library creation.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LIBTOOL

dnl which flags does the compile support?
if test "$GCC" = "yes"; then
  for flag in -fno-strict-aliasing -Wall -std=gnu99 -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Winline -W; do
    oCFLAGS=$CFLAGS
    CFLAGS="$CFLAGS $flag"
    cachename=rd_cv_gcc_flag_`echo $flag|sed 's/[[^A-Za-z]]/_/g'`
    AC_CACHE_CHECK([if gcc likes the $flag flag], $cachename,
       [AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[return 0 ]])],[eval $cachename=yes],[eval $cachename=no])])
    if eval test \$$cachename = no; then
         CFLAGS=$oCFLAGS
    fi
  done
fi



AC_SUBST(RRD_DEFAULT_FONT)

CONFIGURE_PART(Checking for Header Files)
 
dnl Checks for header files.
AC_HEADER_STDC
AC_HEADER_DIRENT
AC_CHECK_HEADERS( features.h sys/stat.h sys/types.h fcntl.h locale.h fp_class.h malloc.h unistd.h ieeefp.h math.h sys/times.h sys/param.h sys/resource.h float.h strings.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_TIME
AC_STRUCT_TM

dnl Checks for libraries.
AC_CHECK_FUNC(acos, , AC_CHECK_LIB(m, acos))

dnl add pic flag in any case this makes sure all our code is relocatable
eval `./libtool --config | grep pic_flag`
CFLAGS="$CFLAGS $pic_flag"

CONFIGURE_PART(Test Library Functions)

dnl Checks for library functions.
AC_FUNC_STRFTIME
AC_FUNC_VPRINTF

AC_C_BIGENDIAN

dnl for each function found we get a definition in config.h 
dnl of the form HAVE_FUNCTION

AC_CHECK_FUNCS(tzset mbstowcs opendir readdir chdir chroot getuid setlocale strerror strerror_r snprintf vsnprintf fpclass class fp_class isnan memmove strchr mktime getrusage gettimeofday posix_fadvise madvise)

AC_CHECK_DECLS(fdatasync, [], [], [#include <unistd.h>])

dnl XXX: dunno about windows.. add AC_CHECK_FUNCS(munmap) there too?
if test "x$enable_mmap" = "xyes"; then
  case "$host" in
  *cygwin*)
    # the normal mmap test does not work in cygwin
    AC_CHECK_FUNCS(mmap)
    if test "x$ac_cv_func_mmap" = "xyes"; then
      ac_cv_func_mmap_fixed_mapped=yes
    fi
  ;;
  *)
    AC_CHECK_HEADERS(sys/mman.h)
    AC_FUNC_MMAP
    AC_CHECK_FUNCS(mmap munmap msync)
    AC_CHECK_DECLS(madvise, [], [], [#ifdef HAVE_SYS_MMAN_H
                                     # include <sys/mman.h>
                                     #endif])
    if test "x$ac_cv_have_decl_madvise" = "xyes";
    then
      AC_CHECK_FUNCS(madvise)
    else
      AC_CHECK_FUNCS(posix_madvise)
      if test "x$ac_cv_func_posix_madvise" != "xyes"; then
        AC_MSG_WARN([madvise() nor posix_madvise() found.])
      fi
    fi
  ;;
  esac
  if test "x$ac_cv_func_mmap" != "xyes";
  then
    AC_MSG_ERROR([--enable-mmap requested but mmap() was not detected])
dnl enable_mmap="no"
  fi
fi

dnl can we use posix_fadvise
AC_CHECK_DECLS(posix_fadvise, [], [], [#define _XOPEN_SOURCE 600
#include <fcntl.h>])
AC_CHECK_FUNCS(posix_fadvise)   

if test "x$enable_mmap" = xyes; then
  case "$host" in
    *cygwin*)
       # the normal mmap test does not work in cygwin
       AC_CHECK_FUNCS(mmap)
       if [ "x${ac_cv_func_mmap}" = xyes ]; then
         ac_cv_func_mmap_fixed_mapped=yes
       fi
    ;;
    *)
       AC_FUNC_MMAP
    ;;
  esac
fi


CONFIGURE_PART(IEEE Math Checks)
 
dnl HP-UX 11.00 does not have finite but does have isfinite as a macro so we need
dnl actual code to check if this works
AC_CHECK_FUNCS(fpclassify, ,
  [AC_MSG_CHECKING(for fpclassify with <math.h>)
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <math.h>
volatile int x;volatile float f; ]], [[x = fpclassify(f)]])],[AC_MSG_RESULT(yes)
      AC_DEFINE(HAVE_FPCLASSIFY)],[AC_MSG_RESULT(no)])])
AC_CHECK_FUNCS(finite, ,
  [AC_CHECK_FUNCS(isfinite, ,
    [AC_MSG_CHECKING(for isfinite with <math.h>)
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <math.h>
volatile int x;volatile float f;  ]], [[x = isfinite(f)]])],[AC_MSG_RESULT(yes)
      AC_DEFINE(HAVE_ISFINITE)],[AC_MSG_RESULT(no)])])])
AC_CHECK_FUNCS(isinf, ,
  [AC_MSG_CHECKING(for isinf with <math.h>)
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <math.h>
volatile int x;volatile float f;  ]], [[x = isinf(f)]])],[AC_MSG_RESULT(yes)
      AC_DEFINE(HAVE_ISINF)],[AC_MSG_RESULT(no)])])

AC_FULL_IEEE

CONFIGURE_PART(Resolve Portability Issues)

dnl what does realloc do if it gets called with a NULL pointer

AC_CACHE_CHECK([if realloc can deal with NULL], rd_cv_null_realloc,
[AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <stdlib.h>
	      int main(void){
              char *x = NULL;
	      x = realloc (x,10);
	      if (x==NULL) return 1;
	      return 0;
             }]])],[rd_cv_null_realloc=yes],[rd_cv_null_realloc=nope],[:])])

if test x"$rd_cv_null_realloc" = xnope; then
AC_DEFINE(NO_NULL_REALLOC)
fi

AC_LANG_PUSH(C)
dnl solaris has some odd defines it needs in order to propperly compile ctime_r
AC_MSG_CHECKING([if ctime_r need special care to act posixly correct])
AC_LINK_IFELSE(
    AC_LANG_PROGRAM(
           [[#include <time.h>]],
           [[ctime_r(NULL,NULL,0)]]
                   ),
    [ CPPFLAGS="$CPPFLAGS -D_POSIX_PTHREAD_SEMANTICS"
      AC_LINK_IFELSE(
          AC_LANG_PROGRAM(
                [[#include <time.h>]],
                [[ctime_r(NULL,NULL)]]
    	                 ),
          [AC_MSG_RESULT([yes, this seems to be solaris style])],
          [AC_MSG_ERROR([Can't figure how to compile ctime_r])]
      )
    ],  
    [ AC_LINK_IFELSE(
          AC_LANG_PROGRAM(
                [[#include <time.h>]],
                [[ctime_r(NULL,NULL)]]
    	                 ),
          [AC_MSG_RESULT(no)],
          [AC_MSG_ERROR([Can't figure how to compile ctime_r])]
      )
    ]  
)
AC_LANG_POP(C)

dnl Check for pthreads
dnl http://autoconf-archive.cryp.to/acx_pthread.m4
 
AC_SUBST(MULTITHREAD_CFLAGS)
AC_SUBST(MULTITHREAD_LDFLAGS)

if test $enable_pthread != no; then 
 ACX_PTHREAD([
    MULTITHREAD_CFLAGS=$PTHREAD_CFLAGS
    MULTITHREAD_LDFLAGS=$PTHREAD_LIBS
	     ],
	     [])
fi

dnl since we use lots of *_r functions all over the code we better
dnl make sure they are known

if test  "x$x_rflag" != "xno"; then
   CPPFLAGS="$CPPFLAGS $x_rflag"
fi

AM_CONDITIONAL(BUILD_MULTITHREAD,[test $enable_pthread != no])

AC_LANG_PUSH(C)
dnl see if we have to include malloc/malloc.h
AC_MSG_CHECKING([do we need malloc/malloc.h])
AC_LINK_IFELSE(
    AC_LANG_PROGRAM(
           [[#include <stdlib.h>]],
           [[malloc(1)]]
                   ),
    [ AC_MSG_RESULT([nope, works out of the box]) ],
    [ AC_LINK_IFELSE(
          AC_LANG_PROGRAM(
                [[#include <stdlib.h>
                  #include <malloc/malloc.h>]],
                [[malloc(1)]]
    	                 ),
          [AC_DEFINE(NEED_MALLOC_MALLOC_H)
           AC_MSG_RESULT([yes we do])],
          [AC_MSG_ERROR([Can not figure how to compile malloc])]
      )
    ]  
)
AC_LANG_POP(C)

CONFIGURE_PART(Find 3rd-Party Libraries)


AM_CONDITIONAL(BUILD_RRDCGI,[test $enable_rrdcgi != no])

CORE_LIBS="$LIBS"

EX_CHECK_ALL(art_lgpl_2, art_vpath_add_point,       libart_lgpl/libart.h,   libart-2.0,  2.3.17, ftp://ftp.gnome.org/pub/GNOME/sources/libart_lgpl/2.3/, /usr/include/libart-2.0)
EX_CHECK_ALL(z,          zlibVersion,               zlib.h,                 zlib,        1.2.3,  http://www.gzip.org/zlib/, "")
EX_CHECK_ALL(png,        png_access_version_number, png.h,                  libpng,      1.2.10,  http://prdownloads.sourceforge.net/libpng/, "")
EX_CHECK_ALL(freetype,   FT_Init_FreeType,          ft2build.h,		    freetype2,   2.1.10,  http://prdownloads.sourceforge.net/freetype/, /usr/include/freetype2)

if test "$EX_CHECK_ALL_ERR" = "YES"; then
  AC_MSG_ERROR([Please fix the library issues listed above and try again.])
fi

ALL_LIBS="$LIBS"
LIBS=

AC_SUBST(CORE_LIBS)
AC_SUBST(ALL_LIBS)

CONFIGURE_PART(Prep for Building Language Bindings)
  
dnl Check for Perl.
AC_PATH_PROG(PERL, perl, no)

AC_ARG_ENABLE(perl,[  --disable-perl          do not build the perl modules],
[],[enable_perl=yes])


AC_ARG_VAR(PERLCC, [[] C compiler for Perl modules])
AC_ARG_VAR(PERLCCFLAGS, [[] CC flags for Perl modules])
AC_ARG_VAR(PERLLD, [[same as PERLCC] Linker for Perl modules])
AC_ARG_VAR(PERLLDFLAGS, [[] LD flags for Perl modules])

if test "x$PERL" = "xno" -o  x$enable_perl = xno; then
	COMP_PERL=
else
	COMP_PERL="perl_piped perl_shared"
        AC_MSG_CHECKING(for the perl version you are running)
	PERL_VERSION=`$PERL -MConfig -e 'print $Config{version}'`
	AC_MSG_RESULT($PERL_VERSION)
        if test -z "$PERLCC"; then
            AC_MSG_CHECKING(for the C compiler perl wants to use to build its modules)
	    perlcc=`$PERL -MConfig -e 'print $Config{cc}'`
	    AC_MSG_RESULT($perlcc)
	    if test ! -x "$perlcc"; then
 	        AC_PATH_PROG(PERL_CC, ${perlcc}, no)
	        if test "$PERL_CC" = "no"; then
                    AC_MSG_WARN([
I would not find the Compiler ($perlcc) that was originally used to compile
your perl binary. You should either make sure that this compiler is
available on your system, pick an other compiler and set PERLCC
appropriately, or use a different perl setup that was compiled locally.

I will disable the compilation of the RRDs perl module for now.
])
  		    COMP_PERL="perl_piped"
	        fi
            fi    
        fi
fi

AC_MSG_CHECKING(Perl Modules to build)
AC_MSG_RESULT(${COMP_PERL:-No Perl Modules will be built})

# Options to pass when configuring perl module
ppref=$prefix
test "$ppref" = "NONE" && ppref=$ac_default_prefix

PERL_MAKE_OPTIONS="PREFIX=$ppref LIB=$ppref/lib/perl/$PERL_VERSION"

dnl pass additional perl options when generating Makefile from Makefile.PL
AC_ARG_ENABLE(perl-site-install,
[  --enable-perl-site-install   by default the rrdtool perl modules are installed
		  	  together with rrdtool in $prefix/lib/perl. You have to
                          put a 'use lib qw($prefix/lib/perl)' into your scripts
                          when you want to use them. When you set this option
                          the perl modules will get installed wherever
                          your perl setup thinks it is best.],
[PERL_MAKE_OPTIONS=],[])

if test ! -z "$PERLCC"; then
   PERL_MAKE_OPTIONS="$PERL_MAKE_OPTIONS CC=$PERLCC"

   if test ! -z "$PERLCCFLAGS"; then
       PERL_MAKE_OPTIONS="$PERL_MAKE_OPTIONS CCFLAGS=$PERLCCFLAGS"
   fi
   
   if test -z "$PERLLD"; then
       PERLLD=$PERLCC
   fi
   PERL_MAKE_OPTIONS="$PERL_MAKE_OPTIONS LD=$PERLLD"
  
   if test ! -z "$PERLLDFLAGS"; then
       PERL_MAKE_OPTIONS="$PERL_MAKE_OPTIONS LDFLAGS=$PERLLDFLAGS"
   fi
fi
        
AC_ARG_WITH(perl-options,
[  --with-perl-options=[OPTIONS]  options to pass on command-line when
                          generating Makefile from Makefile.PL. If you set this
                          option, interesting things may happen unless you know
                          what you are doing!],
[PERL_MAKE_OPTIONS=$withval])

AC_SUBST(PERL_MAKE_OPTIONS)
AC_SUBST(PERL)
AC_SUBST(COMP_PERL)
AC_SUBST(PERL_VERSION)

dnl Check for Ruby.
AC_PATH_PROG(RUBY, ruby, no)

AC_ARG_ENABLE(ruby,[  --disable-ruby          do not build the ruby modules],
[],[enable_ruby=yes])

AC_MSG_CHECKING(if ruby modules can be built)

if test "x$RUBY" = "xno" -o  x$enable_ruby = xno; then
	COMP_RUBY=
 	AC_MSG_RESULT(No .. Ruby not found or disabled)
else
	if $RUBY -e 'require "mkmf"' >/dev/null 2>&1; then
		COMP_RUBY="ruby"
	 	AC_MSG_RESULT(YES)
	else
		COMP_RUBY=
	 	AC_MSG_RESULT(Ruby found but mkmf is missing! Install the -dev package)		
	fi				
fi


dnl pass additional ruby options when generating Makefile from Makefile.PL
AC_ARG_ENABLE(ruby-site-install,
[  --enable-ruby-site-install   by default the rrdtool ruby modules are installed
		  	  together with rrdtool in $prefix/lib/ruby. You have to
                          add $prefix/lib/ruby/$ruby_version/$sitearch to you $: variable
                          for ruby to find the RRD.so file.],
[RUBY_MAKE_OPTIONS=],[RUBY_MAKE_OPTIONS="sitedir=$prefix/lib/ruby"])

    
AC_ARG_WITH(ruby-options,
[  --with-ruby-options=[OPTIONS]  options to pass on command-line when
                          generating Makefile from extconf.rb. If you set this
                          option, interesting things may happen unless you know
                          what you are doing!],
[RUBY_MAKE_OPTIONS=$withval])

AC_SUBST(RUBY_MAKE_OPTIONS)
AC_SUBST(RUBY)
AC_SUBST(COMP_RUBY)


enable_tcl_site=no

AC_ARG_ENABLE(tcl,[  --disable-tcl           do not build the tcl modules],
[],[enable_tcl=yes])

if test  "$enable_tcl" = "yes"; then
  dnl Check for Tcl.
  withval=""
  AC_ARG_WITH(tcllib,[  --with-tcllib=DIR       location of the tclConfig.sh])
  enable_tcl=no
  for dir in $withval /usr/lib /usr/local/lib; do
    AC_MSG_CHECKING(for tclConfig.sh in $dir)
    if test -f "$dir/tclConfig.sh" ; then
    	tcl_config=$dir/tclConfig.sh
        enable_tcl=yes
        AC_MSG_RESULT(yes)
        break
    else
        AC_MSG_RESULT(no)
    fi
  done

  if test "$enable_tcl" = "no"; then
        AC_MSG_WARN([tclConfig.sh not found - Tcl interface won't be built])
  else
	. $tcl_config
	TCL_PACKAGE_DIR="$TCL_PACKAGE_PATH/tclrrd$VERSION"
  fi
  AC_ARG_ENABLE(tcl,[  --enable-tcl-site        install the tcl extension in the tcl tree],
  [],[enable_tcl_site=yes])

fi

AM_CONDITIONAL(BUILD_TCL, test "$enable_tcl" = "yes" )
AM_CONDITIONAL(BUILD_TCL_SITE, test "$enable_tcl_site" = "yes" )

AC_SUBST(TCL_PREFIX)
AC_SUBST(TCL_SHLIB_CFLAGS)
AC_SUBST(TCL_SHLIB_LD)
AC_SUBST(TCL_SHLIB_SUFFIX)
AC_SUBST(TCL_PACKAGE_PATH)
AC_SUBST(TCL_LD_SEARCH_FLAGS)
AC_SUBST(TCL_STUB_LIB_SPEC)
AC_SUBST(TCL_VERSION)
AC_SUBST(TCL_PACKAGE_DIR)

AC_ARG_ENABLE(python,[  --disable-python        do not build the python modules],
[],[enable_python=yes])

if test  "$enable_python" = "yes"; then
dnl Check for python
AM_PATH_PYTHON(2.3,[],[enable_python=no])
AM_CHECK_PYTHON_HEADERS(,[enable_python=no;AC_MSG_WARN(could not find Python headers)])
fi

if test  x$enable_python = xno; then
	COMP_PYTHON=
else
	COMP_PYTHON="python"
fi

AC_SUBST(COMP_PYTHON)

dnl Check for nroff
AC_PATH_PROGS(NROFF, gnroff nroff)
AC_PATH_PROGS(TROFF, groff troff)

AC_ARG_VAR(RRDDOCDIR, [[DATADIR/doc/PACKAGE-VERSION] Documentation directory])
if test -z "$RRDDOCDIR"; then
   RRDDOCDIR='${datadir}/doc/${PACKAGE}-${VERSION}'; fi


CONFIGURE_PART(Apply Configuration Information)
 
AC_CONFIG_FILES([examples/shared-demo.pl])
AC_CONFIG_FILES([examples/piped-demo.pl])
AC_CONFIG_FILES([examples/stripes.pl])
AC_CONFIG_FILES([examples/bigtops.pl])
AC_CONFIG_FILES([examples/minmax.pl])
AC_CONFIG_FILES([examples/4charts.pl])
AC_CONFIG_FILES([examples/perftest.pl])
AC_CONFIG_FILES([examples/Makefile])
AC_CONFIG_FILES([doc/Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([bindings/Makefile])
AC_CONFIG_FILES([bindings/tcl/Makefile])
AC_CONFIG_FILES([bindings/tcl/ifOctets.tcl])
AC_CONFIG_FILES([Makefile])          

AC_CONFIG_COMMANDS([default],[[ chmod +x examples/*.pl]],[[]])
AC_OUTPUT

AC_MSG_CHECKING(in)
AC_MSG_RESULT(and out again)

echo $ECHO_N "ordering CD from http://tobi.oetiker.ch/wish $ECHO_C" 1>&6
sleep 1
echo $ECHO_N ".$ECHO_C" 1>&6
sleep 1
echo $ECHO_N ".$ECHO_C" 1>&6
sleep 1
echo $ECHO_N ".$ECHO_C" 1>&6
sleep 1
echo $ECHO_N ".$ECHO_C" 1>&6
sleep 1
AC_MSG_RESULT([ just kidding ;-)])
echo
echo "----------------------------------------------------------------"
echo "Config is DONE!"
echo
echo "          With MMAP IO: $ac_cv_func_mmap_fixed_mapped"
echo "          Perl Modules: $COMP_PERL"
echo "           Perl Binary: $PERL"
echo "          Perl Version: $PERL_VERSION"
echo "          Perl Options: $PERL_MAKE_OPTIONS"
echo "          Ruby Modules: $COMP_RUBY"
echo "           Ruby Binary: $RUBY"
echo "          Ruby Options: $RUBY_MAKE_OPTIONS"
echo "    Build Tcl Bindings: $enable_tcl"
echo " Build Python Bindings: $enable_python"
echo "          Build rrdcgi: $enable_rrdcgi"
echo "       Build librrd MT: $enable_pthread"
echo
echo
echo "Type 'make' to compile the software and use 'make install' to "
echo "install everything to: $prefix."
echo 
echo "       ... that wishlist is NO JOKE. If you find RRDtool useful"
echo "make me happy. Go to http://tobi.oetiker.ch/wish and"
echo "place an order."
echo 
echo "                               -- Tobi Oetiker <tobi@oetiker.ch>"
echo "----------------------------------------------------------------"

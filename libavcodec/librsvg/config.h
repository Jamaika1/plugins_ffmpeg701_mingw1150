/* config.h.win32.in.  Manually Edited for Windows Builds.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

#include "glib/config_win32.h"

#define SRCDIR "/"

/* Define to 1 if you have the <inttypes.h> header file. */
#if !defined (_MSC_VER) || (_MSC_VER >= 1800)
//#define HAVE_INTTYPES_H 1
#endif

/* Define if your <locale.h> file defines LC_MESSAGES. */
/* #undef HAVE_LC_MESSAGES */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Have the pangoft2 library */
//#define HAVE_PANGOFT2 1

/* Define to 1 if you have the <stdint.h> header file. */
#if !defined (_MSC_VER) || (_MSC_VER >= 1600)
#define HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#ifndef _MSC_VER
  #undef HAVE_STRINGS_H
#endif

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef _MSC_VER
  #undef HAVE_UNISTD_H
#endif

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "librsvg"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://bugzilla.gnome.org/enter_bug.cgi?product=librsvg"

/* Define to the full name of this package. */
#define PACKAGE_NAME "RSVG"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "RSVG 2.40.21-13fbcd1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "librsvg"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.40.21-13fbcd1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "2.40.21-13fbcd1"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/*#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#  define isnan(a) _isnan(a)
#else
#  define isnan(a) (a != a)
#endif*/

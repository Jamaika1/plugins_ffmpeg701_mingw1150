/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */
/* Actually, this version of config.h is manually edited from the above */

#include "../glib/config_win32.h"

#define USE_HB_DWRITE 1

/* Have usable Cairo library and font backend */
#define HAVE_CAIRO 1

/* Whether Cairo can use FreeType for fonts */
#ifndef PANGO_VISUALC_NO_FC
//#define HAVE_CAIRO_FREETYPE 1
#endif

/* Whether Cairo has PDF support */
//#define HAVE_CAIRO_PDF 1

/* Whether Cairo has PNG support */
//#define HAVE_CAIRO_PNG 1

/* Whether Cairo has PS support */
//#define HAVE_CAIRO_PS 1

/* Whether Cairo can use Quartz for fonts */
/* #undef HAVE_CAIRO_QUARTZ */

/* Whether Cairo can use the Win32 GDI for fonts */
#define HAVE_CAIRO_WIN32 1
//#define HAVE_CAIRO_WIN32_DIRECTWRITE 1

/* Whether Cairo has Xlib support */
//#define HAVE_CAIRO_XLIB 1

/* Whether CoreText is available on the system */
/* #undef HAVE_CORE_TEXT */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
//#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the `flockfile' function. */
/* #undef HAVE_FLOCKFILE */

/* Have FreeType 2 library */
#ifndef PANGO_VISUALC_NO_FC
//#define HAVE_FREETYPE 1
#endif

/* Define to 1 if you have the `getpagesize' function. */
/* #undef HAVE_GETPAGESIZE */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <stdint.h> header file. */
#if (!defined (_MSC_VER) || (_MSC_VER >= 1600))
#define HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strtok_r' function. */
/* #undef HAVE_STRTOK_R */

/* Define to 1 if you have the `sysconf' function. */
/* #undef HAVE_SYSCONF */

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
/* #undef HAVE_SYS_MMAN_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Have Xft library */
/* #undef HAVE_XFT */

/* PANGO binary age */
#define PANGO_BINARY_AGE 5400

/* PANGO interface age */
#define PANGO_INTERFACE_AGE 0

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

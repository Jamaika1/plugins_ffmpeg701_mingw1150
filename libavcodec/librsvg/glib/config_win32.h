#define _GLIB_EXTERN extern
#define _GIO_EXTERN extern
#define _GMODULE_EXTERN extern
#define GLIB_DEPRECATED G_DEPRECATED _GLIB_EXTERN
#define GLIB_DEPRECATED_FOR(f) G_DEPRECATED_FOR(f) _GLIB_EXTERN
#define GLIB_VAR _GLIB_EXTERN
#define GOBJECT_VAR _GLIB_EXTERN
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_84
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_26
#define GOBJECT_VERSION_MAX_ALLOWED GOBJECT_VERSION_2_82
#define GOBJECT_VERSION_MIN_REQUIRED GOBJECT_VERSION_2_26
#define GIO_VERSION_MAX_ALLOWED GIO_VERSION_2_84
#define GIO_VERSION_MIN_REQUIRED GIO_VERSION_2_26
#define GMODULE_VERSION_MAX_ALLOWED GMODULE_VERSION_2_82
#define GMODULE_VERSION_MIN_REQUIRED GMODULE_VERSION_2_26
#define GLIB_COMPILATION
#define GIO_COMPILATION
#define GOBJECT_COMPILATION
#define G_SETTINGS_ENABLE_BACKEND

#define USE_SYSTEM_PRINTF 1
#undef G_ATOMIC_LOCK_FREE
#define G_ENABLE_DEBUG 1
#define G_OS_WIN32 1
#define G_PLATFORM_WIN32 1

/* The size of a `char', as computed by sizeof. */
#define SIZEOF_CHAR 1
/* The size of a `short', as computed by sizeof. */
//#define SIZEOF_SHORT 2
/* The size of a `wchar_t', as computed by sizeof. */
#define SIZEOF_WCHAR_T 2
/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG 4
/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4
/* The size of a `size_t', as computed by sizeof. */
//#define SIZEOF_SIZE_T 8
/* The size of a `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8
/* The size of a `long long', as computed by sizeof. */
#ifndef _MSC_VER
//#define SIZEOF_LONG_LONG 8
#else /* _MSC_VER */
//#define SIZEOF_LONG_LONG 0
#endif /* _MSC_VER */

/* Define to the GLIB major version */
#define GLIB_MAJOR_VERSION 2
/* Define to the GLIB minor version */
#define GLIB_MINOR_VERSION 83
/* Define to the GLIB micro version */
#define GLIB_MICRO_VERSION 0

#ifndef G_LIB_STATIC
#define G_LIB_EXPORT __declspec(dllexport)
#else
#define G_LIB_EXPORT extern
#endif

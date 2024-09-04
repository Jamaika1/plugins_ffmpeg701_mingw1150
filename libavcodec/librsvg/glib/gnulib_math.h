/* A GNU-like <math.h>.

   Copyright (C) 2002-2003, 2007-2019 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef _GL_MATH_H

#if __GNUC__ >= 3

#endif


/* The include_next requires a split double-inclusion guard.  */
#include <math.h>

/* The __const__ attribute was added in gcc 2.95.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
# define _GL_ATTRIBUTE_CONST __attribute__ ((__const__))
#else
# define _GL_ATTRIBUTE_CONST /* empty */
#endif

#ifndef _GL_MATH_H
#define _GL_MATH_H

/* On OpenVMS, NAN, INFINITY, and HUGEVAL macros are defined in <fp.h>.  */
#if defined __VMS && ! defined NAN
# include <fp.h>
#endif

#ifndef _GL_INLINE_HEADER_BEGIN
 #error "Please include config.h first."
#endif
_GL_INLINE_HEADER_BEGIN
#ifndef _GL_MATH_INLINE
# define _GL_MATH_INLINE _GL_INLINE
#endif

#include "c++defs.h"

#include "arg-nonnull.h"

/* The definition of _GL_WARN_ON_USE is copied here.  */

#ifdef __cplusplus
/* Helper macros to define type-generic function FUNC as overloaded functions,
   rather than as macros like in C.  POSIX declares these with an argument of
   real-floating (that is, one of float, double, or long double).  */
# define _GL_MATH_CXX_REAL_FLOATING_DECL_1(func) \
static inline int                                                   \
_gl_cxx_ ## func ## f (float f)                                     \
{                                                                   \
  return func (f);                                                  \
}                                                                   \
static inline int                                                   \
_gl_cxx_ ## func ## d (double d)                                    \
{                                                                   \
  return func (d);                                                  \
}                                                                   \
static inline int                                                   \
_gl_cxx_ ## func ## l (long double l)                               \
{                                                                   \
  return func (l);                                                  \
}
# define _GL_MATH_CXX_REAL_FLOATING_DECL_2(func) \
_GL_BEGIN_NAMESPACE                                                 \
inline int                                                          \
func (float f)                                                      \
{                                                                   \
  return _gl_cxx_ ## func ## f (f);                                 \
}                                                                   \
inline int                                                          \
func (double d)                                                     \
{                                                                   \
  return _gl_cxx_ ## func ## d (d);                                 \
}                                                                   \
inline int                                                          \
func (long double l)                                                \
{                                                                   \
  return _gl_cxx_ ## func ## l (l);                                 \
}                                                                   \
_GL_END_NAMESPACE
#endif

/* Helper macros to define a portability warning for the
   classification macro FUNC called with VALUE.  POSIX declares the
   classification macros with an argument of real-floating (that is,
   one of float, double, or long double).  */
#define _GL_WARN_REAL_FLOATING_DECL(func) \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## f (float f)                                               \
{                                                                         \
  return func (f);                                                        \
}                                                                         \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## d (double d)                                              \
{                                                                         \
  return func (d);                                                        \
}                                                                         \
_GL_MATH_INLINE int                                                       \
_GL_WARN_ON_USE_ATTRIBUTE (#func " is unportable - "                      \
                           "use gnulib module " #func " for portability") \
rpl_ ## func ## l (long double l)                                         \
{                                                                         \
  return func (l);                                                        \
}
#define _GL_WARN_REAL_FLOATING_IMPL(func, value) \
  (sizeof (value) == sizeof (float) ? rpl_ ## func ## f (value)     \
   : sizeof (value) == sizeof (double) ? rpl_ ## func ## d (value)  \
   : rpl_ ## func ## l (value))


#if 0
/* Pull in a function that fixes the 'int' to 'long double' conversion
   of glibc 2.7.  */
_GL_EXTERN_C void _Qp_itoq (long double *, int);
static void (*_gl_math_fix_itold) (long double *, int) = _Qp_itoq;
#endif


/* POSIX allows platforms that don't support NAN.  But all major
   machines in the past 15 years have supported something close to
   IEEE NaN, so we define this unconditionally.  We also must define
   it on platforms like Solaris 10, where NAN is present but defined
   as a function pointer rather than a floating point constant.  */
#if !defined NAN || compiles ? 0 : 1
# if !GNULIB_defined_NAN
#  undef NAN
  /* The Compaq (ex-DEC) C 6.4 compiler and the Microsoft MSVC 9 compiler
     choke on the expression 0.0 / 0.0.  */
#  if defined __DECC || defined _MSC_VER
_GL_MATH_INLINE float
_NaN ()
{
  static float zero = 0.0f;
  return zero / zero;
}
#   define NAN (_NaN())
#  else
#   define NAN (0.0f / 0.0f)
#  endif
#  define GNULIB_defined_NAN 1
# endif
#endif

/* Solaris 10 defines HUGE_VAL, but as a function pointer rather
   than a floating point constant.  */
#if 0
# undef HUGE_VALF
# define HUGE_VALF (1.0f / 0.0f)
# undef HUGE_VAL
# define HUGE_VAL (1.0 / 0.0)
# undef HUGE_VALL
# define HUGE_VALL (1.0L / 0.0L)
#endif

/* HUGE_VALF is a 'float' Infinity.  */
#ifndef HUGE_VALF
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0f / 0.0f.  */
#  define HUGE_VALF (1e25f * 1e25f)
# else
#  define HUGE_VALF (1.0f / 0.0f)
# endif
#endif

/* HUGE_VAL is a 'double' Infinity.  */
#ifndef HUGE_VAL
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0 / 0.0.  */
#  define HUGE_VAL (1e250 * 1e250)
# else
#  define HUGE_VAL (1.0 / 0.0)
# endif
#endif

/* HUGE_VALL is a 'long double' Infinity.  */
#ifndef HUGE_VALL
# if defined _MSC_VER
/* The Microsoft MSVC 9 compiler chokes on the expression 1.0L / 0.0L.  */
#  define HUGE_VALL (1e250L * 1e250L)
# else
#  define HUGE_VALL (1.0L / 0.0L)
# endif
#endif


#if defined FP_ILOGB0 && defined FP_ILOGBNAN
 /* Ensure FP_ILOGB0 and FP_ILOGBNAN are correct.  */
# if defined __HAIKU__
  /* Haiku: match what ilogb() does */
#  undef FP_ILOGB0
#  undef FP_ILOGBNAN
#  define FP_ILOGB0   (- 2147483647 - 1) /* INT_MIN */
#  define FP_ILOGBNAN (- 2147483647 - 1) /* INT_MIN */
# endif
#else
 /* Ensure FP_ILOGB0 and FP_ILOGBNAN are defined.  */
# if defined __NetBSD__ || defined __sgi
  /* NetBSD, IRIX 6.5: match what ilogb() does */
#  define FP_ILOGB0   (- 2147483647 - 1) /* INT_MIN */
#  define FP_ILOGBNAN (- 2147483647 - 1) /* INT_MIN */
# elif defined _AIX
  /* AIX 5.1: match what ilogb() does in AIX >= 5.2 */
#  define FP_ILOGB0   (- 2147483647 - 1) /* INT_MIN */
#  define FP_ILOGBNAN 2147483647 /* INT_MAX */
# elif defined __sun
  /* Solaris 9: match what ilogb() does */
#  define FP_ILOGB0   (- 2147483647) /* - INT_MAX */
#  define FP_ILOGBNAN 2147483647 /* INT_MAX */
# else
  /* Gnulib defined values.  */
#  define FP_ILOGB0   (- 2147483647) /* - INT_MAX */
#  define FP_ILOGBNAN (- 2147483647 - 1) /* INT_MIN */
# endif
#endif


_GL_INLINE_HEADER_END

#endif /* _GL_MATH_H */
#endif /* _GL_MATH_H */

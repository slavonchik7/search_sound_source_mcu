#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "compiler.h"

#define __FORCE_INLINE  0
#define __NO_INLINE     1
#define __DEF_INLINE    2

#define __LINEALG_FORCE_INLINE    __FORCE_INLINE
#define __LINEALG_NO_INLINE       __NO_INLINE
#define __LINEALG_DEF_INLINE      __DEF_INLINE


#define __PELENG_CONST_ON_START       0
#define __PELENG_CONST_BEFORE_START   1


/* ---------- start config defines ---------- */ 

/* for options inline for line algorithm functions */
// #define LINEALG_INLINE __LINEALG_FORCE_INLINE
 #define LINEALG_INLINE __LINEALG_NO_INLINE
// #define LINEALG_INLINE __LINEALG_DEF_INLINE


/* using for settings for mym,ath functions */
// #define MYMATH_INLINE __FORCE_INLINE
#define MYMATH_INLINE __NO_INLINE


/* the definition MATH_USE_DOUBLE allows you to choose which precision
 * 	will be used to perform mathematical operations
 * 	and store all floating-point variables */
#ifndef MATH_USE_DOUBLE
//#	define MATH_USE_DOUBLE 0
#	define MATH_USE_DOUBLE 1
#endif


/* determines exactly how the bearing constants
 *  calculated before the program is launched or 
 *  calculated during startup will be used */
// #define PELENG_CONST __PELENG_CONST_ON_START
// #define PELENG_CONST __PELENG_CONST_BEFORE_START


/* this definition allows you to exclude
 * 	the use of double in fmtbuf(),
 * since by default, when passing va_arg, the float type
 * 	is converted by the compiler to double */
#ifndef STRIO_FMT_USE_DOUBLE
//#	define STRIO_FMT_USE_DOUBLE 	0
#	define STRIO_FMT_USE_DOUBLE 	1
#endif /* STRIO_FMT_USE_DOUBLE */

#ifndef STRIO_FMT_DBL_POINT_SIGN
#	define STRIO_FMT_DBL_POINT_SIGN 8
#endif /* STRIO_FMT_DBL_POINT_SIGN */

#ifndef STRIO_DEBUG
//#	define STRIO_DEBUG	0
#	define STRIO_DEBUG	1
#endif /* STRIO_DEBUG */

#ifndef STRIO_DBG_BUF_SIZE
//#	define STRIO_DBG_BUF_SIZE 32
//#	define STRIO_DBG_BUF_SIZE 64
//#	define STRIO_DBG_BUF_SIZE 128
#	define STRIO_DBG_BUF_SIZE 256
//#	define STRIO_DBG_BUF_SIZE 512
#endif /* STRIO_DBG_BUF_SIZE */


#ifndef LCD_DRAW_COLOR_INVERSE
#	define LCD_DRAW_COLOR_INVERSE 0
#endif

#ifndef LCD_WIND_X0
#	define LCD_WIND_X0 60
#endif
#ifndef LCD_WIND_XSIZE
#	define LCD_WIND_XSIZE 120
#endif
#ifndef LCD_WIND_Y0
#	define LCD_WIND_Y0 60
#endif
#ifndef LCD_WIND_YSIZE
#	define LCD_WIND_YSIZE 120
#endif

/* ---------- end config defines ---------- */


#   define __GLOBAL

#if !defined(MYMATH_INLINE)
#   error "MYMATH_INLINE should been define"
#endif

#if defined(LINEALG_INLINE)
#   if LINEALG_INLINE == __LINEALG_FORCE_INLINE
#      define __la_inline static always_inline
#   elif LINEALG_INLINE == __LINEALG_NO_INLINE
#      define __la_inline no_inline
#   elif LINEALG_INLINE == __LINEALG_DEF_INLINE
#      define __la_inline static inline
#   else
#      define __la_inline
#   endif
#else
#   define __la_inline
#endif




#endif /* __CONFIG_H__ */

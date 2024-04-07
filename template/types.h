#ifndef __TYPES_H__
#define __TYPES_H__

#include "config.h"

#include <stdint.h>
#include <float.h>

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define s8  int8_t
#define s16 int16_t
#define s32 int32_t
#define s64 int64_t

#define f32 float

#define d64 double

#define __GLOBAL_U8     __GLOBAL u8
#define __GLOBAL_U16    __GLOBAL u16
#define __GLOBAL_U32    __GLOBAL u32
#define __GLOBAL_U64    __GLOBAL u64

#define __GLOBAL_S8     __GLOBAL s8
#define __GLOBAL_S16    __GLOBAL s16
#define __GLOBAL_S32    __GLOBAL s32
#define __GLOBAL_S64    __GLOBAL s64

#define __GLOBAL_F32    __GLOBAL f32

#define __GLOBAL_D64    __GLOBAL d64


/* defining the type for floating point variables
 *
 * these definitions indicate which floating point precision to use
 *
 * the definition of FP(v) determines how constant
 * 	values will be interpreted, depending on the required accuracy
 *
 * it is advisable to use FP(v) when initializing floating-point values */
#if MATH_USE_DOUBLE
#define FP(v) (v)
typedef double 	fpmath_t;
#else
typedef float 	fpmath_t;
#define FP(v) (v##f)
#endif

#ifndef NULL
#   define NULL 0ULL
#endif /* NULL */

#endif /* __TYPES_H__ */


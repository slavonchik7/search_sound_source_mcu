#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "config.h"
#include "types.h"
#include <math.h>


#define MYABS(v) \
    ({ \
        const fpmath_t volatile __v = (typeof(__v))(v); \
        __v > FP(0.0) ? __v : -__v; \
    })

#define MYMIN(a, b) \
	({ \
		const fpmath_t volatile __a = (typeof(__a))(a); \
		const fpmath_t volatile __b = (typeof(__b))(b); \
		__b > __a ? __a : __b; \
	})

#define MYMAXF(a, b) \
	({ \
		const fpmath_t volatile __a = (typeof(__a))(a); \
		const fpmath_t volatile __b = (typeof(__b))(b); \
		__b > __a ? __b : __a; \
	})


#if MATH_USE_DOUBLE
#	define __mysin(v)		sin(v)
#	define __mycos(v)		cos(v)
#	define __myasin(v)		asin(v)
#	define __myatan(v)		atan(v)
#	define __mysqrt(v)		sqrt(v)
#	define __mypow(v, e)  	pow(v, e)
#else
#	define __mysin(v)		sinf(v)
#	define __mycos(v)		cosf(v)
#	define __myasin(v)		asinf(v)
#	define __myatan(v)		atanf(v)
#	define __mysqrt(v)		sqrtf(v)
#	define __mypow(v, e)  	powf(v, e)
#endif


#if MYMATH_INLINE == __FORCE_INLINE
static always_inline fpmath_t mysin(fpmath_t v)   			{ return __mysin(v); }
static always_inline fpmath_t mycos(fpmath_t v)   			{ return __mycos(v); }
static always_inline fpmath_t myasin(fpmath_t v)  			{ return __myasin(v); }
static always_inline fpmath_t myatan(fpmath_t v)  			{ return __myatan(v); }
static always_inline fpmath_t mysqrt(fpmath_t v)  			{ return __mysqrt(v); }
static always_inline fpmath_t mypow(fpmath_t v, fpmath_t e)	{ return __mypow(v, e); }
#else
no_inline fpmath_t mysin(fpmath_t v);
no_inline fpmath_t mycos(fpmath_t v);
no_inline fpmath_t myasin(fpmath_t v);
no_inline fpmath_t myatan(fpmath_t v);
no_inline fpmath_t mysqrt(fpmath_t v);
no_inline fpmath_t mypow(fpmath_t v, fpmath_t e);
#endif

#endif /* __MYMATH_H__ */

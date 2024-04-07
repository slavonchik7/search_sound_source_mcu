#ifndef __LINEALG_H__
#define __LINEALG_H__

#include "config.h"
#include "types.h"
#include "mymath.h"

typedef struct {
    fpmath_t x;
    fpmath_t y;
} vector2_t;


static no_inline fpmath_t
__la_pnorm2(fpmath_t x, fpmath_t y)
{
	return mysqrt(mypow(x, FP(2.0)) + mypow(y, FP(2.0)));
}

static always_inline fpmath_t
__la_norm2(const vector2_t *v1, const vector2_t *v2)
{   
    return __la_pnorm2((v1->x - v2->x), (v1->y - v2->y));
}

static always_inline void
__la_minus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)
{
    vsave->x = (fpmath_t)(v1->x - v2->x);
    vsave->y = (fpmath_t)(v1->y - v2->y);
}

static always_inline void
__la_plus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)
{
    vsave->x = (fpmath_t)(v1->x + v2->x);
    vsave->y = (fpmath_t)(v1->y + v2->y);
}



#if !defined(LINEALG_INLINE) || (defined(LINEALG_INLINE) && LINEALG_INLINE == __LINEALG_NO_INLINE)
__la_inline fpmath_t  la_pnorm2(fpmath_t x, fpmath_t y);
__la_inline fpmath_t  la_norm2(const vector2_t *v1, const vector2_t *v2);
__la_inline void la_minus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave);
__la_inline void la_plus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave);
__la_inline void la_minus2_nosave(vector2_t *v1, const vector2_t *v2);
__la_inline void la_plus2_nosave(vector2_t *v1, const vector2_t *v2);
#else
__la_inline fpmath_t  la_pnorm2(fpmath_t x, fpmath_t y)									{ return __la_pnorm2(x, y); }
__la_inline fpmath_t  la_norm2(const vector2_t *v1, const vector2_t *v2)                { return __la_norm2(v1, v2); }
__la_inline void la_minus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)  { __la_minus2(v1, v2, vsave); }
__la_inline void la_plus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)   { __la_plus2(v1, v2, vsave); }
__la_inline void la_minus2_nosave(vector2_t *v1, const vector2_t *v2)             		{ __la_minus2(v1, v2, v1); }
__la_inline void la_plus2_nosave(vector2_t *v1, const vector2_t *v2)              		{ __la_plus2(v1, v2, v1); }
#endif




#endif /* __LINEALG_H__ */

#include "linealg.h"

/* if not inline */
#if !defined(LINEALG_INLINE) || (defined(LINEALG_INLINE) && LINEALG_INLINE == __LINEALG_NO_INLINE)

fpmath_t la_pnorm2(fpmath_t x, fpmath_t y)
{
	return __la_pnorm2(x, y);
}

fpmath_t la_norm2(const vector2_t *v1, const vector2_t *v2)
{
    return __la_norm2(v1, v2); 
}

void la_minus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)  
{ 
    __la_minus2(v1, v2, vsave); 
}

void la_plus2(const vector2_t *v1, const vector2_t *v2, vector2_t *vsave)   
{ 
    __la_plus2(v1, v2, vsave); 
}

void la_minus2_nosave(vector2_t *v1, const vector2_t *v2)             
{ 
    __la_minus2(v1, v2, v1); 
}

void la_plus2_nosave(vector2_t *v1, const vector2_t *v2)              
{ 
    __la_plus2(v1, v2, v1); 
}
#endif

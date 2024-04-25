

#include "algorithm.h"
#include "types.h"
#include "mymath.h"
#include "strio.h"


/* storing information about sensors in the system and their delays */

__GLOBAL src_ctx_t src_ctx = 
{
    .sinfo = 
    {
        {
            .pos = {SENSORS_RADIUS, FP(0.0)},
            .delay = FP(0.0),
        },
        {
            .pos = {FP(0.0), SENSORS_RADIUS},
            .delay = FP(0.0),
        },
        {
            .pos = {-SENSORS_RADIUS, FP(0.0)},
            .delay = FP(0.0),
        },
        {
            .pos = {FP(0.0), -SENSORS_RADIUS},
            .delay = FP(0.0),
        },
    },
    .sinfo_sorted = {NULL, NULL, NULL, NULL},
};


__GLOBAL peleng_ctx_t peleng_ctx =  
{
    .delays = 
    {
        {FP(0.0), FP(0.0), FP(0.0), FP(0.0)},
        {FP(0.0), FP(0.0), FP(0.0), FP(0.0)},
        {FP(0.0), FP(0.0), FP(0.0), FP(0.0)},
        {FP(0.0), FP(0.0), FP(0.0), FP(0.0)},
    },
    .i_idx = 0,
    .j_idx = 0,
};


const __GLOBAL fpmath_t div_pi_180 = (fpmath_t)(PI / FP(180.0)); /* PI / 180 const */
const __GLOBAL fpmath_t div_180_pi = (fpmath_t)(FP(180.0) / PI); /* 180 / PI const */

/* the following formula is used to calculate the bearing, 
 *      (delays[i_idx][j] * 343.0) / (2.0 * r * math.sin(-PI/N)) 
 *  as you can see, most of it is always a constant value, 
 *      (343.0) / (2.0 * r * math.sin(-PI/N))
 *  so it makes sense to calculate it in advance and then use it as a multiplier 
 * 
 *      N = 4 - we have 4 sensors
 *      PI = 3.14159265358980f
 *      math.sin(-3.14159265358980 / 4) = -0.7071067811865488
 *      (343.0) / (2.0 * 0.15 * math.sin(-3.14159265358980 / 4)) = -1616.9175063132357
 *  */

static volatile fpmath_t __peleng_p_div_nsensor = (fpmath_t)(PI / FP(4.0));

#if defined(PELENG_CONST) && (PELENG_CONST == __PELENG_CONST_BEFORE_START)
static volatile fpmath_t __peleng_spec_mult = FP(-1616.9175063132357);
#else
static volatile fpmath_t __peleng_spec_mult = FP(0.0);
#endif

#if defined(PELENG_CONST) && (PELENG_CONST == __PELENG_CONST_BEFORE_START)
void bearing_init()
{
}
#else
void bearing_init()
{
    __peleng_spec_mult = (fpmath_t)((SOUND_SPEED) / (FP(2.0) * SENSORS_RADIUS * mysin(-PI / FP(4.0))));
}
#endif

void preparing_values()
{
    fpmath_t dtmin, dtmax;
    int imin = 0, imax = 0, i, k;
    
    for (dtmax = dtmin = src_ctx.sinfo[0].delay, i = 1;
        i < 4;
        i++) 
    {
        fpmath_t d = src_ctx.sinfo[i].delay;

        if (dtmin > d) {
            dtmin = d;
            imin = i;
        }

        if (dtmax < d) {
            dtmax = d;
            imax = i;
        }
    }

    src_ctx.sinfo_sorted[0] = &src_ctx.sinfo[imin];
    src_ctx.sinfo_sorted[1] = &src_ctx.sinfo[imax];
    for (i = 0, k = 2; i < 4; i++) {
        if (i != imin && i != imax) {
            src_ctx.sinfo_sorted[k] = &src_ctx.sinfo[i];
            k++;
        }
    }
}

fpmath_t bearing()
{
    int i, i_idx, j, k;
    fpmath_t phi, saveabs, savesin, savemult, savetest;

    /* i find the sensor number with the least delay */
    for(k = 0; k < 4; k++) {
        if (src_ctx.sinfo[k].delay == FP(0.0)) {
            j = k;
            i = k + 1;
            break;
        }
    }

    i_idx = ((i == 4) ? 0 : i);
    
    /* i calculate the angle of the signal (bearing) */
    phi = myasin(MYABS(src_ctx.sinfo[i_idx].delay - src_ctx.sinfo[j].delay) * __peleng_spec_mult)
            + ((fpmath_t)(i + j)) * __peleng_p_div_nsensor;

    return (phi > FP(0.0)) ? phi : (phi + FP(2.0) * PI);
}

fpmath_t deviation_src_akhmestafina(const vector2_t *src)
{
    fpmath_t t = FP(0.0);
    int i;
    fpmath_t zero_idx_p = la_norm2(src, &src_ctx.sinfo_sorted[0]->pos),
    		first_idx_p = la_norm2(src, &src_ctx.sinfo_sorted[1]->pos);

    for (i = 2; i < 4; i++) {
        fpmath_t dtdiv = src_ctx.sinfo_sorted[i]->delay / src_ctx.sinfo_sorted[1]->delay;

        t += mypow(MYABS(zero_idx_p * (FP(1.0) - dtdiv)
                		+ first_idx_p * dtdiv
						- la_norm2(src, &src_ctx.sinfo_sorted[i]->pos)
						), FP(0.5));
    }

    return t;
}

fpmath_t deviation_src_ru2377594C1(const vector2_t *src)
{
    fpmath_t t = FP(0.0);
    int i;
    fpmath_t zero_idx_p = la_norm2(src, &src_ctx.sinfo_sorted[0]->pos);

    for (i = 1; i < 4; i++) {
    	t += mypow(MYABS(la_norm2(src, &src_ctx.sinfo_sorted[i]->pos)
					- (zero_idx_p + SOUND_SPEED * src_ctx.sinfo_sorted[i]->delay)
					), FP(2.0));
    }

    return mypow(t, FP(0.25)); // mypow(t, FP(0.25)); /* sqrt(sqrt()) == pow(0.25)*/
}


/* the variable needed for use in the __x line() and __line()
 * the variable is initialized by the line_search_paint()
 * 	before calling __getflp() */
static volatile vector2_t __rs_start = {FP(0.0), FP(0.0)};


/* a pointer to the function that will be used as an error
 * 	function within the framework of a single calculation
 * is assigned a pointer to deviation_src_akhmestafina()
 * 	and deviation_src_ru2377594C1()
 * for a detailed description, see the comments
 * 	to the search_sound_source() function */
static volatile fpmath_t (*__deviation) (const vector2_t *src) = NULL;


static no_inline fpmath_t __xline(fpmath_t lp)
{
    /* in fact, the calculation formula should look like this, 
     *  but since the points S and R coincide, 
     *  the values are taken from the same point 
     *      real: x = -Yr * lp + Xs */
    return -__rs_start.y * lp + __rs_start.x;
}

static no_inline fpmath_t __yline(fpmath_t lp)
{
    /* in fact, the calculation formula should look like this, 
     *  but since the points S and R coincide, 
     *  the values are taken from the same point 
     *      real: y = Xr * lp + Ys */
    return __rs_start.x * lp + __rs_start.y;
}

static no_inline fpmath_t __getflp(fpmath_t lp)
{
    vector2_t p = {__xline(lp), __yline(lp)};
    return __deviation(&p);
}


void line_search_point(ls_arg_t *arg)
{
    /* a vector for storing the values of sin(angle) and cos(angle)
     *  in order to use them for calculations in the future */
    __rs_start.x = arg->r * mycos(arg->angle);
    __rs_start.y = arg->r * mysin(arg->angle);

    /* finding the minimum assumes that the left edge
     * 	of the parameter is smaller than the right
	 *	one, so we check the input values
	 *	and bring them to the required form */
    fpmath_t lpl = arg->lpl,
    		 lpr = arg->lpr;

    if (lpl > lpr) {
        lpl = arg->lpr;
        lpr = arg->lpl;
    }

    fpmath_t lptr = lpl,
    		 rptr = lpr;

    /* the initial values are taken for fun,
     *  they just have to be larger than any
     *  of the possible values of the function when searching */
    fpmath_t lmin = FP(9999.0), rmin = FP(9999.0);

    {
		fpmath_t dlp = arg->dlp;
		for (;;) {
			/* if the search points intersect,
			 * 	then we finish the search */
			if (lpl >= lpr)
				break;

			fpmath_t l = __getflp(lpl),
					 r = __getflp(lpr);

			if (l < lmin) {
				lmin = l;
				lptr = lpl;
			}

			if (r < rmin) {
				rmin = r;
				rptr = lpr;
			}

			lpl += dlp;
			lpr -= dlp;
		}
    }

    /* i choose the smallest deviation value
     * 	and the corresponding parameter */
    if (rmin < lmin) {
        arg->deviation = rmin;
        arg->reslp = rptr;
    } else {
    	arg->deviation = lmin;
    	arg->reslp = lptr;
    }

	fpmath_t x = __xline(arg->reslp),
			 y = __yline(arg->reslp);

	{
	    /* i consider the angle (in radians) between the direction
	     * 	to the signal source and the axis (0, Ox) */
		fpmath_t phi = myatan(y / x);

    	/* 	important!!! the angle must be positive for further calculations,
    	 * 	we convert negative angles to positive ones */
		if (x < 0)
			phi += PI;
		else if (y < 0)
			phi += PI2;

		arg->angle = phi;
    }

	arg->point.x = x;
	arg->point.y = y;
}

#define SRC_SEARCH_STEP 0.1

static ls_arg_t __lsarg_sss_first 	= {0,};
static ls_arg_t __lsarg_sss_min		= {0,};
static ls_arg_t __lsarg_sss_max		= {0,};

static void __search_sound_source(vector2_t *src, fpmath_t *bearing)
{
	fpmath_t rmin = SRC_MIN_DISTANCE,
			 rmax = SRC_MAX_DISTANCE;
	fpmath_t dr;

	/* first search for find correctly phi */
	line_search_point(&__lsarg_sss_first);

	__lsarg_sss_min.angle = __lsarg_sss_first.angle;
	__lsarg_sss_max.angle = __lsarg_sss_first.angle;
	int n=0;
	while ((rmax - rmin) > SRC_SEARCH_EPSI) {
		dr = (rmax - rmin) / FP(3.0);

		__lsarg_sss_min.r = rmin + dr;
		__lsarg_sss_max.r = rmax - dr;

		line_search_point(&__lsarg_sss_min);
		line_search_point(&__lsarg_sss_max);

		if (__lsarg_sss_min.deviation > __lsarg_sss_max.deviation)
			rmin = __lsarg_sss_min.r;
		else
			rmax = __lsarg_sss_max.r;

		n++;
	}

	src->x = (__lsarg_sss_max.point.x + __lsarg_sss_min.point.x) / FP(2.0);
	src->y = (__lsarg_sss_max.point.y + __lsarg_sss_min.point.y) / FP(2.0);
	*bearing = __lsarg_sss_min.angle;
}

void search_sound_source(vector2_t *src, fpmath_t *bearing)
{
	/* before you start searching for the coordinates
	 * 	of the sound source, you should determine
	 * 	which error calculation function should be used
	 *
	 * 	the deviation_src_akhmetsafina() function is used as the main one,
	 * 	 since it correctly shows deviations at almost any angle bearing
	 *	deviation_src_akhmetsafina() works poorly only
	 *	 at angles PI/4 + PI/2 *n (45, 135, 225, 315),
	 *	 that is, where the signal arrives at several sensors
	 *	 at the same time, in in this case, the time delay
	 *	 in the neighborhood is 0, which makes it impossible
	 *	 to search for the minimum on this line, since all values in the neighborhood
	 *
	 *	the deviation_src_ru2377594C1() function, on the contrary,
	 *	 correctly reflects the error at angles lying
	 *	 in the vicinity of PI/4 + PI/2 * n (45, 135, 225, 315),
	 *	 therefore, it is well suited for calculating the error
	 *  at other angles, the minimum values of the function
	 *   on the entire straight line are slightly different
	 *   from each other and are highly scattered, therefore the search
	 *   it cannot be implemented using the existing algorithm
	 *
	 *  based on these considerations, it is necessary
	 *   to check the angle of arrival of the signal (bearing)
	 *   and select the required function according to it
	 * 	*/

	/* the vicinity of the signal arrival angle */
	fpmath_t phi_epsi = ANGLE_TO_RAD(FP(5.0)); /* 5 degree */
	register fpmath_t brng = *bearing;

	if ((MYABS(brng - ANGLE_TO_RAD(FP(45.0)))  < phi_epsi) || /* check 45 degree */
		(MYABS(brng - ANGLE_TO_RAD(FP(135.0))) < phi_epsi) ||	/* check 135 degree */
		(MYABS(brng - ANGLE_TO_RAD(FP(225.0))) < phi_epsi) ||	/* check 225 degree */
		(MYABS(brng - ANGLE_TO_RAD(FP(315.0))) < phi_epsi))	/* check 315 degree */
	{
		__deviation = deviation_src_ru2377594C1;

		__lsarg_sss_first.angle = *bearing;
		__lsarg_sss_first.r 	= (SRC_MAX_DISTANCE - SRC_MIN_DISTANCE) / FP(2.0);
		__lsarg_sss_first.lpl 	= FP(-0.1);
		__lsarg_sss_first.lpr 	= FP(0.1);
		__lsarg_sss_first.dlp 	= FP(0.002);
		__lsarg_sss_first.deviation = FP(0.0);
		__lsarg_sss_first.point.x = FP(0.0);
		__lsarg_sss_first.point.y = FP(0.0);
		__lsarg_sss_first.reslp   = FP(0.0);

		__lsarg_sss_min.lpl 	= FP(-0.005);
		__lsarg_sss_min.lpr 	= FP(0.005);
		__lsarg_sss_min.dlp 	= FP(0.0002);
		__lsarg_sss_min.deviation = FP(0.0);
		__lsarg_sss_min.point.x = FP(0.0);
		__lsarg_sss_min.point.y = FP(0.0);
		__lsarg_sss_min.r 		= FP(0.0);
		__lsarg_sss_min.reslp   = FP(0.0);

		__lsarg_sss_max.lpl 	= FP(-0.005);
		__lsarg_sss_max.lpr 	= FP(0.005);
		__lsarg_sss_max.dlp 	= FP(0.0002);
		__lsarg_sss_max.deviation = FP(0.0);
		__lsarg_sss_max.point.x = FP(0.0);
		__lsarg_sss_max.point.y = FP(0.0);
		__lsarg_sss_max.r 		= FP(0.0);
		__lsarg_sss_max.reslp   = FP(0.0);

		__search_sound_source(src, bearing);
	} else {
		__deviation = deviation_src_akhmestafina;

		__lsarg_sss_first.angle = *bearing;
		__lsarg_sss_first.r 	= (SRC_MAX_DISTANCE - SRC_MIN_DISTANCE) / FP(2.0);
		__lsarg_sss_first.lpl 	= FP(-0.1);
		__lsarg_sss_first.lpr 	= FP(0.1);
		__lsarg_sss_first.dlp 	= FP(0.001);
		__lsarg_sss_first.deviation = FP(0.0);
		__lsarg_sss_first.point.x = FP(0.0);
		__lsarg_sss_first.point.y = FP(0.0);
		__lsarg_sss_first.reslp   = FP(0.0);

		__lsarg_sss_min.lpl 	= FP(-0.001);
		__lsarg_sss_min.lpr 	= FP(0.001);
		__lsarg_sss_min.dlp 	= FP(0.0005);
		__lsarg_sss_min.deviation = FP(0.0);
		__lsarg_sss_min.point.x = FP(0.0);
		__lsarg_sss_min.point.y = FP(0.0);
		__lsarg_sss_min.r 		= FP(0.0);
		__lsarg_sss_min.reslp   = FP(0.0);

		__lsarg_sss_max.lpl 	= FP(-0.001);
		__lsarg_sss_max.lpr 	= FP(0.001);
		__lsarg_sss_max.dlp 	= FP(0.0005);
		__lsarg_sss_max.deviation = FP(0.0);
		__lsarg_sss_max.point.x = FP(0.0);
		__lsarg_sss_max.point.y = FP(0.0);
		__lsarg_sss_max.r 		= FP(0.0);
		__lsarg_sss_max.reslp   = FP(0.0);

		__search_sound_source(src, bearing);
	}

}

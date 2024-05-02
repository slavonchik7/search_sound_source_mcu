#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "types.h"
#include "linealg.h"


/* use this flags for check unexpected converts from float to double
 * 	if you want use only float instead double type
 * -Wdouble-promotion -fsingle-precision-constant
 */

#ifndef PI
#   define PI  FP(3.141592653589793)
#endif /* PI */

#ifndef PI2
#	define PI2 FP(6.283185307179586)
#endif /* PI2 */

#ifndef SOUND_SPEED
    /* the speed is taken at a temperature of 20 degrees Celsius */
#   define SOUND_SPEED FP(300.0)
#endif /* SOUND_SPEED */

#ifndef SENSORS_RADIUS
#   define SENSORS_RADIUS FP(0.08)
#endif /* SENSORS_RADIUS */

/* ============================================================================ */
/* definitions that allow you to customize the sound source search
 * the selected constants are optimal for searching
 * this system is not designed to search for a sound source
 * further than 10 meters, even if it is able to do so */
#ifndef SRC_MIN_DISTANCE /* in meters */
#	define SRC_MIN_DISTANCE FP(0.2)
#endif /* SRC_MIN_DISTANCE */

#ifndef SRC_MAX_DISTANCE /* in meters */
#	define SRC_MAX_DISTANCE FP(20.0)
#endif /* SRC_MAX_DISTANCE */

/* the definition specifies with what accuracy
 * 	the coordinates of the sound source will be found */
#ifndef SRC_SEARCH_EPSI
#	define SRC_SEARCH_EPSI FP(0.1)
#endif /* SRC_SEARCH_EPSI */

/* NOT TOUCH THIS DEFINE !!!!!!!!!!!!!!!!!!!!!!!!
	#ifndef SRC_SEARCH_STEP
	#	define SRC_SEARCH_STEP FP(0.1)
	#endif
 * */
/* ============================================================================ */


extern const __GLOBAL fpmath_t div_pi_180; /* PI / 180 const */
extern const __GLOBAL fpmath_t div_180_pi; /* 180 / PI const */


#define ANGLE_TO_RAD(v) ((v) * div_pi_180)
#define RAD_TO_ANGLE(v) ((v) * div_180_pi)

typedef struct {
    /* delay table between sensors there are 4 sensors */
    fpmath_t delays[4][4];

    /* the value of i_idx indicates the index of 
     *  an element in the sinfo array whose delay is 0 
     * the value of j_idx indicates the index of 
     *  the element in the info array that follows i_idx */
    u16 i_idx;
    u16 j_idx;
} peleng_ctx_t;

extern __GLOBAL peleng_ctx_t peleng_ctx;

typedef struct {
    vector2_t pos; 	/* sensor coordinates */
    fpmath_t delay;		/* sensor delay */
} sensor_info_t;


typedef struct {

    /* information about all sensors in the system, 
     *  their coordinates and delays received from the FPGA */
    sensor_info_t sinfo[4];
    
    /* an array containing information in the order 
     *  required to perform calculations 
     * namely, the sensor with a delay of 0 is the first in the array, 
     *  that is, the signal came to it first, 
     * the sensor whose delay is the largest is next, 
     *  that is, the signal came to it last */
    sensor_info_t *sinfo_sorted[4];
} src_ctx_t;



/* storing information about sensors in the system and their delays */
extern __GLOBAL src_ctx_t src_ctx;


/* the function is called 1 time to initialize internal values */
no_inline void bearing_init();

/* the function calculates the values of the bearing 
 *  (that is, the angle of arrival of the signal)
 * the function does not accept arguments, 
 *  all global variables must be set before calling the function */
no_inline fpmath_t bearing();

no_inline void preparing_values();

/* the deviation_src_*() functions are used as an indicator
 * 	of the deviation of the 'src' point from the real signal source */
no_inline fpmath_t deviation_src_akhmestafina(const vector2_t *src);
no_inline fpmath_t deviation_src_ru2377594C1(const vector2_t *src);


#define __ls_in
#define __ls_out
#define __ls_inout

/* a large number of arguments must be passed to the line_search_point function
 *  and several output values must be obtained.
 * it is very expensive and inconvenient to pass so many values to the function,
 * 	therefore, the line_search_arg structure has been created,
 * 	which stores both input and output parameters */

typedef struct line_search_arg {
	fpmath_t 		__ls_inout 	angle; 		/* the angle of the vector by which we will search for the point
	 	 	 	 	 	 	 	 	 	 	 * 	save the angle of the vector to the found point */
	fpmath_t 		__ls_in 	r;			/* the module of the vector by which we will search for the point */
	fpmath_t	 	__ls_in 	lpl;		/* values of the left start limit of the parameter */
	fpmath_t 		__ls_in 	lpr;		/* values of the right start limit of the parameter */
	fpmath_t 		__ls_in 	dlp;		/* the step with which the parameter will be searched */
	fpmath_t		__ls_out 	reslp;		/* the found value of the straight line parameter */
	vector2_t 		__ls_out 	point;		/* save the found point */
	fpmath_t		__ls_out 	deviation; 	/* save the value of the error function at this point (deviation) */
} ls_arg_t;
#undef __ls_in
#undef __ls_out
#undef __ls_inout


/* it is difficult for me to explain what this function
 * does in short, it allows you to find a more accurate
 * 	value of the angle of arrival of the "angle" signal
 * 	at a distance "r" from the origin (0, 0) */
no_inline void line_search_point(ls_arg_t *arg);


/* the function searches for the coordinates of
 * 	the sound source, minimizing the error function
 *
 * in the parameter *src, the coordinates of the object
 *
 * are stored in the parameter *bearing, the calculated angle
 * 	of arrival of the signal is transmitted using
 * 	the bearing() function, also an updated angle
 * 	value is stored in this parameter (more accurate) */
no_inline void search_sound_source(vector2_t *src, fpmath_t *bearing);

#endif /* __ALGORITHM_H__ */

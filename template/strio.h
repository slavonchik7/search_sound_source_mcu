/*
 * strio.h
 *
 *  Created on: 1 апр. 2024 г.
 *      Author: christmas
 */

#ifndef __STRIO_H__
#define __STRIO_H__

#include "config.h"
#include <stdarg.h>


#if STRIO_DEBUG

extern int fmtdebug(char *fmt, ...);

/* the pointer to the function will be called
 * 	every time an output operation is used,
 * the user should implement this function himself
 * 	and assign its address to the internul (*f_putbyte) variable
 * 	(by default is NULL)
 * f_putbyte should return 0 if successful,
 * 	any other value will be interpreted as an error
 * 	and fmtdebug() will stop executing */
extern void strio_set_f_putbyte(int (*f_putbyte)(int b));

#else

static always_inline void strio_set_f_putbyte(int (*f_putbyte)(int b))
{

}

static always_inline int fmtdebug(char *fmt, ...)
{

}

#endif

#if MATH_USE_DOUBLE
#	define FLOAT_TYPE double
#else
#	define FLOAT_TYPE float
#endif

extern void strreverse(char* str, int len);
extern int itos(int v, char *save);
extern int ftos(float n, char* res, int afterpoint);
extern int vfmtbuf(char *to, int tosize, char *fmt, va_list args);
extern int fmtbuf(char *to, int tosize, char *fmt, ...);
extern int striolen(char *s);
extern int striocopy(char *to, char *from);


#endif /* __STRIO_H__ */

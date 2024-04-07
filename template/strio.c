/*
 * strio.c

 *
 *  Created on: 1 апр. 2024 г.
 *      Author: christmas
 */

#include "strio.h"
#include "mymath.h"


#if STRIO_FMT_USE_DOUBLE
#	define __STRIO_D2F(v) \
		({ \
			const volatile float __v = (typeof(__v))(v); \
			__v; \
		})
#endif



static int (*putbyte)(int b) = NULL;


void strio_set_f_putbyte(int (*f_putbyte)(int b))
{
	putbyte = f_putbyte;
}

int fmtdebug(char *fmt, ...)
{
	static char buf[STRIO_DBG_BUF_SIZE];
	int len, n;
	va_list args;

	if (!putbyte)
	    	return 0;

    va_start(args, fmt);
	len = vfmtbuf(buf, sizeof(buf), fmt, args);
    va_end(args);

    buf[len] = 0;

    for (n = 0; n < len + 1; n++)
    	if (putbyte((int)buf[n]) != 0)
    		goto out;

 out:
 	 return len - n;
}

int striolen(char *s)
{
    char *p;
    for (p = s; *s++ != 0;);
    return (int)(s - p - 1);
}

void strreverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char *str, int d)
{
    int i = 0;
    int negflag = 0;
    if (x < 0) {
        *str++ = '-';
        x = -x;
        negflag = 1;
    }

    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    strreverse(str, i);
    str[i] = '\0';
    return i + negflag;
}


// Converts a floating-point/double number to a string.
int ftos(float n, char* res, int afterpoint)
{
    float fpart;
    int i, ipart;

    if (n < 0.0f) {
        *res++ = '-';
        n = -n;
    }

    // Extract integer part
    i = 0;
    ipart = (int)n;
    if (ipart == 0)
        *res++ = '0';
    else
        // convert integer part to string
        i = intToStr(ipart, res, 0);

    // Extract floating part
    fpart = n - (float)ipart;

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        ipart = (int)(fpart * powf(10, afterpoint));
        i += intToStr(ipart, res + i + 1, afterpoint) + 1;
    }

    return i;
}

int itos(int v, char *save)
{
    return intToStr(v, save, 0);
}

int striocopy(char *to, char *from)
{
    int len;
    for (len = 0; (*to++ = *from++); len++) {};
    return len;
}

int vfmtbuf(char *to, int tosize, char *fmt, va_list args)
{
	char *tosave = to;

	while (to - tosave < tosize) {
        char b = *fmt++;

        if(b == 0) {
            *to = b;
            break;
        }

        if (b == '%') {
        	float f;
            switch (*fmt)
            {
            case 'd':
                to += itos(va_arg(args, int), to);
                break;
            case 's':
                to += striocopy(to, va_arg(args, char*));
                break;
#if STRIO_FMT_USE_DOUBLE
            case 'f':
            	f = (float)va_arg(args, double);
                to += ftos(f, to, STRIO_FMT_DBL_POINT_SIGN);
                break;
#endif
            case 'c':
                *to++ = (char)va_arg(args, int);
                break;
            default:
                goto copy_byte; /* if default, copy '%' in to */
            }
            fmt++;
        } else {
        copy_byte:
            *to++ = b;
        }
    }

	return (int)(to - tosave);
}

int fmtbuf(char *to, int tosize, char *fmt, ...)
{
	int len;
	va_list args;
    va_start(args, fmt);
    len = vfmtbuf(to, tosize, fmt, args);
    va_end(args);
    return len;
}



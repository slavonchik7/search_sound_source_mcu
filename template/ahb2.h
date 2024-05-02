/*
 * ahb2.h
 *
 *  Created on: 2 мая 2024 г.
 *      Author: christmas
 */

#ifndef __AHB2_H__
#define __AHB2_H__

#include "gw1ns4c.h"

#define __ADDR	uint32_t
#define __VADDR	volatile uint32_t*
#define AHB2_IO_BASE  ((__ADDR)(AHB2PERIPH_BASE + 0x0000))

#define AHB2_WRITE(addr, data) 	(*((__VADDR)(AHB2_IO_BASE + (__ADDR)(addr))) = (data))
#define AHB2_READ(addr)			(*((__VADDR)(AHB2_IO_BASE + (__ADDR)(addr))))

#endif /* __AHB2_H__ */

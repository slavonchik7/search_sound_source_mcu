/*
 * st7789_240_240.h
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: christmas
 */

#ifndef SRC_ST7789_240_240_H_
#define SRC_ST7789_240_240_H_

#include "gw1ns4c.h"


#define ST7789_FB_SIZE 7200

#define ST7789_CS_PORT 	GPIO0
#define ST7789_CS_PIN	GPIO_Pin_13

#define ST7789_WR_PORT 	GPIO0
#define ST7789_WR_PIN	GPIO_Pin_11

#define ST7789_RD_PORT 	GPIO0
#define ST7789_RD_PIN	GPIO_Pin_15

#define ST7789_RS_PORT 	GPIO0
#define ST7789_RS_PIN	GPIO_Pin_10

#define ST7789_DC_PORT	GPIO0
#define ST7789_DC_PIN	GPIO_Pin_12

#define ST7789_D0_PORT 	GPIO0
#define ST7789_D0_PIN 	GPIO_Pin_0

#define ST7789_D1_PORT	GPIO0
#define ST7789_D1_PIN	GPIO_Pin_1

#define ST7789_D2_PORT	GPIO0
#define ST7789_D2_PIN	GPIO_Pin_2

#define ST7789_D3_PORT	GPIO0
#define ST7789_D3_PIN	GPIO_Pin_3

#define ST7789_D4_PORT	GPIO0
#define ST7789_D4_PIN	GPIO_Pin_4

#define ST7789_D5_PORT	GPIO0
#define ST7789_D5_PIN	GPIO_Pin_5

#define ST7789_D6_PORT	GPIO0
#define ST7789_D6_PIN	GPIO_Pin_6

#define ST7789_D7_PORT	GPIO0
#define ST7789_D7_PIN	GPIO_Pin_7


#define ST7789_MS_DELAY(ms) delayMillis(ms)


#define __NPORT(name) 	ST7789_##name##_PORT
#define __NPIN(name) 	ST7789_##name##_PIN

#define __Dx_PORT(x) __NPORT(D##x)
#define __Dx_PIN(x) __NPIN(D##x)

#define __ST7789_WRITE_PIN(port, pin, state) \
	((port)->DATAOUT = (state) ? ((port)->DATAOUT | (pin)) : ((port)->DATAOUT & ~(pin)))

#define __ST7789_FAST_WRITE_Dn(n, state) \
	__ST7789_WRITE_PIN(__Dx_PORT(n), __Dx_PIN(n), state)

#if 1
#define ST7789_RESET(name) 	((__NPORT(name))->DATAOUT &=  (~(__NPIN(name))))
#define ST7789_SET(name) 	((__NPORT(name))->DATAOUT |= (__NPIN(name)))
#else
#define ST7789_RESET(name) 	GPIO_ResetBit(__NPORT(name), __NPIN(name))
#define ST7789_SET(name) 	GPIO_SetBit(__NPORT(name), __NPIN(name))
#endif


#define CLR_RS 	ST7789_RESET(RS)
#define SET_RS 	ST7789_SET(RS)

#define CLR_DC	ST7789_RESET(DC)
#define SET_DC	ST7789_SET(DC)

#define CLR_CS	ST7789_RESET(CS)
#define SET_CS	ST7789_SET(CS)

#define CLR_WR	ST7789_RESET(WR)
#define SET_WR	ST7789_SET(WR)

#define CLR_RD	ST7789_RESET(RD)
#define SET_RD	ST7789_SET(RD)


/* one bit is one pixel */
//extern uint8_t st7789_fb[ST7789_FB_SIZE];


void st7789_write_parall_byte(uint8_t byte);

#define LCD_WRITE(x) st7789_write_parall_byte(x)

#define LCD_WRTIE_WR(x) \
	do { \
		st7789_write_parall_byte(x); \
		CLR_WR; \
		SET_WR; \
	} while (0)

#if 0
static inline void LCD_WRTIE_WR(uint8_t b)
{
	__LCD_WRTIE_WR(b);
}
#endif

void st7789_init_new(void);
void st7789_send_cmd(uint8_t cmd);
void st7789_send_data(uint8_t data);
void st7789_fill_bw(uint8_t bw /* 0 or 1 */); /* black white */
void st7789_set_draw_pos(uint8_t x, uint8_t y);
void st7789_update(void);
void st7789_draw_pixel(uint8_t x, uint8_t y, uint8_t bw);
void st7789_draw_cube(uint8_t x, uint8_t x_size, uint8_t y, uint8_t y_size, uint8_t bw);
void st7789_set_draw_limits(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);

#endif /* SRC_ST7789_240_240_H_ */

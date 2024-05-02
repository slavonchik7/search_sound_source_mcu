/*
 * st7789_240_240.h
 *
 *  Created on: 20 Р°РїСЂ. 2024 Рі.
 *      Author: christmas
 */

/* to save memory, the library uses
 * 	only black and white (1 bit per point)
 * the maximum number of bits the controller has is
 * 	18 bits per point, but I don't need that much */

#ifndef SRC_ST7789_240_240_H_
#define SRC_ST7789_240_240_H_

#include "compiler.h"
#include "gw1ns4c.h"
#include "config.h"

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

extern void delayMillis(uint32_t ms);
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

typedef struct UB_Font_t {
  const uint16_t *table;
  uint16_t width;
  uint16_t height;
}UB_Font;


extern uint16_t Arial_14x22_Table[];

void st7789_write_parall_byte(uint8_t byte);

#define LCD_WRITE(x) st7789_write_parall_byte(x)

#if LCD_FAST_WRITE
#define LCD_WRITE_WR(x) \
	do { \
		st7789_write_parall_byte(x); \
		CLR_WR; \
		SET_WR; \
	} while (0)
#else
void LCD_WRITE_WR(uint8_t x);
#endif


void st7789_init_new(void);
void st7789_send_cmd(uint8_t cmd);
void st7789_send_data(uint8_t data);
void st7789_fill_bw(uint8_t bw /* 0 or 1 */); /* black white */
void st7789_update(void);
void st7789_draw_pixel(uint8_t x, uint8_t y);
void st7789_draw_cube(uint8_t x, uint8_t x_size, uint8_t y, uint8_t y_size, uint8_t bw);
void st7789_set_draw_limits(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);

/* the st7789_draw_circle() function draws a circle with a thickness
 * 	of 1 pixel with a radius radius and
 * 	a center at the point (x0, y0) */
void st7789_draw_circle(uint8_t x0, uint8_t y0, uint8_t radius);


/* st7789_draw_circle_bold() is similar to st7789_draw_circle(),
 * 	but draws a circle with a line thickness of bold pixels
 *
 * the step parameter determines in which direction
 * 	the circle will thicken from the original radius line
 *
 * ST7789_CIRCLE_BOLD_STEP_IN - inside, to the center of the circle
 * ST7789_CIRCLE_BOLD_STEP_OUT - outside the circle from the center */
#define ST7789_CIRCLE_BOLD_STEP_IN	(-1)
#define ST7789_CIRCLE_BOLD_STEP_OUT	( 1)


static void always_inline st7789_set_draw_pos(uint8_t x, uint8_t y)
{
	st7789_set_draw_limits(x, 240, y, 240);
}


void st7789_draw_circle_bold(uint8_t x0, uint8_t y0,
							uint8_t radius, uint8_t bold, int8_t step);

#define __ST7789_FONT_WIDTH 	14
#define __ST7789_FONT_HEIGHT 	22

#define __CH_W					__ST7789_FONT_WIDTH
#define __CH_H					__ST7789_FONT_HEIGHT

/* functions with the names st7789_a_* are similar in their
 * 	operation to the functions st7789_*, only they work
 * 	with a pre-limited area in accordance with the definitions
 * 	LCD_WIND_X0, LCD_WIND_XSIZE, LCD_WIND_Y0, LCD_WIND_YSIZE */

void st7789_a_fill_bw(uint8_t bw);
void st7789_a_draw_char(uint8_t x, uint8_t y, uint8_t ch);


/* the function draws a character in the same way as
 * 	st7789_a_draw_char(), only instead of a character
 * 	it takes a pointer to a buffer that stores font bits */
void __st7789_a_draw_char_raw(uint8_t x, uint8_t y, uint16_t *wert);

static void always_inline st7789_a_clear_screen(void)
{
	st7789_draw_cube(LCD_WIND_X0, LCD_WIND_XSIZE, LCD_WIND_Y0, LCD_WIND_YSIZE, 0);
}

void st7789_a_draw_string(uint8_t x, uint8_t y,
						uint8_t slen /* byte */, uint8_t *str);

#endif /* SRC_ST7789_240_240_H_ */

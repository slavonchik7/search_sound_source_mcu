/*
 * st7789_240_240.c
 *
 *  Created on: 20 апр. 2024 г.
 *      Author: christmas
 */

#include "st7789_240_240.h"


#include <stdint.h>

typedef struct pin_port {
	uint8_t 		pin;
	GPIO_TypeDef 	*port;
} pp_t;

#define ARRAY_SIZE(parr) (sizeof((parr)) / sizeof((parr)[0]))

#define DEF_PP(n) {ST7789_D##n##_PIN, ST7789_D##n##_PORT}
static pp_t D8bit_buf[8] =
{
		DEF_PP(0),
		DEF_PP(1),
		DEF_PP(2),
		DEF_PP(3),
		DEF_PP(4),
		DEF_PP(5),
		DEF_PP(6),
		DEF_PP(7),
};
#undef DEF_PP


/* one bit is one pixel */





#define ST7789_00_NOP       (0x00)
#define ST7789_01_SWRESET   (0x01)
#define ST7789_04_RDDID     (0x04)
#define ST7789_09_RDDST     (0x09)
#define ST7789_0A_RDDPM     (0x0A)
#define ST7789_0B_RDDMADCTL (0x0B)
#define ST7789_0C_RDDCOLMOD (0x0C)
#define ST7789_0D_RDDIM     (0x0D)
#define ST7789_0E_RDDSM     (0x0E)
#define ST7789_0F_RDDSDR    (0x0F)
#define ST7789_10_SLPIN     (0x10)
#define ST7789_11_SLPOUT    (0x11)
#define ST7789_12_PTLON     (0x12)
#define ST7789_13_NORON     (0x13)
#define ST7789_20_INVOFF    (0x20)
#define ST7789_21_INVON     (0x21)
#define ST7789_26_GAMSET    (0x26)
#define ST7789_28_DISPOFF   (0x28)
#define ST7789_29_DISPON    (0x29)
#define ST7789_2A_CASET     (0x2A)
#define ST7789_2B_RASET     (0x2B)
#define ST7789_2C_RAMWR     (0x2C)
#define ST7789_2E_RAMRD     (0x2E)
#define ST7789_30_PTLAR     (0x30)
#define ST7789_33_VSCRDEF   (0x33)
#define ST7789_34_TEOFF     (0x34)
#define ST7789_35_TEON      (0x35)
#define ST7789_36_MADCTL    (0x36)
#define ST7789_37_VSCRSADD  (0x37)
#define ST7789_38_IDMOFF    (0x38)
#define ST7789_39_IDMON     (0x39)
#define ST7789_3A_COLMOD    (0x3A)
#define ST7789_3C_RAMWRC    (0x3C)
#define ST7789_3E_RAMRDC    (0x3E)
#define ST7789_44_TESCAN    (0x44)
#define ST7789_45_RDTESCAN  (0x45)
#define ST7789_51_WRDISBV   (0x51)
#define ST7789_52_RDDISBV   (0x52)
#define ST7789_53_WRCTRLD   (0x53)
#define ST7789_54_RDCTRLD   (0x54)
#define ST7789_55_WRCACE    (0x55)
#define ST7789_56_RDCABC    (0x56)
#define ST7789_5E_WRCABCMB  (0x5E)
#define ST7789_5F_RDCABCMB  (0x5F)
#define ST7789_68_RDABCSDR  (0x68)
#define ST7789_B0_RAMCTRL   (0xB0)
#define ST7789_B1_RGBCTRL   (0xB1)
#define ST7789_B2_PORCTRL   (0xB2)
#define ST7789_B3_FRCTRL1   (0xB3)
#define ST7789_B7_GCTRL     (0xB7)
#define ST7789_BA_DGMEN     (0xBA)
#define ST7789_BB_VCOMS     (0xBB)
#define ST7789_C0_LCMCTRL   (0xC0)
#define ST7789_C1_IDSET     (0xC1)
#define ST7789_C2_VDVVRHEN  (0xC2)
#define ST7789_C3_VRHS      (0xC3)
#define ST7789_C4_VDVSET    (0xC4)
#define ST7789_C5_VCMOFSET  (0xC5)
#define ST7789_C6_FRCTR2    (0xC6)
#define ST7789_C7_CABCCTRL  (0xC7)
#define ST7789_C8_REGSEL1   (0xC8)
#define ST7789_CA_REGSEL2   (0xCA)
#define ST7789_CC_PWMFRSEL  (0xCC)
#define ST7789_D0_PWCTRL1   (0xD0)
#define ST7789_D2_VAPVANEN  (0xD2)
#define ST7789_DA_RDID1     (0xDA)
#define ST7789_DB_RDID2     (0xDB)
#define ST7789_DC_RDID3     (0xDC)
#define ST7789_DF_CMD2EN    (0xDF)
#define ST7789_E0_PVGAMCTRL (0xE0)
#define ST7789_E1_NVGAMCTRL (0xE1)
#define ST7789_E2_DGMLUTR   (0xE2)
#define ST7789_E3_DGMLUTB   (0xE3)
#define ST7789_E4_GATECTRL  (0xE4)
#define ST7789_E8_PWCTRL2   (0xE8)
#define ST7789_E9_EQCTRL    (0xE9)
#define ST7789_EC_PROMCTRL  (0xEC)
#define ST7789_FA_PROMEN    (0xFA)
#define ST7789_FC_NVMSET    (0xFC)
#define ST7789_FE_PROMACT   (0xFE)



void st7789_write_parall_byte(uint8_t byte)
{
	int i;
#if 0
	for (i = 0; i < 8; i++)
		HAL_GPIO_WritePin(D8bit_buf[i].port, D8bit_buf[i].pin,
				(byte >> i) & 0x01);
#elif 0
	for (i = 0; i < 8; i++)
		__ST7789_WRITE_PIN(
				D8bit_buf[i].port,
				D8bit_buf[i].pin,
				(byte >> i) & 0x01);
#else
	__ST7789_FAST_WRITE_Dn(0, byte & 0x01);
	__ST7789_FAST_WRITE_Dn(1, byte & 0x02);
	__ST7789_FAST_WRITE_Dn(2, byte & 0x04);
	__ST7789_FAST_WRITE_Dn(3, byte & 0x08);
	__ST7789_FAST_WRITE_Dn(4, byte & 0x10);
	__ST7789_FAST_WRITE_Dn(5, byte & 0x20);
	__ST7789_FAST_WRITE_Dn(6, byte & 0x40);
	__ST7789_FAST_WRITE_Dn(7, byte & 0x80);
#endif

}

void st7789_send_cmd(uint8_t cmd)
{
	// Select the LCD's command register
	// Select the LCD controller
	CLR_DC;

	CLR_CS;
	//Put the command on the port
	LCD_WRITE(cmd);
	//Clock the write
	CLR_WR;
	//ST7789_MS_DELAY(1);
	SET_WR;
	// Deselect the LCD controller
	SET_CS;
}

void st7789_send_data(uint8_t data)
{
	// Select the LCD's data register
	SET_DC;
	// Select the LCD controller
	CLR_CS;
	//Put the data on the port
	LCD_WRITE(data);
	//Clock the write
	CLR_WR;
	SET_WR;
	// Deselect the LCD controller
	SET_CS;
}

void st7789_init_new(void)
{
	  SET_RS;
	  CLR_CS;
	  SET_WR;
	  SET_RD;

	  st7789_send_cmd(ST7789_01_SWRESET);
	  ST7789_MS_DELAY(150);//120mS max

	  st7789_send_cmd(ST7789_11_SLPOUT);
	  ST7789_MS_DELAY(120);      //Delay 120ms

	  st7789_send_cmd(ST7789_3A_COLMOD);

	  st7789_send_data(0x03);// Default:
	                     // IFPF[2:0] MCU Interface Color Format
	                     // IFPF[2:0] | Format
	                     //      000b | reserved
	                     //      001b | reserved
	                     //      010b | reserved
	                     //      011b | 12-bit/pixel
	                     //      100b | reserved
	                     //      101b | 16-bit/pixel
	                     //      110b | 18-bit/pixel   <<<<<
	                     //      111b | reserved

	  st7789_send_cmd(ST7789_36_MADCTL);
	  st7789_send_data(0x08);// YXVL RH--
	                 // |||| ||||-- Unused: 0
	                 // |||| ||---- MH: Horizontal Refresh Order
	                 // |||| |        0 = left to right
	                 // |||| |        1 = right to left
	                 // |||| |----- RGB: RGB vs BGR Order
	                 // ||||          0 = RGB color filter panel
	                 // ||||          1 = BGR color filter panel
	                 // ||||------- ML: Vertical Refresh Order
	                 // |||           0 = top to bottom
	                 // |||           1 = bottom to top
	                 // |||-------- MV: Row / Column Exchange
	                 // ||--------- MX: Column Address Order  <<<<<
	                 // |---------- MY: Row Address Order

	  // COLMOD (3Ah): Interface Pixel Format
	  // * This command is used to define the format of RGB picture
	  //   data, which is to be transferred via the MCU interface.


	  // CASET (2Ah): Column Address Set
	  st7789_send_cmd(ST7789_2A_CASET);
	  st7789_send_data(0x00); //Start MSB Start = 0
	  st7789_send_data(0x00); //Start LSB
	  st7789_send_data(0x00); //End MSB End = 249
	  st7789_send_data(240); //End LSB

	  // RASET (2Bh): Row Address Set
	  st7789_send_cmd(ST7789_2B_RASET);
	  st7789_send_data(0x00); //Start MSB Start = 0
	  st7789_send_data(0x00); //Start LSB
	  st7789_send_data(0); //End MSB End = 319
	  st7789_send_data(240); //End LSB

	  st7789_send_cmd(ST7789_13_NORON);

	  st7789_send_cmd(
#if LCD_DRAW_COLOR_INVERSE
			  ST7789_20_INVOFF
#else
			  ST7789_21_INVON
#endif
			  );

	  // DISPON (29h): Display On
	  st7789_send_cmd(ST7789_29_DISPON);
}


union bits8 {
	uint8_t cmn;
	uint8_t b0: 1;
	uint8_t b1: 1;
	uint8_t b2: 1;
	uint8_t b3: 1;
	uint8_t b4: 1;
	uint8_t b5: 1;
	uint8_t b6: 1;
	uint8_t b7: 1;
};

/* bit to RGB */
#define B2RGB(b) ((b) ? (0x0f) : (0x00))
#define B2RGB_H(b) ((b) ? (0x0f) : (0x00))
#define B2RGB_L(b) ((b) ? (0xf0) : (0x00))

void st7789_fill_bw(uint8_t bw)
{
	uint32_t i;
	SET_DC;
	CLR_CS;

	for (i = 0; i < ST7789_FB_SIZE; i++)
	{
#define _HELPME \
	LCD_WRTIE_WR((bw) ? 0xff : 0x00); \
	LCD_WRTIE_WR((bw) ? 0xff : 0x00); \
	LCD_WRTIE_WR((bw) ? 0xff : 0x00);

		_HELPME
		_HELPME
		_HELPME
		_HELPME
	}

	SET_CS;
}

void st7789_draw_pixel(uint8_t x, uint8_t y)
{
	st7789_set_draw_limits(x, x, y, y);
	SET_DC;
	CLR_CS;
	LCD_WRTIE_WR(0xff);
	LCD_WRTIE_WR(0xf0); /* only low byte chapter */
	SET_CS;
}

void st7789_set_draw_limits(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end) {
	st7789_send_cmd(ST7789_2A_CASET); //Column address set
	//Write the parameters for the "column address set" command
	st7789_send_data(0);     //Start MSB = XS[15:8]
	st7789_send_data(x_start); //Start LSB = XS[ 7:0]
	st7789_send_data(0);      //End LSB   = XE[ 7:0]
	st7789_send_data(x_end);        //End MSB   = XE[15:8] 240-1

	//Write the "row address set" command to the LCD
	//RASET (2Bh): Row Address Set
	// * The value of YS [15:0] and YE [15:0] are referred when RAMWR
	//   command comes.
	// * Each value represents one row line in the Frame Memory.
	// * YS [15:0] always must be equal to or less than YE [15:0]
	st7789_send_cmd(ST7789_2B_RASET); //Row address set
	//Write the parameters for the "row address set" command
	//Use 1st quadrant coordinates: 0,0 is lower left, 239,319 is upper right.
	st7789_send_data(0);     //Start MSB = YS[15:8]
	st7789_send_data(y_start); //Start LSB = YS[ 7:0]
	st7789_send_data(0);     //End MSB   = YE[15:8] 320-1
	st7789_send_data(y_end);     //End LSB   = YE[ 7:0]

	//Write the "write data" command to the LCD
	//RAMWR (2Ch): Memory Write
	st7789_send_cmd(ST7789_2C_RAMWR); //write data
}

void st7789_draw_cube(uint8_t x, uint8_t x_size, uint8_t y, uint8_t y_size, uint8_t bw)
{
	x_size += x;
	y_size += y;

	/* check */
	uint8_t flag = y_size % 2;
	uint8_t clr_h = bw ? 0xff : 0x00;
	uint8_t clr_l = bw ? 0xf0 : 0x00;

	while (x_size-- != x) {
		st7789_set_draw_limits(x_size, x_size, y, y + y_size);
		SET_DC;
		CLR_CS;
		for (uint8_t j = y; j < y_size; j += 2) {
				LCD_WRTIE_WR(clr_h);
				LCD_WRTIE_WR(clr_h);
				LCD_WRTIE_WR(clr_h);
		}
		if (!flag) {
			LCD_WRTIE_WR(clr_h);
			LCD_WRTIE_WR(clr_l); /* only low byte chapter */
		}
		SET_CS;
	}
}

void st7789_update(void)
{

}

void st7789_draw_circle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  uint16_t x = (uint16_t)radius;
  uint16_t y = 0;
  int16_t radiusError = 1 - (int16_t) x;

  while (x >= y) {
	//11 O'Clock
	  st7789_draw_pixel(x0 - y, y0 + x);
	//1 O'Clock
	  st7789_draw_pixel(x0 + y, y0 + x);
	//10 O'Clock
	  st7789_draw_pixel(x0 - x, y0 + y);
	//2 O'Clock
	  st7789_draw_pixel(x0 + x, y0 + y);
	//8 O'Clock
	  st7789_draw_pixel(x0 - x, y0 - y);
	//4 O'Clock
	  st7789_draw_pixel(x0 + x, y0 - y);
	//7 O'Clock
	  st7789_draw_pixel(x0 - y, y0 - x);
	//5 O'Clock
	  st7789_draw_pixel(x0 + y, y0 - x);

	y++;
	if (radiusError < 0) {
		radiusError += (int16_t)(2 * y + 1);
	} else {
	  x--;
	  radiusError += 2 * (((int16_t) y - (int16_t) x) + 1);
	}
  }
}


/* the function draws a symbol on the display
 *
 * IMPORTANT!!!
 * for rendering on the display, a 12-bit pixel
 * 	format is used for 3 8-bit transactions,
 * 	data on two pixels is sent to the display,
 * therefore it is not possible to transfer 1 pixel
 *	at a time, therefore a font multiple of 2 along the Ox axis
 *	of the display was taken to draw 2 pixels at a time */
static uint16_t *__ft = Arial_14x22_Table; /* font table ptr */
static uint8_t __fh = 22; /* font height */
static uint8_t __fw = 14; /* font width */
void st7789_a_draw_char(uint8_t x, uint8_t y, uint8_t ch)
{
	const uint16_t *wert;
	uint16_t xn,
			 yn;

	/* shifting the position of the symbol to the
	 * 	rendering window specified in the config */
	x += LCD_WIND_X0;
	y += LCD_WIND_Y0;

	/* i don't know why this is (ya prosto spizdil)
	 * see for details: https://cxem.net/mc/mc311.php */
	ch -= 32;
	wert = &__ft[ch * __fh];

	for (yn = 0; yn < __fh; yn++) {
		register uint16_t mask = 0x8000;
		st7789_set_draw_pos(x, yn + y);
		for (xn = 0; xn < __fw; xn += 2) {
			register uint16_t mask_shift = (mask >> 1);

			SET_DC;
			CLR_CS;

			/* send two pixels by time */
			LCD_WRTIE_WR((wert[yn] & mask) ? 0xff : 0x00);
			LCD_WRTIE_WR(
				((wert[yn] & mask) ? (0xf0) : (0x00))
				| ((wert[yn] & (mask_shift)) ? (0x0f) : (0x00))
			);
			LCD_WRTIE_WR((wert[yn] & (mask_shift)) ? 0xff : 0x00);
			/* 				*/

			SET_CS;

			mask >>= 2;
		}
	}
}


void st7789_a_draw_string(uint8_t x, uint8_t y,
						uint8_t slen /* byte */, uint8_t *str)
{
	uint8_t cnt = 0;
	uint8_t col = 0;
	uint8_t line = 0;
	for (; cnt < slen; cnt++) {
		if (str[cnt] == '\n') {
			line++;
			col = 0;
			continue;
		}

		st7789_a_draw_char(x + col * __fw, y + line * __fh, str[cnt]);
		col++;
	}
}


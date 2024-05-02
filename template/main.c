

#define TEST_ALGORITHM

#include "linealg.h"
#include "algorithm.h"

#include "st7789_240_240.h"
#include "strio.h"
#include "ahb2.h"
#include "gw1ns4c.h"
/*----------------------------------------------------------------------------*/
#include <stdio.h>



/* it is recorded at AHB2_LISTEN_SOUND_ADDR address
 *	1, if you need to read the values from the sensors at the moment
 * 	0, sensor data will be ignored */
#define	AHB2_LISTEN_SOUND_ADDR (0x0004)


/* Declarations*/
void initializeGPIO();
void initializeTimer();
void delayMillis(uint32_t ms);
void initializeUART();
void draw_result(vector2_t *src, fpmath_t bearing);

/* radius of the circle on the display */
#define LCD_RES_CIRCLE_RADIUS 	120
#define LCD_RES_CIRCLE_CNTR_X	120
#define LCD_RES_CIRCLE_CNTR_Y	120

int writeByte(int b)
{
	UART_SendChar(UART0, (char)b);
	return 0;
}
static vector2_t src = {FP(-6.), FP(-12.0)};


void prepare_test_data()
{
    fpmath_t pdt[4];
    for (int i = 0; i < 4; i++) {
    	pdt[i] = la_norm2(&src, &src_ctx.sinfo[i].pos) / SOUND_SPEED;
    }

    fpmath_t dtmin;
    dtmin = pdt[0];

    for (int i = 1; i < 4; i++) {
        if (dtmin > pdt[i]) {
            dtmin = pdt[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        src_ctx.sinfo[i].delay = pdt[i] - dtmin;
    }
}

int main()
{
  	SystemInit(); //Configures CPU for the defined system clock
  	initializeGPIO();
  	initializeTimer();
  	initializeUART();

    /* ======================= display init ======================= */
	st7789_init_new();
	st7789_set_draw_pos(0, 0);
	st7789_fill_bw(0);


#if 0
	st7789_draw_circle_bold(LCD_RES_CIRCLE_CNTR_X,
							LCD_RES_CIRCLE_CNTR_Y,
							LCD_RES_CIRCLE_RADIUS,
							4,
							ST7789_CIRCLE_BOLD_STEP_IN);
    /* ======================= display init ======================= */



	prepare_test_data();
    preparing_values();
    bearing_init();
    fpmath_t p = bearing();


    vector2_t msrc;
  	search_sound_source(&msrc, &p);
	draw_result(&msrc, p);
#else
	char buf[128];
	int len;
	int v = (int)AHB2_READ(0x0020);
	len = fmtbuf(buf, sizeof(buf), "queue:%d\n", v);
	st7789_a_draw_string(50, 50, len, buf);
	AHB2_WRITE(0x0080, 0x000f);
	//AHB2_WRITE(h001Ñ, 0x0001);
#endif
  	/* Infinite loop */
  	while(1)
  	{

	while (v != 0) {
		v = (int)AHB2_READ(0x000C);
		len = fmtbuf(buf, sizeof(buf), "queue:%d\n", v);
		st7789_a_draw_string(0, 0, len, buf);
	}
		v = (int)AHB2_READ(0x000C);
		len = fmtbuf(buf, sizeof(buf), "queue:%d\n", v);
		st7789_a_draw_string(0, 0, len, buf);
		len = fmtbuf(buf, sizeof(buf), "-------------\n");
		st7789_a_draw_string(0, 0, len, buf);
		AHB2_WRITE(0x001C, 0x0001);
  	}

    return 0;
}

void initializeUART()
{
	UART_InitTypeDef uartInitStruct;
	//Enable transmission
	uartInitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	//Disable reception
	uartInitStruct.UART_Mode.UARTMode_Rx = DISABLE;
	//9600 baud rate typical of Arduinos
	uartInitStruct.UART_BaudRate = 115200;
	//Initialize UART0 using the struct configs
	UART_Init(UART0, &uartInitStruct);
}

void initializeGPIO() {
	GPIO_InitTypeDef gpioInitStruct;

	//Select pin7, you can OR pins together to initialize them at the same time
	gpioInitStruct.GPIO_Pin = 	GPIO_Pin_0 |
								GPIO_Pin_1 |
								GPIO_Pin_2 |
								GPIO_Pin_3 |
								GPIO_Pin_4 |
								GPIO_Pin_5 |
								GPIO_Pin_6 |
								GPIO_Pin_7 |
								GPIO_Pin_10 |
								GPIO_Pin_11 |
								GPIO_Pin_12 |
								GPIO_Pin_13 |
								GPIO_Pin_15;

	//Set selected pins as output (see GPIOMode_TypeDef in gw1ns4c_gpio.h)
	gpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;

	//Disable interrupts on selected pins (see GPIOInt_TypeDef)
	gpioInitStruct.GPIO_Int = GPIO_Int_Disable;

	//Initialize the GPIO using the configured init struct
	//GPIO0 is a pointer containing the memory address of the GPIO APB peripheral
	GPIO_Init(GPIO0, &gpioInitStruct);
}


void initializeTimer() {
	TIMER_InitTypeDef timerInitStruct;

	timerInitStruct.Reload = 0UL;

	//Disable interrupt requests from timer for now
	timerInitStruct.TIMER_Int = DISABLE;

	//Disable timer enabling/clocking from external pins (GPIO)
	timerInitStruct.TIMER_Exti = TIMER_DISABLE;

	TIMER_Init(TIMER0, &timerInitStruct);
	TIMER_StopTimer(TIMER0);
  }


#define CYCLES_PER_MILLISEC (SystemCoreClock / 1000UL)
void delayMillis(uint32_t ms) {
	TIMER_StopTimer(TIMER0);
	//Reset timer just in case it was modified elsewhere
	TIMER_SetValue(TIMER0, 0);
	TIMER_EnableIRQ(TIMER0);

	uint32_t reloadVal = CYCLES_PER_MILLISEC * ms;
	//Timer interrupt will trigger when it reaches the reload value
	TIMER_SetReload(TIMER0, reloadVal);

	TIMER_StartTimer(TIMER0);
	//Block execution until timer wastes the calculated amount of cycles
	while (TIMER_GetIRQStatus(TIMER0) != SET);

	TIMER_StopTimer(TIMER0);
	TIMER_ClearIRQ(TIMER0);
	TIMER_SetValue(TIMER0, 0);
}


uint16_t font_colon[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [:]
};
uint16_t font_r[] =
{
	0x0000,0x0000,0x0000,0x0000,0x31C0,0x1BE0,0x1C70,0x1820,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [r]
};
uint16_t font_a[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0FC0,0x1FE0,0x3870,0x3030,0x0030,0x03F0,0x1FF0,0x3C30,0x3030,0x3070,0x38F0,0x1FB0,0x0F18,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [a]
};
uint16_t font_dot[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [.]
};
uint16_t font_numbers_table[] =
{
	0x0780,0x0FC0,0x1CE0,0x1860,0x3030,0x3030,0x3030,0x3330,0x3330,0x3030,0x3030,0x3030,0x3030,0x1860,0x1CE0,0x0FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [0]
	0x0180,0x0180,0x0380,0x0F80,0x1D80,0x1180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [1]
	0x07C0,0x1FE0,0x1860,0x3030,0x3030,0x0030,0x0030,0x0060,0x0060,0x00C0,0x0180,0x0700,0x0C00,0x1800,0x3000,0x3FF0,0x3FF0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [2]
	0x0F80,0x1FC0,0x18E0,0x3060,0x3060,0x0060,0x00C0,0x07C0,0x07C0,0x0060,0x0030,0x0030,0x3030,0x3030,0x1860,0x1FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [3]
	0x00C0,0x01C0,0x01C0,0x03C0,0x03C0,0x06C0,0x0CC0,0x0CC0,0x18C0,0x18C0,0x30C0,0x3FF0,0x3FF0,0x00C0,0x00C0,0x00C0,0x00C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [4]
	0x3FE0,0x3FE0,0x3000,0x3000,0x3000,0x3780,0x3FC0,0x3860,0x3070,0x0030,0x0030,0x0030,0x3030,0x3070,0x18E0,0x1FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [5]
	0x07C0,0x0FE0,0x1C70,0x1830,0x3800,0x3000,0x33C0,0x37E0,0x3860,0x3030,0x3030,0x3030,0x3030,0x1870,0x1860,0x0FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [6]
	0x3FF0,0x3FF0,0x0030,0x0060,0x00C0,0x00C0,0x0180,0x0180,0x0300,0x0300,0x0600,0x0600,0x0600,0x0400,0x0C00,0x0C00,0x0C00,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [7]
	0x0780,0x0FC0,0x1CE0,0x1860,0x1860,0x1860,0x0CC0,0x0300,0x1FC0,0x1860,0x3030,0x3030,0x3030,0x3030,0x1860,0x1FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [8]
	0x0780,0x1FC0,0x1C60,0x3820,0x3030,0x3030,0x3030,0x3030,0x1870,0x1FB0,0x0F30,0x0030,0x0070,0x3060,0x38E0,0x1FC0,0x0F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [9]
};


/* the definition returns a pointer to a string
 * 	in the font_numbers_table[] array, which corresponds
 * 	to the font of the transmitted digit character */
#define __GETP_NUM_WRET(ch) (&font_numbers_table[(ch - '0') * __CH_H])

static void __draw_result_float_str(uint8_t x0, uint8_t y0, uint8_t slen /* byte */, uint8_t *str)
{
	uint8_t cnt = 0;
	uint8_t col = 0;
	for (; cnt < slen; cnt++, col++) {
		if (str[cnt] == '.')
			__st7789_a_draw_char_raw(x0 + col * __CH_W, y0, font_dot);
		else
			__st7789_a_draw_char_raw(x0 + col * __CH_W, y0, __GETP_NUM_WRET(str[cnt]));

	}
}


void draw_result(vector2_t *src, fpmath_t bearing)
{
	uint8_t buf[16];
	uint8_t len;


	/* 'a' */
	__st7789_a_draw_char_raw(LCD_WIND_X0,
							40 + LCD_WIND_Y0,
								font_a);
	/* ':' */
	__st7789_a_draw_char_raw(LCD_WIND_X0 + __CH_W,
							40 + LCD_WIND_Y0,
							font_colon);

	/* angle in degrees */
	len = (uint8_t)ftos(bearing * div_180_pi, buf, LCD_RES_AFTERPOINT);
	__draw_result_float_str(LCD_WIND_X0 + __CH_W * 2,
							40 + LCD_WIND_Y0,
							len, buf);

	/* 'r' */
	__st7789_a_draw_char_raw(LCD_WIND_X0,
							45 + LCD_WIND_Y0 + __CH_H,
							font_r);
	/* ':' */
	__st7789_a_draw_char_raw(LCD_WIND_X0 + __CH_W,
							45 + LCD_WIND_Y0 + __CH_H,
							font_colon);

	/* distance to sound source */
	len = (uint8_t)ftos(la_pnorm2(src->x, src->y), buf, LCD_RES_AFTERPOINT);
	__draw_result_float_str(LCD_WIND_X0 + __CH_W * 2,
							45 + LCD_WIND_Y0 + __CH_H,
							len, buf);

	/* draw point marker */
	st7789_draw_circle_bold(
			 120 + (int16_t)((LCD_RES_CIRCLE_RADIUS - 18) * mycos(bearing)),
			 120 - (int16_t)((LCD_RES_CIRCLE_RADIUS - 18) * mysin(bearing)),
			 10, 9, ST7789_CIRCLE_BOLD_STEP_IN);
}

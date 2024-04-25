

#define TEST_ALGORITHM

#include "linealg.h"
#include "algorithm.h"

#include "st7789_240_240.h"
#include "strio.h"

#include "gw1ns4c.h"
/*----------------------------------------------------------------------------*/
#include <stdio.h>

/* Declarations*/
void initializeGPIO();
void initializeTimer();
void initializeUART();
void delayMillis(uint32_t ms);

int writeByte(int b)
{
	UART_SendChar(UART0, (char)b);
	return 0;
}
static vector2_t src = {FP(2.0), FP(5.0)};

#ifdef TEST_ALGORITHM
#if 0

volatile int hardfault = 0;

void hardfault_handler()
{
	fmtdebug("----FATAL HARDWARE FUALT----\n\r");
	while (1) {};
}

void print_src_ctx_info()
{
	fmtdebug("----src_ctx_inf----\n\r");
	for (int i = 0; i < 4; i++)
	{

		fmtdebug("%d, pos:(%f,%f), delay:%f\n\r",
				i,
				(src_ctx.sinfo[i].pos.x),
				(src_ctx.sinfo[i].pos.y),
				(src_ctx.sinfo[i].delay));
	}
	fmtdebug("----src_ctx_inf----\n\r");
}

void print_src_ctx_sorted_info()
{
	fmtdebug("----src_ctx_sorted_inf----\n\r");
	for (int i = 0; i < 4; i++)
	{
		double d = src_ctx.sinfo_sorted[i]->pos.x;
		fmtdebug("%d, pos:(%f,%f), delay:%f\n\r",
				i,
				src_ctx.sinfo_sorted[i]->pos.x,
				src_ctx.sinfo_sorted[i]->pos.y,
				src_ctx.sinfo_sorted[i]->delay);
	}
	fmtdebug("----src_ctx_sorted_inf----\n\r");
}
#endif

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
#endif /* TEST_ALGORITHM  */



int main()
{
  	SystemInit(); //Configures CPU for the defined system clock
  	initializeGPIO();
  	initializeTimer();
  	initializeUART();

#ifdef TEST_ALGORITHM
  	//strio_set_f_putbyte(writeByte);

  	//printf("\n\r");
	prepare_test_data();
    preparing_values();
	//print_src_ctx_info();
    //print_src_ctx_sorted_info();
    bearing_init();
    fpmath_t p = bearing();
    //fmtdebug("bearing rad:%f,angle:%f\n\r", p, RAD_TO_ANGLE(p));


#if 1
    //fmtdebug("start search!\n\r");
    vector2_t msrc;
  	search_sound_source(&msrc, p);
  	//fmtdebug("src: (%f,%f)\n\r", msrc.x, msrc.y);
  	//fmtdebug("end search!\n\r");
#else
  	for (fpmath_t i = FP(1.0); i < 10.0; i += FP(1.0)) {
  		vector2_t test;
  		test.x = i / FP(2.0);
  		test.y = i;
  		fpmath_t res = deviation_src_ru2377594C1(&test);
  		fmtdebug("src: (%f, %f), err: %f\r\n", test.x, test.y, res);
  	}
#endif
#endif /* TEST_ALGORITHM */

	st7789_init_new();
	st7789_set_draw_pos(0, 0);
	st7789_fill_bw(0);
	st7789_draw_circle_bold(120, 120, 120, 4, ST7789_CIRCLE_BOLD_STEP_IN);
	//st7789_a_draw_char(0, 0, 'a');
	char buf[] = "a:134.64\nr:2.54";
	st7789_a_draw_string(0, 40, sizeof(buf) - 1, buf);
  	/* Infinite loop */
  	while(1)
  	{

#if 0
  		//fmtdebug("coreClock: %d, bearing: %d\n\r", SystemCoreClock, p++);
  		GPIO_ResetBit(GPIO0, GPIO_Pin_6);
  		delayMillis(500);
  		GPIO_SetBit(GPIO0, GPIO_Pin_6);
  		delayMillis(500);
#else
#	if 0
  		st7789_set_draw_pos(0, 0);
  		st7789_draw_pixel(100, 100);
  		st7789_fill_bw(0);
  		st7789_set_draw_pos(0, 0);
		st7789_set_draw_pos(0, 0);
  		st7789_fill_bw(1);
#	endif
#endif
  	}


    return 0;
}

#if 1
void initializeUART()
{
	UART_InitTypeDef uartInitStruct;
	//Enable transmission
	uartInitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	//Disable reception
	uartInitStruct.UART_Mode.UARTMode_Rx = DISABLE;
	//9600 baud rate typical of Arduinos
	uartInitStruct.UART_BaudRate = 115200L;
	//Initialize UART0 using the struct configs
	UART_Init(UART0, &uartInitStruct);
}
#endif

#if 1
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
								GPIO_Pin_14 |
								GPIO_Pin_15;

	//Set selected pins as output (see GPIOMode_TypeDef in gw1ns4c_gpio.h)
	gpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;

	//Disable interrupts on selected pins (see GPIOInt_TypeDef)
	gpioInitStruct.GPIO_Int = GPIO_Int_Disable;

	//Initialize the GPIO using the configured init struct
	//GPIO0 is a pointer containing the memory address of the GPIO APB peripheral
	GPIO_Init(GPIO0, &gpioInitStruct);
}
#endif
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

#if 1
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
#endif

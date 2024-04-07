

#define TEST_ALGORITHM

#ifdef TEST_ALGORITHM
#include "linealg.h"
#include "algorithm.h"
#endif /* TEST_ALGORITHM */

#include "strio.h"

#include "gw1ns4c.h"
/*----------------------------------------------------------------------------*/
#include <stdio.h>

/* Declarations*/
void initializeGPIO();
void initializeTimer();
void initializeUART();
void delayMillis(uint32_t ms);


#ifdef TEST_ALGORITHM
static vector2_t src = {8.0f, 6.0f};
#if 1

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

int writeByte(int b)
{
	UART_SendChar(UART0, (char)b);
	return 0;
}

int main()
{
  	SystemInit(); //Configures CPU for the defined system clock
  	initializeGPIO();
  	initializeTimer();
  	initializeUART();

  	strio_set_f_putbyte(writeByte);

  	//printf("\n\r");
#ifdef TEST_ALGORITHM
	prepare_test_data();
    preparing_values();
	//print_src_ctx_info();
    //print_src_ctx_sorted_info();
    bearing_init();
    fpmath_t p = bearing();
    fmtdebug("bearing rad:%f,angle:%f\n\r", p, RAD_TO_ANGLE(p));
#endif /* TEST_ALGORITHM */


    fmtdebug("start search!\n\r");
    vector2_t msrc;
  	search_sound_source(&msrc, p);
  	fmtdebug("src: (%f,%f)\n\r", msrc.x, msrc.y);
  	fmtdebug("end search!\n\r");

  	/* Infinite loop */
  	while(1)
  	{
  		//fmtdebug("coreClock: %d, bearing: %d\n\r", SystemCoreClock, p++);
  		GPIO_ResetBit(GPIO0, GPIO_Pin_6);
  		delayMillis(500);
  		GPIO_SetBit(GPIO0, GPIO_Pin_6);
  		delayMillis(500);
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
	gpioInitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;

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

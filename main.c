#include <LPC17xx.h>
#include <stdbool.h>
#include "sound.h"
#define PRESCALE (3000-1)

void timer_init(void);
void delay(unsigned long int ms);
int main(void)
{
	timer_init();
	LPC_GPIO1->FIODIR |= 1<<23;
	while (true) {
		LPC_GPIO1->FIOSET = 1<<23;
		delay(1);
		LPC_GPIO1->FIOCLR = 1<<23;
		delay(1);
}
}

void timer_init(void)
{
	/*Assuming that PLL0 has been setup with CCLK = 100Mhz and PCLK = 25Mhz.*/
	LPC_SC->PCONP |= (1<<1); //Power up TIM0. By default TIM0 and TIM1 are enabled.
	//LPC_SC->PCLKSEL0 &= ~(0x3<<3); //Set PCLK for timer = CCLK/4 = 100/4 (default)

	LPC_TIM0->CTCR = 0x0;
	LPC_TIM0->PR = PRESCALE; //Increment TC at every 29999+1 clock cycles
	//3000 clock cycles @3Mhz = 0.1 mS

	LPC_TIM0->TCR = 0x02; //Reset Timer
}

void delay(unsigned long int milliseconds) //Using Timer0
{
	LPC_TIM0->TCR = 0x02; //Reset Timer

	LPC_TIM0->TCR = 0x01; //Enable timer

	while(LPC_TIM0->TC < milliseconds); //wait until timer counter reaches the desired delay

	LPC_TIM0->TCR = 0x00; //Disable timer
}


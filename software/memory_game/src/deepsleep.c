#include "deepsleep.h"
#include "ch32fun.h"
#include <stdint.h>

void deepsleep_init(){
    // enable power interface module clock
	RCC->APB1PCENR |= RCC_APB1Periph_PWR;

	// enable low speed oscillator (LSI)
	RCC->RSTSCKR |= RCC_LSION;
	while ((RCC->RSTSCKR & RCC_LSIRDY) == 0) {}

	// enable AutoWakeUp event
	EXTI->EVENR |= EXTI_Line9;
	EXTI->FTENR |= EXTI_Line9;

	// configure AWU prescaler
	PWR->AWUPSC |= PWR_AWU_Prescaler_4096;

    // enable AWU
	PWR->AWUCSR |= (1 << 1);

	// select standby on power-down
	PWR->CTLR |= PWR_CTLR_PDDS;
}

void deepsleep(uint32_t sleep_time){
 	// configure AWU window comparison value
	PWR->AWUWR &= ~0x3f; // zero out the value
	PWR->AWUWR |= sleep_time; // 63 is about 1 second  

	// peripheral interrupt controller send to deep sleep
	PFIC->SCTLR |= (1 << 2);
}

// Note: Will need this on wake
// __WFE();
// SystemInit(); // restore system clock to full speed
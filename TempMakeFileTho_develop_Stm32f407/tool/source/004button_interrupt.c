/*
 * 004button_interrupt.c
 *
 *  Created on: Oct 10, 2022
 *      Author: ADMIN
 */

#include <string.h>
#include "stm32f407xx.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	// this will introduce ~200ms delay when system clock is 16MHz
	for (uint32_t i = 0; i < 500000 / 2; i++)
		;
}

int main(void)
{

	GPIO_Handle_t GpioLed, GPIOBtn;

	// gán tất cả các giá trị thành 0
	// memset(&GpioLed,0,sizeof(GpioLed));
	// memset(&GPIOBtn,0,sizeof(GpioLed));

	// this is led gpio configuration
	GpioLed.pGPIOx = GPIOC;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed);

	GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_11, GPIO_PIN_RESET);

	// this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOB;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GPIOBtn);

	// IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	while (1)
		;
}

void EXTI15_10_IRQHandler(void)
{
	delay();						  // 200ms . wait till button de-bouncing gets over
	GPIO_IRQHandling(GPIO_PIN_NO_11); // clear the pending event from exti line
	GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_11);
}

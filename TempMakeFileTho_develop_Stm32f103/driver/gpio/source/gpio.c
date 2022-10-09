#include "stm32f10x.h"

void gpio_initPB10(void)
{
	RCC->APB2ENR |= 0x08; /*  --> Anabling Preiph GPIOB */

	GPIOB->CRH &= 0xFFFFF0FF; /* Reset the PORT B PIN 10 */
	GPIOB->CRH |= 0x00000300; /* Set Port B PIN 10 as Output  */
	GPIOB->ODR &= ~0x0400;	  /* Clean Port B Pin 10 */
}

void gpio_initPB11(void)
{
	RCC->APB2ENR |= 0x08; /*  --> Anabling Preiph GPIOB */

	GPIOB->CRH &= 0xFFFF0FFF; /* Reset the PORT B PIN 11 */
	GPIOB->CRH |= 0x00003000; /* Set Port B PIN 11 as Output  */
	GPIOB->ODR &= ~0x0800;	  /* Clean Port B Pin 11 */
}

void gpio_SetPinPB10(void)
{
	GPIOB->ODR |= 0x0400;
}

void gpio_ResetPinPB10(void)
{
	GPIOB->ODR &= ~0x0400;
}

void gpio_SetPinPB11(void)
{
	GPIOB->ODR |= 0x0800;
}

void gpio_ResetPinPB11(void)
{
	GPIOB->ODR &= ~0x0800;
}

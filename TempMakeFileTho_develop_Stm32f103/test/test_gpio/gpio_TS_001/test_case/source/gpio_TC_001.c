#include "stm32f10x.h"
#include "gpio.h"
#include "result.h"

/****************************************************************************************
 *                           Prototypes of the startup file
 *****************************************************************************************/

/****************************************************************************************
 *                           Prototypes of my application
 *****************************************************************************************/

/*************************************************************************************************
 *                            Start with my code
 **************************************************************************************************/
void gpio_TC_001(void)
{
	RESET_RESULT();

	gpio_initPB10();
	gpio_SetPinPB10();

	gpio_initPB11();
	gpio_SetPinPB11();

	CHECK_RESULT(1, 1);
}

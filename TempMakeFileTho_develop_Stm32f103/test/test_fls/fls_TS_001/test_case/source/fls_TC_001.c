#include "stm32f10x.h"
#include "fls.h"
#include "result.h"

uint8_t u8WriteBuff[8]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8};
uint8_t u8ReadBuff[8]={0};
/****************************************************************************************
*                           Prototypes of the startup file 
*****************************************************************************************/

/****************************************************************************************
*                           Prototypes of my application  
*****************************************************************************************/

/*************************************************************************************************
*                            Start with my code
**************************************************************************************************/
void fls_TC_001(void)
{
	FlashStatus ResultTest;
	uint8_t u8Count = 0;
	
	/* Erase at address: 0x08001000 */
	ResultTest = Flash_Erase(0x08001000, 100000);
	CHECK_RESULT(ResultTest, FLASH_NO_ERRORS);
	
	/* Write at address: 0x08001000 */
    ResultTest = Flash_Write(0x08001000, u8WriteBuff ,8);
	CHECK_RESULT(ResultTest, FLASH_NO_ERRORS);
	
	/* Write at address: 0x08001000 */
    ResultTest = Flash_Read(0x08001000, u8ReadBuff ,8);
	CHECK_RESULT(ResultTest, FLASH_NO_ERRORS);
	
	/* Checking read data*/
	for (u8Count =0; u8Count < 8; u8Count++)
	{
		CHECK_RESULT(u8WriteBuff[u8Count], u8ReadBuff[u8Count]);
	}
	
}



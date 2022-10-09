
typedef enum
{
	FLASH_ERRORS = 0U,    /* There is a error */
	FLASH_NO_ERRORS,      /* There is no errors */
	FLASH_PENDING,        /* Working is pending  */
	FLASH_ERRORS_TIMEOUT  /* There is a error due to timeout */
} FlashStatus;

void Flash_Unlock(void);
FlashStatus Flash_Erase(volatile uint32_t u32StartAddr, uint32_t u32TimeOut);
FlashStatus Flash_Write(volatile uint32_t u32StartAddr, uint8_t* u8BufferWrite, uint32_t u32Length);
FlashStatus Flash_Read(volatile uint32_t u32StartAddr, uint8_t* u8BufferRead, uint32_t u32Length);
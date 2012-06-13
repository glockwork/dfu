
#ifndef __DFU_CONFIG_H_
#define __DFU_CONFIG_H_

#define PIN_FLASH_MODE GPIO_Pin_14
#define PIN_OP_MODE    GPIO_Pin_15
#define PIN_PORT       GPIOC
#define PIN_CLK        RCC_AHBPeriph_##PIN_PORT
#define DFU_FILE_NAME  firmware.bin
#define FIRMWARE_START_ADDRESS 0x8003000
#define FLASH_SECTOR_SIZE 512

#endif



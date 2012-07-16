
#ifndef __I2C_H_
#define __I2C_H_

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "queue.h"

/*
//void i2cSetEn( uint8_t en );
//void i2cConfig( uint8_t host, uint16_t address, uint8_t _10bit, uint16_t speed );
//void i2cSetTimeout( uint32_t timeout );
//uint8_t i2cSendByte( uint16_t address, uint8_t value );

#define HDW_I2C                         I2C1
#define HDW_I2C_CLK                     RCC_APB1Periph_I2C1
#define HDW_I2C_SCL_PIN                 GPIO_Pin_6                  // PB.06
#define HDW_I2C_SCL_GPIO_PORT           GPIOB                       // GPIOB
#define HDW_I2C_SCL_GPIO_CLK            RCC_APB2Periph_GPIOB
#define HDW_I2C_SDA_PIN                 GPIO_Pin_7                  // PB.07
#define HDW_I2C_SDA_GPIO_PORT           GPIOB                       // GPIOB
#define HDW_I2C_SDA_GPIO_CLK            RCC_APB2Periph_GPIOB
#define HDW_I2C_SMBUSALERT_PIN          GPIO_Pin_5                  // PB.05
#define HDW_I2C_SMBUSALERT_GPIO_PORT    GPIOB                       // GPIOB
#define HDW_I2C_SMBUSALERT_GPIO_CLK     RCC_APB2Periph_GPIOB
#define HDW_I2C_DR                      ((uint32_t)0x40005410)
*/
#define I2C_PORT     GPIOB
#define RCC_I2C_GPIO_CLK  RCC_APB2Periph_GPIOB

typedef struct
{
    uint8_t  sendCnt, 
             receiveCnt;
    uint8_t  master;
    uint8_t  status;
    
    I2C_TypeDef * i2c;
    uint8_t  address;
    uint32_t speed;
    uint32_t timeout;
    uint32_t elapsed;
    xQueueHandle sendQueue;
    xQueueHandle receiveQueue;
} TI2C;

TI2C * i2c( uint8_t index );
void i2cInit( uint8_t index );
void i2cSetEn( uint8_t index, uint8_t en );
void i2cConfig( uint8_t index, uint8_t master, uint8_t address, uint32_t speed );
xQueueHandle sendQueue( uint8_t index );
xQueueHandle receiveQueue( uint8_t index );

#endif




#ifndef __GPIO_H_
#define __GPIO_H_

#include "stm32f10x.h"

void gpioInit( void );
void gpioConfig( uint8_t port, uint16_t pins, uint8_t state );
void gpioSet( uint8_t port, uint16_t pins, uint16_t vals );
uint16_t gpio( uint8_t port, uint16_t pins );



#endif






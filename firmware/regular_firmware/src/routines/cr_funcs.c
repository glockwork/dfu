
#include "cr_funcs.h"
#include "cr_usbio.h"
#include "config.h"

#include "gpio.h"

uint8_t g_funcId = FUNC_IDLE;

xQueueHandle invokeFunc( uint8_t funcId )
{
    g_funcId = funcId;
}

void crFuncs( xCoRoutineHandle xHandle, 
              unsigned portBASE_TYPE uxIndex )
{
    static uint8_t     * buf;
    static uint8_t     * out;
    static uint16_t    res16;
    static portBASE_TYPE cr;
    static xQueueHandle  q;
    buf = buffer();
    q   = fromMcu();
    crSTART( xHandle );

    for ( ;; )
    {
        g_funcId = FUNC_IDLE;
        crDELAY( xHandle, 1 );
        switch ( g_funcId )
        {
            case FUNC_GPIO_CONFIG:
                gpioConfig( buf[0], 
                            *(uint16_t *)(&(buf[1])), 
                            buf[3] );
                break;
            case FUNC_GPIO_SET:
                gpioSet( buf[0], 
                         *(uint16_t *)(&(buf[1])), 
                         *(uint16_t *)(&(buf[3])) );
                break;
            case FUNC_GPIO:
                res16 = gpio( buf[0], 
                              *(uint16_t *)(&(buf[1])) ); 
                out = (uint8_t *)&res16;
                crQUEUE_SEND( xHandle, q, out,     0, &cr );
                crQUEUE_SEND( xHandle, q, &out[1], 0, &cr );
                break;
        }
    }

    crEND();
}




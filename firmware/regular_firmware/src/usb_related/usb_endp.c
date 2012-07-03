/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
// FreeRTOS interaction.
#include "cr_usbio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
    /*xQueueHandle q = fromMcu();
    portBASE_TYPE cr = pdFALSE;
    uint8_t i = 0;
    while ( crQUEUE_RECEIVE_FROM_ISR( q, &(USART_Rx_Buffer[i]), &cr ) == pdTRUE )
    {
        i++;
    }
 
    UserToPMABufferCopy( USART_Rx_Buffer, ENDP1_TXADDR, i );
    SetEPTxCount( ENDP1, i );
    SetEPTxValid( ENDP1 );*/
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{
    static uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
    uint16_t USB_Rx_Cnt;
    uint16_t i;
 
    /* Get the received data buffer and update the counter */
    USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, USB_Rx_Buffer);
    if ( USB_Rx_Cnt > 0 )
    {
        xQueueHandle q = toMcu();
        portBASE_TYPE rc = pdFALSE;
        for (i=0; i<USB_Rx_Cnt; i++)
        {
            //USB_SetLeds(USB_Rx_Buffer[i]);
            rc = crQUEUE_SEND_FROM_ISR( q, &USB_Rx_Buffer[i], rc );
        }
    }
  
    /* Enable the receive of data on EP3 */
    SetEPRxValid(ENDP3);
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SOF_Callback(void)
{
 static uint8_t USART_Rx_Buffer[ BULK_MAX_PACKET_SIZE ];

 //static uint32_t FrameCount = 0;
  
  if(bDeviceState == CONFIGURED)
  {
    //if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
    //{
      /* Reset the frame counter */
      //FrameCount = 0;
      
      /* Check the data to be sent through IN pipe */

      xQueueHandle q = fromMcu();
      portBASE_TYPE cr = pdFALSE;
      uint8_t i = 0;
      while ( crQUEUE_RECEIVE_FROM_ISR( q, &(USART_Rx_Buffer[i]), &cr ) == pdTRUE )
      {
          i++;
      }
 
      if ( i > 0 )
      {
          UserToPMABufferCopy( USART_Rx_Buffer, ENDP1_TXADDR, i );
          SetEPTxCount( ENDP1, i );
          SetEPTxValid( ENDP1 );
      }
    //}
  }  
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/


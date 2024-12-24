/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
// 
#include "main.h"
#include "usart.h"

/* ----------------------- static functions ---------------------------------*/
void prvvUARTTxReadyISR( void );
void prvvUARTRxISR( void );

extern UART_HandleTypeDef huart5;

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
	#if 1
	if(xRxEnable){
		// enable usart RXNE IT
		//MB_EN_RECV;
		__HAL_UART_ENABLE_IT(&huart5, UART_IT_RXNE);
	} else{
		// disable usart RXNE IT
		//MB_EN_TRAN;
		__HAL_UART_DISABLE_IT(&huart5, UART_IT_RXNE);
	}

	if(xTxEnable){
		// enable usart TXE IT
		__HAL_UART_ENABLE_IT(&huart5, UART_IT_TXE);

	}else{
		// disable usart TXE IT
		 __HAL_UART_DISABLE_IT(&huart5, UART_IT_TXE);
	}
	#endif
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
	if(HAL_UART_Transmit (&huart5 ,(uint8_t *)&ucByte,1,0x01) != HAL_OK ){
		 return FALSE;
	 } else{
		 return TRUE;
	 }
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
	if(HAL_UART_Receive (&huart5 ,(uint8_t *)pucByte,1,0x01) != HAL_OK ){
		return FALSE;
	} else {
		return TRUE;
	}

}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR( void )
{
  pxMBFrameCBTransmitterEmpty();
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR( void )
{
  pxMBFrameCBByteReceived();
}

/**
  * @brief 
  * @param  None
  * @retval None
  */
#if 0
void USART3_IRQHandler(void)
{
	OSIntEnter();	
  	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
  	{
    	prvvUARTRxISR();  
    	USART_ClearITPendingBit(USART3, USART_IT_RXNE);   
  	}
  
  	if(USART_GetITStatus(USART3, USART_IT_TC) == SET)
  	{
    	prvvUARTTxReadyISR();
    	USART_ClearITPendingBit(USART3, USART_IT_TC);
  	}
	OSIntExit();
}
#endif

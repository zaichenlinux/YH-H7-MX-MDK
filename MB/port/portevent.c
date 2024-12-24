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
 * File: $Id: portevent.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "main.h"

#include "cmsis_os.h"
//extern OS_EVENT *qMsgMdb;
//static u8 errQMsgMdb;

//extern osMessageQueueId_t Mb_Event_QueueHandle;

/* ----------------------- Variables ----------------------------------------*/
//static eMBEventType   eQueuedEvent;
/* ----------------------- Start implementation -----------------------------*/
/**
  * @brief  
  * @param  None
  * @retval None
  */
 #if 0
BOOL
xMBPortEventInit( void )
{
//    xEventInQueue = FALSE;
    return TRUE;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
BOOL
xMBPortEventPost( eMBEventType eEvent )
{
	#if 0
	eQueuedEvent = eEvent;
	OSQPost(qMsgMdb, &eQueuedEvent);
	return TRUE;
	#endif

	#if 1
	eQueuedEvent = eEvent;
	osMessageQueuePut (Mb_Event_QueueHandle, &eQueuedEvent, 0, 0xffff);
	return TRUE;
	#endif
}

/**
  * @brief 
  * @param  None
  * @retval None
  */
BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
	#if 0
	*eEvent = *((eMBEventType*)OSQPend(qMsgMdb, 0, &errQMsgMdb));
	return TRUE;
	#endif

	#if 1
	osMessageQueueGet (Mb_Event_QueueHandle, (void *)eEvent, NULL, 0xffff); 
	return TRUE;
	#endif
}
#endif

#if 1
	static eMBEventType eQueuedEvent;
	static BOOL     xEventInQueue;

	/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortEventInit( void )
{
    xEventInQueue = FALSE;
    return TRUE;
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
    xEventInQueue = TRUE;
    eQueuedEvent = eEvent;
    return TRUE;
}

BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
    BOOL            xEventHappened = FALSE;

    if( xEventInQueue )
    {
        *eEvent = eQueuedEvent;
        xEventInQueue = FALSE;
        xEventHappened = TRUE;
    }
    return xEventHappened;
}


#endif
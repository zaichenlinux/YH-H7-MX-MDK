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
 * File: $Id: port.h,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#ifndef _PORT_H
#define _PORT_H

#include <assert.h>
#include <inttypes.h>

//#include "stm32f4xx.h"
#include "main.h"
#include "cmsis_os.h"

#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION( )   __set_PRIMASK(1) 
#define EXIT_CRITICAL_SECTION( )    __set_PRIMASK(0)    

typedef uint8_t         BOOL;

typedef unsigned char   UCHAR;
typedef char            CHAR;

typedef uint16_t        USHORT;
typedef int16_t         SHORT;

typedef uint32_t        ULONG;
typedef int32_t         LONG;

#if 1
#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif
#endif
// 下面的IO口操作，不同的单片机有不同寄存器，需要修改
#if 0
#define GPIO_On(gpio,pin)     (gpio)->BSRR = (pin)
#define GPIO_Off(gpio,pin)    (gpio)->BRR = (pin)
#define GPIO_Toggle(gpio,pin) (gpio)->ODR ^= (pin)
#define GPIO_Get(gpio,pin)    readbit((gpio)->IDR,(pin))


/* 485配置  *****************************************************************/
// USART3

#define GPIO_USARTxx_TX        GPIOB
#define PIN_USARTxx_TX         GPIO_Pin_10

#define GPIO_USARTxx_RX        GPIOB
#define PIN_USARTxx_RX         GPIO_Pin_11

#define GPIO_485_RD           GPIOB
#define PIN_485_RD            GPIO_Pin_9

#define RS485_EnterSend()			GPIO_On(GPIO_485_RD, PIN_485_RD)
#define RS485_EnterReceive()	GPIO_Off(GPIO_485_RD, PIN_485_RD)
#endif



#endif

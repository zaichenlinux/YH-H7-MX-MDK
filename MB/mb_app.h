/*
 * mb_app.h
 *
 *  Created on: Apr 11, 2024
 *      Author: chenzai
 */

#ifndef MB_APP_H_
#define MB_APP_H_

/* Includes ------------------------------------------------------------------*/
	#include "main.h"
	
typedef enum {FALSE = 0, TRUE = !FALSE} bool, boolean;
#ifndef BV
	#define BV(bit) (1<<(bit))
#endif

#ifndef CBI
	#define CBI(reg,bit) reg &= ~(BV(bit))
#endif

#ifndef SBI
	#define SBI(reg,bit) reg |= (BV(bit))
#endif

#ifndef is_SBI
	#define is_SBI(reg,bit) (reg & BV(bit))
	#define is_CBI(reg,bit) (!is_SBI(reg,bit))
#endif
/* Exported macro ------------------------------------------------------------*/
// function code 0x01 coil status 
#define	HMI_OUT_01	((ucRegCoilsBuf[0])&(1<<0) )	// 0X_1
#define	HMI_OUT_02	((ucRegCoilsBuf[0])&(1<<1) )	// 0X_2
#define	HMI_OUT_03	((ucRegCoilsBuf[0])&(1<<2) )	// 0X_3
#define	HMI_OUT_04	((ucRegCoilsBuf[0])&(1<<3) )	// 0X_4
#define	HMI_OUT_05	((ucRegCoilsBuf[0])&(1<<4) )	// 0X_5
#define	HMI_OUT_06	((ucRegCoilsBuf[0])&(1<<5) )	// 0X_6
#define	HMI_OUT_07	((ucRegCoilsBuf[0])&(1<<6) )	// 0X_7
#define	HMI_OUT_08	((ucRegCoilsBuf[0])&(1<<7) )	// 0X_8

#define	HMI_OUT_01_ON	SBI(ucRegCoilsBuf[0], 0)
#define	HMI_OUT_02_ON	SBI(ucRegCoilsBuf[0], 1)
#define	HMI_OUT_03_ON	SBI(ucRegCoilsBuf[0], 2)
#define	HMI_OUT_04_ON	SBI(ucRegCoilsBuf[0], 3)

#define	HMI_OUT_01_OFF	CBI(ucRegCoilsBuf[0], 0)
#define	HMI_OUT_02_OFF	CBI(ucRegCoilsBuf[0], 1)
#define	HMI_OUT_03_OFF	CBI(ucRegCoilsBuf[0], 2)
#define	HMI_OUT_04_OFF	CBI(ucRegCoilsBuf[0], 3)

// function code 0x02 input status
#define	HMI_INPUT_01_ON		SBI(ucRegDiscreteBuf[0], 0)			// 1x_01	IO1.01
#define	HMI_INPUT_02_ON		SBI(ucRegDiscreteBuf[0], 1)			// 1x_02	IO1.02
#define	HMI_INPUT_03_ON		SBI(ucRegDiscreteBuf[0], 2)			// 1x_03	IO1.03
#define	HMI_INPUT_04_ON		SBI(ucRegDiscreteBuf[0], 3)			// 1x_04	IO1.04
#define	HMI_INPUT_05_ON		SBI(ucRegDiscreteBuf[0], 4)			// 1x_05	IO1.05
#define	HMI_INPUT_06_ON		SBI(ucRegDiscreteBuf[0], 5)			// 1x_06	IO1.06
#define	HMI_INPUT_07_ON		SBI(ucRegDiscreteBuf[0], 6)			// 1x_07	IO1.07
#define	HMI_INPUT_08_ON		SBI(ucRegDiscreteBuf[0], 7)			// 1x_08	IO1.08

#define	HMI_INPUT_01_OFF	CBI(ucRegDiscreteBuf[0], 0);
#define	HMI_INPUT_02_OFF	CBI(ucRegDiscreteBuf[0], 1);
#define	HMI_INPUT_03_OFF	CBI(ucRegDiscreteBuf[0], 2);
#define	HMI_INPUT_04_OFF	CBI(ucRegDiscreteBuf[0], 3);
#define	HMI_INPUT_05_OFF	CBI(ucRegDiscreteBuf[0], 4);
#define	HMI_INPUT_06_OFF	CBI(ucRegDiscreteBuf[0], 5);
#define	HMI_INPUT_07_OFF	CBI(ucRegDiscreteBuf[0], 6);
#define	HMI_INPUT_08_OFF	CBI(ucRegDiscreteBuf[0], 7);

// function code 0x03      	
// holding buffer
#define	AO_4X_01_TEST				( 0 )		
#define	AO_4X_02_TEST				( 1 )		

// function code 0x04 
// input buffer
#define AI_3X_01		( 0 )		
#define AI_3X_02		( 1 )		
#define AI_3X_03		( 2 )		
#define AI_3X_04		( 3 )		
#define AI_3X_05		( 4 )		
/* Private variables ---------------------------------------------------------*/
extern uint8_t ucRegCoilsBuf[8]; 
extern uint8_t ucRegDiscreteBuf[8];
extern uint16_t usRegHoldingBuf[50];
extern uint16_t usRegInputBuf[50];
#endif /* MB_APP_H_ */


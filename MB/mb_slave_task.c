/**
  ******************************************************************************
  * @file    Bsp/modbus task 
  * @author  Mr_zai
  * @version V1.0.0
  * @date    2020-05-13
  * @brief   Freemodbus module
  ******************************************************************************
  */
#include "stm32h7xx_hal.h"
#include "mb.h"
#include "mbutils.h"
#include "main.h"

// Function code 0x01 read coils out DO
#define REG_COILS_START       0x0000		
#define REG_COILS_SIZE        64		

// Fuction code 0x02 read discrete input DI
#define REG_DISCRETE_START    0x0000		
#define REG_DISCRETE_SIZE     64	

// Function code 0x03 read holding register AO
#define REG_HOLDING_START     0x0000	
#define REG_HOLDING_NREGS     50

// Function code 0x04 read input register AI
#define REG_INPUT_START       0x0000		
#define REG_INPUT_NREGS       50		

/* Private variables ---------------------------------------------------------*/
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00}; 		
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x00};	
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS] = {0x0000};
uint16_t usRegHoldingStart = REG_HOLDING_START;
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000};
uint16_t usRegInputStart = REG_INPUT_START;

static void update_mb_buffer(void);

void MB_Slave_Task_Entry(void *p)
{
  	for(;;)
	{ 		
		update_mb_buffer();
		eMBPoll(); 
		osDelay(1);
	}
	
 }
static void update_mb_buffer(void)
{

}

// freemodbus call back function
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int16_t         iRegIndex;
  if( ( (int16_t)usAddress >= REG_INPUT_START ) \
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
  {
    iRegIndex = ( int16_t )( usAddress - usRegInputStart );
    while( usNRegs > 0 )
    {
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
      iRegIndex++;
      usNRegs--;
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int16_t	iRegIndex;
	
  if( ( (int16_t)usAddress >= REG_HOLDING_START ) \
     && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
  {
    iRegIndex = ( int16_t )( usAddress - usRegHoldingStart );
    
    switch ( eMode )
    {
      /* Pass current register values to the protocol stack. */
      case MB_REG_READ:
        while( usNRegs > 0 )
        {
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
          iRegIndex++;
          usNRegs--;
        }
        break;
     	/* Update current register values with new values from the
         * protocol stack. */
      case MB_REG_WRITE:
        while( usNRegs > 0 )
        {
          usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
          usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
          iRegIndex++;
          usNRegs--;
        }
        break;
     }
  }
  else
  {
   
    eStatus = MB_ENOREG;
  }
  
  return eStatus;
}

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{	
	eMBErrorCode    eStatus = MB_ENOERR;
	int16_t         iNCoils = ( int16_t )usNCoils;
	int16_t         usBitOffset;
	if( ( (int16_t)usAddress >= REG_COILS_START ) && ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
  	{	
    	usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
    	switch ( eMode )
    	{
      		case MB_REG_READ:
        	while( iNCoils > 0 )
        	{
          		*pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
                                          ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
          		iNCoils -= 8;
          		usBitOffset += 8;
        	}
        	break;
      		case MB_REG_WRITE:
        	while( iNCoils > 0 )
       		{
          		xMBUtilSetBits( ucRegCoilsBuf, usBitOffset, ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ), *pucRegBuffer++ );
          		iNCoils -= 8;
        	}
        	break;
    	}

 	}
  	else
  	{
    	eStatus = MB_ENOREG;
  	}
  	return eStatus;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	eMBErrorCode    eStatus = MB_ENOERR;
  	int16_t         iNDiscrete = ( int16_t )usNDiscrete;
  	uint16_t        usBitOffset;

  if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&
        ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
  {
    usBitOffset = ( uint16_t )( usAddress - REG_DISCRETE_START );
    while( iNDiscrete > 0 )
    {
      *pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,
                                      ( uint8_t)( iNDiscrete > 8 ? 8 : iNDiscrete ) );
      iNDiscrete -= 8;
      usBitOffset += 8;
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}


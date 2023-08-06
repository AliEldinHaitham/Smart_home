

#ifndef IMT_FINALPROJECT_INTERFACE_H_
#define IMT_FINALPROJECT_INTERFACE_H_

/*   Includes  */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_Interface.h"
#include "EX_INT_Interface.h"
#include "IMT_FINALPROJECT_CFG.h"

/* Functions */
void FINALPROJECT_VidInit()              ;
u16 LM35_U16_ReadTemp()                  ;
void normal_state(void)                  ;
void Emergency_state (void)              ;
void StateBeforeCheck(u8 Copy_U8Temp)    ;
void StateOfFunAndBuzzer(u8 Copy_U8Temp) ;
void SetDoorAngle(u8 Copy_U8Angel)       ;
void DisplayTempOnLCD(u8 Copy_U8Temp)    ;
void EnteringUrID(u8 Copy_U8IDNum)       ;
u8 CheckOnPassword(void)                 ;
void IsPasswordFalse(void)               ;
void ExistRoom(void)                     ;
u8 NumOfHumansInRoom(void)               ;
u8 EnterID(void)						 ;
void RoomTemp(void)						 ;

#endif /* IMT_FINALPROJECT_INTERFACE_H_ */


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "TIMER_Private.h"
#include "TIMER_CFG.h"




/************************* TIMER0 FUNC *******************************/

void TIMER0_VidInitialize (void) ;                                    //use to initialize TIMER0

#if TIMER0_MODE == FAST_PWM

void Timer0_VidSETDUTY (u8 duty ) ;                                   //to select specific duty in timer0

#elif TIMER0_MODE != FAST_PWM

void TIMER0_Set_Time_S (u8 Copy_U8Time);                                     //to set wanted time
void TIMER0_Set_Time_mS (u16 Copy_U8Time);                                   //to set wanted time
void TIMER_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void));     //use to point on excuted function in ISR

#endif


/************************* TIMER2 FUNC *******************************/

void TIMER2_VidInitialize (void) ;                                    //use to initialize TIMER0

#if TIMER2_MODE == FAST_PWM

void Timer2_VidSETDUTY (u8 duty ) ;                                   //to select specific duty in timer0

#elif TIMER2_MODE != FAST_PWM

void TIMER2_Set_Time_S (u8 Copy_U8Time);                                     //to set wanted time
void TIMER2_Set_Time_mS (u16 Copy_U8Time);                                   //to set wanted time
void TIMER_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void));     //use to point on excuted function in ISR

#endif

#endif /* TIMER_INTERFACE_H_ */

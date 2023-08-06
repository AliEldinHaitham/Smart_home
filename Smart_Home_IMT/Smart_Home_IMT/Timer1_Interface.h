#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_




void TIMER1_VidCallback(void(*pfun)(void));

void  TIMER1_VidICUcallback(void(*pfun)(void));

void TIMER1_VidSetClock();

void TIMER1_VidICURisingEdge();

void TIMER1_VidICUFallingEdge();

void TIMER1_VidSetCounterRegister(u16 Preload);

void TIMER1_VidSetCompareMatchRegA(u16 value);

void TIMER1_VidSetCompareMatchRegB(u16 value);

void TIMER1_VidSetICR1Reg(u16 value);

u16 TIMER1_VidGetICR1Register();

void TIMER1_VidPWMGenerationOC1A(f32 PWMFreqKHz,f32 DutyPercentage);

void TIMER1_VidPWMGenerationOC1B(f32 PWMFreqKHz,f32 DutyPercentage);

u8 TIMER1_U8GetICF1();

void TIMER1_VidClearICF1();

void TIMER1_VidReadPWMusingICU1(f128*Freq,f32*Duty_cycle);

void TIMER1_VidStop();

void TIMER1_VidInit();


void Servo();






#endif





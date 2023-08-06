#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "Timer1_cfg.h"
#include "Timer1_private.h"

void NULL_FUNCTION(void){}




void(*TIMER1_callback)(void)=&NULL_FUNCTION;
void(*TIMER1_ICU_callback)(void)=&NULL_FUNCTION;


void TIMER1_VidCallback(void(*pfun)(void))
{
	TIMER1_callback=pfun;
}

void  TIMER1_VidICUcallback(void(*pfun)(void))
{
	TIMER1_ICU_callback=pfun;
}


void TIMER1_VidSetClock()
{
	/*Clear CS0,CS1,CS2	 bits*/
	TCCR1B=TCCR1B&0b11111000;

#if TIMER1_CLOCK_MODE == MCU_CLOCK
	TCCR1B=TCCR1B|1;
#elif TIMER1_CLOCK_MODE == DIVIDE_8
	TCCR1B=TCCR1B|2;
#elif TIMER1_CLOCK_MODE == DIVIDE_64
	TCCR1B=TCCR1B|3;
#elif TIMER1_CLOCK_MODE == DIVIDE_256
	TCCR1B=TCCR1B|4;
#elif TIMER1_CLOCK_MODE == DIVIDE_1024
	TCCR1B=TCCR1B|5;
#elif TIMER1_CLOCK_MODE == T0_FALLING
	TCCR1B=TCCR1B|6;
#elif TIMER1_CLOCK_MODE == T0_RISING
	TCCR1B=TCCR1B|7;
#endif

}

void TIMER1_VidStop()
{
	TCCR1B=0;
}


void Servo()
{
	ICR1H=0;
	ICR1L=255;
	OCR1AH=0;
	OCR1AL=187;

}

void TIMER1_VidInit()
{
	SET_BIT(SREG,7);

#if TIMER1_OPERATING_MODE == NORMAL
	/*Normal mode*/
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	/*input capture*/
    SET_BIT(TCCR1B,6);
#elif TIMER1_OPERATING_MODE == FAST_PWM
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	CLR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
	CLR_BIT(TCCR1A,FOC1A);
	CLR_BIT(TCCR1A,FOC1B);
	/*FAST PWM ICR1 as TOP*/
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	/*Enable Timer interrupts*/
	/*SET_BIT(TIMSK,OCIE1A);
	SET_BIT(TIMSK,TOIE1);
	SET_BIT(TIMSK,TICIE1);*/
#endif
	TIMER1_VidSetClock();
}

void TIMER1_VidICURisingEdge()
{
	   SET_BIT(TCCR1B,6);
}

void TIMER1_VidICUFallingEdge()
{
	   CLR_BIT(TCCR1B,6);
}


void TIMER1_VidSetCompareMatchRegA(u16 value)
{
	OCR1AH=(u8)(value>>8);
	OCR1AL=(u8)value;

}

void TIMER1_VidSetCompareMatchRegB(u16 value)
{

	OCR1BH=(u8)(value>>8);
	OCR1BL=(u8)value;
}

void TIMER1_VidSetICR1Reg(u16 value)
{
	ICR1H=(u8)(value>>8);
	ICR1L=(u8)value;
}

void TIMER1_VidSetCounterRegister(u16 value)
{
	TCNT1H=(u8)(value>>8);
	TCNT1L=(u8)value;
}

u16 TIMER1_VidGetCounterRegister()
{
	u8 Low=TCNT1L;
	u8 high=TCNT1H;
	u16 shifted_high=high<<8;
	return(shifted_high+Low);

}


u16 TIMER1_VidGetICR1Register()
{
	u8 Low=ICR1L;
	u8 high=ICR1H;
	u16 shifted_high=high<<8;
	return(shifted_high+Low);

}

void TIMER1_VidPWMGenerationOC1A(f32 PWMFreqKHz,f32 DutyPercentage)
{
	u16 TOP=(MCU_INPUT_FREQ)/(PWMFreqKHz*1000*PRESCALER)-1;
	TIMER1_VidSetICR1Reg(TOP);
	TIMER1_VidSetCompareMatchRegA(TOP*DutyPercentage/100);
}

void TIMER1_VidPWMGenerationOC1B(f32 PWMFreqKHz,f32 DutyPercentage)
{
	u16 TOP=(MCU_INPUT_FREQ)/(PWMFreqKHz*1000*PRESCALER)-1;
	TIMER1_VidSetICR1Reg(TOP);
	TIMER1_VidSetCompareMatchRegB(TOP*DutyPercentage/100);
}

void TIMER1_VidClearICF1()
{
	SET_BIT(TIFR,ICF1);
}

u8 TIMER1_U8GetICF1()
{
	return(GET_BIT(TIFR,ICF1));
}


void TIMER1_VidReadPWMusingICU1(f128*Freq,f32*Duty_cycle)
{
	u16 Snap1,Snap2,Snap3,High,Period;
	TIMER1_VidSetCounterRegister(0);
	TIMER1_VidClearICF1();  	/* Clear ICF (Input Capture flag) flag */
	TIMER1_VidICURisingEdge(); 	/* Rising edge, no prescaler */

	while (TIMER1_U8GetICF1()==0);
	Snap1 = TIMER1_VidGetICR1Register();  		/* Take value of capture register */
	TIMER1_VidClearICF1();  	/* Clear ICF flag */

	TIMER1_VidICUFallingEdge();	/* Falling edge, no prescaler */
	while (TIMER1_U8GetICF1()== 0);
	Snap2 = TIMER1_VidGetICR1Register();
	TIMER1_VidClearICF1();   	/* Clear ICF flag */

	TIMER1_VidICURisingEdge();  	/* Rising edge, no prescaler */
	while (TIMER1_U8GetICF1()== 0);
	Snap3 = TIMER1_VidGetICR1Register(); /* Take value of capture register */
	TIMER1_VidClearICF1();    	/* Clear ICF flag */
	if(Snap1<Snap2 && Snap2<Snap3)
	{
		High=Snap2-Snap1;
		Period=Snap3-Snap1;
		*Freq=((MCU_INPUT_FREQ/PRESCALER)/Period);
		*Duty_cycle =((f32)High/(f32)Period)*100;

	}
	else
	{
		*Freq=-1;
		*Duty_cycle=-1;
	}

}

/*ICU ISR*/












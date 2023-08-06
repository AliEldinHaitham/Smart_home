#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*Operating modes.*/
#define NORMAL 0
#define FAST_PWM 1

/*TIMER0 Clock modes*/
#define NO_CLOCK 0
#define MCU_CLOCK 1
#define DIVIDE_8 2
#define DIVIDE_64 3
#define DIVIDE_256 4
#define DIVIDE_1024 5
#define T0_FALLING 6
#define T0_RISING 7






/*Timer1 Capture event ISR*/
void __vector_6(void)  __attribute__((signal));


#define TIFR *((volatile u8*)0x58)
#define ICF1 5



/*Define Timer1 registers*/
#define TCCR1A *((volatile u8*)0x4F)
#define TCCR1B *((volatile u8*)0x4E)
//#define TCNT1  *((volatile u16*)0x4C)
#define TCNT1L  *((volatile u8*)0x4C)
#define TCNT1H  *((volatile u8*)0x4D)
//#define OCR1A  *((volatile u16*)0x4A)
#define OCR1AL  *((volatile u8*)0x4A)
#define OCR1AH  *((volatile u8*)0x4B)
//#define OCR1B  *((volatile u16*)0x48)
#define OCR1BL  *((volatile u8*)0x48)
#define OCR1BH  *((volatile u8*)0x49)
//#define ICR1  *((volatile u16*)0x46)
#define ICR1L  *((volatile u8*)0x46)
#define ICR1H  *((volatile u8*)0x47)




#define SREG *((volatile u8*)0x5F)




/*TIMER1 Defined pins*/
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4
#define FOC1A 3
#define FOC1B 2
#define COM1A0 6
#define COM1A1 7
#define COM1B0 4
#define COM1B1 5




/*TIMSK REG defined bits*/
#define TOIE0 0
#define OCIE0 1
#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2 6
#define OCIE2 7

#endif





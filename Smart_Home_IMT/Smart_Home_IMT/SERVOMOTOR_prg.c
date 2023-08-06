#include"STD_TYPES.h"
#include "Timer1_Interface.h"


#define OC1A_PIN 5
#define OC1B_PIN 4


void SERVOMOTOR_VidSetDirection(u8 Degree,u8 PWMPin)
{
	f32 Duty=(Degree+48.75)/18.75;
	switch(PWMPin)
	{
	/*Generate PWM of frequency 0.050KHz of the desired Duty cycle percentage*/
	case OC1A_PIN:{TIMER1_VidPWMGenerationOC1A(0.050,Duty); break;}
	case OC1B_PIN:{TIMER1_VidPWMGenerationOC1B(0.050,Duty); break;}
	}

}


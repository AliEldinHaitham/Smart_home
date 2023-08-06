
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "DCMOTOR_Interface.h"
#include "DCMOTOR_Private.h"
#include "DCMOTOR_CFG.h"

void DcMotor_VidInit(void){
	/*set the direction of the two input pins of the dc motor to be output pins */
	DIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
	DIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);

	/*initialize the dc motor to be stop at the beginning*/
	DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
}

void DcMotor_VidRotate(u8 state){
	switch(state){
	case STOP:
		/*make the dc motor stop*/
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		break;
	case CLK_WISE:
		/*make the dc motor start in CLOCK_WISE direction*/
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);
		break;
	case ANTI_CLK_WISE:
		/*make the dc motor start in ANTI_CLOCK_WISE  direction*/
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
		DIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		break;
	}
}



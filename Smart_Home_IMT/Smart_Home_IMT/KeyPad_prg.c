
#include<util/delay.h>
#include"STD_TYPES.h"
#include"Bit_math.h"
#include "DIO_interface.h"
//#include "ADC_interface.h"
#include"KeyPad_interface.h"
#include"KeyPad_cfg.h"
#include"KeyPad_Private.h"

//#define KPD_PORT 3
#define KPD_PORT_0_4 0
#define KPD_PORT_5_8 1


u8 keypad_U8GetPressed()
{
	u8 key = 50;
	u8 Pressed;
	for(u8 c=4; c<8; c++)
	{
		DIO_VidSetPinValue(KPD_PORT_5_8,c,LOW);
		for(u8 Row =2; Row<6; Row++)
		{
			Pressed = DIO_U8GetPinValue(KPD_PORT_0_4,Row);
			if(LOW == Pressed)
			{
				key = ((Row-2) * 4) + (c-3);
				while(LOW == Pressed)
				{
					Pressed =  DIO_U8GetPinValue(KPD_PORT_0_4,Row);
				}
				_delay_ms(5);
			}
		}
		DIO_VidSetPinValue(KPD_PORT_5_8,c,HIGH);
	}
	return key;
}

void keypad_init()
{
		DIO_VidSetPinDirection(KPD_PORT_0_4,2,INPUT);
		DIO_VidSetPinDirection(KPD_PORT_0_4,3,INPUT);
		DIO_VidSetPinDirection(KPD_PORT_0_4,4,INPUT);
		DIO_VidSetPinDirection(KPD_PORT_0_4,5,INPUT);

		DIO_VidSetPinDirection(KPD_PORT_5_8,4,OUTPUT);
		DIO_VidSetPinDirection(KPD_PORT_5_8,5,OUTPUT);
		DIO_VidSetPinDirection(KPD_PORT_5_8,6,OUTPUT);
		DIO_VidSetPinDirection(KPD_PORT_5_8,7,OUTPUT);

		DIO_VidSetPinValue(KPD_PORT_0_4,2,HIGH);
		DIO_VidSetPinValue(KPD_PORT_0_4,3,HIGH);
		DIO_VidSetPinValue(KPD_PORT_0_4,4,HIGH);
		DIO_VidSetPinValue(KPD_PORT_0_4,5,HIGH);

		DIO_VidSetPinValue(KPD_PORT_5_8,4,HIGH);
		DIO_VidSetPinValue(KPD_PORT_5_8,5,HIGH);
		DIO_VidSetPinValue(KPD_PORT_5_8,6,HIGH);
		DIO_VidSetPinValue(KPD_PORT_5_8,7,HIGH);


}

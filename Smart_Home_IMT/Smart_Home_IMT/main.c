
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "IMT_FINALPROJECT_Interface.h"

	u8 temp	=0;                                             //define temperature
	u8 Home_work = 0 ;                                    //to work whole companent of home
	u8 ExistHuman = 0 ;                                   //to detect if human in room or not



int main()
{
	FINALPROJECT_VidInit();                               //to initialize all functions that we need
	

	while(1)
	{
		/* first check on temperature */
		temp = LM35_U16_ReadTemp() ;

		/*
		to make sure that the temperature not excess
		40 while u entered password and return normal state if temperature less than 40'C
		*/
		StateBeforeCheck(temp);

		/* to enter the numbers in compared array with the default */
		EnterID();
				
		/* to check on password if it's correct */
		Home_work =  CheckOnPassword();

		/* to make some orders on false password */
		if(Home_work==0){IsPasswordFalse();}
			
		ExistHuman = NumOfHumansInRoom()  ;
		
		RoomTemp();  /* Sync on temperature  */
	
  
  }//end of while 1
}//end main


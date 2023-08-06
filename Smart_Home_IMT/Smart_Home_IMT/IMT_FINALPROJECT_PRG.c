

/*   Includes  */
#include "IMT_FINALPROJECT_Interface.h"
#include "INTERRUPT_Interface.h"
#include "TIMER_Interface.h"
#include "DCMOTOR_Interface.h"
#include "KeyPad_Interface.h"
#include "SERVOMOTOR_interface.h"
#include <avr/delay.h>
#include "ADC_interface.h"
#include "IMT_FINALPROJECT_Private.h"
#include "IMT_FINALPROJECT_CFG.h"

/*   GLOBAL Variables  */
	u8 normal_flag = 0 ;                                  //to check on normal condition
	u8 Duty_Fan ;                                         //define duty direct "FUN in PWM_Volt_fan "
	u8 ID_compare[5] = {0} ;                              //to check on input numbers
	u8 ID_index = 0 ;                                     //to point on default ID numbers
	//u8 ID[5] = {'4','5','6','7','8'} ;                              //to set default password on door
	u8 ID[5] = {4,5,6,7,8} ;                              //to set default password on door

	u8 ID_flag = 0 ;                                      //to check on that u still in password state
	u8 count=0;
	u8 Wrong_inputs=0;
	u8 ID_input_num=0 ;                                     //to store number that get from user
	u8 counter_exsit = 0 ;
	u8 counter_enter = 0 ;
	u8 IDCode[5]={0,0,0,0,0};
		
	extern u8 temp;                                             //define temperature
	extern	u8 Home_work ;                                    //to work whole companent of home
	extern	u8 ExistHuman ;                                   //to detect if human in room or not


/*
 Name        : FUNC
 Input       : void
 Output      : void
 Description : pointer to function which excuted in interrupt
*/
void FUNC (void){
	counter_exsit++;

	/* To make angle of door while entering */
	SetDoorAngle(GET_OUT);
}

/*
 Name        : FINALPROJECT_VidInit
 Input       : void
 Output      : void
 Description : to initialize every function in project
*/

void FINALPROJECT_VidInit(){
	   /* For LCD & LM35 & DCMOTOR & KEYPAD & USART*/
	    ADC_VidInit();
		LCD_VidInit();
		DcMotor_VidInit();
		keypad_init();
		//UART_Vidinit();

		/* For Fun */
		TIMER0_VidInitialize();
		TIMER1_VidInit();
		/* For TEMP SENSOR INTRUPPT */
		TIMER2_VidInitialize();



		/* decleration of external interrupt to exist room */
	    GIE_VidEnable();
	    EX_INT_VidINIT();
		EX_PIE_VidEnable(INT_NUM);
		EX_INT_VidSetCallBack(INT_NUM,FUNC);
		EX_INT_VidSetEdge(INT_NUM,FALLING);


		DIO_VidSetPinDirection(BUZZER_PORT,BUZZER_PIN,HIGH);  //define buzzer pin direction
		DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);       //define initial value for buzzer

		DIO_VidSetPinDirection(SWITCH_PORT,SWITCH_PIN,LOW);   //define Switch as an input pin direction
		DIO_VidSetPinValue(SWITCH_PORT,SWITCH_PIN,HIGH);      //Pull up switch
		
		DIO_VidSetPinDirection(SERVO_PORT,SERVO_PIN,HIGH);			  //define Servo pin direction

		DIO_VidSetPinDirection(PORT_LED,LED_PIN,HIGH);        //led input
		
			LCD_VidPosCur(0,0);                                   //to print helping massage
			LCD_VidSendString(" Enter your ID ");
			 /* Check Temp Every 0.1 Sec */
			TIMER_VidSetCallBack(2,&RoomTemp); 
			TIMER2_Set_Time_mS(100);            
}

/*
 Name        : LM35_U16_ReadTemp
 Input       : void
 Output      : u16
 Description : to read temperature by LM35
*/
u16 LM35_U16_ReadTemp()
{
	return ADC_VidReadChannel(7)/10 ;
}

/*
 Name        : Emergency_state
 Input       : void
 Output      : void
 Description : to put project in emergency state when temperature more than 40'C
               1)warning massage  2)open servo 90 degree   3)open buzzer
*/
void Emergency_state (void){
	LCD_VidPosCur(0,0);
	LCD_VidSendString("TEMP more than 38 C");
	Duty_Fan = FULL_DUTY ;
	DcMotor_VidRotate(CLK_WISE);
	Timer0_VidSETDUTY(Duty_Fan);
	DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
	SetDoorAngle(GET_OUT_FIRE);
}//end FUNC

/*
 Name        : normal_state
 Input       : void
 Output      : void
 Description : stop DC motor "fan" - close buzzer - begin question on password and clear warning massage
*/
void normal_state(void){
	u8 Duty_Fan =0 ;
	DcMotor_VidRotate(STOP);
	Timer0_VidSETDUTY(Duty_Fan);
	DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
	LCD_VidPosCur(0,0);
	LCD_VidSendString("Enter your ID ");
	LCD_VidPosCur(1,0);
	LCD_VidSendString("               ");
}

/*
 Name        : StateBeforeCheck
 Input       : u8
 Output      : void
 Description : To check on the state of the home while you entering password or you aren't in home
*/
void StateBeforeCheck(u8 Copy_U8Temp){
	if (Copy_U8Temp > MAX_TEMP ){
		Emergency_state();
		normal_flag = EMERGENCY_STATE ;
	}//end if
	else {
	    if (normal_flag == EMERGENCY_STATE ){
			normal_state();
			normal_flag = NORMAL_STATE ;
	    }//end if
	}//end else
}

/*
 Name        : StateOfFunAndBuzzer
 Input       : u8
 Output      : void
 Description : to set the duty of fan and state of buzzer
*/
void StateOfFunAndBuzzer(u8 Copy_U8Temp){
	/*
	in temp below than 20 :
	  1)STOP Fan
	  2)close buzzer
	*/
	if (Copy_U8Temp < MIN_TEMP ){
		Duty_Fan = ZERO_DUTY ;
		DcMotor_VidRotate(STOP);
		Timer0_VidSETDUTY(Duty_Fan);
		DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
	}//end if

	/*
	in temp below between 20 : 40 :-
	  1)rotate  Fan with the needed voltage
	  2)close buzzer
	*/
	else if (Copy_U8Temp >= MIN_TEMP && Copy_U8Temp < MAX_TEMP ){

		//to make discrete duty of fan
		if (Copy_U8Temp >= MIN_TEMP && Copy_U8Temp < MIN_TEMP+5 ){
			Duty_Fan = QUATER_DUTY ;
		}
		else if (Copy_U8Temp >= MIN_TEMP+5 && Copy_U8Temp < MID_TEMP ){
			Duty_Fan = MID_DUTY ;
		}
		else if (Copy_U8Temp >= MID_TEMP && Copy_U8Temp < MID_TEMP+5 ){
			Duty_Fan = THREE_QUATER ;
		}
		else {
			Duty_Fan = FULL_DUTY ;
		}

		DcMotor_VidRotate(CLK_WISE);
		Timer0_VidSETDUTY(Duty_Fan);
		DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
	}//end else if

	/*
	in temp below more than 38 :-
	  1)rotate  Fan with the max voltage
	  2)open buzzer
	*/
	u8 OPEN_ONCE=1;
	while (Copy_U8Temp >= MAX_TEMP ){
		/*to check on temperature*/
		Copy_U8Temp = LM35_U16_ReadTemp() ;
		DisplayTempOnLCD(Copy_U8Temp);
		Duty_Fan = FULL_DUTY ;
		DcMotor_VidRotate(CLK_WISE);
		Timer0_VidSETDUTY(Duty_Fan);
		DIO_VidSetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
		if (OPEN_ONCE==1){SetDoorAngle(GET_OUT_FIRE);OPEN_ONCE=2;}
	   }//end while
	 if (OPEN_ONCE==2){SetDoorAngle(GET_OUT);OPEN_ONCE=1;}
}//end Func

/*
 Name        : SetDoorAngle
 Input       : void
 Output      : void
 Description : to set the duty of fan and state of buzzer
*/
void SetDoorAngle(u8 Copy_U8Angel) {
	/*Set the direction of the servo motor to 90 degrees, and make the OC1A PIN as a PWM to the servo*/
	if(Copy_U8Angel==GET_IN){
	/*i.e Open the door*/
	//SERVOMOTOR_VidSetDirection(90,OC1A_PIN);
	SERVOMOTOR_VidSetDirection(0,OC1A_PIN);
	_delay_ms(2000);
	/*Set the direction of the servo motor to 0 degrees, and make the OC1A PIN as a PWM to the servo*/
	/*i.e Close the door*/
	//SERVOMOTOR_VidSetDirection(0,OC1A_PIN);
	SERVOMOTOR_VidSetDirection(90,OC1A_PIN);
	}
	else if(Copy_U8Angel==GET_OUT){
			/*i.e Open the door*/
			SERVOMOTOR_VidSetDirection(180,OC1A_PIN);
			_delay_ms(3000);
			/*i.e Close the door*/
			SERVOMOTOR_VidSetDirection(90,OC1A_PIN);
	}
	else{SERVOMOTOR_VidSetDirection(180,OC1A_PIN);}


		
	}



/*
 Name        : DisplayTempOnLCD
 Input       : U8
 Output      : void
 Description : to Display Temperture on LCD
*/
void DisplayTempOnLCD(u8 Copy_U8Temp){
	LCD_VidPosCur(0,0);
	LCD_VidSendString("TEMPERATURE : ");
	LCD_VidPrintVar(Copy_U8Temp);
	LCD_VidSendChar('C');
	LCD_VidSendChar(' ');
}

/*
 Name        : EnteringUrID
 Input       : U8
 Output      : void
 Description : to Enter the ID num in Global array to check on the permission
*/
void EnteringUrID(u8 Copy_U8IDNum){
	if (Copy_U8IDNum != NO_INPUT_NUM ){
		ID_compare[ID_index] = Copy_U8IDNum ;
		LCD_VidPosCur(1,ID_index);
		LCD_VidSendChar('*') ;
		//LCD_VidSendChar(Copy_U8IDNum) ;

		ID_index++ ;
	}//end if
}

/*
 Name        : CheckOnPassword
 Input       : void
 Output      : u8
 Description : to check on password which in ID_compare and rising flag to detect on the
               validability on password
*/
u8 CheckOnPassword(void){
	ID_flag==RISE_FLAG;
	u8 counterIDIndex= 0 ;
	u8 countRightMatch =0;
	if ( ID_index == NUM_OF_ELEMENT_IN_PASS ){
		while (counterIDIndex < NUM_OF_ELEMENT_IN_PASS){		
			if (ID[counterIDIndex] == ID_compare[counterIDIndex] ){
				//ID_flag = RISE_FLAG ;			
				countRightMatch++;			
			}//end if
			counterIDIndex++;
		}//end while
	}//end if check

	/*to begin in core programme with needed orders
	  1)welcome massage   2)begin home working
	 */
	if (countRightMatch==5 ){
	    LCD_VidClear();
		LCD_VidPosCur(0,0);
		LCD_VidSendString("correct ID");
		LCD_VidPosCur(1,0);
		LCD_VidSendString("   WELCOME");
		Wrong_inputs=0;
		_delay_ms(1000);
	    LCD_VidClear();
		ID_index = 0 ;
		countRightMatch=0;

		/* to count num of human entering room */
		counter_enter++;

		/* To make angle of door while entering */
		SetDoorAngle(GET_IN);
		ID_flag==LOW_FLAG;
	    return RISE_FLAG ;
	}//end if
	
	
	return LOW_FLAG ;
	
}//end FUNC

/*
 Name        : IsPasswordFalse
 Input       : void
 Output      : void
 Description : to make some orders on false password like display statement on LCD and and check on max numbers
               of iterations
*/
void IsPasswordFalse(void){
	//if (ID_flag==1){
	    LCD_VidClear();
		LCD_VidPosCur(0,0);
		LCD_VidSendString("incorrect ID");
		Wrong_inputs++;
		_delay_ms(1000);
	if ( Wrong_inputs == 3 ){
		LCD_VidClear();
		LCD_VidPosCur(0,0);
		LCD_VidSendString("WAIT 3 SECONDS");
		_delay_ms(3000);
		Wrong_inputs=0;
	}//end if
	LCD_VidClear();
	LCD_VidPosCur(0,0);
	LCD_VidSendString("Enter your ID    ");
	ID_index = 0 ;
	ID_flag = LOW_FLAG ;
	//end if check on password if it's not correct to do needed orders
//to begin in core programme if pass is true
}

/*
 Name        : NumOfHumansInRoom
 Input       : void
 Output      : u8
 Description : to count number of humans in room
*/
u8 NumOfHumansInRoom(void){
    return	 (counter_enter-counter_exsit) ;
}


/*
 Name        : EnterID
 Input       : void
 Output      : u8
 Description : to read ID by UART
*/

u8 EnterID(void){

for (u8 i=0;i<5;i++)
{
	IDCode[i]=keypad_U8GetPressed();
	while(IDCode[i]==50){
	IDCode[i]=keypad_U8GetPressed();

	count++;
	if(count==0)RoomTemp();  /* Sync on temperature  */
	}
	//IDCode[i]=UART_U8GetChar();
	//UART_U8SendChar(IDCode[i]);
	//ID_input_num = 10 * ID_input_num + IDCode[i];
	
	EnteringUrID(IDCode[i]);
}
}


/*
 Name        : RoomTemp
 Input       : void
 Output      : void
 Description : to read Temp in Room
*/

void RoomTemp(void){
	
	if (Home_work || ExistHuman ){
		temp = LM35_U16_ReadTemp() ;
		/* To determine speed of fun and Buzzer situation */
		StateOfFunAndBuzzer(temp);
		StateBeforeCheck(temp);

		/* to display temperture on LCD */
		DisplayTempOnLCD(temp);

		/* lighten led */
		DIO_VidSetPinValue(PORT_LED,LED_PIN,HIGH);
	}//end if home work
}


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_Interface.h"
#include"LCD_cfg.h"
#include"LCD_private.h" 
#include<avr/delay.h>


void LCD_VidSendCommend(u8 Copy_U8Commend){

#ifdef EIGHT_BIT

/**************to disable RS *** *********************/
	DIO_VidSetPinValue(CONTROL_PORT,RS,LOW);
/******to out the value of commend on data port *****/
	DIO_VidSetPortValue(DATA_PORT,Copy_U8Commend);
/*************to make pulse for enable **************/
	DIO_VidSetPinValue(CONTROL_PORT,E,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
	_delay_ms(2);

#endif

#ifndef EIGHT_BIT

/**************to disable RS RW *********************/
	DIO_VidSetPinValue(CONTROL_PORT,RS,LOW);
/******to out the value of upper_commend on data port ****/
	DIO_VidSetPinValue(CONTROL_PORT,D7, GET_BIT(Copy_U8Commend,7) );
	DIO_VidSetPinValue(CONTROL_PORT,D6, GET_BIT(Copy_U8Commend,6) );
	DIO_VidSetPinValue(CONTROL_PORT,D5, GET_BIT(Copy_U8Commend,5) );
	DIO_VidSetPinValue(CONTROL_PORT,D4, GET_BIT(Copy_U8Commend,4) );
/*************to make pulse for enable *************/
		DIO_VidSetPinValue(CONTROL_PORT,E,HIGH) ;
		_delay_ms(1);
		DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
		_delay_ms(2);
/**********to out the value of lower_commend on data port*********/
	DIO_VidSetPinValue(CONTROL_PORT,D7, GET_BIT(Copy_U8Commend,3) );
	DIO_VidSetPinValue(CONTROL_PORT,D6, GET_BIT(Copy_U8Commend,2) );
	DIO_VidSetPinValue(CONTROL_PORT,D5, GET_BIT(Copy_U8Commend,1) );
	DIO_VidSetPinValue(CONTROL_PORT,D4, GET_BIT(Copy_U8Commend,0) );
/*************to make pulse for enable *************/
	DIO_VidSetPinValue(CONTROL_PORT,E,HIGH) ;
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
	_delay_ms(2);

#endif
}



void LCD_VidInit (void) {

#ifdef EIGHT_BIT

/****to define CONTROL PORT as OUTPUT PINS******/
	DIO_VidSetPinDirection(CONTROL_PORT,RS,HIGH);
	DIO_VidSetPinDirection(CONTROL_PORT,E,HIGH);
/****to define DATA PORT as OUTPUT PINS********/
	DIO_VidSetPortDirection(DATA_PORT,0xff);
/******to initialize LCD after power***********/
	_delay_ms(40);
	//send function set commend
	LCD_VidSendCommend (FUNC_SET);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Display_ON & Cursor_OFF Command
	LCD_VidSendCommend(DISPLAY_ON_CURSOR_OFF);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Entry Mode Set Command
	LCD_VidSendCommend(ENTERY_MODE);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Clear Display Command
	LCD_VidSendCommend(DISPLAY_CLEAR);
	// Delay for more than 1.53 ms
	_delay_ms(2);
#endif

#ifndef EIGHT_BIT

/****to define CONTROL PORT as OUTPUT PINS******/
	DIO_VidSetPinDirection(CONTROL_PORT,RS,HIGH);
	DIO_VidSetPinDirection(CONTROL_PORT,E,HIGH);
/****to define DATA PORT as OUTPUT PINS********/
	DIO_VidSetPinDirection(DATA_PORT,D7,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,D6,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,D5,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,D4,HIGH);
/******to initialize LCD after power***********/
	_delay_ms(40);
	//send function set commend
	LCD_VidSendCommend (FUNC_SET);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Display_ON & Cursor_OFF Command
	LCD_VidSendCommend(DISPLAY_ON_CURSOR_OFF);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Entry Mode Set Command
	LCD_VidSendCommend(ENTERY_MODE);
	// Delay for more than 39 us
	_delay_us(40);
	// Send Clear Display Command
	LCD_VidSendCommend(DISPLAY_CLEAR);
	// Delay for more than 1.53 ms
	_delay_ms(2);
#endif
}

void LCD_VidSendChar(u8 Copy_U8Char){

#ifdef EIGHT_BIT
	/******* to define RS / RW ***********/
	DIO_VidSetPinValue(CONTROL_PORT,RS,HIGH);
	/*to define value of character on port*/
	DIO_VidSetPortValue(DATA_PORT,Copy_U8Char);
	/*********to make enable pulse*********/
	DIO_VidSetPinValue(CONTROL_PORT,E,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
	_delay_ms(2);
#endif

#ifndef EIGHT_BIT

	/******* to define RS / RW ***********/
	DIO_VidSetPinValue(CONTROL_PORT,RS,HIGH);
	/******to out the value of upper_data on data port ****/
		DIO_VidSetPinValue(DATA_PORT,D7, GET_BIT(Copy_U8Char,7) );
		DIO_VidSetPinValue(DATA_PORT,D6, GET_BIT(Copy_U8Char,6) );
		DIO_VidSetPinValue(DATA_PORT,D5, GET_BIT(Copy_U8Char,5) );
		DIO_VidSetPinValue(DATA_PORT,D4, GET_BIT(Copy_U8Char,4) );
	/*************to make pulse for enable *************/
			DIO_VidSetPinValue(CONTROL_PORT,E,HIGH) ;
			_delay_ms(1);
			DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
			_delay_ms(2);
	/******to out the value of lower_data on data port*****/
		DIO_VidSetPinValue(DATA_PORT,D7, GET_BIT(Copy_U8Char,3) );
		DIO_VidSetPinValue(DATA_PORT,D6, GET_BIT(Copy_U8Char,2) );
		DIO_VidSetPinValue(DATA_PORT,D5, GET_BIT(Copy_U8Char,1) );
		DIO_VidSetPinValue(DATA_PORT,D4, GET_BIT(Copy_U8Char,0) );
	/*************to make pulse for enable *************/
		DIO_VidSetPinValue(CONTROL_PORT,E,HIGH) ;
		_delay_ms(1);
		DIO_VidSetPinValue(CONTROL_PORT,E,LOW);
		_delay_ms(2);

#endif

}

void LCD_VidSendString(u8 Copy_U8String[] ){
	u8 i=0;
	while( Copy_U8String[i] != '\0' ){
		if (15 == i){
			LCD_VidSendCommend(LINE_2_START);
		}
		LCD_VidSendChar(Copy_U8String[i]);
		_delay_us(1);
		i++;
	}//end while
}//end FUNC LCD_VidSendString

u32 LCD_U32Pow(u8 Copy_U8Base , u8 Copy_U8Bow ){
  u32 local_res = 1 ;
  while (Copy_U8Bow >0 ){
	  local_res *= Copy_U8Base ;
	  Copy_U8Bow--;
  }
  return  local_res ;
}

void LCD_VidPrintVar(u64 Copy_U8Var){
    u64 local_num = 0 ;
    u8 i = 0 ;
    // to check if it 0
	if (0 == Copy_U8Var){
		LCD_VidSendChar('0');
		return ;
	}//end if

	// to know the count of digit in the number
	while (  Copy_U8Var / (LCD_U32Pow(10,i) )  != 0 ){
		i++ ;
	}

	s8 copy_i = i-1 ;

	// to reverse the arrang of digits in num
	while ( copy_i >= 0 ){
		local_num += (Copy_U8Var % 10) * ( LCD_U32Pow(10,copy_i) ) ;
		Copy_U8Var/=10 ;
		copy_i-- ;
	}//end while

	// to print the digit in arrange
	while( i > 0 ){
		LCD_VidSendChar( (local_num % 10) +'0' ) ;
		local_num /= 10 ;
		i--;
	}//end while

}
void LCD_VidPosCur(u8 Copy_U8Row , u8 Copy_U8Col ) {
	u8 Local_Address = 0 ;
	if (Copy_U8Row == 0)
		Local_Address =0x80 ;
	else if (Copy_U8Row == 1)
		Local_Address =0xC0 ;
	if (Copy_U8Col < 16 )
		Local_Address += Copy_U8Col ;
	LCD_VidSendCommend ( Local_Address );
}
void LCD_VidClear (){
	LCD_VidSendCommend(DISPLAY_CLEAR) ;
}

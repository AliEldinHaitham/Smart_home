

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "DIO_interface.h"
#include "EX_INT_Interface.h"
#include "EX_INT_private.h"
#include "EX_INT_cfg.h"

/*arrange of make external interrupt should be like that
    GIE_VidEnable();                                   //to open global interrupt
	INT_VidINIT();
    PIE_VidEnable(0);                                  //to enable interrupt
    PIE_VidEnable(1);                                  //to enable interrupt
    PIE_VidEnable(2);                                  //to enable interrupt
  */

static void (*INT0_PFUNC)(void) = 0 ;
static void (*INT1_PFUNC)(void) = 0 ;
static void (*INT2_PFUNC)(void) = 0 ;


//preferred to use this FUNC in line 1 in main code to avoid some problems in memory
void EX_INT_VidSetCallBack (u8 Copy_NumOfINT , void (*ptr)(void)){
	switch (Copy_NumOfINT){
	case 0 :INT0_PFUNC = ptr ;             break ;
	case 1 :INT1_PFUNC = ptr ;             break ;
	case 2 :INT2_PFUNC = ptr ;             break ;
	}
}
/**********************************************************/
void EX_INT_VidINIT(void){

#ifdef INT0       //to define edge of interrupt 0
    if (INT0_SENSE == LOW_LEVEL) {
        //INT0 sense control = low level
    	CLR_BIT(MCUCR,ISC00);
    	CLR_BIT(MCUCR,ISC01);
    }
	else if (INT0_SENSE == CHANG_EDGE) {
		//INT0 sense control = change edge
    	SET_BIT(MCUCR,ISC00);
    	CLR_BIT(MCUCR,ISC01);
    }
    else if (INT0_SENSE == FALLING){
		//INT0 sense control = falling edge
        DIO_VidSetPinDirection(PORTD,PD2,LOW);     //to define bit interrupt 0 as input
        DIO_VidSetPinValue(PORTD,PD2,HIGH);        // pull up resistor on interrupt 0
		CLR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
    }
    else if (INT0_SENSE == RASING) {
        //INT0 sense control = raising edge
    	SET_BIT(MCUCR,ISC00);
        SET_BIT(MCUCR,ISC01);
    }
#endif

#ifdef INT1      //to define edge of interrupt 1
    if (INT1_SENSE == LOW_LEVEL) {
        //INT1 sense control = low level
    	CLR_BIT(MCUCR,ISC10);
    	CLR_BIT(MCUCR,ISC11);
    }
	else if (INT1_SENSE == CHANG_EDGE) {
		//INT1 sense control = change edge
    	SET_BIT(MCUCR,ISC10);
    	CLR_BIT(MCUCR,ISC11);
    }
    else if (INT1_SENSE == FALLING){
		//INT1 sense control = falling edge
        DIO_VidSetPinDirection(PORTD,PD3,LOW);     //to define bit interrupt 1 as input
        DIO_VidSetPinValue(PORTD,PD3,HIGH);        // pull up resistor on interrupt 1
		CLR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
    }
    else if (INT1_SENSE == RASING) {
        //INT1 sense control = raising edge
    	SET_BIT(MCUCR,ISC10);
        SET_BIT(MCUCR,ISC11);
    }
#endif

#ifdef INT2      //to define edge of interrupt 2
    if (INT2_SENSE == FALLING){
        DIO_VidSetPinDirection(PORTB,PB2,LOW);     //to define bit interrupt 2 as input
        DIO_VidSetPinValue(PORTB,PB2,HIGH);        // pull up resistor on interrupt 2
		CLR_BIT(MCUCSR,ISC2);		//INT2 sense control = falling edge
    }
    else if (INT2_SENSE == RASING) {
    	SET_BIT(MCUCSR,ISC2);        //INT2 sense control = raising edge
    }
#endif

}

/**********************************************************/
void EX_PIE_VidEnable(u8 COPY_U8INT_NUM){
	switch(COPY_U8INT_NUM) {
	case 0 : SET_BIT(GICR,INT0);  break ;   //INT0 Enable
	case 1 : SET_BIT(GICR,INT1);  break ;   //INT1 Enable
	case 2 : SET_BIT(GICR,INT2);  break ;   //INT2 Enable
	}
}

void EX_PIE_VidDisable(u8 COPY_U8INT_NUM){
	switch(COPY_U8INT_NUM) {
	case 0 : CLR_BIT(GICR,INT0);  break ;   //INT0 Enable
	case 1 : CLR_BIT(GICR,INT1);  break ;   //INT1 Enable
	case 2 : CLR_BIT(GICR,INT2);  break ;   //INT2 Enable
	}
}

/**********************************************************/
void __vector_1(void){
	//to toggle led
	INT0_PFUNC();
}

void __vector_2(void){
	//to toggle led
	INT1_PFUNC();
}

void __vector_3(void){
	//to toggle led
	INT2_PFUNC();
}

void EX_INT_VidSetEdge(u8 COPY_U8INT_NUM , u8 COPY_U8INT_EDGE){
	switch (COPY_U8INT_EDGE){
	case 1 :
		if (COPY_U8INT_NUM == 0 ){
			//INT0 sense control = falling edge
	        DIO_VidSetPinDirection(PORTD,PD2,LOW);     //to define bit interrupt 0 as input
	        DIO_VidSetPinValue(PORTD,PD2,HIGH);        // pull up resistor on interrupt 0
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
		}
		if (COPY_U8INT_NUM == 1 ){
			//INT1 sense control = falling edge
	        DIO_VidSetPinDirection(PORTD,PD3,LOW);     //to define bit interrupt 1 as input
	        DIO_VidSetPinValue(PORTD,PD3,HIGH);        // pull up resistor on interrupt 1
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
		}
		if (COPY_U8INT_NUM == 2 ){
	        DIO_VidSetPinDirection(PORTB,PB2,LOW);     //to define bit interrupt 2 as input
	        DIO_VidSetPinValue(PORTB,PB2,HIGH);        // pull up resistor on interrupt 2
			CLR_BIT(MCUCSR,ISC2);		//INT2 sense control = falling edge
		}
		break ;
	case 2 :
		if (COPY_U8INT_NUM == 0 ){
	        //INT0 sense control = raising edge
	    	SET_BIT(MCUCR,ISC00);
	        SET_BIT(MCUCR,ISC01);
		}
		if (COPY_U8INT_NUM == 1 ){
	        //INT1 sense control = raising edge
	    	SET_BIT(MCUCR,ISC10);
	        SET_BIT(MCUCR,ISC11);
		}
		if (COPY_U8INT_NUM == 2 ){
	    	SET_BIT(MCUCSR,ISC2);        //INT2 sense control = raising edge
		}
	    break ;
	case 3 :
		if (COPY_U8INT_NUM == 0 ){
			//INT0 sense control = low level
	    	CLR_BIT(MCUCR,ISC00);
	    	CLR_BIT(MCUCR,ISC01);
		}
		if (COPY_U8INT_NUM == 1 ){
	        //INT1 sense control = low level
	    	CLR_BIT(MCUCR,ISC10);
	    	CLR_BIT(MCUCR,ISC11);
		}
		break ;
	case 4 :
		if (COPY_U8INT_NUM == 0 ){
			//INT0 sense control = change edge
	    	SET_BIT(MCUCR,ISC00);
	    	CLR_BIT(MCUCR,ISC01);
		}
		if (COPY_U8INT_NUM == 1 ){
			//INT1 sense control = change edge
	    	SET_BIT(MCUCR,ISC10);
	    	CLR_BIT(MCUCR,ISC11);
		}
		break ;
	}
}




/*private*/
/*to define KEYPAD_PORT*/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/*to define HIGH VOLTAGE AND LOW VOLTAGE */
#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

/**************if KEYPAD_TYPE == KEYPAD_4*4 ******************/
#ifdef KEYPAD_4_4  //to define the number of rows and columns

#define KEYPAD_NUM_COL 4
#define KEYPAD_NUM_ROW 4

#endif


/**************if KEYPAD_TYPE == KEYPAD_3*3 ******************/
#ifdef KEYPAD_3_3  //to define the number of rows and columns

#define KEYPAD_NUM_COL 3
#define KEYPAD_NUM_ROW 3

#endif

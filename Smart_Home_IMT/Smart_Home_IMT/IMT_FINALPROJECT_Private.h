
#ifndef IMT_FINALPROJECT_PRIVATE_H_
#define IMT_FINALPROJECT_PRIVATE_H_


/* temperature*/
#define MAX_TEMP 38
#define MIN_TEMP 20
#define MID_TEMP 28

/*num of digits in password*/
#define NUM_OF_ELEMENT_IN_PASS 5

/* to discuss the staution of Home before entering the correct pass  */
#define EMERGENCY_STATE 1
#define NORMAL_STATE    2

/* no input from keypad  */
#define NO_INPUT_NUM   0

/* to control in flags */
#define RISE_FLAG 1
#define LOW_FLAG  0

/* to define ports */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* to check on flags */
#define HIGH 1
#define LOW 0

/* to control on DC motor*/
#define STOP 0
#define CLK_WISE 1
#define ANTI_CLK_WISE 2


/* duty*/
#define ZERO_DUTY     0
#define QUATER_DUTY  25
#define MID_DUTY     50
#define THREE_QUATER 75
#define FULL_DUTY    100

#define FALLING    1
#define RASING     2
#define LOW_LEVEL  3
#define CHANG_EDGE 4

#endif /* IMT_FINALPROJECT_PRIVATE_H_ */

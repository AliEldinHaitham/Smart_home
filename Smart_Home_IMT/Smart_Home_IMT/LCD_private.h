
/*** to enable 8-bit mode ***/
#ifdef EIGHT_BIT
#define FUNC_SET 0b00111100
#endif

/*** to enable 4-bit mode ***/
#ifndef EIGHT_BIT
#define FUNC_SET 0b00101100
#endif

/****** commmon commend  ********/
#define DISPLAY_ON_CURSOR_ON_BLINKING 0x0F
#define DISPLAY_CLEAR  0x01
#define HOME_RETURN 0x02
#define DISPLAY_ON_CURSOR_ON 0x0E
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define DISPLAY_OFF_CURSOR_OFF 0x08
#define DISPLAY_SHIFT_RIGHT 0x1C
#define DISPLAY_SHIT_LEFT 0x18
#define CURSOR_SHIFT_RIGHT 0x14
#define CURSOR_SHIFT_LEFT 0x10
#define LINE_2_START 0xC0
#define ENTERY_MODE 0x06


#define HIGH 1
#define LOW 0

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3


#ifdef FOUR_BIT

#define D7 7
#define D6 6
#define D5 5
#define D4 4

#endif


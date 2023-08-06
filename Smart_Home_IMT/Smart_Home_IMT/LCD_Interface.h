
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"LCD_private.h"

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
 
void LCD_VidInit();
void LCD_VidSendCommend(u8 Copy_U8Commend);
void LCD_VidSendChar(u8 Copy_U8Char);
void LCD_VidSendString(u8 Copy_U8String[] );
void LCD_VidPrintVar(u64 Copy_U8Var);
u32 LCD_U32Pow(u8 Copy_U8Base , u8 Copy_U8Bow );
void LCD_VidPosCur(u8 Copy_U8Row , u8 Copy_U8Col ) ;
void LCD_VidClear ();

#endif

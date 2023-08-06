
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define EX_REF 0                             //to define V REFERENCE
#define AVCC_5V 1                            //to define V REFERENCE
#define INTERNAL_AVREF_2.5 3                 //to define V REFERENCE

#define PRE_SCALAR_2    0                     //to define PRE_SCALAR
#define PRE_SCALAR_2_   1                     //to define PRE_SCALAR
#define PRE_SCALAR_4    2                     //to define PRE_SCALAR
#define PRE_SCALAR_8    3                     //to define PRE_SCALAR
#define PRE_SCALAR_16   4                     //to define PRE_SCALAR
#define PRE_SCALAR_32   5                     //to define PRE_SCALAR
#define PRE_SCALAR_64   6                     //to define PRE_SCALAR
#define PRE_SCALAR_128  7                     //to define PRE_SCALAR

#define RIGHT_ADJEUSTED 0                     //to define how to read data register
#define LEFT_ADJUSTED 1                       //to define how to read data register

#define VREF  5
#define MAX_DIGITAL 1023

#define ADMUX *((volatile u8*)(0x27))
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4 4
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

#define ADCSRA *((volatile u8*)(0x26))
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#define ADCH *((volatile u8*)(0x25))
#define ADC  *((volatile u16*)(0x24))

#endif /* ADC_PRIVATE_H_ */

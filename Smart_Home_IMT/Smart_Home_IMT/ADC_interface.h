
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_VidInit (void);                                 //to initialize ADC perpherial
u16 ADC_VidReadChannel (u8 Copy_U8Channel);              //to specific read channel
void ADC_VidDeinit (void);                               //to de_initialize ADC perpherial

#endif /* ADC_INTERFACE_H_ */

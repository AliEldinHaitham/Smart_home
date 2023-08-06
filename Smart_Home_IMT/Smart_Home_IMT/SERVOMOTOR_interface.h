#ifndef SERVOMOTOR_INTERFACE_H_
#define SERVOMOTOR_INTERFACE_H_

/*All components operate at frequency of 50 Hz*/
/*The functions are based on PWM generation of TIMER1 */


#define OC1A_PIN 5
#define OC1B_PIN 4

void SERVOMOTOR_VidSetDirection(u8 Degree,u8 PWMPin);


#endif /* PWMCOMPONENTS_INTERFACE_H_ */

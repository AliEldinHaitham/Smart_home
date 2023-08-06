

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/* (voltage reference selection bit)
   to select :  REFS1   REFS0
   External V    0        0         "EX_REF" "0"
   AVCC = 5 V    0        1         "AVCC_5V" "1"
   VREF = 2.5 V  1        1         "INTERNAL_AVREF_2.5" "3"
*/

#define VREF_USED AVCC_5V

	/*
	 - to enable ADC perpherial
	 - to select specific :
	 1) pre_scalar  /2    0 0 0 or 0 0 1      "PRE_SCALAR_2"  "0" "1"
	 2) pre_scalar  /4    0 1 0               "PRE_SCALAR_4"  "2"
	 3) pre_scalar  /8    0 1 1               "PRE_SCALAR_8"  "3"
	 4) pre_scalar  /16   1 0 0               "PRE_SCALAR_16" "4"
	 5) pre_scalar  /32   1 0 1               "PRE_SCALAR_32" "5"
	 6) pre_scalar  /64   1 1 0               "PRE_SCALAR_64" "6"
	 7) pre_scalar  /128  1 1 1               "PRE_SCALAR_128" "7"
	  */
#define PRE_SCALAR PRE_SCALAR_128

	/*
	  - "RIGHT_ADJEUSTED" "0"
	  - "LEFT_ADJUSTED"   "1"
	 */
#define ADJUSTED_USED RIGHT_ADJEUSTED

#endif /* ADC_CFG_H_ */

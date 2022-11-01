// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void pwm_init (void);

void pwm_set (int *pwm_dc1, int *pwm_dc2, int PWM_DIR);

int pwm_calc(int ADCr, int *pwm_dc1, int *pwm_dc2, int PWM_DIR);

#endif	/* XC_HEADER_TEMPLATE_H */


#include <pic16f886.h>

void pwm_init (void) {
    // Input switch
    TRISB6 = 1; // SW é entrada
    nRBPU = 0;  // permite usar pull-ups no Port B
    WPUB6 = 1;  // liga weak pull-up para SW
    IOCB6 = 1;  // usa I-O-C para SW
    RBIE = 1;   // habilita interrupção do Port B
    
    // LED output -> PWMn_DIR
    TRISA1 = 0; // PORTA pin 1 configured as output
    ANS1 = 0;   // PORTA pin 1 (AN1) as digital I/O
    RA1 = 1;    // PORTA pin 1 output logic level is HIGH
    TRISB1 = 0; // PORTB pin 1 configured as output
    ANS10 = 0;  // PORTB pin 1 (AN11) as digital I/O
    RB1 = 1;    // PORTB pin 1 output logic level is HIGH
    
    // PWM1 & PWM2 config
    TRISC1 = 1;                   // PORTC pin 1 configured as output
    TRISC2 = 1;                   // PORTC pin 2 configured as output
    PR2 = 249;                    // Timer2 Module Period Register
    CCP1CONbits.P1M = 0b00;       // PWM1: Single output; P1A modulated; P1B, P1C, P1D assigned as port pins
    CCP1CONbits.CCP1M = 0b1100;   // PWM1 mode: P1A, P1C active-high; P1B, P1D active-high
    CCP2CONbits.CCP2M = 0b1100;   // PWM2 mode (11xx)
    T2CONbits.T2CKPS = 0b01;      // TMR2 Prescaler = 4
    T2CONbits.TMR2ON = 0b1;       // TMR2 is ON
    TMR2IF = 0;                   // Timer2 to PR2 Interrupt Flag bit  ->  0: no match occurred
    unsigned int n = 500;         // PWM1 = PWM2 = 50%
    CCPR1L = n >> 2;              // PWM Register 1 Low Byte (LSB)
    CCPR2L = n >> 2;              // PWM Register 2 Low Byte (LSB)
    CCP1CONbits.DC1B = n % 4;     // PWM1 Duty Cycle Least Significant bits
    CCP2CONbits.DC2B0 = n & 0b01; // PWM2 Duty Cycle Least Significant bits
    CCP2CONbits.DC2B1 = n & 0b10;
    while(!TMR2IF) // wait TMR2 quit overflow
    TRISC1 = 0;    // PORTC pin 1 configured as input
    TRISC2 = 0;    // PORTC pin 1 configured as input
}

void pwm_set (int *pwm_dc1, int *pwm_dc2, int PWM_DIR) {
    // nDC = round( 4 * (PR2 + 1) * d )       , with d->[0,1]
    // nDC = round( 4 * (PR2 + 1) * D / 100 ) , with D->[0,100]
    // For PR2 = 249
    // nDC = round( 4 * 250 * D / 100 ) = round( 10 * D ) = 10 * D
    // For D = 50   ->   nDC = 500
    unsigned int n1 = 10 * (PWM_DIR * (*pwm_dc1)); // PWM1
    unsigned int n2 = 10 * (PWM_DIR * (*pwm_dc2)); // PWM2
    
    CCPR1L = n1 >> 2;              // PWM Register 1 Low Byte (LSB)
    CCP1CONbits.DC1B = n1 % 4;     // PWM1 Duty Cycle Least Significant bits
    
    CCPR2L = n2 >> 2;              // PWM Register 2 Low Byte (LSB)
    CCP2CONbits.DC2B0 = n2 & 0b01; // PWM2 Duty Cycle Least Significant bits
    CCP2CONbits.DC2B1 = n2 & 0b10;
    
    while(!TMR2IF) // wait TMR2 quit overflow
    TRISC1 = 0;    // PORTC pin 1 configured as input
    TRISC2 = 0;    // PORTC pin 1 configured as input
}

int pwm_calc(int ADCr, int *pwm_dc1, int *pwm_dc2, int PWM_DIR) {
    // Mmax = 512 -> max value in symmetric scale measument
    // x/Mmax = x>>9 (less computation)
    // L = 75 mm  -> car length
    int R; // Radius
    int M = ADCr - 512; // symmetric scale
    
    if (M == 0) R = 0; // R = INF
    else R = 19200 / M; // R = (Mmax*L)/(2*M) = 19200/M  [mm]

    *pwm_dc1 = (25 * (512 - M)) >> 8; // PMW1 = 50*(1-M/Mmax)  [0-100%]
    *pwm_dc2 = 100 - *pwm_dc1;        // PWM2 = 50*(1+M/Mmax)  [0-100%]
    // PWM1 + PWM2 = 100
    
    *pwm_dc1 = PWM_DIR * (*pwm_dc1); // car direction: +1 (forward) or -1 (backward)
    *pwm_dc2 = PWM_DIR * (*pwm_dc2);
    
    return R;
}
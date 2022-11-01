/* 
 * PMR3406 - Microcontroladores (2021)
 * Turma 02 - Grupo 07 - MMB
 * Author: Marcelo Monari Baccaro
 * Created on June 05, 2021, 13:05
 */

// PIC16F886 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EC        // Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <pic16f886.h>
#include <xc.h>
#include <stdio.h>
#include "always.h"
#include "delay.h"
#include "io.h"
#include "lcd.h"
#include "adc.h"
#include "debug.h"
#include "pwm.h"

#define TMR0_PRESCALER 6 // divide por n=128 -> Tpsl=Toscx4*n=0.0256ms
#define POLLING_PERIOD 195 // m=round(Tobj/Tpsl)=195 -> T=Tpsl*m=4.992ms ~ 5ms
#define TMR0_SETTING (255 - POLLING_PERIOD) // valor inicial da contagem do Timer 0

// global variables
volatile unsigned int ADCr = 0; // ADC measurement
volatile int R, PWM1, PWM2;     // Raio, PWMs
volatile int PWM_DIR = 1;       // car direction: +1 (forward) or -1 (backward)

void interrupt isr(void) {
  // Tratamento da interrupção do Timer 0
  if (T0IE && T0IF) {
    ADCr = adc_read_0(); // leitura do ADC
    TMR0 = TMR0_SETTING ; // valor inicial do Timer 0
    T0IF = 0; // limpa a flag do Timer 0
  }
  
  // Tratamento da interrupção do Port B
  if (RBIE && RBIF) {
    char portB = PORTB; // leitura do port B -> limpa interrupção
    io_sw_read(portB);  // lê o estado da chave
    if (io_sw_pressed()) {
      RA1 = ~RA1;   // inverte LED PWM_DIR1
      RB1 = ~RB1;   // inverte LED PWM_DIR2
      PWM_DIR = -PWM_DIR; // inverte sinal
      PWM1 = -PWM1; // inverter sinal
      PWM2 = -PWM2; // inverter sinal
    }
    RBIF = 0; // limpa o flag de interrupção do Port B
  }
}

// Inicialização do Timer 0
void t0_init(void) {
  T0IE = 1; // habilita a interrupção do Timer 0
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0; // prescaler usado no Timer 0 e não no WDT (watchdog)
  OPTION_REGbits.PS = TMR0_PRESCALER ; // prescaler do Timer 0
  TMR0 = TMR0_SETTING ; // valor inicial do Timer 0
}

// Programa Principal
void main(void) {
  //variáveis locais
  char message[16];  // "string" para mensagens

  // Inicializações
  t0_init();    // inicializa Timer 0
  lcd_init();   // inicializa LCD
  adc_init_0(); // inicializa ADC
  pwm_init();   // inicializa PWM, chave e os LED de PWM_DIR
  ei();         // macro do XC8, equivale a GIE = 1, habilita interrupções
  delay_us(10); // wait for ADC initialization

  // Configurações iniciais
  lcd_cursor(0); // desliga o cursor do LCD  

  // Loop principal (infinito)
  while(1) {
    R = pwm_calc (ADCr, &PWM1, &PWM2, PWM_DIR);

    pwm_set (&PWM1, &PWM2, PWM_DIR);

    if (R == 0) sprintf(message, "Radius = %c    mm", 0xf3);
    else sprintf(message, "Radius = %05dmm", PWM_DIR * R);
    lcd_goto(0);
    lcd_puts(message);

    sprintf(message, "P1=%04d%% P2=%04d%%", PWM1, PWM2);
    lcd_goto(64);
    lcd_puts(message);

    delay_ms(200); // espera de 200 ms
  }
}

/*
 * File:   debug.c
 * Author: Jun Okamoto Jr.
 *
 * Created on April 28, 2020, 20:36
 */

#include <xc.h> // include processor files - each processor file is guarded.

#define D_LED1 RA4
#define D_LED2 RB2
#define D_LED3 RB1

void debug_init(void) {
  TRISA4 = 0; // RA4 - LED 1 é saída
  TRISB2 = 0; // RB2 - LED 2 é saída
  TRISB1 = 0; // RB1 - LED 3 é saída
  
  ANS8 = 0;   // RB2 é digital
  ANS12 = 0;  // RB1 é digital
}

void debug_led_on(char led) {
  switch (led) {
    case 1:
      D_LED1 = 1;
      break;
    case 2:
      D_LED2 = 1;
      break;
    case 3:
      D_LED3 = 1;
      break;
    default:
      break;
  }      
}

void debug_led_off(char led) {
    switch (led) {
    case 1:
      D_LED1 = 0;
      break;
    case 2:
      D_LED2 = 0;
      break;
    case 3:
      D_LED3 = 0;
      break;
    default:
      break;
  }
}

void debug_led_toggle(char led) {
  switch (led) {
    case 1:
      D_LED1 = ~D_LED1;
      break;
    case 2:
      D_LED2 = ~D_LED2;
      break;
    case 3:
      D_LED3 = ~D_LED3;
      break;
    default:
      break;
  }  
}

/*
 * File:   io.c
 * Author: Jun Okamoto Jr.
 *
 * Created on April 18, 2020, 12:58 PM
 */

#include <xc.h> // include processor files - each processor file is guarded.
#include "always.h"
#include "delay.h"
#include "io.h"

#define LED RB5
#define SW  RB6
#define BUZZER RB7

void io_init(void) {
  TRISB5 = 0; // LED é saída
  ANS13 = 0;  // [jo:200504] LED é junto com AN13 e é digital (corrigido)
  TRISB7 = 0; // BUZZER é saída
  TRISB6 = 1; // SW é entrada
  nRBPU = 0;  // permite usar pull-ups no Port B
  WPUB6 = 1;  // liga weak pull-up para SW
  IOCB6 = 1;  // usa I-O-C para SW
  RBIE = 1;   // habilita interrupção do Port B
}

void io_led_on(void) {
  LED = 1;
}

void io_led_off(void) {
  LED = 0;
}

void io_led_toggle(void) {
  LED = ~LED;
}

void io_beep(int period) {
  while (period-- > 0) {
    BUZZER = 1;
    delay_ms(4);
    BUZZER = 0;
    delay_ms(4);
  }
}

void io_sw_read(char port) {
  static char swOld = 1; // para armazenar o estado anterior
  char swNew = (port & 0b01000000) >> 6; // retira o bit 6
  if (swNew == 0 && swOld == 1) { // detecta borda de descida
    swPressed = TRUE; // seta flag
  }
  swOld = swNew; // guarda o estado
}

int io_sw_pressed(void) {
  if (swPressed) { // se a chave foi pressionada
    swPressed = FALSE; // reseta flag
    return TRUE;
  }
  return FALSE;
}

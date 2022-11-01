/* 
 * File:        debug.h
 * Author:      Jun Okamoto Jr.
 * Comments:
 *   Essas funções podem ser usadas para debugar os programas marcando a
 *   passagem por certos trechos ligando de desligando LEDs.
 *   São disponíveis 3 leds, numerados de 1 a 3.
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DEBUG_H
#define	DEBUG_H

#include <xc.h> // include processor files - each processor file is guarded.  

///
/// Inicializa LEDs de debug
///
extern void debug_init(void);

///
/// Liga LEDs de debug
/// @param led - número do LED de 1 a 3
///
extern void debug_led_on(char led);

///
/// Desliga LEDs de debug
/// @param led - número do LED de 1 a 3
///
extern void debug_led_off(char led);

///
/// Chaveia LEDs de debug
/// @param led - número do LED de 1 a 3
///
extern void debug_led_toggle(char led);

#endif	/* DEBUG_H */


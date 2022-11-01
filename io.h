/*
 * File:   io.h
 * Author: Jun Okamoto Jr.
 *
 * Created on April 18, 2020, 12:58 PM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_H
#define	IO_H

volatile bit swPressed;

extern void io_init(void);

extern void io_led_on(void);

extern void io_led_off(void);

extern void io_led_toggle(void);

extern void io_beep(int period);

extern void io_sw_read(char port);

extern int io_sw_pressed(void);


#endif	/* IO_H */


/*
 * File:   delay.h
 * Author: Jun Okamoto Jr.
 *
 * Created on April 19, 2020, 15:29
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DELAY_H
#define	DELAY_H

#define _XTAL_FREQ 20000000 // define a frequencia do clock em MHz

// Atrasos produzidos por macros do compilador

// Produz atraso em ms, time < 50.463.240
#define delay_ms(time) __delay_ms(time)

// Produz atraso em us, time < 50.463.240
#define delay_us(time) __delay_us(time)

#endif	/* DELAY_H */

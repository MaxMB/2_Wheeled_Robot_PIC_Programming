/*
 * File:   serial.h
 * Author: Jun Okamoto Jr.
 *
 * Created on April 18, 2020, 12:58 PM
 */

#ifndef SERIAL_H
#define SERIAL_H

/// Inicializa o canal serial
void serial_init(void);

/// Verifica e retorna um caractere de 8-bits
/// Se nenhum caractere estiver disponível no buffer
/// de recepção esta função retorna 255.
/// IMPORTANTE: sempre retorna sem esperar
///
unsigned char chkchr(void);

/// Envia um caractere de 8-bits pelo canal serial
void putch(unsigned char c);

/// Envia um string pelo canal serial
void putst(register const char * str);

/// Envia um Line Feed
#define putlf putst("\n")

#endif

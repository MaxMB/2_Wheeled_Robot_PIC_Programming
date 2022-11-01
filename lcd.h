///
/// LCD interface header file
///
/// File: lcd.h
/// Author: Jun Okamoto Jr.
/// Date: 18/04/2020
///

#ifndef LCD_H
#define LCD_H

///
/// Inicializa LCD - deve ser chamado antes de usar
///
extern void lcd_init(void);

/// Limpa o LCD e coloca o cursor na 1a. posição da 1a. linha 
/// Não deve ser chamado dentro de loops, é muito lento
extern void lcd_clear(void);

///
/// Escreve um string no LCD na posição do cursor
/// @param s - vetor de caracteres contendo string
///
extern void lcd_puts(const char * s);

///
/// Coloca o cursor na posição definida
/// @param pos -   0 a  40 - 1a. linha
///               64 a 104 - 2a. linha
///
extern void lcd_goto(unsigned char pos);

///
/// Desliga e liga o cursor
/// @param on - 1 = ON; 0 = OFF
///
extern void lcd_cursor(int on);

///
/// Escreve um caracter no LCD na posição do cursor
/// @param c - caracter ASCII
///
extern void lcd_putchar(char c);

#endif
#include <pic16f886.h>

extern void adc_init_0 (void) {
    TRISA0 = 1; // AN0 = RA0 (pino 0 do Port A) � entrada
    ANS0 = 1; // pino 0 do Port A tem I/O anal�gico
    ADCON0bits.ADCS = 0b10; // ADCS[1:0] = 10 -> Facd1b = Fosc / 32
    VCFG1 = 0; // Vref- = Vss =  0V
    VCFG0 = 0; // Vref+ = Vdd = +5V
    ADCON0bits.CHS = 0b0000; // convers�o pelo canal AN0
    ADFM = 1; // justificado a direita
    ADON = 1; // liga conversor ADC
}

extern unsigned int adc_read_0 (void) {
    GO = 1; //inicializa convers�o
    while (GO); // espera convers�o acabar
    unsigned int ADCr = (ADRESH << 8) | ADRESL; // ADRESH * 256 + ADRESL
    ADIF = 0; // limpa flag da convers�o
    return ADCr;
}

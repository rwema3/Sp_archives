/*
 * File:   main_function.c
 * Author: imrwe
 *
 * Created on January 26, 2024, 4:38 PM
 */

#include <xc.h>

#define _XTAL_FREQ 20000000 // Using 20MHz Crystal

void main(void) {
    TRISB = 0x00; // Configure PORTB as output
    TRISC = 0x00; // Configure PORTC as output
    
    while(1) {
        PORTB = 0xFF; // Turn ON all LEDs connected to PORTB
        PORTC = 0xFF; // Turn ON all LEDs connected to PORTC
        __delay_ms(500); 
        
        PORTB = 0x00; // Turn OFF all LEDs connected to PORTB
        PORTC = 0x00; // Turn OFF all LEDs connected to PORTC
        __delay_ms(500); // Delay of 500ms
    }
}

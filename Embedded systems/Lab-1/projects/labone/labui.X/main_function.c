#include <xc.h>

#define _XTAL_FREQ 20000000 // Using 20MHz Crystal

// Function to initialize the ports
void initializePorts(void) {
    TRISB = 0x00; // Configure PORTB as output
    TRISC = 0x00; // Configure PORTC as output
    TRISD = 0x00; // Configure PORTD as output
    TRISE = 0x00; // Configure PORTE as output
    TRISA = 0x00; // Configure PORTA as output
}

// Function to turn ON all LEDs for the specified port
void turnOnAllLEDs(char *port) {
    *port = 0xFF; // Turn ON all LEDs for the specified port
}

// Function to turn OFF all LEDs for the specified port
void turnOffAllLEDs(char *port) {
    *port = 0x00; // Turn OFF all LEDs for the specified port
}

void main(void) {
    char *portB = &PORTB;
    char *portC = &PORTC;
    char *portD = &PORTD;
    char *portE = &PORTE;
    char *portA = &PORTA;

    initializePorts();
    
    while(1) {
        turnOnAllLEDs(portB);
        turnOnAllLEDs(portC);
        turnOnAllLEDs(portD);
        turnOnAllLEDs(portE);
        turnOnAllLEDs(portA);
        __delay_ms(500); 
        
        turnOffAllLEDs(portB);
        turnOffAllLEDs(portC);
        turnOffAllLEDs(portD);
        turnOffAllLEDs(portE);
        turnOffAllLEDs(portA);
        __delay_ms(100); // Delay of 500ms
    }
}

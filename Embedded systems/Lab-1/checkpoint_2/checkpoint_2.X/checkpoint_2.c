#include <xc.h>

#define BUTTON_PRESSED 0

// Function to check the button state and toggle LED accordingly
void toggleLED(int *buttonState) {
    if (PORTCbits.RC0 == BUTTON_PRESSED) {
        // Button is pressed
        *buttonState = !(*buttonState);  // Toggle button state
    }

    // Check the button state and set the LED accordingly
    if (*buttonState == 1) {
        PORTBbits.RB0 = 1; // Set RB0 high
    } else {
        PORTBbits.RB0 = 0; // Set RB0 low
    }
}

void main() {
    TRISBbits.TRISB0 = 0; // Set RB0 as an output
    TRISCbits.TRISC0 = 1; // Set RC0 as an input

    int buttonState = 0;  // Variable to track button state

    while(1) {
        toggleLED(&buttonState);  // Call the function to handle button state and LED
    }    
}

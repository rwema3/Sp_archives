# 1 "checkpoint_2.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/MCPxxxx_DFP/1.4.59/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "checkpoint_2.c" 2
void main() {
    TRISB0 = 0;
    TRISC0 = 1;

    while(1) {
        if (PORTC0 == 0) {
            PORTB0 = 1;
        } else {
            PORTB0 = 0;
        }
    }
}

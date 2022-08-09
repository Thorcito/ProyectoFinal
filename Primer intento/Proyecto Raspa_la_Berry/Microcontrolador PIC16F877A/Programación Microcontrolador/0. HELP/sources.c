#define _XTAL_FREQ 24000000 //20 MHz

#include <xc.h>

void main() {
    
    TRISB=0b00000010;
    PORTB=0b00000010;
     
    __delay_ms (100);

    while (1){
        if (PORTBbits.RB1 == 0){
        PORTBbits.RB0 = 1;
        __delay_ms (100);
        }

        else{
        PORTBbits.RB0 = 0;
        }
    }
}

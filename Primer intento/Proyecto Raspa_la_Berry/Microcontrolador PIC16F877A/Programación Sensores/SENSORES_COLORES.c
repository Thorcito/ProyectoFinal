#define _XTAL_FREQ 24000000

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

void Deteccion_Impacto (){
//impactamos el color verde
if (PORTD.RD0 == 1){
PORTD.RD4 = 1;
PORTD.RD5 = 0;
PORTD.RD6 = 0;
PORTD.RD7 = 0;
}
//impactamos el color negro
else if (PORTD.RD1 == 1){
PORTD.RD4 = 0;
PORTD.RD5 = 1;
PORTD.RD6 = 0;
PORTD.RD7 = 0;
}
//impactamos color azul
else if (PORTD.RD2 == 1){
PORTD.RD4 = 0;
PORTD.RD5 = 0;
PORTD.RD6 = 1;
PORTD.RD7 = 0;
}
//impactamos color rojo
else if (PORTD.RD3 == 1){
PORTD.RD4 = 0;
PORTD.RD5 = 0;
PORTD.RD6 = 0;
PORTD.RD7 = 1;
}
else {
 PORTD.RD4 = 0;
PORTD.RD5 = 0;
PORTD.RD6 = 0;
PORTD.RD7 = 0;
}
}




void main() {

//Senal de los sensores
TRISD.RD0 = 1;  //color verde
TRISD.RD1 = 1;  //color negro
TRISD.RD2 = 1;  //color azul
TRISD.RD3 = 1;  //color rojo

TRISD.RD4 = 0;  //impacto color verde
TRISD.RD5 = 0;  //impacto color negro
TRISD.RD6 = 0;   //impacto color azul
TRISD.RD7 = 0;   //impacto color rojo

PORTD = 0b00000000; //se inicializan con un valor de 0

while (1){
Deteccion_Impacto();
}


}
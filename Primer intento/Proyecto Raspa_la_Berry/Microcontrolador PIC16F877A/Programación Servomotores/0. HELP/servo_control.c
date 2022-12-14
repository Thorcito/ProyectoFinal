#define _XTAL_FREQ 24000000
#include <xc.h>
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
void ADC_INITI() {

ADCON0 = 0x41; //ADC Module Turned ON and Clock is selected
                 //lectura_movimiento
                 //binary 1100 0001
                 //01=CLK/8
                 //000= Pin:A0
                 //0=go/done
                 //0=X 'NO IMPORTA'
                 //1=A/D is powered on
ADCON1 = 0xC4; //binario 10000100
               //1 = adresl
               //1 = CLK/16
               //00 cale picha
               //0100 =  A0,A1, A3
}


unsigned int ADC_Read1(unsigned char canal){
ADCON0 &= 0xC5; //Clear de canal
ADCON0 |= (canal<<3); //Shifteamos 3 para movernos a los bit responsables de direccion en ADCON0
ADCON0 |= 4;//inicia la lectura
__delay_ms(100); //tiempo en el que el capacitor carga los datos
ADCON0.GO =0;
//while (ADCON0.GO == 1) {
return ((ADRESH <<8) + ADRESL); //Retorna los 8bits ya que no son necesarios los 10 para esta aplicacion
//}
}

 //variables a utilizar
int HOR;
int VER;




void main(){
 //Se iniciliazan como inputs
TRISA.RA0 = 1;
TRISA.RA1 = 1;
TRISA.RA3 = 1;
//se iniicializan los puertos de entrada
PORTA.RA0 = 0;
PORTA.RA1 = 0;
PORTA.RA2 = 0;
//se inicializan como outputs
TRISB.RB3 = 0;  //motor horizontal
TRISB.RB4 = 0;  //motor vertical
TRISB.RB5 = 0;  //motor horizontal
TRISB.RB6 = 0;  //motor vertical
//se inicializan los puertos de las salidas
PORTB.RB3 = 0;
PORTB.RB4 = 0;
PORTB.RB5 = 0;
PORTB.RB6 = 0;
ADC_INITI();
__delay_ms(100);
__delay_ms(100);


/*while (1){
HOR = ADC_Read1(0);  //movimiento horizontal
if (HOR < 200){
PORTB.RB3 = 1;
PORTB.RB4 = 0;
}
else if (HOR > 800){
PORTB.RB3 = 0;
PORTB.RB4 = 1;
}
else {
PORTB.RB3 = 0;
PORTB.RB4 = 0;
}
VER = ADC_Read1(1);  //movimiento vertical
if (VER < 200){
PORTB.RB5 = 0;
PORTB.RB6 = 1;
}
else if (VER > 800){
PORTB.RB5 = 1;
PORTB.RB6 = 0;
}
else {
PORTB.RB5 = 0;
PORTB.RB6 = 0;
}
//VER = ADC_Read (1); //movimiento vertical
//if (VER |= 0){}
}
*/
while (1){
HOR = ADC_Read1 (0);  //movimiento horizontal
if (HOR < 500){
PORTB.RB3 = 1;
__delay_ms(1);
PORTB.RB3 = 0;
__delay_ms(19);
}
if (HOR > 530){
PORTB.RB3 = 1;
__delay_us(2200);
PORTB.RB3 = 0;
__delay_ms(19);
}
if (HOR >= 500, HOR <= 530){
PORTB.RB3 = 1;
__delay_us(1500);
PORTB.RB3 = 0;
__delay_ms(19);
}
}
}

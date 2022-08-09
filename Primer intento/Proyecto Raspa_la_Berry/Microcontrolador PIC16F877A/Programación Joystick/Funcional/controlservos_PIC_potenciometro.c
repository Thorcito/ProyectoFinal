/* 
 * File:   prueba_personal.c
 * Author: usuario
 *
 * Created on 18 de mayo de 2022, 09:06 PM
 */
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

#include <xc.h>

//TIMER0    8-bit    $$RegValue = 256-((Delay * Fosc)/(Prescalar*4))$$

char value = 0;
int on_time1 ;//= 150; //On-Time for the PWM signal
int count1; //count gets incremented for every timer overlap
int pot_value1;

//another potenciometer
int on_time2 ;//= 150; //On-Time for the PWM signal
int count2; //count gets incremented for every timer overlap
int pot_value2;

/*********ADC Functions*********/
void ADC_Init()
{
  ADCON0 = 0x41; //ADC Module Turned ON and Clock is selected
  ADCON1 = 0xC0; //All pins as Analog Input
                //With reference voltages VDD and VSS
}
unsigned int ADC_Read(unsigned char channel)
{
  if(channel > 7) //If Invalid channel selected 
    return 0;     //Return 0
  ADCON0 &= 0xC5; //Clearing the Channel Selection Bits, funciona como una AND: C &= 2 is same as C = C & 2
  ADCON0 |= channel<<3; //Setting the required Bits, funciona como una OR: C |= 2 is same as C = C | 2
  __delay_ms(2); //Acquisition time to charge hold capacitor
  GO_nDONE = 1; //Initializes A/D Conversion
  while(GO_nDONE); //Wait for A/D Conversion to complete
  return ((ADRESH<<8)+ADRESL); //Returns Result
}
  //*************************************************//

/*void __interrupt() timer_isr(void)
{  
    if(TMR0IF==1) // Timer has overflown
    {
        TMR0 = 252;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
                          TImer0 needs two instruction Cycles to start incrementing TMR0 
        TMR0IF=0;       // Clear timer interrupt flag
        count1++;
        count2++;
    } 
    
    if (count1 >= on_time1)
    {
        RB0=1;  // complement the value for blinking the LEDs
    }

    if (count1 >= (on_time1+(200-on_time1)))
    {
        RB0=0;
        count1=0;
    }
    
    //
    
    if (count2 >= on_time2)
    {
        RB1=1;  // complement the value for blinking the LEDs
    }

    if (count2 >= (on_time2+(200-on_time2)))
    {
        RB1=0;
        count2=0;
    }
}
*/
void main()
{    
 /***************I/O PORT Initialization*************/
  TRISB = 0x00; //RB0 used as Servo signal pin
  TRISA = 0xFF; //Analog inputs 
 //*************************************************//

 ADC_Init(); //Initializes ADC Module
    OPTION_REG = 0b00000100;  // Timer0 with external freq and 32 as prescaler
    TMR0=251;       // Load the time value for 1us delayValue can be between 0-256 only
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt

    while(1)
    { 
        pot_value1 = (ADC_Read(4))*0.039; // el valor que se encuentra dentro del ADC_read es el canal ANx
        on_time1 = (170-pot_value1);
        
        pot_value2 = (ADC_Read(3))*0.039; // el valor que se encuentra dentro del ADC_read es el canal ANx
        on_time2 = (170-pot_value2);
    }
}
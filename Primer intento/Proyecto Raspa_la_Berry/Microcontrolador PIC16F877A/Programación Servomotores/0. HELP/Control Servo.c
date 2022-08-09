/*
 * File:   Control Servo.c
 * Author: Jorge Peralta C
 * Canal Youtube: Jorge APC
 *
 * Created on 27 de abril de 2019, 08:28 AM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000             //Frecuencia del Oscilador 20MHz.
#define PWM_Frequency 0.05              // in KHz (50Hz)

//TIMER0    8 bits y Prescaler de 64
//valor desbordamiento = 256-((retardo * Fosc)/(Prescalar*4))   retardo en s y frecuencia en hz

int POT_val;                            // En esta variable almacenamos el valor de ADC
int count;                              // Contador
int T_TOTAL = (1/PWM_Frequency)/10;     //Tiempo Total Periodo en milisegundos //2msec
int T_ON=0;                             //Valor tiempo en ON
int Duty_cycle;                         //Ciclo de trabajo señal PWM

void ADC_Initialize()                   //Función para configurar el módulo ADC 
{
  ADCON0 = 0b01000001;                  //Activamos ADC y  Fosc/16 es seleccionado 
  ADCON1 = 0b11000000;                  // Seleccionamos el voltaje de referencia interno-
}

unsigned int ADC_Read(unsigned char channel) //Función para leemos desde ADC
{
  ADCON0 &= 0x11000101;                 //Limpiamos los bits del canal seleccionado. 
  ADCON0 |= channel<<3;                 //Establecemos los bits requeridos.
  __delay_ms(2);                        //Tiempo de adquisición para cargar el condensador.
  GO_nDONE = 1;                         //Inicializamos la conversión A/D
  while(GO_nDONE);                      //Esperamos hasta que la conversión A/D se complete.
  return ((ADRESH<<8)+ADRESL);          //Devulve el resuktado de la conversión A/D.
}

void __interrupt() timer0()
{  
    if(TMR0IF==1)                       //Si la bandera IF=1 el timer0 se a desbordado cada 0.1ms.
    {
        TMR0 = 248;                     //Cargamos el contador del Timer0.
        TMR0IF=0;                       //Limpiamos la bandera IF.
        count++;                        //El contador se incrementa cada 0.1ms -> count/10 sera el valor en ms 
    } 
    
    if (count <= (T_ON) )
        RD1=1;
    else
        RD1=0;
    
    if (count >= (T_TOTAL*10) )
        count=0;
}

void main()
{    
    OPTION_REG = 0b00000101;            // Timer0 con frecuencia externa y prescaler de 64 (resistencias Pull Ups habilitadas).
    TMR0=248;                           // Cargamos el tiempo para 0.0001s; 
    TMR0IE=1;                           // Habilitamos la interrución por desbordamiento de timer0.
    GIE=1;                              // Habilitamos las interrupciones globales.
    PEIE=1;                             // Habilitamos las interrupciones por perifericos. 
    TRISD = 0x00;                       // Configuramos el PUERTOD como salida.
    PORTD=0x00;                         // Inicializamos todos los pines del puerto D a nivel bajo.
    ADC_Initialize();                   //Llamamos al afunción ADC_Initialize()

    while(1)                            //Bucle infinito.
    {
       POT_val = (ADC_Read(0));         //Leemos el valor del potenciometro desde ADC_read()
       Duty_cycle = (POT_val * 0.0976); //Mapeamos 0 a 1024 --> 0% a 100%
       T_ON = ((Duty_cycle * T_TOTAL)*10 / 100); //Calculo del tiempo en ON.
       __delay_ms(100);                 //Retardo de 100ms.
    }
}
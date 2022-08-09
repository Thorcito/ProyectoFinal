/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::   CONTROL DE MOTOR DC    ::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::    CANAL DE YOUTUBE      ::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::        Jorge APC         ::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#include <16F877A.h>                                     //PIC 16F877A
#device ADC=10                                           //Habilitamos el uso del m�dulo ADC
#fuses XT, NOWDT, PUT, NOLVP, NOPROTECT                  //Bits de configuraci�n
#use delay(clock=4000000)                                //Crista de 4HMz
#use fast_io(B)   
#use fast_io(C)

unsigned int16 analog;

//:::::::::::::::::::::::::::: Funci�n de configuraci�n :::::::::::::::::::::::::::::::
void configuracion (void)
{
   port_b_pullups(TRUE);                                 //Habilitamos �as resistencias Pull Up del port b
   output_b(0);
   set_tris_b(0b0111);                                        //Configuramos los bit RB0, RB1 y RB2 como entradas
   output_c(0);
   set_tris_c(0);                                        //Configuramos los 8 bits del port C como salidas
   setup_adc(ADC_CLOCK_DIV_32);                          //Utilizamos el oscilador interno del m�dulo ADC
   setup_adc_ports(AN0);                                 //Definimos la entrada anal�gica
   set_adc_channel(0);                                   //definimos el canal 0
   //setup_ccp1(ccp_pwm);                                //Habilitamos el m�dulo PWM 1
   //setup_ccp2(ccp_pwm);                                //Habilitamos el m�dulo PWM 2
   setup_timer_2(T2_DIV_BY_16, 127,1);                   //Prescaler 16, PR2=127,Postcaler 1
   delay_ms(500);                                        //Retardo de 500ms
}

//:::::::::::::::::::::::::::: Funci�n de principal ::::::::::::::::::::::::::::::::::::
void main (void)
{
   configuracion();                                      //Llamamos a la funci�n configuraci�n
   while(1)
   {
   analog=read_adc();                                    //Leemos el valor de la conversi�n ADC y la guardamos en analog
   if(input(PIN_B3)==1)                                  //Si el el led RB3 esta en alto
   {
      set_pwm1_duty(analog);                             //Cargamos el ciclo de trabajo con el valos "analog"
   }
   if(input(PIN_B4)==1)                                  //Si el led RB4 esta en alto
   {
      set_pwm2_duty(analog);                             //Cargamos el ciclo de trabajo con el valor "analog"
   }
   delay_ms(10);                                         //Retardo de 10ms
   if(input(PIN_B0)==0)                                  //Si el pulsador RB0 esta a nivel bajo
   {
      if(input(PIN_B3)==0)                               //Si el led esta apagado 
      {
         output_b(0);                                    //Ponemos los dos leds a nivel bajo
         setup_ccp1(ccp_off);                            //Desactivamos la se�al PWM1
         setup_ccp2(ccp_off);                            //Desactivamos la se�al PWM2
         output_c(0);                                    //Ponemos a nivel bajo las se�ales PWM
         delay_ms(100);                                  //Retardo de 100ms
         setup_ccp1(ccp_pwm);                            //Activamos la se�al pwm1
         output_high(PIN_B3);                            //Ponemos a nivel alto el led RB3
      }
   }
   if(input(PIN_B1)==0)                                  //Si el pulsador RB1 esta a nivel bajo
   {
      if(input(PIN_B4)==0)                               //Si el led RB4 esta en nivel bajo                           
      {
         output_b(0);                                    //Ponemos los dos leds a nivel bajo
         setup_ccp1(ccp_off);                            //Desactivamos la se�al PWM1
         setup_ccp2(ccp_off);                            //Desactivamos la se�al PWM2
         output_c(0);                                    //Ponemos a nivel bajo las se�ales PWM
         delay_ms(100);                                  //Retardo de 100ms
         setup_ccp2(ccp_pwm);                            //Activamos la se�al pwm2
         output_high(PIN_B4);                            //Ponmos a nivel alto el led RB4
      }
   }
   if(input(PIN_B2)==0)                                  //Si el pulsador de STOP RB2 esta en nivel bajo
   {
      setup_ccp1(ccp_off);                               //Desactivamos la se�al PWM1
      setup_ccp2(ccp_off);                               //Desactivamos la se�al PWM2
      output_c(0);                                       //Poneos a nivel bajos las se�ales PWM
      output_b(0);                                       //Ponemos a nivel bajo los dos leds 
   }
   }
}

   

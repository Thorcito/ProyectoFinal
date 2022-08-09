#include <16f877a.h>
#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,NOBROWNOUT
#use delay(clock=20000000)
#use standard_io(B)

#define use_servo_1                                   // Habilita el servo 1
#define use_servo_2                                   // Habilita el servo 2
#define use_servo_3                                   // Habilita el servo 3

#define servo_1 PIN_B0                                // Asigna el pin de control del servo 1 al pin B0
#define servo_2 PIN_B1                                // Asigna el pin de control del servo 2 al pin B1
#define servo_3 PIN_B2                                // Asigna el pin de control del servo 3 al pin B2

#include <servo_st.c>                                 // Libreria para controlar servomotores

void main()
{
   servo_init();                                      // Inicializa todos los servos configurados
   servo_1_write(0);                                  // Inicializan los 3 servos en 0°
   servo_2_write(0);
   servo_3_write(0);
   delay_ms(1000);
   
   while(true)
   {
      ///////////////////////// Secuencia 1 /////////////////////////
      servo_1_write(90);
      delay_ms(1000);
      servo_2_write(90);
      delay_ms(1000);
      servo_3_write(90);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 2 /////////////////////////
      servo_1_write(180);
      delay_ms(1000);
      servo_2_write(180);
      delay_ms(1000);
      servo_3_write(180);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 3 /////////////////////////
      servo_1_write(0);
      delay_ms(1000);
      servo_2_write(0);
      delay_ms(1000);
      servo_3_write(0);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 4 /////////////////////////
      servo_1_write(90);
      servo_2_write(90);
      servo_3_write(90);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 5 /////////////////////////
      servo_1_write(180);
      servo_2_write(180);
      servo_3_write(180);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 6 /////////////////////////
      servo_1_write(0);
      servo_2_write(0);
      servo_3_write(0);
      delay_ms(1000);
   }
}

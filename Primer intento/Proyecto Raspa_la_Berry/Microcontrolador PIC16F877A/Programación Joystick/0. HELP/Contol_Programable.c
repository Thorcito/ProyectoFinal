#include <16f877a.h>
#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,NOBROWNOUT
#use delay(clock=20000000)
#use standard_io(B)

#define use_servo_1                                   // Habilita el servo 1
#define use_servo_2                                   // Habilita el servo 2

#define servo_1 PIN_B3                                // Asigna el pin de control del servo 1 al pin B3
#define servo_2 PIN_B4                                // Asigna el pin de control del servo 2 al pin B4

#include <servo_st.c>                                 // Libreria para controlar servomotores. 

void main()
{
   servo_init();                                      // Inicializa todos los servos configurados
   servo_1_write(0);                                  // Inicializan los 2 servos en 0�
   servo_2_write(0);
   delay_ms(1000);
   //Servo 1 controla la base
   //Servo 2 controla el ca��n
   while(true)
   {
      ///////////////////////// Secuencia 1 /////////////////////////Moverse en un eje/rotaci�n X cantidad de unidades
      servo_1_write(0);
      servo_2_write(145); //solo se mueve la c�mara
      delay_ms(1000);
      
      ///////////////////////// Secuencia 2 /////////////////////////Movimiento simultaneo en dos o m�s ejes/rotaciones en X,Y unidades
      servo_1_write(180); //gira completamente hacia un lado
      servo_2_write(0); //la c�mara queda observando el suelo
      delay_ms(1000);
           
      ///////////////////////// Secuencia 3 /////////////////////////Pausa de X segundos
      servo_1_write(steady); //steady corresponde a un estado de stand by
      servo_2_write(steady);
      delay_ms(x); //x corresponde a la cantidad de milisegundos que se desea pausar
      //aqu� falta alg�n contador o algo que me haga ver los segundos que estoy en pausa
      
      ///////////////////////// Secuencia 4 /////////////////////////Regresar a posici�n de reposo
      servo_1_write(0);                                  
      servo_2_write(0);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 5 /////////////////////////Disparo de un ca��n
      servo_1_write(steady);
      servo_2_write(90); //la c�mara observa de forma horizontal
      Canon_shot(1); //Canon_shot es la funci�n que le dice al ca�on si disparar o no, al estar en 1, el ca��n debe disparar
      delay_ms(1000);
      
      ///////////////////////// Secuencia 6 /////////////////////////Apuntar de forma directa vertical
      servo_1_write(steady);//no nos importa realmente la posici�n de este servo
      servo_2_write(180); //al estar en 180 grados, la c�mara (y ca��n) queda viendo de forma directa vertical
      delay_ms(1000);
      
      ///////////////////////// Secuencia 7 /////////////////////////Movimiento a posici�n cardinal sobre la base de la media esfera
      servo_1_write(base); //base corresponde a la posici�n en la que se desea ubicar el servo que controla la base
      servo_2_write(canon);//canon corresponde a la posici�n en la que se desea ubicar el servo que controla la c�mara (y el ca��n))
      delay_ms(1000);
   }
}


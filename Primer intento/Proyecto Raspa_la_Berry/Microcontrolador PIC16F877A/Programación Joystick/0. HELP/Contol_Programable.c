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
   servo_1_write(0);                                  // Inicializan los 2 servos en 0°
   servo_2_write(0);
   delay_ms(1000);
   //Servo 1 controla la base
   //Servo 2 controla el cañón
   while(true)
   {
      ///////////////////////// Secuencia 1 /////////////////////////Moverse en un eje/rotación X cantidad de unidades
      servo_1_write(0);
      servo_2_write(145); //solo se mueve la cámara
      delay_ms(1000);
      
      ///////////////////////// Secuencia 2 /////////////////////////Movimiento simultaneo en dos o más ejes/rotaciones en X,Y unidades
      servo_1_write(180); //gira completamente hacia un lado
      servo_2_write(0); //la cámara queda observando el suelo
      delay_ms(1000);
           
      ///////////////////////// Secuencia 3 /////////////////////////Pausa de X segundos
      servo_1_write(steady); //steady corresponde a un estado de stand by
      servo_2_write(steady);
      delay_ms(x); //x corresponde a la cantidad de milisegundos que se desea pausar
      //aquí falta algún contador o algo que me haga ver los segundos que estoy en pausa
      
      ///////////////////////// Secuencia 4 /////////////////////////Regresar a posición de reposo
      servo_1_write(0);                                  
      servo_2_write(0);
      delay_ms(1000);
      
      ///////////////////////// Secuencia 5 /////////////////////////Disparo de un cañón
      servo_1_write(steady);
      servo_2_write(90); //la cámara observa de forma horizontal
      Canon_shot(1); //Canon_shot es la función que le dice al cañon si disparar o no, al estar en 1, el cañón debe disparar
      delay_ms(1000);
      
      ///////////////////////// Secuencia 6 /////////////////////////Apuntar de forma directa vertical
      servo_1_write(steady);//no nos importa realmente la posición de este servo
      servo_2_write(180); //al estar en 180 grados, la cámara (y cañón) queda viendo de forma directa vertical
      delay_ms(1000);
      
      ///////////////////////// Secuencia 7 /////////////////////////Movimiento a posición cardinal sobre la base de la media esfera
      servo_1_write(base); //base corresponde a la posición en la que se desea ubicar el servo que controla la base
      servo_2_write(canon);//canon corresponde a la posición en la que se desea ubicar el servo que controla la cámara (y el cañón))
      delay_ms(1000);
   }
}


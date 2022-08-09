/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   ::::::::::::::::::::::                              ::::::::::::::::::::
   ::::::::::::::::::::::      Comunicación Serie      ::::::::::::::::::::
   ::::::::::::::::::::::  Canal Youtube: Jorge APC    ::::::::::::::::::::
   ::::::::::::::::::::::                              ::::::::::::::::::::
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
   
   #include <16F877A.h>                            //Microcontrolador utilizado
   #fuses XT, NOWDT, NOPROTECT, PUT, NOLVP         //Bits de configuración
   #use delay(clock=4000000)                       //Cristal Externo de 4MHz
   #include <lcd.c>                                //Incluimos la libreria LCD
   #use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8)   //Configuramos la comunicación serie
   
   char dato;
   
   #INT_RDA                                        //Interrupción por datos recibidos disponibles RS232
   void serie(void)                                //Función de interrupción por dato recivido comunicación serie
   {
      dato=getc();                                 //Almacena el carácter recibido por la patilla RCV 
                                                   //y retorna el carácter recibido este caracter se guarda en la variable "dato"
      printf(lcd_putc, "%c", dato);                //Imprimir el la pantalle LCD el "caracter dato"
   }
   
   void configuracion (void)                       //Función de configuración
   {
      lcd_init();                                  //Inicializamos la pantalla LCD
      enable_interrupts(GLOBAL);                   //Habilitamos las interrupciones
      enable_interrupts(INT_RDA);                  //Habilitamos la interrupción por dato recibido RS232
   }
   
   void main (void)                                //Función Principal
   {
      configuracion();                             //Llamamos a la función de configuración.
      printf("INGRESE TEXTO:");          //Cadena de caracteres
      while (true)                                 //Bucle infinito
      {
         
      }
   }
   
      

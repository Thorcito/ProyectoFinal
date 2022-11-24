#include <Servo.h>
#include "Arduino.h"


Servo AXE;
int Servo_Pin = 13;  //PIN DEL SERVO MOTOR
int SW = 35;         //PIN DEL BOTON
int IN1 = 25;        //PIN ccw m1
int IN2 = 33;        //PIN cw m1
int IN3 = 4;         //PIN ccw m2
int IN4 = 5;         //PIN cw m2
int VRX = 14;        //PIN JOYSTICK X
int VRY = 12;        //PIN JOYSTICK Y
int posicion_X = 0;  //VARIABLE CON POSICION X
int posicion_Y = 0;  //VARIABLE CON POSICION Y
String instruccion;  //String de Instruccion proporcionado por la Raspi
String comando;      //
int SEL = 0;         //VARIABLE PARA PERMANCER EN ALGUN MODO
unsigned long time_1;
unsigned long time_2;
int stop = 0;              //VARIABLE PARA TIMER DE ZXE AUTOMATICO
bool Interrupcion = HIGH;  //
int matriz_pos[6][6];      //matriz de posiciones j,k
int j_sig;                 //contador matriz fila
int j_ant = 5;             //matriz fila inicial
int k_sig;                 //contador matriz columna
int k_ant = 1;             //matriz columna inicial
signed int nose = 0;              //posicion cardinal del robot para el modo manual

//funcion de la interrupcion
void Accionar_Axe() {
  Interrupcion = !Interrupcion;  //Se cambia el estado de la variable de la interrupcion
  // Serial.print("INT: ");
  // Serial.println(Interrupcion);
}
void Motor_OFF() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void Mover_Motores_Manual(int posX, int posY) {
  if (posX > 1800 and posX < 1850) {  //EJE X EN CERO
    if (posY > 4090) {
      Serial.println("DERECHA");
      nose = nose + 1;
      if (abs(nose) == 4) {
        nose = 0;
      }
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
      delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
      Motor_OFF();
      return;
    } else if (posY < 10) {
      Serial.println("IZQUIERDA");
      nose = nose - 1;
      if (abs(nose) == 4) {
        nose = 0;
      }
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
      delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
      Motor_OFF();
      return;
    } else {
      // Serial.println("CENTRO");
      Motor_OFF();
      return;
    }
  }
  if (posY > 1900 and posY < 1950) {  //EJE Y EN CERO
    if (posX > 4090) {
      Serial.println("ATRAS");
      switch (nose) {
        case 0:
          k_sig = k_ant;
          j_sig = j_ant + 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite inferior");
            Motor_OFF();
            break;
          }
        case 1:
          k_sig = k_ant - 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite izquierda");
            Motor_OFF();
            break;
          }
        case 2:
          k_sig = k_ant;
          j_sig = j_ant - 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite superior");
            Motor_OFF();
            break;
          }
        case 3:
          k_sig = k_ant + 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite derecha");
            Motor_OFF();
            break;
          }
        case -1:
          k_sig = k_ant + 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite derecho");
            Motor_OFF();
            break;
          }
        case -2:
          k_sig = k_ant;
          j_sig = j_ant - 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite superior");
            Motor_OFF();
            break;
          }
        case -3:
          k_sig = k_ant - 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 1);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 1);
            Serial.println("ATRAS");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite izquierdo");
            Motor_OFF();
            break;
          }
      }
    } else if (posX < 10) {
      Serial.println("DELANTE");
      switch (nose) {
        case 0:
          k_sig = k_ant;
          j_sig = j_ant - 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite superior");
            Motor_OFF();
            break;
          }
        case 1:
          k_sig = k_ant + 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite derecho");
            Motor_OFF();
            break;
          }
        case 2:
          k_sig = k_ant;
          j_sig = j_ant + 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite inferior");
            Motor_OFF();
            break;
          }
        case 3:
          k_sig = k_ant - 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite izquierdo");
            Motor_OFF();
            break;
          }
        case -1:
          k_sig = k_ant - 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite izquierdo");
            Motor_OFF();
            break;
          }
        case -2:
          k_sig = k_ant;
          j_sig = j_ant + 1;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite inferior");
            Motor_OFF();
            break;
          }
        case -3:
          k_sig = k_ant + 1;
          j_sig = j_ant;
          if (matriz_pos[j_sig][k_sig] == 0) {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 1);
            digitalWrite(IN3, 1);
            digitalWrite(IN4, 0);
            Serial.println("DELANTE");
            delay(5000);  //DELAY NECESARIO PARA RECORRER UNA CASILLA
            Motor_OFF();
            k_ant = k_sig;
            j_ant = j_sig;
            break;
          } else {
            Serial.println("Se llego al limite derecha");
            Motor_OFF();
            break;
          }
      }
    } else {
      // Serial.println("CENTRO");
      Motor_OFF();
      return;
    }
  }
  Serial.print("Posicion: ");
  Serial.print(j_ant);
  Serial.print(" - ");
  Serial.println(k_ant);
  Serial.print("NOSE: ");
  Serial.println(nose);
}

//BIEN
void Mover_Axe_Manual(bool Encender) {
  if (Encender == 0) {
    AXE.write(180);
    Serial.println("ACTIVADO");
    delay(1500);
    AXE.write(50);
    Serial.println("DESACTIVADO");
    delay(1500);
    Interrupcion = HIGH;
  }
}

void Mover_Motores_Auto(String instr) {
  if (instr.equalsIgnoreCase("front")) {
    Serial.println("DELANTE");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  } else if (instr.equalsIgnoreCase("back")) {
    Serial.println("ATRAS");
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  } else if (instr.equalsIgnoreCase("left")) {
    Serial.println("IZQUIERDA");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  } else if (instr.equalsIgnoreCase("right")) {
    Serial.println("DERECHA");
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  } else if (instr.equalsIgnoreCase("stop")) {
    Serial.println("STOP");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
  } else if (instr.equalsIgnoreCase("chop")) {
    Serial.println("STOP");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
  } else {
    Serial.println("Esperando...");
  }
}

void Mover_Axe_Auto(String cmd) {
  int Encender;
  if (cmd.equalsIgnoreCase("chop")) {
    AXE.write(180);
    Encender = 0;
    Serial.println(Encender);
    while (Encender == 0) {
      if (millis() >= time_1 + 1500) {
        time_1 += 1500;
        AXE.write(50);
        Serial.println("GOING BACK");
        Encender = 1;
      }
    }
  }
  ///AXE.write(60);
  else {
    Encender = 1;
    return;
  }
  ///AXE.write(60);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Servo_Pin, OUTPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SW), Accionar_Axe, FALLING);
  Serial.begin(9600);
  AXE.attach(Servo_Pin);
  AXE.write(50);

  //Creamos una matriz de 7x7 limitada por 1
  for (int i = 0; i < 7; i++) {
    matriz_pos[0][i] = 1;
    matriz_pos[i][0] = 1;
    matriz_pos[6][i] = 1;
    matriz_pos[i][6] = 1;
  }
}

void loop() {
  Serial.println("Esperando Comando.... ");
  while (Serial.available() == 0) {}
  instruccion = Serial.readString();
  instruccion.trim();
  Serial.println(instruccion);
  if (instruccion.equalsIgnoreCase("MANUAL")) {
    Serial.println("Modo Manual Activado");
    SEL = 1;
    while (SEL) {
      while (Serial.available() == 0) {
        posicion_X = analogRead(VRX);
        posicion_Y = analogRead(VRY);
        Mover_Motores_Manual(posicion_X, posicion_Y);
        Mover_Axe_Manual(Interrupcion);
      }
      instruccion = Serial.readString();
      instruccion.trim();
      Serial.println(instruccion);
      if (instruccion.equalsIgnoreCase("ATRAS")) {
        SEL = 0;
        break;
      }
    }
  } else if (instruccion.equalsIgnoreCase("AUTO")) {
    SEL = 1;
    comando = "NADA";
    while (SEL) {
      Serial.println("Ingrese dato puta: ");  //aqui se envia el dato por la raspi
      while (Serial.available() == 0) {       //aqui se envia el dato por la raspi
        Mover_Motores_Auto(comando);
        Mover_Axe_Auto(comando);
      }
      comando = Serial.readString();
      comando.trim();
      Serial.println(comando);
      if (comando.equalsIgnoreCase("ATRAS")) {
        Mover_Motores_Auto("STOP");
        SEL = 0;
        break;
      }
    }
  } else {
    Serial.println("COMMANDO NO RECONOCIDO");
  }
}
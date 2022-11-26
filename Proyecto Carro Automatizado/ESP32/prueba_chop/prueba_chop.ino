#include <Servo.h>
#include "Arduino.h"


Servo AXE;
int Servo_Pin = 13;  //PIN DEL SERVO MOTOR
int SW = 35;         //PIN DEL BOTON
int IN1 = 25;        //PIN ccw m1
int IN2 = 33;        //PIN cw m1
int IN3 = 5;         //PIN ccw m2
int IN4 = 18;         //PIN cw m2
int VRX = 14;        //PIN JOYSTICK X
int VRY = 12;        //PIN JOYSTICK Y
int posicion_X = 0;  //VARIABLE CON POSICION X
int posicion_Y = 0;  //VARIABLE CON POSICION Y
String instruccion;  //String de Instruccion proporcionado por la Raspi
String comando;      //
String mov_chop;
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
String x_entrante;
String y_entrante;
String uno;
String dos;
signed int nose = 0;  //posicion cardinal del robot para el modo manual

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
  delay(1000);
}

void front_auto() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(1450);
  // digitalWrite(IN1, 1);
  // digitalWrite(IN2, 0);
  // digitalWrite(IN3, 1);
  // digitalWrite(IN4, 0);
  // delay(25);
}

void back_auto() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(1350);
  // digitalWrite(IN1, 0);
  // digitalWrite(IN2, 1);
  // digitalWrite(IN3, 0);
  // digitalWrite(IN4, 1);
  // delay(25);
}
void left_auto() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(1050);
}
void right_auto() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(1080);
}

void Mover_Motores_Manual(int posX, int posY) {
  if (posX > 1800 and posX < 1850) {  //EJE X EN CERO
    if (posY < 10) {
      Serial.println("DERECHA");
      nose = nose + 1;
      if (abs(nose) == 4) {
        nose = 0;
      }
      right_auto();
      Motor_OFF();
      return;
    } else if (posY > 4090) {
      Serial.println("IZQUIERDA");
      nose = nose - 1;
      if (abs(nose) == 4) {
        nose = 0;
      }
      left_auto();
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
            back_auto();
            Serial.println("ATRAS");
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
            back_auto();
            Serial.println("ATRAS");
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
            back_auto();
            Serial.println("ATRAS");
            Motor_OFF();
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
            back_auto();
            Serial.println("ATRAS");
            Motor_OFF();
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
            back_auto();
            Serial.println("ATRAS");
            Motor_OFF();
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
            back_auto();
            Serial.println("ATRAS");
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
            back_auto();
            Serial.println("ATRAS");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
            front_auto();
            Serial.println("DELANTE");
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
  switch (nose) {
    case 0:
      if (instr == "arriba") {
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        nose = nose + 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      }
    case 1:
      if (instr == "arriba") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      }
    case 2:
      if (instr == "arriba") {
        nose = nose - 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      }
    case 3:
      if (instr == "arriba") {
        nose = nose - 3;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        front_auto();
        Motor_OFF();
        break;
      }
    case -1:
      if (instr == "arriba") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        front_auto();
        Motor_OFF();
        break;
      }
    case -2:
      if (instr == "arriba") {
        nose = nose + 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      }
    case -3:
      if (instr == "arriba") {
        nose = nose + 3;
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "abajo") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "derecha") {
        front_auto();
        Motor_OFF();
        break;
      } else if (instr == "izquierda") {
        nose = nose + 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        front_auto();
        Motor_OFF();
        break;
      }
  }
}

void Mover_Auto_Chop (String mov_chop){
  Serial.print("Giro a hacia ");
  Serial.print(mov_chop);
  Serial.println(" para chopear");
  switch (nose) {
    case 0:
      if (mov_chop == "abajo") {
        nose = nose + 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        front_auto();
        break;
      } else if (mov_chop == "derecha") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "izquierda") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      }
    case 1:
      if (mov_chop == "arriba") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "abajo") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "izquierda") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        break;
      }
    case 2:
      if (mov_chop == "arriba") {
        nose = nose - 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "derecha") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "izquierda") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      } 
    case 3:
      if (mov_chop == "arriba") {
        nose = nose - 3;
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "abajo") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "derecha") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        break;
      }
    case -1:
      if (mov_chop == "arriba") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "abajo") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "derecha") {
        nose = nose - 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        break;
      } 
    case -2:
      if (mov_chop == "arriba") {
        nose = nose + 2;
        right_auto();
        Motor_OFF();
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "derecha") {
        nose = nose - 1;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "izquierda") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      }
    case -3:
      if (mov_chop == "arriba") {
        nose = nose + 3;
        left_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "abajo") {
        nose = nose + 1;
        right_auto();
        Motor_OFF();
        break;
      } else if (mov_chop == "izquierda") {
        nose = nose + 2;
        left_auto();
        Motor_OFF();
        left_auto();
        Motor_OFF();
        break;
      }  
  }
}

void Mover_Axe_Auto(String cmd) {
  if (cmd == "chop") {
    AXE.write(180);
    Serial.println("ACTIVADO");
    delay(1500);
    AXE.write(50);
    Serial.println("DESACTIVADO");
    delay(1500);
  }
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
    Serial.println("Esperando Direccion Inicial...");
    while (Serial.available() == 0) {};
    instruccion = Serial.readString();
    instruccion.trim();
    Serial.println(instruccion);
    x_entrante = instruccion.substring(0, instruccion.indexOf(" "));
    y_entrante = instruccion.substring(instruccion.indexOf(" ") + 1);
    j_ant = x_entrante.toInt();
    k_ant = y_entrante.toInt();
    Serial.print("Direccion Seleccionada: ");
    Serial.print(j_ant);
    Serial.print(" ");
    Serial.println(k_ant);
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
    Serial.println("Modo Automatico Activado");
    SEL = 1;
    delay(1000);
    while (SEL) {
      Serial.println("Esperando Direccion: ");  //aqui se envia el dato por la raspi
      while (Serial.available() == 0) {}        //aqui se envia el dato por la raspi
      instruccion = Serial.readString();
      instruccion.trim();
      if (instruccion.equalsIgnoreCase("chop")) {
        while (Serial.available() == 0) {} 
        mov_chop = Serial.readString();
        mov_chop.trim();
        Mover_Auto_Chop(mov_chop);
        Mover_Axe_Auto("chop");
        front_auto();
        Motor_OFF();
        Serial.print("NOSE: ");
        Serial.println(nose);
      }
      else if (instruccion.equalsIgnoreCase("ATRAS")) {
        Motor_OFF();
        SEL = 0;
        break;
      }
      else {
        Serial.println(instruccion);
        Mover_Motores_Auto(instruccion);
        Serial.print("NOSE: ");
        Serial.println(nose);
      }
    }
  } else if (instruccion.equalsIgnoreCase("AUTO2")){
      Serial.println("Modo Automatico 2 Activado");
      SEL = 1;
      delay(1000);
      while (SEL) {
        Serial.println("Esperando Direccion: ");  //aqui se envia el dato por la raspi
        while (Serial.available() == 0) {}        //aqui se envia el dato por la raspi
        instruccion = Serial.readString();
        instruccion.trim();
        uno = instruccion.substring(0, instruccion.indexOf(" "));
        dos = instruccion.substring(instruccion.indexOf(" ") + 1);
        if (uno.equalsIgnoreCase("n")){
          Mover_Motores_Auto(dos);
        }
        else if(uno.equalsIgnoreCase("s")){
          Mover_Auto_Chop(dos);
          Mover_Axe_Auto("chop");
          front_auto();
          Motor_OFF();
          Serial.print("NOSE: ");
          Serial.println(nose);
        }
        else if (instruccion.equalsIgnoreCase("ATRAS")) {
          Motor_OFF();
          SEL = 0;
          break;
        }
      }
    } else {
    Serial.println("COMMANDO NO RECONOCIDO");
  }
}

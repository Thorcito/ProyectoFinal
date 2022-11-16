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
String instruccion;  //
String comando;
int Activar_Servo = 0;  //VARIABLE SW
int SEL = 0;            //VARIABLE PARA PERMANCER EN ALGUN MODO
unsigned long time_1;
unsigned long time_2;
int stop = 0; //VARIABLE PARA TIMER DE ZXE AUTOMATICO

void Mover_Motores_Manual(int posX, int posY) {
  if (posX > 1800 and posX < 1850) {  //EJE X EN CERO
    if (posY > 4090) {
      Serial.println("DERECHA");
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
    } else if (posY < 10) {
      Serial.println("IZQUIERDA");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
    } else {
      // Serial.println("CENTRO");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      return;
    }
  }
  if (posY > 1900 and posY < 1950) {  //EJE Y EN CERO
    if (posX > 4090) {
      Serial.println("ATRAS");
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
    } else if (posX < 10) {
      Serial.println("DELANTE");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
    } else {
      // Serial.println("CENTRO");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      return;
    }
  }
}

void Mover_Axe_Manual(int Encender) {
  if (Encender == LOW) {
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
  } else {
    Encender = 1;
    return;
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
  } else {
    Encender = 1;
    return;
  }
}

void setup() {
  // put your setup code here, to run once:
  AXE.attach(Servo_Pin);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  AXE.write(50);
}

void loop() {
  Serial.println("Toy waiting.... ");
  while (Serial.available() == 0) {}
  instruccion = Serial.readString();
  instruccion.trim();
  Serial.println(instruccion);
  if (instruccion.equalsIgnoreCase("MANUAL")) {
    SEL = 1;
    while (SEL) {
      while (Serial.available() == 0) {
        posicion_X = analogRead(VRX);
        posicion_Y = analogRead(VRY);
        Activar_Servo = digitalRead(SW);
        Mover_Motores_Manual(posicion_X, posicion_Y);
        Mover_Axe_Manual(Activar_Servo);
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
      while (Serial.available() == 0) {     //aqui se envia el dato por la raspi
      Mover_Motores_Auto(comando);
      Mover_Axe_Auto(comando);
      }
      comando = Serial.readString();
      comando.trim();
      Serial.println(comando);
      if (comando.equalsIgnoreCase("ATRAS")) {
        SEL = 0;
        break;
      }
    }
  } else {
    Serial.println("I DONT SPEAK CHINO");
  }
}
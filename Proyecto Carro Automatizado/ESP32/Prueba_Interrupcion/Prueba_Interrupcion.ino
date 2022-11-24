#include <Servo.h>
#include "Arduino.h"

Servo AXE;
int Servo_Pin = 13;
int SW = 35;
bool Interrupcion = HIGH;
int SEL = 0;

unsigned long time_1;
int VRX = 14;        //PIN JOYSTICK X
int VRY = 12;        //PIN JOYSTICK Y
int posicion_X = 0;  //VARIABLE CON POSICION X
int posicion_Y = 0;  //VARIABLE CON POSICION Y
String instruccion;  //


void Accionar_Axe() {
  Interrupcion = !Interrupcion;
  Serial.println("INT ACTIVADA");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Servo_Pin, OUTPUT);
  AXE.attach(Servo_Pin);
  pinMode(SW, INPUT);
  Serial.begin(9600);
  AXE.write(50);
  attachInterrupt(digitalPinToInterrupt(SW), Accionar_Axe, FALLING);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
}

void Mover_Motores_Manual(int posX, int posY) {
  if (posX > 1800 and posX < 1850) {  //EJE X EN CERO
    if (posY > 4090) {
      Serial.println("DERECHA");
    } else if (posY < 10) {
      Serial.println("IZQUIERDA");
    } else {
      return;
    }
  }
  if (posY > 1900 and posY < 1950) {  //EJE Y EN CERO
    if (posX > 4090) {
      Serial.println("ATRAS");
    } else if (posX < 10) {
      Serial.println("DELANTE");
    } else {
      return;
    }
  }
}

void Mover_Axe_Manual(bool Encender) {
  if (Encender == 0){
    AXE.write(180);
    Serial.println("ACTIVADO");
    delay(1500);
    AXE.write(50);
    Serial.println("DESACTIVADO");
    Interrupcion = HIGH;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Estado: ");
  Serial.println(Interrupcion);
  Serial.println("Esperando Comando.... ");
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
        //Activar_Servo = digitalRead(SW);
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
  }
}

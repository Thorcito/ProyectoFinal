#include <Servo.h>
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#define ROTARY_ENCODER_A_PIN 27
#define ROTARY_ENCODER_B_PIN 26
#define ROTARY_ENCODER_BUTTON_PIN -1  //QUITARLO
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder2 = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

#define ROTARY_ENCODER2_A_PIN 15
#define ROTARY_ENCODER2_B_PIN 2
#define ROTARY_ENCODER2_BUTTON_PIN -1  //QUITARLO
#define ROTARY_ENCODER2_VCC_PIN -1
#define ROTARY_ENCODER2_STEPS 1
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER2_A_PIN, ROTARY_ENCODER2_B_PIN, ROTARY_ENCODER2_BUTTON_PIN, ROTARY_ENCODER2_VCC_PIN, ROTARY_ENCODER2_STEPS);

Servo AXE;
int Servo_Pin = 13;
int POT = 14;
int BOT = 32;
int SW = 35;

int IN1 = 25;  //ccw m1
int IN2 = 33;  //cw m1
int IN3 = 4;  //ccw m2
int IN4 = 5;  //cw m2

int VRX = 14;
int VRY = 12;
int posicion_X = 0;
int posicion_Y = 0;


unsigned long time_1;
unsigned long time_2;

bool CW1 = 0;
bool CCW1 = 0;
int long vuelta = 0;
int CHECK = 0;

void rotary_loop() {
  //dont print anything unless value changed
  if (rotaryEncoder.encoderChanged()) {
    Serial.print("Value: ");
    int long a = rotaryEncoder.readEncoder();
    Serial.println(a);
  }
}

void rotary2_loop() {
  //dont print anything unless value changed
  if (rotaryEncoder2.encoderChanged()) {
    Serial.print("Value2: ");
    int long b = rotaryEncoder2.readEncoder();
    Serial.println(b);
    if (b >= 840 and CHECK == 0){
      Serial.print("V2: ");
      vuelta++;
      Serial.println(vuelta);
      CHECK = 1;
    }
    if (b <= 100){
      CHECK = 0;
    }
    
  }
}

void IRAM_ATTR readEncoderISR() {
  rotaryEncoder.readEncoder_ISR();
}

void readEncoder2ISR() {
  rotaryEncoder2.readEncoder_ISR();
}

//DONE
void Quitar_Objeto(int Encender) {
  if (Encender == LOW) {
    AXE.write(180);
    Encender = 0;
    Serial.println(Encender);
    while (Encender == 0) {
      if (millis() >= time_1 + 1500) {
        time_1 += 1500;
        AXE.write(60);
        Serial.println("GOING BACK");
        Encender = 1;
      } 
    }
  }
  else {
    Encender = 1;
    return;
    }
}

//DONE
void Motor_Movement(int posX, int posY){
    if (posX > 1800 and posX < 1850){  //EJE X EN CERO
    if (posY > 4090){
      Serial.println("DERECHA");
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
    }
    else if (posY < 10 ){
      Serial.println("IZQUIERDA");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
    }
    else {
      Serial.println("CENTRO");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      return;
    }
  }
  if (posY > 1900 and posY < 1950){  //EJE Y EN CERO
    if (posX > 4090){
      Serial.println("ATRAS");
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
      }
    else if (posX < 10 ){ 
      Serial.println("DELANTE");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
      }
    else {
      Serial.println("CENTRO");
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      return;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  AXE.attach(Servo_Pin);  // attaches the servo on pin 13 to the servo object
  pinMode(IN1, OUTPUT);
  pinMode(POT, INPUT);
  pinMode(BOT, INPUT);
  pinMode(SW, INPUT_PULLDOWN);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER2_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER2_B_PIN, INPUT_PULLUP);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  Serial.begin(9600);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  //set boundaries and if values should cycle or not
  //in this example we will set possible values between 0 and 1000;
  bool circleValues = true;
  rotaryEncoder.setBoundaries(-5000, 5000, circleValues);  //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.disableAcceleration();                     //acceleration is now enabled by default - disable if you dont need it
                                                           //rotaryEncoder.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
  rotaryEncoder2.begin();
  rotaryEncoder2.setup(readEncoder2ISR);
  rotaryEncoder2.setBoundaries(0, 963, circleValues);  //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder2.disableAcceleration();
  AXE.write(60);
}

void loop() {
  ////////////////////////////////////
  //CONTROL DE SERVO CON POT
  //int PotVal = analogRead(POT);
  //int Val = PotVal * 180 / 4095;
  //Serial.println(Val);
  //AXE.write(Val);
  /////////////////////////////
  int Activar_Servo = digitalRead(SW);
  Quitar_Objeto(Activar_Servo);
  int ON = digitalRead(BOT);
  //Serial.println(ON);
  // if (millis() >= time_2 + 5000) {
  //   time_2 += 5000;
  //   CCW1 = !CCW1;
  //   CW1 = !CW1;
  //   // Serial.println("PASARON 5 SEGUNDOS");
  //   // Serial.print("CW: ");
  //   // Serial.println(CW1);
  // }
  // if (ON == 0){
  //   CW1 = 1;
  // }
  // else {
  //   CW1 = 0;
  // }
  // digitalWrite(IN1, CCW1);
  // digitalWrite(IN2, CW1);
  // digitalWrite(IN3, CW1);
  // digitalWrite(IN4, CCW1);

  posicion_X = analogRead(VRX);
  posicion_Y = analogRead(VRY);
  Motor_Movement(posicion_X, posicion_Y);

  

  //rotary_loop();
  rotary2_loop();

  //control de las vueltas se puede hacer por medio de timmers, y se controla cuanto tiempo
  //se dura recorriendo un cuadrado del mapa 
}
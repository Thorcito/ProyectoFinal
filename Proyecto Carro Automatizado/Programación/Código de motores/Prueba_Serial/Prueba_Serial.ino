int VRX = 14;
int VRY = 12;
int posX = 0;
int posY = 0;
String instr;



//YA ESTA EN CODIGO
int IN1 = 25;  //ccw m1
int IN2 = 33;  //cw m1
int IN3 = 4;   //ccw m2
int IN4 = 5;   //cw m2
bool CW1 = 0;
bool CCW1 = 0;

void Movement_Auto (String instruccion){
  if (instruccion.equalsIgnoreCase("front")) {
    Serial.println("DELANTE");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  } else if (instruccion.equalsIgnoreCase("back")) {
    Serial.println("ATRAS");
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  } else if (instruccion.equalsIgnoreCase("left")) {
    Serial.println("IZQUIERDA");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  } else if (instruccion.equalsIgnoreCase("right")) {
    Serial.println("DERECHA");
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  } else if (instruccion.equalsIgnoreCase("stop")) {
    Serial.println("STOP");
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
  } else {
    Serial.println('I DONT UNDERSTAND PUTO');
  }
}

void Quitar_Objeto_Manual(int Encender) {
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

void setup() {
  // put your setup code here, to run once:
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) {}
  instr = Serial.readString();
  instr.trim();
  Serial.println(instr);
  if (instr.equalsIgnoreCase("manual")){
    Quitar_Objeto_Man(instr);
    Movement_Man(instr);    
  }
  else if (){
    Quitar_Objeto_Auto(instr);
    Movement_Auto(instr);
  }
  
  
}
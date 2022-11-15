int VRX = 14;
int VRY = 12;
int posX = 0;
int posY = 0;
String instruccion;



//YA ESTA EN CODIGO
int IN1 = 25;  //ccw m1
int IN2 = 33;  //cw m1
int IN3 = 4;   //ccw m2
int IN4 = 5;   //cw m2
bool CW1 = 0;
bool CCW1 = 0;



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
  instruccion = Serial.readString();
  instruccion.trim();
  Serial.println(instruccion);
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
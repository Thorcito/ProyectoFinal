#include "Wifi.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wifi.mode(WIFI_STA);
  Wifi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:

}

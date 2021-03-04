#include "device.h"

char* SSID = "";
char* pass = "";
char* connectionstring = "";

auto device = new Device();

void setup() {
  Serial.begin(9600);
  delay(2000);

  device->InitDevice(connectionstring,SSID, pass);

  Serial.println("Setup completed");
}

void loop() {
    device->run();
}

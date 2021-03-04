#include "device.h"

char* SSID = "";
char* pass = "0";
char* connectionstring = "";

auto device = new Device();

void setup() {
  Serial.begin(9600);
  device->InitDevice(connectionstring,SSID, pass);

}

void loop() {
    device->run();
}

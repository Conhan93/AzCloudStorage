#include "device.h"

char* SSID = "";
char* pass = "";
char* connectionstring = "";


auto device = Device();

void setup() {
  Serial.begin(9600);
  // initialize
  device.InitDevice(connectionstring, SSID, pass);

}

void loop() {
  device.run();
}

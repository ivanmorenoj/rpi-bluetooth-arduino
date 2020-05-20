#include <SoftwareSerial.h>

SoftwareSerial bt_serial(15, 14); // RX, TX
String serialBuff, bt_serialBuff;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Start serial communication");

  bt_serial.begin(115200);
}

void loop() {

  while (bt_serial.available()) {
    bt_serialBuff += String((char)bt_serial.read()); 
  }
  while (Serial.available()) {
    char auxc = Serial.read();
    Serial.write(auxc);
    serialBuff += String(auxc); 
  }

  if (bt_serialBuff.length() > 0 ) {

    Serial.println("Server response: " + bt_serialBuff);
    Serial.print("You response -> ");
    bt_serialBuff = "";
  }
  if (serialBuff.endsWith("\r")) {
    bt_serial.println(serialBuff);
    Serial.println();
    serialBuff = "";
  }
}


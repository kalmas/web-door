#include <SoftwareSerial.h>

const int lockPin = 2;
const int RFIDRX = 7;
const int RFIDTX = 8;
const int RFIDResetPin = 9;

SoftwareSerial mySerial(RFIDRX, RFIDTX); 

void setup()
{
  // Start USB serial
  Serial.begin(9600);
  // Start RFID serial
  mySerial.begin(9600);
  
  pinMode(lockPin, OUTPUT);
  
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);
}
 
void loop()
{
  // Pass RFID input along to USB
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if (Serial.available()) {
    int incomingByte = Serial.read();
 
    if (incomingByte == 0x01) {
      digitalWrite(lockPin, HIGH);
    } else if (incomingByte == 0x00) {
      digitalWrite(lockPin, LOW);
    }
  }
}

#include <SoftwareSerial.h>

/*
 * Lock control, on equals open
 */
const int lockPin = 2;

/*
 * RFID sensor serial input
 */
const int RFIDRX = 7;

/*
 * RFID sensor serial output
 */
const int RFIDTX = 8;

/*
 * RFID sensor reset
 */
const int RFIDResetPin = 9;

/*
 * We're using the "Software Serial" library to connect to RFID
 * reader because we need the default Serial to be library to 
 * read and write on USB channel
 *
 * Init software serial using RFID in/out
 */
SoftwareSerial mySerial(RFIDRX, RFIDTX); 

void setup()
{
  /**
   * Start serial for USB com
   */
  Serial.begin(9600);
  
  /**
   * Start serial for RFID sensor com
   */
  mySerial.begin(9600);
  
  /**
   * Init pin for sending "open sesame" signal
   */
  pinMode(lockPin, OUTPUT);
  
  /**
   * Reset RFID sensor
   */
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);
}
 
void loop()
{
  /*
   * Pass RFID tag down the USB
   */
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  /**
   * Control lock
   */
  if (Serial.available()) {
    int incomingByte = Serial.read();
 
    if (incomingByte == 0x01) {
      digitalWrite(lockPin, HIGH);
    } else if (incomingByte == 0x00) {
      digitalWrite(lockPin, LOW);
    }
  }
}

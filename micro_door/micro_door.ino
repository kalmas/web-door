#include <SoftwareSerial.h>

char* passcodes[] = {
  "4B00DA49A971", // spare??
  "05003D765C12", //vinny
  "4B00DA30B415", //ross
  "4B00DA14F772", //jon
  "4B00DA359034", //steve
  "4B00DA2249FA", //mandy
  "4B00DA3EF05F", //dyanna
  "1A004116317C", //??
  "1E009A81F9FC", //??
  "1A004162261F", //??
  "05007EA84E9D", // cody
  "040016B3B716", // adam
  "040007B29021", // s2
  "040007AE4DE0", // s3
  "4800E4F6C2980", // pete
  "05003DC468940", // chuck
  "05003E29D5C70", // shelby
  "040006CE428E0", //phil
  "05003E02D5EC", //jacki
  "0400175FF2BE", //kyle
  "05003DC60EF0", //chris
  "04001AD10DC2", //boby
  "04001ACFF627" //andrea  
};
int passcodeCount = 23;

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

char tagString[13];
int tagIndex = 0;
 
void loop()
{
  tagIndex = 0;
  
  /** 
   * Read from RFID
   */
  // Serial.write("here");
  if (mySerial.available()) {
    //  Serial.write("there");
    
    Serial.write("Incoming\n");
    while(tagIndex < 13) {
      if (mySerial.available()) {
        int readByte = mySerial.read();

        if (readByte != 2 && readByte != 10 && readByte != 13) {
          tagString[tagIndex] = readByte;
          tagIndex = tagIndex + 1;
        }
      }
    }


    Serial.write("Tag: ");
    Serial.write(tagString);
    Serial.write("\n");
    
    if (isAllowed(tagString)) {
      Serial.write("Open Sesame!");
      digitalWrite(lockPin, HIGH);
      delay(2000);
      digitalWrite(lockPin, LOW);
    } else {
      Serial.write("Sry, Not Allowed :(");
    }
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

boolean isAllowed(char tagString[])
{
  for (int i = 0; i < passcodeCount; i++) {
    if (match(tagString, passcodes[i])) {
      return true;
    }
  }

  return false;
}

boolean match(char one[], char two[])
{ 
  if (strlen(one) == 0) {
    return false;
  }

  for (int i = 0; i < 12; i++) {
    if (one[i] != two[i]) {
      return false;
    }
  }

  return true;
}

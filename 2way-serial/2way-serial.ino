/**
  2 way serial communication between arduino and a pc
  Name: 2way-serial

  @author Miroslav Vidovic (miroslav-vidovic@hotmail.com)
  @version 1.0 - 02.11.2019.
*/

// include the SD library:
#include <SD.h>                    
#include <Wire.h>
#include <SPI.h>

// timestamp library
#include <RTClib.h>

// RTC Object
RTC_DS1307 rtc;

// Define logfile
File Logfile;  

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 10;

// Data sent from pc to arduino
String incomingData;

void setup() {
  Serial.begin(9600);
  SD.begin(chipSelect); 
  rtc.begin();
  adjustRTC();
  Wire.begin();
  randomSeed(analogRead(0));
}

void loop() {
  int randNumber = random(1,3);
  Serial.println(randNumber);
  delay(1000);
  
  // If incoming data is available
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingData = Serial.readString();
    
    DateTime time = rtc.now();
  
    Logfile=SD.open("UnoTrans.txt",FILE_WRITE);
    Logfile.print(time.timestamp(DateTime::TIMESTAMP_FULL));
    Logfile.print(",");
    Logfile.print(incomingData);
    Logfile.println();
    Logfile.close();
  }
}

/**
 *  Adjust RCT value based on date and time values from the pc.
 *  Check if rtc is running before adjustment.
 */ 
void adjustRTC() {
  if (! rtc.isrunning()) {

    // following line sets the RTC to the date and time this sketch was compiled
    // local computer date and time values are used
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2020 at 3am you would call:
    // rtc.adjust(DateTime(2020, 1, 21, 3, 0, 0));
  }
}

/**
 *  Adjust RCT value based on date and time values from the pc.
 *  Call only once if the time is incorrect, but the rtc is running.
 */ 
void forceAdjustRTC() {
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

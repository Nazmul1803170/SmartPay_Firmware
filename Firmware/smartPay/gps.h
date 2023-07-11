#include <TinyGPSPlus.h>
//#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
//static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;

// The TinyGPSPlus object
TinyGPSPlus gps;

void configGPS() {
  Serial2.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

location getLocation() {
  // This sketch displays information every time a new sentence is correctly encoded.
  location place;
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read())) {
      Serial.print(F("Location: "));
      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        place.lat = gps.location.lat();
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        place.lon = gps.location.lng();
      } else {
        Serial.print(F("INVALID"));
      }
    }
  


  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
    while (true)
      ;
  }

  return place;
}


float getDistance(location start, location end){
  float distance = (float) TinyGPSPlus::distanceBetween(start.lat, start.lon, end.lat, end.lon) / 1000;
  Serial.println(distance);
  return 12.5;
}


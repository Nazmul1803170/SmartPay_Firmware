#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5    // ESP32 pin GIOP5
#define RST_PIN 27  // ESP32 pin GIOP27

MFRC522 rfid(SS_PIN, RST_PIN);



void config_rfid() {
  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void setup() {
  Serial.begin(9600);
  pinMode(4,INPUT);
  config_rfid();
}

String readCard() {
  String uid = "";
  if (rfid.PICC_IsNewCardPresent()) {  // new tag is available
    if (rfid.PICC_ReadCardSerial()) {  // NUID has been readed
      // MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      // Serial.print("RFID/NFC Tag Type: ");
      // Serial.println(rfid.PICC_GetTypeName(piccType));

      // print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        // Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(rfid.uid.uidByte[i]);
        uid += rfid.uid.uidByte[i];
      }
      Serial.println();
      Serial.print("RAW UID:");
      Serial.println(uid);

      rfid.PICC_HaltA();       // halt PICC
      rfid.PCD_StopCrypto1();  // stop encryption on PCD
    }
  }
  return uid;
}


void loop() {
  Serial.println(readCard());
  Serial.println(digitalRead(27));
  delay(1000);
}

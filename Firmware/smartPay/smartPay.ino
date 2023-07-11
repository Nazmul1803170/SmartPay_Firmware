#define BUS_ID "001"
struct trip{
  String status;
  float lat;
  float lon;
};

struct user{
  String name;
  String contact;
};

struct location{
  float lat;
  float lon;
};

uint8_t runningMode = 0;

#include "display.h"
#include "rfid_reader.h"
#include "http_client.h"
#include "gps.h"
#include "json.h"
#include "dataProcessor.h"

//#include <WiFi.h>

const char* ssid = "bro";
const char* password = "12345678";



void setup() {
  Serial.begin(115200);
  pinMode(BUZ_PIN,OUTPUT);
  digitalWrite(BUZ_PIN,LOW);
  
  //config_rfid();
  configDisplay();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  config_rfid();

  //tripp();
  //getTripInfo("1803170");
  //getUserInfo(2);
}

void loop() {
  while(1){
    String id = readCard();
    if(id != ""){
      Serial.println(id);
      buzzer();
      postLocation(id,BUS_ID);
    }
    //delay(500);
  }
  // if(runningMode == 1){
  //   addUserCard();
  // }
  //Serial.println(digitalRead(4));
  //Send an HTTP POST request every 10 minutes
  //Check WiFi connection status
  //Serial.println(httpPost(addcard, "id=1803170&contact=01772959123"));
  //Serial.println(httpGet(tripping,""));
  //getTripInfo("1803170");
  delay(1000);
}
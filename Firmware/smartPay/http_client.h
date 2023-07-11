#include <WiFi.h>
#include <HTTPClient.h>



//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.102:8000/user/addcard/";
String tripping = "http://192.168.43.137:8000/user/tripping/";
String addcard = "http://192.168.43.137:8000/user/addcard/";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String httpGet(String url, String param){
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, url+param);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payLoad = http.getString();

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();

    return payLoad;

  } else {
    Serial.println("WiFi Disconnected");
    return "";
  }
}

String httpPost(String url, String postData){
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, url);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(postData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String payLoad = http.getString();

    // Free resources
    http.end();

    return payLoad;
  } else {
    Serial.println("WiFi Disconnected");
    return "";
  }
}



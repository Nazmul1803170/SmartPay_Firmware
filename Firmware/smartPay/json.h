#include <ArduinoJson.h>

trip json_parse(String jsonString) {
  trip info;
  const size_t capacity = JSON_OBJECT_SIZE(10);  // Adjust the size based on your JSON structure
  //StaticJsonDocument jsonBuffer(capacity);
  StaticJsonDocument<capacity> jsonBuffer;

  DeserializationError error = deserializeJson(jsonBuffer, jsonString);

  if (error) {
    Serial.println("Parsing Failed: ");
    Serial.println(error.c_str());
  }

  String sts = jsonBuffer["status"];
  info.status = sts;
  info.lat = jsonBuffer["lat"];
  info.lon = jsonBuffer["lon"];

  return info;
}

trip getTripInfo(String id) {
  String jsonString = httpGet(tripping, "?id="+id);  // Replace with your JSON string
  trip info = json_parse(jsonString);
  Serial.print("Status: ");
  Serial.println(info.status);
  Serial.print("Latitude: ");
  Serial.println(info.lat);
  Serial.print("Longitude: ");
  Serial.println(info.lon);
  return info;
}


user user_info(String jsonArrayString, int index) {
  user info;

  // Calculate the required capacity for the JSON document
  const size_t capacity = JSON_OBJECT_SIZE(100);

  // Create a JSON document with the calculated capacity
  StaticJsonDocument<capacity> doc;

  // Deserialize the JSON array string into the JSON document
  DeserializationError error = deserializeJson(doc, jsonArrayString);

  // Check for parsing errors
  if (error) {
    Serial.print("Parsing failed: ");
    Serial.println(error.c_str());
  }

  // Access the values in the JSON document
  JsonArray jsonArray = doc.as<JsonArray>();

  // Iterate over each object in the JSON array
  info.name = jsonArray[index]["name"].as<const char*>();
  info.contact = jsonArray[index]["contact"].as<const char*>();

  return info;
}

user getUserInfo(int index){
  user info = user_info(httpGet(addcard, ""), index);
  // Print the parsed values
  Serial.print("Name: ");
  Serial.println(info.name);
  Serial.print("Contact: ");
  Serial.println(info.contact);
  return info;
}


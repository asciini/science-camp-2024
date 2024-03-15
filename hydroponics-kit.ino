#include <WiFi.h>                                                //include wifi library 
#include "config.h"

WiFiClient client;   

const char* ssid = SSID;                           // Wi-Fi network name
const char* password = WIFI_PASSWORD;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}


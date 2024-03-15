#include <WiFi.h>                                                //include wifi library 
#include <PubSubClient.h>
#include "config.h"

WiFiClient wifi_client;
PubSubClient client;

const char* ssid = SSID;                           // Wi-Fi network name
const char* password = WIFI_PASSWORD;

// necessary for the MQTT communication
IPAddress server(192, 168, 20, 1);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  if (String(topic) == "esp32lr20/cmd/relay1/on") {
      digitalWrite(25, HIGH);
  } else if (String(topic) == "esp32lr20/cmd/relay1/off") {
      digitalWrite(25, LOW);
  } else if (String(topic) == "esp32lr20/cmd/relay2/on") {
      digitalWrite(33, HIGH);
  } else if (String(topic) == "esp32lr20/cmd/relay2/off") {
      digitalWrite(33, LOW);
  }
}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient", "admin", "root")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("#");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

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

  client.setClient(wifi_client);
  client.setServer(server, 1883);
  client.setCallback(callback);

  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

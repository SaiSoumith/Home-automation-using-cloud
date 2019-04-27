/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  This example illustrate the cloud part of aREST that makes the board accessible from anywhere
  See the README file for more details.

  Written in 2016 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);

// aREST API key (that you can get at dashboard.arest.io)6
char * key = "xot5iacj13zbri4g";

// WiFi parameters
const char* ssid = "POCO";
const char* password = "srinandh";

// Variables to be exposed to the API


// Functions
void callback(char* topic, byte* payload, unsigned int length);

void setup(void)
{
  
  Serial.begin(115200);
  

  rest.setKey(key);
  client.setCallback(callback);

 
 
 
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Set output topic
  char* out_topic = rest.get_topic();

}

void loop() {

  // Connect to the cloud
  
  rest.loop(client);
  
  
  

}


void callback(char* topic, byte* payload, unsigned int length) {

  rest.handle_callback(client, topic, payload, length);

}

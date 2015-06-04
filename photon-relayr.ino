#include "SparkJson/SparkJson.h"
#include "MQTT.h"

//define your mqtt credentials
#define DEVICE_ID "5439a96f-f58a-4ec2-ad3b-6f74526acaee"
#define MQTT_USER "5439a96f-f58a-4ec2-ad3b-6f74526acaee"
#define MQTT_PASSWORD "rCuF.1JgO7C0"
#define MQTT_SERVER "mqtt.relayr.io"
#define MQTT_CLIENTID "photon-relayr" //can be anything else

const int sensorPin = A0;
const int led = D7;
int ledState = LOW;
char message_buff[100];
unsigned long lastPublishTime = 0;
unsigned long lastBlinkTime = 0;

                                                // Set here the time in milliseconds between publications
int publishingPeriod = 1000;					// ATTENTION !!!
                                                // DO NOT try to set values under 200 ms of the server
                                                // will kick you out

void callback(char* topic, byte* payload, unsigned int length);

//create our instance of MQTT object
MQTT client(MQTT_SERVER, 1883, callback);

//implement our callback method thats called on receiving data from a subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
  //store the received payload and convert it to string
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  //print the topic and the payload received
  Serial.println("topic: " + String(topic));
  Serial.println("payload: " + String(p));
  //call our method to parse and use the payload received
  handlePayload(p);
}

void handlePayload(char* payload) {
  StaticJsonBuffer<200> jsonBuffer;
  //convert payload to json
  JsonObject& json = jsonBuffer.parseObject(payload);
  if (!json.success()) {
    Serial.println("json parsing failed");
    return;
  }
  //get value of the key "command"
  const char* command = json["command"];
  Serial.println("parsed command: " + String(command));
  if (String(command).equals("color"))
  {
    const char* color = json["value"];
    Serial.println("parsed color: " + String(color));
    String s(color);
    if (s.equals("red"))
      RGB.color(255, 0, 0);
    else if (s.equals("blue"))
      RGB.color(0, 0, 255);
    else if (s.equals("green"))
      RGB.color(0, 255, 0);
  }
}

void mqtt_connect() {
  Serial.println("Connecting to mqtt server");
  if (client.connect(MQTT_CLIENTID, MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("Connection success, subscribing to topic");
    //subscribe to a topic
    client.subscribe("/v1/"DEVICE_ID"/cmd");
  }
  else {
    Serial.println("Connection failed, check your credentials or wifi");
  }
}

void setup() {
  RGB.control(true);
  Serial.begin(9600);
  Serial.println("Hello There, I'm your photon!");
  //setup our LED pin and connect to mqtt broker
  pinMode(led, OUTPUT);
  //set 200ms as minimum publishing period
  publishingPeriod = publishingPeriod > 200 ? publishingPeriod : 200;
  mqtt_connect();
}

void loop() {
  if (client.isConnected()) {
    client.loop();
    //publish within publishing period
    if (millis() - lastPublishTime > publishingPeriod) {
      lastPublishTime = millis();
      publish();
    }
    blink(publishingPeriod / 2);
  }
  else {
    //if connection lost, reconnect
    Serial.println("retrying..");
    mqtt_connect();
  }
}

void publish() {
  //create our json payload as {"meaning":"moisture","value":sensorvalue}
  StaticJsonBuffer<100> pubJsonBuffer;
  JsonObject& pubJson = pubJsonBuffer.createObject();
  //define a meaning for what we're sending
  pubJson["meaning"] = "moisture";
  //set our value key to the sensor's reading
  pubJson["value"] = analogRead(sensorPin);
  //copy our json object as a char array and publish it via mqtt
  char message_buff[100];
  pubJson.printTo(message_buff, sizeof(message_buff));
  client.publish("/v1/"DEVICE_ID"/data", message_buff);
  Serial.println("Publishing " + String(message_buff));
}

void blink(int interval) {
  if (millis() - lastBlinkTime > interval) {
    // save the last time you blinked the LED
    lastBlinkTime = millis();
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
  }
}


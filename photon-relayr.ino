#include "MQTT.h"

//define your mqtt credentials
#define DEVICE_ID "5439a96f-f58a-4ec2-ad3b-6f74526acaee" 
#define MQTT_USER "5439a96f-f58a-4ec2-ad3b-6f74526acaee" 
#define MQTT_PASSWORD "rCuF.1JgO7C0"
#define MQTT_SERVER "mqtt.relayr.io"
#define MQTT_CLIENTID "photon-relayr" //can be anything else

const int led = D7;
const int sensorPin = A0;
char message_buff[100];
unsigned long lastTime = 0;

                                // Set here the time in milliseconds between publications
int publishingPeriod = 1000;    // ATTENTION !!!
                                // DO NOT try to set values under 200 ms of the server
                                // will kick you out

void callback(char* topic, byte* payload, unsigned int length);

//create our mqtt client object
MQTT client(MQTT_SERVER,1883,callback);

// implement our callback method thats called on receiving data
void callback(char* topic, byte* payload, unsigned int length) {
    //blink for 1 second on receiving data
    blink(1000);
    //store the received payload and print it at the Serial port
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
    Serial.println("Command Received: "+message);

//handle message received
//change the photon's RGB LED according to payload received
    if (message.equals("{\"Color\":\"RED\"}"))
        RGB.color(255, 0, 0);
    else if (message.equals("{\"Color\":\"GREEN\"}"))
        RGB.color(0, 255, 0);
    else if (message.equals("{\"Color\":\"BLUE\"}"))
        RGB.color(0, 0, 255);
    else
    //if different payload change LED color to white
        RGB.color(255, 255, 255);
    delay(100);
}

void mqtt_connect() {
  Serial.println("Connecting to mqtt server");
  if(client.connect(MQTT_CLIENTID, MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("Connection success, subscribing to topic");
    //subscribe to a topic, cmd in this case
    client.subscribe("/v1/"DEVICE_ID"/cmd");
  }
  else {
    Serial.println("Connection failed, check your credentials");
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
        if (millis() - lastTime > publishingPeriod) {
        lastTime = millis();
        publish();
      }
    } else {
        //if connection lost, try to reconnect
      mqtt_connect();
    }
}

void publish() {
    //create our json payload
    String pubString = "{\"meaning\":\"moisture\", \"value\":";
    //read and add sensor data to payload
    pubString += analogRead(sensorPin);
    pubString += "}";
    pubString.toCharArray(message_buff, pubString.length()+1);
    //publish our json payload
    client.publish("/v1/"DEVICE_ID"/data", message_buff);
    Serial.println("Publishing " + String(message_buff));
    //100ms blink when publishing
    blink(100);
}

void blink(int time) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(time);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(time);
}

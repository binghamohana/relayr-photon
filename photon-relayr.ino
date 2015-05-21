#include "MQTT.h"

#define DEVICE_ID "8627732b-3b00-4042-9d78-316e42856116"
#define MQTT_USER "d8ac6b9e-0ba3-447f-9140-1beaefbd8702"
#define MQTT_PASSWORD "M7YHyf8OF34c"
#define MQTT_SERVER "mqtt.relayr.io"

const int led = D7;

void callback(char *topic, byte *payload, unsigned int length);

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
//MQTT client("server_name", 1883, callback);
MQTT client(MQTT_SERVER,1883,callback );

// recieve message
void callback(char* topic, byte *payload, unsigned int length) {
    blink(1000);
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    Serial.println(message);

    if (message.equals("{\"\":\"RED\"}"))
        RGB.color(255, 0, 0);
    else if (message.equals("{\"\":\"GREEN\"}"))
        RGB.color(0, 255, 0);
    else if (message.equals("{\"\":\"BLUE\"}"))
        RGB.color(0, 0, 255);
    else
        RGB.color(255, 255, 255);
    delay(100);
}


void setup() {
    RGB.control(true);
    Serial.begin(9600);
    Serial.println("Hello");
    pinMode(led, OUTPUT);

   // connect to the server
   mqtt_connect();
}

void loop() {
    if (client.isConnected()) {
        client.loop();
        if (millis() - lastTime > 500) {
        lastTime = millis();
        publish();
      }
    } else {
      mqtt_connect();
    }
}

void mqtt_connect(){
  Serial.println("Connecting to mqtt server");
  if(client.connect("spark-photon-relayr", MQTT_USER, MQTT_PASSWORD)) }
    Serial.println("Connection success");
    client.subscribe("/v1/"DEVICE_ID"/cmd");
  }
  else { 
    Serial.println("Connection failed");
  }
}

void publish() {
    client.publish("/v1/"DEVICE_ID"/data", "{\"up_ch_payload\":[1,2]}");
    blink(100);
}

void blink(int time) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(time);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(time);
}
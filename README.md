# The relayr - Photon repository

Welcome to the relayr-Photon library. Following the code in this library you would be able to connect your [Photon](https://www.particle.io/prototype#photon) particle to the relayr cloud and use it to relay data from a device.

This library also contains a short sample app to help you get started with this integration.

## Adding your Photon to the relayr cloud and receiving data-publishing credentials (curl)

1. Open a curl terminal window and enter the following to register your photon:

    `curl -H "Content-Type: application/json" -H "Authorization: Bearer <your access token>" -X POST -d '{"name":"<your device name> ", "owner":"<your user id>", "integrationType":"wunderbar1"}' https://api.relayr.io/devices/`

2. Next, use the following to receive credentials for publishing data:

    `curl -H "Content-Type: application/json" -H "Authorization: Bearer <your access token>" -X POST -d '{"transport":"mqtt"}' https://api.relayr.io/devices/<your device id retrieved from the previous step>/transmitter`

The response received would look similar to this:

    {
    "id": "eabdb2ed-2375-4137-b006-da24c93c9507",
    "secret": "na1R6Hn3dYg1",
    "owner": "9210dce8-25da-4275-a73a-1383b9774255",
    "name": "no transmitter  no model device",
    "credentials": {
    "user": "eabdb2ed-2375-4137-b006-da24c93c9507",
    "password": "na1R6Hn3dYg1",
    "clientId": "T6r2y7SN1QTewBtokyTyVBw",
    "topic": "/v1/eabdb2ed-2375-4137-b006-da24c93c9507/"
    },
    "integrationType": "wunderbar1"
    }  

You should now be able to see your new device on the dashboard at https://developer.relayr.io/dashboard devices 

You can also enter the credentials received into [this web tool](https://mqtt.relayr.io/) to see the data arriving. 

## Onboarding your Photon

1. Access https://www.particle.io/build
2. Login with your [Particle.io](https://www.particle.io) credentials
3. Claim your photon through the mobile app or manually by following [these steps](http://docs.particle.io/connect/)
4. Create your app on [build.particle.io](https://build.particle.io)
5. Go to the libraries tab in the particle IDE and import two libraries, 'MQTT' and 'SparkJson'. (if it doesn't work, you can manually add the files using the “+” sign on the top right of your project then copy paste their content)
6. Copy and paste the example code in **mqtt-relayr.ino** from the [repository](https://www.github/relayr/relayr-photon).
7. Update the following part of the code with your credentials received from the first step.
    

             //define your mqtt credentials
        #define DEVICE_ID "c36642b8-3327-4935-8f21-19a0196e7349"
        #define MQTT_USER "c36642b8-3327-4935-8f21-19a0196e7349"
        #define MQTT_PASSWORD "H_Ex02fQyBno"
        #define MQTT_SERVER "mqtt.relayr.io"
        #define MQTT_CLIENTID "photon-relayr" //can be anything else`
    
    
8. Attach your own sensor pin A0. (in our case we used a moisture sensor)
9. Update your JSON in the publish method at the line pubJson["meaning"] = "moisture"; with your new sensor's meaning. This will send your payload in the {"meaning":<meaning>,"value":<value>} format.

**The meaning parameter** denotes the meaning of the reading transferred. Meaning can be temperature, humidity, luminosity, color etc.
10. Flash your new firmware onto the photon.

## Example (Web Client)

The example web application allows you to see your sensor's reading and change the colors of the RGB LED of the photon.

To quickly run the example web application, go to the */www* folder, inside your cloned repository and run:

`python -m SimpleHTTPServer 8000` or `python3 -m http.server 8000` if you're using python 3.x

The example should now be available at: http://localhost:8000 and you should be able to see your new sensor's data.

Click on any of the "red" "green" or "blue" buttons to send a "{"command":"color","value":<color>}" payload to the photon and change its RGB LED color. 

Have fun ;)!


## Debugging

To see what's happening inside of the photon you can use a serial monitor such as **Screen** or **Putty** for debugging:

In order to check which port your photon is connected to, you can use the Arduino IDE. Simply go to *tools -> ports* and check which port is listed under *Serial ports*. Now you can listen to this port using one of the following:

#### For Linux:
screen /dev/ttyACMx 9600
#### For MacOS:
screen /dev/tty.usbmodem14xx 9600
#### For Windows:
You can use putty. First find the the *COMM* name of the device and configure it for serial monitoring at 9600 bps before connecting. You can also use Arduino's serial monitor.

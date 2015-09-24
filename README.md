# The relayr - Photon repository

Welcome to the relayr-Photon library. Following the code in this library you would be able to connect your [Photon](https://www.particle.io/prototype#photon) particle to the relayr cloud and use it to relay data from a device.

This library also contains a short sample app to help you get started with this integration.

## Adding your Photon to the relayr cloud and receiving data-publishing credentials (Developer Dashboard)

You are now able to add your prototype directly from the Developer Dashboard. 

1. In the [My Devices](https://developer.relayr.io/dashboard/devices) page click the + sign on the bottom right part of the screen
2. Select 'Add Prototype'
3. Give your prototype a name and follow the instructions to add it
4. Enter the credentials received in the respective places in your code

You should now be able to see your new device on the Developer Dashboard under [My Devices](https://developer.relayr.io/dashboard/devices)

You can also enter the credentials received into [this web tool](https://mqtt.relayr.io/) to see the data arriving. 

## Onboarding your Photon

1. Access https://www.particle.io/build
2. Login with your [Particle.io](https://www.particle.io) credentials
3. Claim your photon through the mobile app or manually by following [these steps](http://docs.particle.io/connect/)
4. Create your app on [build.particle.io](https://build.particle.io)
5. Go to the libraries tab in the particle IDE and import two libraries, 'MQTT' and 'SparkJson'. (if it doesn't work, you can manually add the files using the “+” sign on the top right of your project then copy and paste their content)
6. Copy and paste the example code under **mqtt-relayr.ino** in the [repository](https://www.github.com/relayr/relayr-photon).
7. Update the following part of the code with the credentials received from the curl request.
    

             //define your mqtt credentials
        #define DEVICE_ID "c36642b8-3327-4935-8f21-19a0196e7349"
        #define MQTT_USER "c36642b8-3327-4935-8f21-19a0196e7349"
        #define MQTT_PASSWORD "H_Ex02fQyBno"
        #define MQTT_SERVER "mqtt.relayr.io"
        #define MQTT_CLIENTID "photon-relayr" //can be anything else, you do not have to use the one received in the response JSON`
    
    
8. Attach your own sensor pin A0. (in the example we used a moisture sensor)
9. Update your JSON in the publish method line pubJson["meaning"] = "moisture"; with your new sensor meaning. This will send your payload in the {"meaning":<meaning>,"value":<value>} format.

**The meaning parameter** denotes the meaning of the reading transferred. Meaning can be temperature, humidity, luminosity, color etc.
10. Flash your new firmware onto the photon.

## Example (Web Client)

The example web application allows you to see your sensor readings and change the colors of the RGB LED of the photon.

To quickly run the example web application, go to the */www* folder, inside your cloned repository and run:

`python -m SimpleHTTPServer 8000` or `python3 -m http.server 8000` if you're using python 3.x

The example should now be available at: http://localhost:8000 and you should be able to see your new sensor data.

Click on any of the "red" "green" or "blue" buttons to send a "{"command":"color","value":<color>}" payload to the photon and change its RGB LED color. 

Have fun ;)!


## Debugging

To debug the inside workings of the photon you can use a serial monitor such as **Screen** or **Putty**.

In order to check which port your photon is connected to, you can use the Arduino IDE. Simply go to *tools -> ports* and check which port is listed under *Serial ports*. Now you can listen to this port using one of the following:

#### For Linux:
screen /dev/ttyACMx 9600
#### For MacOS:
screen /dev/tty.usbmodem14xx 9600
#### For Windows:
You can use putty. First find the the *COMM* name of the device and configure it for serial monitoring at 9600 bps before connecting. You can also use Arduino's serial monitor.

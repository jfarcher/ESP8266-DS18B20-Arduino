##ESP based temperature sensor##
Add a Dallas DS18B20 temperature sensor to an ESP chip and output the data to an MQTT server.

In this sketch the data pin of the DS18B20 connects to D4 of a Wemos D1 Mini, or NodeMCU board, VCC to 3V and GND to GND.

Note the DS18B20 requires connection of a 4.7k pullup resistor between DATA and VCC.

The Arduino OTA library is included to send OTA updates from the Arduino IDE.

This sketch is constantly active, reporting the temperature every 10000 milisecs, therefore will require a permanent power supply. A seperate sketch will follow which will harness deep sleep for use with battery (obviously this will discard the use of OTAvia MDNS)


#How to Use:#
### Installing with Boards Manager ###
Taken from: ```https://github.com/esp8266/Arduino```

Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

- Install Arduino 1.6.8 from the [Arduino website](http://www.arduino.cc/en/main/software).
- Start Arduino and open Preferences window.
- Enter ```http://arduino.esp8266.com/stable/package_esp8266com_index.json``` into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

###Once you have the IDE configured you will need to add the following libraries:###

OneWire

Wire

PubSubClient

ArduinoOTA

There is an included config.h.sample, you will need to copy this to config.h and edit the properties to reflect your WiFi details and MQTT server.

##Bill of materials##

D1 Mini http://www.banggood.com/D1-Mini-NodeMcu-Lua-WIFI-ESP8266-Development-Board-p-1044858.html

DS18B20 module (inc 4.7k resistor) http://www.banggood.com/DS18B20-Digital-Temperature-Sensor-Module-For-Arduino-p-76516.html



#include "config.h"

#include <PubSubClient.h>
#include <DallasTemperature.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>


#define OWBUS 2
OneWire oneWire(OWBUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempsens;

WiFiClient ESPClient;
PubSubClient client(ESPClient);

/*     MAIN  */


void setup() {
  Serial.begin(115200);
  setup_wifi();
 
  setup_OTA();
  setup_sensors();  
  client.setServer(mqtt_server, 1883);
  #define mac  WiFi.macAddress()
  #define mqtt_topic (String("device/" + mac + "/temperature").c_str())

}

void setup_sensors(){
sensors.begin();
  //Serial.println(sensors.getDeviceCount(), DEC);
  if (!sensors.getAddress(tempsens, 0)) Serial.println("Unable to find address for Device 0");
  sensors.setResolution(tempsens, 9);
  
}

void setup_wifi() {  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart(); 
  }
  //Serial.println(WiFi.localIP());

}


void setup_OTA() {
  delay(10);
  //ArduinoOTA.setHostname("Lounge");

  ArduinoOTA.onStart([](){
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([](){
    Serial.println("\nEnd");
  });
 ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
});
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
ArduinoOTA.begin();
   

}


void reconnect() {
  while (!client.connected()){
    Serial.println("Attempting MQTT connection.....");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");      


    } else{
      Serial.println("Failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}




long lastMsg = 0;
float temp = 0.0;

void loop() {
  ArduinoOTA.handle();
  
  
  long now = millis();
  if (now - lastMsg > 10000){    
    lastMsg = now;
    sensors.requestTemperatures();
    float tempC = sensors.getTempC(tempsens);
    if (!client.connected()) {
      reconnect();
    }
    client.publish(mqtt_topic, String(tempC).c_str(), false);
  }
  client.loop();
}




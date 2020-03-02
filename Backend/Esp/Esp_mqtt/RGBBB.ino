#include "EspMQTTClient.h"
#define defaulturl "abbexpectmore@gmail.com"

#define G 14 //D5
#define R 12 //D6
#define B 13 //D7

void onConnectionEstablished();

EspMQTTClient client(
 "ABB_Indgym_Guest",           // Wifi ssid
  "Welcome2abb",           // Wifi password
  "maqiatto.com",  // MQTT broker ip
  1883,             // MQTT broker port
  "abbexpectmore@gmail.com",            // MQTT username
  "ABBExpectMore2020",       // MQTT password
  "Node",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);

void change(int x,int y,int z){
  x = map(x, 0, 255, 0, 1024);
  y = map(y, 0, 255, 0, 1024);
  z = map(z, 0, 255, 0, 1024);
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  analogWrite(R,x);
  analogWrite(G,y);
  analogWrite(B,z);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(G, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(B, OUTPUT);
}

void onConnectionEstablished(){
  client.subscribe("abbexpectmore@gmail.com/light", [] (const String &payload)
  {
    //Serial.println(payload);
    if (payload == "on"){
      Serial.println("on: " + payload);
      
      change(255,255,255);
      
    } else if (payload == "off"){
      Serial.println("off: " + payload);
      change(0,0,0);
    } else {
      Serial.println("something else: " + payload);
      Serial.println("värde: " + payload.charAt(4) + payload.charAt(5) + payload.charAt(6));
    }
    
  });
  client.subscribe("abbexpectmore@gmail.com/ctrl", [] (const String &payload1)
  {
    if (payload1 == "on"){
      change(255,255,255);
    } else if (payload1 == "off"){
      change(0,0,0);
    }else{
      Serial.println(payload1);

      int valR = payload1.substring(1,payload1.indexOf(',')).toInt();
      int valG = payload1.substring(payload1.indexOf(',')+1,payload1.lastIndexOf(',')).toInt();
      int valB = payload1.substring(payload1.lastIndexOf(',')+1).toInt();

      Serial.println(valR);
      Serial.println(valG);
      Serial.println(valB);

      valR = constrain(valR,0,255);
      valG = constrain(valG,0,255);
      valB = constrain(valB,0,255);

      change(valR,valG,valB);
    }
  });
  
  client.publish("abbexpectmore@gmail.com/light", "I'm online!");

  client.executeDelayed(5 * 1000, []() {
    //client.publish("joakim.flink@abbindustrigymnasium.se/lampa", "This is a message sent 5 seconds later");
  });
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}

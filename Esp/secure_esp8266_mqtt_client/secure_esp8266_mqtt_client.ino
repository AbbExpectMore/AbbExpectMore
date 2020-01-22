/*

Använder https://github.com/tsi-software/Secure_ESP8266_MQTT_poc

*/


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "AsyncWait.h"
#include "globals.h"
#include "SetupWifi.h"

#define G 14 //D5
#define R 12 //D6
#define B 13 //D7

const int topic_count = 3;
const char *topics[topic_count] = {"/ctrl", "/power", "/brightness"};

//TODO: implement secure credintials as a runtime config file
//      rather than a header file.
// #include "/home/wtaylor/private/Secure_ESP8266_MQTT/secure_credentials.h"
#include "secure_credentials.h"

SetupWifi setupWifi(
    STASSID, STAPSK,
    CA_CERT_PROG, CLIENT_CERT_PROG, CLIENT_KEY_PROG);

const char *mqtt_server = MQTT_SERVER;
//IPAddress broker(192,168,1,1); // IP address of your MQTT broker

const char *ID = "RGB-ESP"; // Name of our device, must be unique

static PubSubClient pubsubClient(setupWifi.getWiFiClient());

void change(int x, int y, int z)
{
  x = map(x, 0, 255, 0, 1024);
  y = map(y, 0, 255, 0, 1024);
  z = map(z, 0, 255, 0, 1024);
  DEBUG_LOGLN(x);
  DEBUG_LOGLN(y);
  DEBUG_LOGLN(z);
  analogWrite(R, x);
  analogWrite(G, y);
  analogWrite(B, z);
}

// Handle incomming messages from the broker
void callback(char *topic, byte *payload, unsigned int length)
{
  String topicStr;
  String payloadStr;

  for (int i = 0; topic[i]; i++)
  {
    topicStr += topic[i];
  }

  for (int i = 0; i < length; i++)
  {
    payloadStr += (char)payload[i];
  }

  DEBUG_LOGLN("");
  DEBUG_LOG("Message arrived - [");
  DEBUG_LOG(topicStr);
  DEBUG_LOG("] ");
  DEBUG_LOGLN(payloadStr);

  if (topicStr == "/ctrl")
  {

    int valR = payloadStr.substring(1, payloadStr.indexOf(',')).toInt();
    int valG = payloadStr.substring(payloadStr.indexOf(',') + 1, payloadStr.lastIndexOf(',')).toInt();
    int valB = payloadStr.substring(payloadStr.lastIndexOf(',') + 1).toInt();

    // DEBUG_LOGLN(valR);
    // DEBUG_LOGLN(valG);
    // DEBUG_LOGLN(valB);

    valR = constrain(valR, 0, 255);
    valG = constrain(valG, 0, 255);
    valB = constrain(valB, 0, 255);

    change(valR, valG, valB);
  }
  else if (topicStr == "/power")
  {
    if (payloadStr == "on")
    {
      change(255, 255, 255);
    }
    else
    {
      change(0, 0, 0);
    }
  }
  else if (topicStr == "/brightness")
  {
    change(map(payloadStr.toInt(), 0, 100, 0, 255), map(payloadStr.toInt(), 0, 100, 0, 255), map(payloadStr.toInt(), 0, 100, 0, 255));
  }
}

// Reconnect to the MQTT client.
void reconnectToMQTT(MilliSec currentMilliSec)
{
  if (pubsubClient.connected())
  {
    // We are connected so nothing further needs to be done.
    return;
  }

  static AsyncWait waitToRetry;
  if (waitToRetry.isWaiting(currentMilliSec))
  {
    return;
  }

  DEBUG_LOGLN("Attempting MQTT connection...");
  // Attempt to connect
  if (pubsubClient.connect(ID))
  {
    DEBUG_LOG("connected as ");
    DEBUG_LOGLN(ID);

    for (int i = 0; i < topic_count; i++)
    {
      DEBUG_LOG("Subcribing to: ");
      DEBUG_LOGLN(topics[i]);
      pubsubClient.subscribe(topics[i]);
    }

    // pubsubClient.subscribe(TOPIC_ZONE_OFF.c_str());
    // DEBUG_LOG("Subcribed to: ");
    // DEBUG_LOGLN(TOPIC_ZONE_OFF);

    // pubsubClient.subscribe(TOPIC_ZONE_STATUS.c_str());
    // DEBUG_LOG("Subcribed to: ");
    // DEBUG_LOGLN(TOPIC_ZONE_STATUS);
  }
  else
  {
    DEBUG_LOGLN(" try again in 5 seconds.");
    waitToRetry.startWaiting(currentMilliSec, 5000);
  }
}

void setup()
{
  // Set programResetPin to high impedance and default its value to HIGH.
  pinMode(G, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(B, OUTPUT);

#ifdef DEBUG
  Serial.begin(115200); // Start serial communication at 115200 baud
#endif

  setupWifi.setupWifi();
  //pubsubClient.setServer(broker, 1883);
  pubsubClient.setServer(mqtt_server, 8883);
  pubsubClient.setCallback(callback); // Initialize the callback routine
}

void loop()
{
  setupWifi.loopWifi();
  if (!setupWifi.isReadyForProcessing())
  {
    // The WiFi is not ready yet so
    // don't do any further processing.
    return;
  }

  if (!pubsubClient.connected())
  {
    // Reconnect if connection is lost.
    MilliSec currentMilliSec = millis();
    reconnectToMQTT(currentMilliSec);
  }
  pubsubClient.loop();
}

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
#define knapp 15 // D8

const int topic_count = 3;
const char *topics[topic_count] = {"/ctrl", "/power", "/brightness"};
int last_color[3] = {0, 0, 0};
int rainbow_color[3] = {10, 55, 250};
int rawe_color[3] = {9, 55, 250};

unsigned long time_now;
int animationDelay = 50;
int counter = 0;
int numColors = 255;
int rawe_delay = 150;

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
  DEBUG_LOGLN(x);
  DEBUG_LOGLN(y);
  DEBUG_LOGLN(z);
  x = map(x, 0, 255, 0, 1024);
  y = map(y, 0, 255, 0, 1024);
  z = map(z, 0, 255, 0, 1024);
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

    last_color[0] = valR;
    last_color[1] = valG;
    last_color[2] = valB;

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
  pinmode(knapp, INPUT);

#ifdef DEBUG
  Serial.begin(115200); // Start serial communication at 115200 baud
#endif

  setupWifi.setupWifi();
  //pubsubClient.setServer(broker, 1883);
  pubsubClient.setServer(mqtt_server, 8883);
  pubsubClient.setCallback(callback); // Initialize the callback routine
  time_now = millis();
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

  for (int i = 0; i < 3; i++) // check for rainbow
  {
    // DEBUG_LOGLN(i);
    if (last_color[i] != rainbow_color[i])
    {
      // DEBUG_LOGLN(i);
      // DEBUG_LOG(last_color[i]);
      // DEBUG_LOG(" är inte ");
      // DEBUG_LOGLN(rainbow_color[i]);
      // delay(100);
      break;
    }

    if (i == 2 && millis() > time_now + animationDelay)
    {
      // DEBUG_LOGLN("rainbowtime");
      rainbow();
    }
  }

  for (int i = 0; i < 3; i++) // check for rainbow
  {
    if (last_color[i] != rawe_color[i])
    {
      break;
    }
    if (i == 2)
    {
      rawe();
    }
  }

  if (digitalRead(knapp)){
    last_color = {0, 0, 0};
    change(0, 0, 0);
  }

  // if (last_color == rainbow_color && (millis() > time_now + animationDelay))
  // {
  //   rainbow();
  // }
  // if (last_color == rawe_color)
  // {
  //   rawe();
  // }
}

void rawe()
{
  DEBUG_LOGLN("Doin the rawe");
  change(random(0, 255), random(0, 255), random(0, 255));
  delay(rawe_delay);
}

void rainbow()
{
  DEBUG_LOGLN("Doin the rainbow");

  float colorNumber = counter > numColors ? counter - numColors : counter;

  // Play with the saturation and brightness values
  // to see what they do
  float saturation = 1;                               // Between 0 and 1 (0 = gray, 1 = full color)
  float brightness = .05;                             // Between 0 and 1 (0 = dark, 1 is full brightness)
  float hue = (colorNumber / float(numColors)) * 360; // Number between 0 and 360
  long color = HSBtoRGB(hue, saturation, brightness);

  // Get the red, blue and green parts from generated color
  int red = color >> 16 & 255;
  int green = color >> 8 & 255;
  int blue = color & 255;

  red = map(red, 0, 12, 0, 255);
  green = map(green, 0, 12, 0, 255);
  blue = map(blue, 0, 12, 0, 255);

  change(red, green, blue);

  // Counter can never be greater then 2 times the number of available colors
  // the colorNumber = line above takes care of counting backwards (nicely looping animation)
  // when counter is larger then the number of available colors
  counter = (counter + 1) % (numColors * 2);

  // If you uncomment this line the color changing starts from the
  // beginning when it reaches the end (animation only plays forward)
  // counter = (counter + 1) % (numColors);

  time_now = millis();
}

long HSBtoRGB(float _hue, float _sat, float _brightness)
{
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;

  if (_sat == 0.0)
  {
    red = _brightness;
    green = _brightness;
    blue = _brightness;
  }
  else
  {
    if (_hue == 360.0)
    {
      _hue = 0;
    }

    int slice = _hue / 60.0;
    float hue_frac = (_hue / 60.0) - slice;

    float aa = _brightness * (1.0 - _sat);
    float bb = _brightness * (1.0 - _sat * hue_frac);
    float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));

    switch (slice)
    {
    case 0:
      red = _brightness;
      green = cc;
      blue = aa;
      break;
    case 1:
      red = bb;
      green = _brightness;
      blue = aa;
      break;
    case 2:
      red = aa;
      green = _brightness;
      blue = cc;
      break;
    case 3:
      red = aa;
      green = bb;
      blue = _brightness;
      break;
    case 4:
      red = cc;
      green = aa;
      blue = _brightness;
      break;
    case 5:
      red = _brightness;
      green = aa;
      blue = bb;
      break;
    default:
      red = 0.0;
      green = 0.0;
      blue = 0.0;
      break;
    }
  }

  long ired = red * 255.0;
  long igreen = green * 255.0;
  long iblue = blue * 255.0;

  return long((ired << 16) | (igreen << 8) | (iblue));
}

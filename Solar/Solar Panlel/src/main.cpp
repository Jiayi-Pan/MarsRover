#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <ESP32Servo.h>

static const int servoPin1 = 13;
static const int servoPin2 = 12;
static const int servoPin3 = 14;

static const int channel1 = 4;
static const int channel2 = 2;
static const int channel3 = 3;

static int openflag = 0;
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

const char *ssid = "my_room";
const char *password = "aniu0828";

const char *hostname = "espui";

int statusLabelId;
int graphId;
int millisLabelId;
int testSwitchId;

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 180)
{
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

int val = 0;
int val_former = 0;
int state = 0;
int pos = 90;
int ang = 45;

int angle[3] = {0, 0, 0};

void clos(void)
{
  ledcAnalogWrite(channel1, 0);
  ledcAnalogWrite(channel2, 90);
  ledcAnalogWrite(channel3, 90);
}

void ope(void)
{
  ledcAnalogWrite(channel1, 180);
  ledcAnalogWrite(channel2, 0);
  ledcAnalogWrite(channel3, 90);
}

void Switch(Control *sender, int value)
{ //Finger
  Serial.println("check");
  Serial.println(value);
  switch (value)
  {
  case S_ACTIVE:
    if (openflag == 0)
    {
      openflag = 1;
      ope();
      Serial.print("Switch On\n");
    }
    break;

  case S_INACTIVE:
    if (openflag == 1)
    {
      openflag = 0;
      clos();
      Serial.print("Switch Off\n");
    }
    break;
  }
}

void sunflower(void)
{
  Serial.print("Sunflower On\n");

  val = analogRead(27);
  if (state == 0)
  {
    val_former = val;
    state += 1;
  }

  if (state == 1)
  {
    ledcAnalogWrite(channel1, 180);
    ledcAnalogWrite(channel2, 45);
    ledcAnalogWrite(channel3, pos);
    for (int an = 45; an >= 0; an--)
    { // 0°到180°
      val = analogRead(27);
      ledcAnalogWrite(channel3, an);
      if (val - val_former >= 100)
      {
        state += 1;
        ledcAnalogWrite(channel3, an);
        Serial.println(val);
        break;
      }
      else if (val_former >= val)
      {
        val_former = val;
        ang = an;
      }
      Serial.println(an);
      delay(50);
    }
  }
  if (state == 2)
  {
    ledcAnalogWrite(channel1, 180);
    ledcAnalogWrite(channel2, ang);
    ledcAnalogWrite(channel3, pos);
    delay(50);
    for (int an = ang; an <= 90; an++)
    { // 0°到180°
      val = analogRead(27);
      ledcAnalogWrite(channel3, an);
      if (val - val_former >= 80)
      {
        state += 1;
        ledcAnalogWrite(channel3, an);
        //Serial.println(666);
        break;
      }
      else if (val_former >= val)
      {
        val_former = val;
        ang = an;
      }
      //Serial.println(pos);
      delay(50);
    }
  }
  else
  {
    ledcAnalogWrite(channel1, 180);
    ledcAnalogWrite(channel2, ang);
    ledcAnalogWrite(channel3, pos);
  }
  //Serial.println(state);
}

void SwitchSunflower(Control *sender, int value)
{ //Finger
  switch (value)
  {
  case S_ACTIVE:
    if (openflag == 1)
    {
      sunflower();
      Serial.print("Sunflower On\n");
    }
    break;
  }
}
void setup()
{
  Serial.begin(115200);
  ledcSetup(channel1, 50, 16);        // channel, freq, resolution
  ledcAttachPin(servoPin1, channel1); // pin, channel

  ledcSetup(channel2, 50, 16);        // channel, freq, resolution
  ledcAttachPin(servoPin2, channel2); // pin, channel

  ledcSetup(channel3, 50, 16);        // channel, freq, resolution
  ledcAttachPin(servoPin3, channel3); // pin, channel

  WiFi.setHostname(hostname);
  // try to connect to existing network
  WiFi.begin(ssid, password);
  Serial.print("\n\nTry to connect to existing network");

  // Wait for connection, 5s timeout
  do
  {
    delay(500);
    Serial.print(".");
  } while (WiFi.status() != WL_CONNECTED);

  dnsServer.start(DNS_PORT, "*", apIP);

  Serial.println("\n\nWiFi parameters:");
  Serial.print("Mode: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());

  ESPUI.switcher("Switch", &Switch, ControlColor::Alizarin);
  ESPUI.switcher("Sunflower", &SwitchSunflower, ControlColor::Alizarin);
  ESPUI.begin("Solar Panel Controller");
}

void loop()
{
  //val= analogRead(servoPin1);
  //Serial.println(val);
  //ope();
  //val= analogRead(27);
  //Serial.println(val);
  //Serial.println(openflag);
  dnsServer.processNextRequest();

  // static long oldTime = 0;
  // static bool testSwitchState = false;

  // if (millis() - oldTime > 5000) {

  //   testSwitchState = !testSwitchState;
  //   ESPUI.updateSwitcher(testSwitchId, testSwitchState);

  //   oldTime = millis();
  // }

  //Serial.println(state);
}

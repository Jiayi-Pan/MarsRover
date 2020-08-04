// Finger -> D2
// Base ->D4
#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <ESP32Servo.h>

int fingerpin = 21;
int basepin = 5;
int pin1 = 18;
int pin2 = 19;
int pin3 = 4;
int pin4 = 22;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 180) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}


const char *ssid = "iPhone";
const char *password = "12345678";

const char *hostname = "espui";

int statusLabelId;
int graphId;
int millisLabelId;
int testSwitchId;


void Finger(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(1,sender->value.toInt());
}
void Base(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(2,sender->value.toInt());
}
void Slider3(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(3,sender->value.toInt());
}
void Slider4(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(4,sender->value.toInt());
}
void Slider5(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(5,sender->value.toInt());
}
void Slider6(Control *sender, int type) { //Finger
  // Servo
  ledcAnalogWrite(6,sender->value.toInt());
}



void setup(void) {
	// Finger
  ledcSetup(1,50,16); // channel, freq, resolution
  ledcAttachPin(fingerpin,1); // pin, channel
  // Base
  ledcSetup(2,50,16); // channel, freq, resolution
  ledcAttachPin(basepin,2); // pin, channel

  ledcSetup(3,50,16); // channel, freq, resolution
  ledcAttachPin(pin1,3); // pin, channel

  ledcSetup(4,50,16); // channel, freq, resolution
  ledcAttachPin(pin2,4); // pin, channel

  ledcSetup(5,50,16); // channel, freq, resolution
  ledcAttachPin(pin3,5); // pin, channel

  ledcSetup(6,50,16); // channel, freq, resolution
  ledcAttachPin(pin4,6); // pin, channel

  // ESPUI.setVerbosity(Verbosity::VerboseJSON);
  Serial.begin(115200);

  WiFi.setHostname(hostname);
  // try to connect to existing network
  WiFi.begin(ssid, password);
  Serial.print("\n\nTry to connect to existing network");

    // Wait for connection, 5s timeout
    do {
      delay(500);
      Serial.print(".");
    } while (WiFi.status() != WL_CONNECTED);


  dnsServer.start(DNS_PORT, "*", apIP);

  Serial.println("\n\nWiFi parameters:");
  Serial.print("Mode: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());

  ESPUI.slider("Finger", &Finger, ControlColor::Alizarin, 120,100,150);
  ESPUI.slider("Base", &Base, ControlColor::Alizarin, 90,0,360);
  ESPUI.slider("3", &Slider3, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("4", &Slider4, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("5", &Slider5, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("6", &Slider6, ControlColor::Alizarin, 90,0,180);


  /*
   * .begin loads and serves all files from PROGMEM directly.
   * If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
   * (.prepareFileSystem has to be run in an empty sketch before)
   */
 

 
  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
   * SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password
   * since it is transmitted in cleartext. Just add a string as username and
   * password, for example begin("ESPUI Control", "username", "password")
   */


  ESPUI.begin("Robotic Arm Controller");

    ledcAnalogWrite(1,100);
    ledcAnalogWrite(2,90);
    ledcAnalogWrite(3,90);
    ledcAnalogWrite(4,90);
    ledcAnalogWrite(5,90);
    ledcAnalogWrite(6,90);


}

void loop(void) {
  dnsServer.processNextRequest();

  static long oldTime = 0;
  static bool testSwitchState = false;

  if (millis() - oldTime > 5000) {

    testSwitchState = !testSwitchState;
    ESPUI.updateSwitcher(testSwitchId, testSwitchState);
    
    oldTime = millis();
  }
}
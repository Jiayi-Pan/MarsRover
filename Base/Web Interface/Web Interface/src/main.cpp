#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>

// Below is the Mars Pro Protocol
#define MODELSWITCH1 11
#define MODELSWITCH2 12
#define MODELSWITCH3 13
#define MAGNETSWITCH1 21
#define MAGNETSWITCH2 22
#define MAGNETSWITCH3 23
#define ON 2
#define OFF 1
#define ROTATE 40
#define UP 50
#define DOWN 60
#define RIGHT 70
#define LEFT 80
#define BEGIN 4
#define STOP 3
#define SPEED 90


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

void modelSwitch1(Control *sender, int value) {
  switch (value) {
  case S_ACTIVE:
    Serial.print(MODELSWITCH1);
    Serial.print("h");
    Serial.print(ON);    
    Serial.print("h");
    break;

  case S_INACTIVE:
    Serial.print(MODELSWITCH1);
    Serial.print("h");
    Serial.print(OFF);    
    Serial.print("h");
    break;
  }
}

void modelSwitch2(Control *sender, int value) {
    switch (value) {
  case S_ACTIVE:
    Serial.print(MODELSWITCH2);
    Serial.print("h");
    Serial.print(ON);    
    Serial.print("h");
    break;

  case S_INACTIVE:
    Serial.print(MODELSWITCH2);
    Serial.print("h");
    Serial.print(OFF);    
    Serial.print("h");
    break;
  }
}

void modelSwitch3(Control *sender, int value) {
    switch (value) {
  case S_ACTIVE:
    Serial.print(MODELSWITCH3);
    Serial.print("h");
    Serial.print(ON);
    Serial.print("h");
    break;

  case S_INACTIVE:
    Serial.print(MODELSWITCH3);
    Serial.print("h");
    Serial.print(OFF);
    Serial.print("h");
    break;
  }
}

void magnetSwitch1(Control *sender, int value) {
   switch (value) {
  case S_ACTIVE:
    Serial.print(MAGNETSWITCH1);
    Serial.print("h");
    Serial.print(ON);
    Serial.print("h");
    break;

  case S_INACTIVE:
    Serial.print(MAGNETSWITCH1);
    Serial.print("h");
    Serial.print(OFF);   
    Serial.print("h");
    break;
  }
}

void magnetSwitch2(Control *sender, int value) {
   switch (value) {
  case S_ACTIVE:
    Serial.print(MAGNETSWITCH2);
    Serial.print("h");
    Serial.print(ON);
    Serial.print("h");

    break;

  case S_INACTIVE:
    Serial.print(MAGNETSWITCH2);
    Serial.print("h");
    Serial.print(OFF);
    Serial.print("h");
    break;
  }
}

void magnetSwitch3(Control *sender, int value) {
   switch (value) {
  case S_ACTIVE:
    Serial.print(MAGNETSWITCH3);
    Serial.print("h");
    Serial.print(ON);
    Serial.print("h");
    break;

  case S_INACTIVE:
    Serial.print(MAGNETSWITCH3);
    Serial.print("h");
    Serial.print(OFF);
    Serial.print("h");
    break;
  }
}


void Rotate(Control *sender, int type) {
  if (sender->value.toInt() <= 120){
    Serial.println(5);
  }else if (sender->value.toInt() >=240)
  {
    Serial.println(6);
  }
  
}


void Move(Control *sender, int value) {
  switch (value) {
  case P_FOR_DOWN:
    Serial.println(1);
    break;

  case P_BACK_DOWN:
    Serial.println(2); 
    break;

  case P_LEFT_DOWN:
    Serial.println(3);
    break;

  case P_RIGHT_DOWN:
    Serial.println(4);
    break;

  case P_CENTER_DOWN:
    Serial.println(7);
    break;
  }
}


void Speed (Control *sender, int value){
  Serial.print(SPEED);
  Serial.print("h");
  Serial.print(sender->value);
  Serial.print("h");
}



void setup(void) {
	// Servo
  ledcSetup(2,50,16); // channel, freq, resolution
  ledcAttachPin(2,2); // pin, channel

  // ESPUI.setVerbosity(Verbosity::VerboseJSON);
  Serial.begin(9600);

  WiFi.setHostname(hostname);
  // try to connect to existing network
  WiFi.begin(ssid, password);

  // Serial.print("\n\nTry to connect to existing network");

    // Wait for connection, 5s timeout
    do {
      delay(500);
      Serial.print(".");
    } while (WiFi.status() != WL_CONNECTED);


  dnsServer.start(DNS_PORT, "*", apIP);
/*
  Serial.println("\n\nWiFi parameters:");
  Serial.print("Mode: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());
*/

  // Web Controller begins
  ESPUI.slider("Rotate", &Rotate, ControlColor::Alizarin, 180,0,360);
  ESPUI.padWithCenter("Move",&Move, ControlColor::Alizarin);
 
 /*
  ESPUI.slider("Speed", &Speed, ControlColor::Alizarin, 255,0,255);
  ESPUI.switcher("Model Switch1",&modelSwitch1,ControlColor::Turquoise);
  ESPUI.switcher("Model Switch2",&modelSwitch2,ControlColor::Turquoise);
  ESPUI.switcher("Model Switch3",&modelSwitch3,ControlColor::Turquoise);
  ESPUI.switcher("Magnet Switch1",&magnetSwitch1,ControlColor::Emerald);
  ESPUI.switcher("Magnet Switch2",&magnetSwitch2,ControlColor::Emerald);
  ESPUI.switcher("Magnet Switch3",&magnetSwitch3,ControlColor::Emerald);
*/



  /*
   * .begin loads and serves all files from PROGMEM directly.
   * If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
   * (.prepareFileSystem has to be run in an empty sketch before)
   */
 

 
  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  //ESPUI.sliderContinuous = true;

  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
   * SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password
   * since it is transmitted in cleartext. Just add a string as username and
   * password, for example begin("ESPUI Control", "username", "password")
   */


  ESPUI.begin("Car Central Controller");

  //Serial.print(120);
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
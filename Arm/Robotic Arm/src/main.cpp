#include <Arduino.h>

#include <DNSServer.h>
#include <ESPUI.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

#include <WiFi.h>


const char *ssid = "2302";
const char *password = "Panjiayiduanjunxiapanjiantun_20010311";

const char *hostname = "espui";

int statusLabelId;
int graphId;
int millisLabelId;
int testSwitchId;

void slider(Control *sender, int type) {
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println(sender->value);
  // Like all Control Values in ESPUI slider values are Strings. To use them as int simply do this:
  int sliderValueWithOffset = sender->value.toInt() + 1;
  Serial.print("SliderValue with offset: ");
  Serial.println(sliderValueWithOffset);
}


void setup(void) {
  ESPUI.setVerbosity(Verbosity::VerboseJSON);
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

  
  ESPUI.slider("Slider one", &slider, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("Slider two", &slider, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("Slider three", &slider, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("Slider four", &slider, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("Slider five", &slider, ControlColor::Alizarin, 90,0,180);
  ESPUI.slider("Slider six", &slider, ControlColor::Alizarin, 90,0,180);

  /*
   * .begin loads and serves all files from PROGMEM directly.
   * If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
   * (.prepareFileSystem has to be run in an empty sketch before)
   */
 

 
  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  // ESPUI.sliderContinuous = true;

  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
   * SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password
   * since it is transmitted in cleartext. Just add a string as username and
   * password, for example begin("ESPUI Control", "username", "password")
   */


  ESPUI.begin("Robotic Arm Controller");
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
#include <ESP32Servo.h>
#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>


const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;


const char *ssid = "TP-LINK_303";
const char *password = "64129548";

const char *hostname = "espui";

int statusLabelId;
int graphId;
int millisLabelId;
int testSwitchId;

int openflag = 0;

static const int servoPin1 = 13;
static const int servoPin2 = 12;
static const int servoPin3 = 14;

Servo servo1;
Servo servo2;
Servo servo3;

int val=0;
int val_former=0;
int state=0;
int pos=90;
int ang=45;

int angle[3]={0,0,0};


void clos(void){  
  servo1.write(0);// high
  servo2.write(90);
  servo3.write(90);
  delay(20);}

void ope(void){  
  servo1.write(180);// high
  servo2.write(0);
  servo3.write(90);
  delay(20);}

void Switch(Control *sender, int value) { //Finger
   switch (value) {
  case S_ACTIVE:
    if (openflag == 0){
      openflag = 1;
      ope();
      }
    break;

  case S_INACTIVE:
    if (openflag == 1){
      openflag = 0;
      clos();
      }
    break;
    break;
  }
}






void sunflower(void){
  
   val= analogRead(27);
   if(state==0){val_former=val;state+=1;}

  
    if (state==1){
    servo1.write(180);  
    delay(1000);
    servo2.write(45);
    delay(1000);
    servo3.write(pos);
    delay(2000);
    for (int an = 45; an >= 0; an --) { // 0°到180°
      val= analogRead(27);
      servo3.write(an);              
        if(val-val_former>=100){
          state+=1;
          servo3.write(an);
          Serial.println(val);
          break;
        }
        else if(val_former>=val){
          val_former=val;ang=an;
       }
   Serial.println(an);
   delay(100);
  }
    }
    if (state==2
    ){
    servo1.write(180);  
    delay(100);
    servo2.write(ang);
    delay(100);
    servo3.write(pos);
    delay(200);
    for (int an = ang; an <= 90; an ++) { // 0°到180°
      val= analogRead(27);
      servo3.write(an);              
        if(val-val_former>=80){
          state+=1;
          servo3.write(an);
          //Serial.println(666);
          break;
        }
        else if(val_former>=val){
          val_former=val;ang=an;
       }
   //Serial.println(pos);
   delay(100);
  }
    }
    else{
      servo1.write(180);  
      servo2.write(ang);
      servo3.write(pos);
    }
    //Serial.println(state);
  }
   
void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

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


  // Web Controller begins
  ESPUI.switcher("Switch",&Switch,ControlColor::Turquoise);
}

void loop() {

  //val= analogRead(servoPin1);
  //Serial.println(val);
  //ope();
  //val= analogRead(27);
  //Serial.println(val);
  dnsServer.processNextRequest();

  static long oldTime = 0;
  static bool testSwitchState = false;

  if (millis() - oldTime > 5000) {

    testSwitchState = !testSwitchState;
    ESPUI.updateSwitcher(testSwitchId, testSwitchState);
    
    oldTime = millis();
  }
  if(openflag == 1){
    sunflower();
  }
  //Serial.println(state);
}
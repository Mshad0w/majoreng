#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EasyDDNS.h>
#include <RCSwitch.h>
#include <Ticker.h>
//#include "index.h"
#include "index2.h"
#include "DHT.h"

#define DHTPIN D5     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

#define LED D4  //On board LED
DHT dht(DHTPIN, DHTTYPE);
RCSwitch mySwitch = RCSwitch();
Ticker ticker;
Ticker ticker2;
MDNSResponder mdns;

//////////////////////////////// WIFI SSID ////////////////////////

const char* ssid = "SSID"; // your connection name
const char* password = "PASS"; // your connection password

ESP8266WebServer server(8090);

int gpio1_pin = 2;  // D4 of nodemcu
int gpio2_pin = 13; // D7 of nodemcu
int gpio3_pin =14; //  D5 of nodemcu

float TON;
float TOFF;
float TON2;
float TOFF2;
int Sqn;
int Sqn2;
float ttemp;
float ttemp2;
float ttemp_on;
  float ttemp_off;
  float ttemp_on2;
  float ttemp_off2;
int seqflag=0;
bool stat;
int seqflag2=0;
bool stat2;
String PIRvalue="0";
int   PValue;
int cntr;
int cntr2;
int cntr3;
int sign;
bool haltmode=false;
bool haltmode1=false;
/////////////////////////////////////////// Callback Function for Ticker1///////////////////
//void Cback()
//{
//  mySwitch.send(10036513, 24);
//  delay(100);
//    mySwitch.send(10036514, 24);
//      seqflag++;
//
//    Serial.print("Counting to ");
//  Serial.println(seqflag);
//
// 
//  
//  if (stat)
//  {
//  ttemp=TOFF*60;
//  }
//  else 
//  {
//    ttemp=TON*60;
//  }
//
//  
//    
//stat=!stat;
//Serial.print("Status: ");
//  Serial.println(stat);
//  //ticker.detach();
//  ticker.attach(ttemp, Cback);
//  
//   if (seqflag>2*Sqn-2)
//  {
//    ticker.detach();
//    seqflag=0;
//    
//  }
//}
void Cback()
{
  mySwitch.send(sign, 24);  
      seqflag++;
stat=!stat;
Serial.print("Status: ");
  Serial.println(stat);
  
    Serial.print("Counting to ");
  Serial.println(seqflag);

 
  
  if (stat)
  {
  ttemp=ttemp_off;
  sign=000000; //Off signal code of remote
  //sign=1396995;
  }
  else 
  {
    ttemp=ttemp_on;
    sign=111111; //ON signal code of remote
    //sign=1397004;
  }
  
  //ticker.detach();
  ticker.attach(ttemp, Cback);
  
   if (seqflag>=2*Sqn-1)
  {
    ticker.detach();
    seqflag=0;
    
  }
}

void Cback2()
{
  mySwitch.send(sign, 24);  
      seqflag2++;
stat2=!stat2;
Serial.print("Status: ");
  Serial.println(stat2);
  
    Serial.print("Counting to ");
  Serial.println(seqflag2);

 
  
  if (stat2)
  {
  ttemp=ttemp_off2;
  sign=000000; //Off signal code of remote
  //sign=1396995;
  }
  else 
  {
    ttemp=ttemp_on2;
    sign=111111; //On signal code of remote
    //sign=1397004;
  }
  
  //ticker.detach();
  ticker2.attach(ttemp2, Cback2);
  
   if (seqflag2>=2*Sqn2-1)
  {
    ticker2.detach();
    seqflag2=0;
    
  }
}




//Check if header is present and correct
bool is_authentified(){
  Serial.println("Enter is authentified");
  if (server.hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

//login page, also called for disconnect
void handleLogin(){
  String msg;
  if (server.hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")){
    Serial.println("Disconnection");
    server.sendHeader("Location","/login");
    server.sendHeader("Cache-Control","no-cache");
    server.sendHeader("Set-Cookie","ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){
    if (server.arg("USERNAME") == "Admin" &&  server.arg("PASSWORD") == "admin" ) // enter ur username and password you want
    {
      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.sendHeader("Set-Cookie","ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
      return;

      }

  msg = "Wrong username/password! try again.";
  Serial.println("Log in Failed");
  }
  String content = "<html><body style='background-color:MediumAquaMarine'><form action='/login' method='POST'><p  align ='center' style='font-size:300%;'><u><b><i>  Log In  </i></b></u></p><br>";
  content += " <p   align ='center' style='font-size:160%'><b> UserName:<input type='text' name='USERNAME' placeholder='user name' required></b></p><br>";
  content += "<p  align ='center' style='font-size:160%'><b>Password:<input type='password' name='PASSWORD' placeholder='password' required></b></p><br>";
  content += "<p  align ='center' style='font-size:160%'><input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "</p><br> </body></html>";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot(){
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()){
    server.sendHeader("Location","/login");
    server.sendHeader("Cache-Control","no-cache");
    server.send(301);
    return;
  }
   String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

//no need authentification
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
/////////////////////////////////////////////////////////////////////// Form Handle Begin //////////////////////////////////////////
void handleForm() {
 
 String ACc = server.arg("AC Cooler"); 
 String WCc = server.arg("Water Cooler"); 
 String Fhouse = server.arg("Flower House");
 String lmp = server.arg("Lamp");  
 
 
 
 Serial.println(ACc);
 Serial.println(WCc);
 Serial.println(Fhouse);
 Serial.println(lmp);
 
//if (lmp=="true")
//{
//  if (server.arg("ONtime")=="0" && server.arg("OFFtime")=="0" && server.arg("Seqn")=="0")
//  {
//    ticker2.detach();
//    mySwitch.send(10036513, 24);
//mySwitch.send(10036514, 24);
//    
//  }
//  lmp="false";
//  String ONtime = server.arg("ONtime"); 
// String OFFtime = server.arg("OFFtime"); 
// String Seqn = server.arg("Seqn"); 
// Serial.print("ON Time:");
// Serial.println(ONtime);
// TON=ONtime.toFloat();
// Serial.print("OFF Time:");
// Serial.println(OFFtime);
//TOFF=OFFtime.toFloat();
// Serial.print("Sequence Number:");
// 
// Serial.println(Seqn);
// 
//  ttemp_on=TON*60;
//  ttemp_off=TOFF*60;
//ttemp=ttemp_on;
//Sqn=Seqn.toInt();
////blinker.active();
//
//mySwitch.send(10036513, 24);
//delay(100);
//mySwitch.send(10036514, 24);
//stat=true;
// ticker.attach(ttemp,Cback);
//}
if (lmp=="true")
{
  if (server.arg("ONtime")=="0" && server.arg("OFFtime")=="0" && server.arg("Seqn")=="0") //HALT any operation
  {
    ticker.detach();
    mySwitch.send(000000, 24); //Off signal code of remote
    mySwitch.send(000000, 24); //Off signal code of remote
    mySwitch.send(000000, 24); //Off signal code of remote
    haltmode1=true;
  }
  else
  {haltmode1=false;
  }
    Serial.println("halt mode:");

  Serial.println(haltmode1);
  lmp="false";
  String ONtime = server.arg("ONtime"); 
 String OFFtime = server.arg("OFFtime"); 
 String Seqn = server.arg("Seqn"); 
 Serial.print("ON Time:");
 Serial.println(ONtime);
 TON=ONtime.toFloat();
 Serial.print("OFF Time:");
 Serial.println(OFFtime);
TOFF=OFFtime.toFloat();
 Serial.print("Sequence Number:");
 
 Serial.println(Seqn);
ttemp_on=TON*60;
  ttemp_off=TOFF*60;
ttemp=ttemp_on;
Sqn=Seqn.toInt();
if(!haltmode1)
{
  
//blinker.active();
sign=5723916;//ON
mySwitch.send(sign, 24);
stat=true;
 ticker.attach(ttemp, Cback);
 
  
 sign=5724096;//off signal
}

}
if (Fhouse=="true")
{
  if (server.arg("ONtime")=="0" && server.arg("OFFtime")=="0" && server.arg("Seqn")=="0") //HALT any operation
  {
    ticker2.detach();
    mySwitch.send(000000, 24); //Off signal code of remote
    mySwitch.send(000000, 24); //Off signal code of remote
    mySwitch.send(000000, 24); //Off signal code of remote
    haltmode=true;
  }
  else
  {haltmode=false;
  }
    Serial.println("halt mode:");

  Serial.println(haltmode);
  Fhouse="false";
  String ONtime2 = server.arg("ONtime"); 
 String OFFtime2 = server.arg("OFFtime"); 
 String Seqn2 = server.arg("Seqn"); 
 Serial.print("ON Time:");
 Serial.println(ONtime2);
 TON2=ONtime2.toFloat();
 Serial.print("OFF Time:");
 Serial.println(OFFtime2);
TOFF2=OFFtime2.toFloat();
 Serial.print("Sequence Number:");
 
 Serial.println(Seqn2);
ttemp_on2=TON2*60;
  ttemp_off2=TOFF2*60;
ttemp2=ttemp_on2;
Sqn2=Seqn2.toInt();
if(!haltmode)
{
  
//blinker.active();
sign=111111 ;//ON signal
mySwitch.send(sign, 24);
stat2=true;
 ticker2.attach(ttemp2, Cback2);
 
  
 sign=000000; //OFF signal
}
}
//seqflag=0;
//blinker.detach();
// for (int i=0;i<Sqn;i++)
//  {
//    digitalWrite(gpio1_pin, LOW);
//    mySwitch.send(10036513, 24);
//    delay(TON*1000UL*60);
//      
//
//    digitalWrite(gpio1_pin, HIGH);
//    mySwitch.send(10036513, 24);
//    delay(TOFF*1000UL*60);
//  }
 String s = "<a href='/'> Go Back </a>";
 server.send(200, "text/html", s); //Send web page
}
/////////////////////////////////////////////////////////////////////// ADC Handle Begin //////////////////////////////////////////
void handleADC() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
String adcValue = String(hic)+ " °C  Humidity:" +String(h)+ "%";
// int a = analogRead(A0);
// String adcValue = String(a,DEC);
// 
// server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
server.send(200, "text/plane", adcValue);
}

void handlePIR() {

 if (mySwitch.available()) {
  PValue = mySwitch.getReceivedValue();
Serial.println(PValue);
   if ( PValue==123456){  //PIR 1 Code
    cntr++;
    delay(500);
   }
   if ( PValue==54321){ //PIR 2 Code
    cntr2++;
    delay(500);
   }
   if ( PValue==98765){ // Door Sensor
    cntr3++;
    delay(500);
   }
   
      PIRvalue=" PIR UP: "+String(cntr)+" PIR Down: "+String(cntr2)+" Ent Door: "+String(cntr3);
Serial.println(cntr);
   mySwitch.resetAvailable();
 }
 
 
 server.send(200, "text/plane", PIRvalue); //Send ADC value only to client ajax request
}
 
void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
  mySwitch.send(111111, 24);  /// ON signal For any device like Home Alarm system
  
  
 }
 else
 {
  digitalWrite(LED,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter
  mySwitch.send(000000, 24);  /// OFF signal For any device like Home Alarm system
  cntr=0;
  cntr2=0;
  cntr3=0;
  PIRvalue="0";
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}

///////////////////////////////// S--E--T--U--P /////////////////////////////  

void setup(void){

mySwitch.enableTransmit(D1);  //pin D1
mySwitch.enableReceive(D2); ///pin D2
   // preparing GPIOs
  pinMode(gpio1_pin, OUTPUT);
  digitalWrite(gpio1_pin, HIGH);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  pinMode(gpio3_pin, OUTPUT);
  digitalWrite(gpio3_pin, LOW);
  dht.begin();
  IPAddress ip(192,168,3,10);   
IPAddress gateway(192,168,3,1);   
IPAddress subnet(255,255,255,0); 
IPAddress primaryDNS(8, 8, 8, 8);  
WiFi.config(ip, gateway, subnet,primaryDNS);
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

//  if (mdns.begin("esp8266", WiFi.localIP())) {
//    Serial.println("MDNS responder started");
//    }


  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works without need of authentification");
  });
  
  server.on("/action_page", handleForm); //form action is handled here
server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  server.on("/readPIR", handlePIR);
 
  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );


//  server.on("/",[](){
//   //
//  });
//  server.on("/switch1On", [](){
//   // 
//    digitalWrite(gpio1_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/switch1Off", [](){
// //  
//    digitalWrite(gpio1_pin, LOW);
//    delay(1000); 
//  });
//  server.on("/switch2On", [](){
//  //
//    digitalWrite(gpio2_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/switch2Off", [](){
//    //
//    digitalWrite(gpio2_pin, LOW);
//    delay(1000); 
//  });
//  server.on("/switch3On", [](){
//    digitalWrite(gpio3_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/switch3Off", [](){
//    digitalWrite(gpio3_pin, LOW);
//    delay(1000); 
//  });
   server.begin();
  Serial.println("HTTP server started");
  EasyDDNS.service("duckdns");    // Enter your DDNS Service Name - "duckdns" / "noip"
EasyDDNS.client("blahblah.duckdns.org","Tocken Code");    // Enter ddns Domain & Token | Example - "esp.duckdns.org","1234567"
EasyDDNS.update(1000);
Serial.println("DNS Initiated...");
}

void loop(void){
  EasyDDNS.update(10*60*60000);
  server.handleClient();
//  for (int i=0;i<Sqn;i++)
//  {
//    digitalWrite(gpio2_pin, HIGH);
//    delay(TON*1000UL*60);
//    digitalWrite(gpio2_pin, LOW);
//    delay(TOFF*1000UL*60);
//  }

}

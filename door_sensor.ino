#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//For WiFi Setup
const char* ssid = "[INSERT WIFI NETWORK]";
const char* password = "[INSERT WIFI PASSWORD]";
const String url = "[INSERT LOCAL FLASK SERVER IP]";


//For UltraSonic Sensor Setup
const int trigPin = 5;
const int echoPin = 4;
long duration;
int distance;


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
     delay(1000);
     Serial.print("Connecting");
  }
  
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);

  //  Distances may vary based on setup. < 10 typically does the job if placed above door on doorframe
  if(distance < 10){
    doorRequest();
    delay(30000);
  }
  
 delay(100);
}

void doorRequest(){

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    WiFiClient client;

    http.begin(client, url);
    int httpCode = http.GET();
    http.end();
    
  }
}

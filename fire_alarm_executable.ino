#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "<BLYNK TEMPLATE ID goes here>"
#define BLYNK_DEVICE_NAME "<BLYNK DEVICE NAME goes here>"
#define BLYNK_AUTH_TOKEN "<BLYNK AUTH TOKEN goes here>"

#define BLYNK_PRINT Serial

const int fireSensor = D5;
const int led = D4;
const int Buzzer = D6;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "<WIFI SSID goes here>"; // wifi name
char pass[] = "<WIFI PASSWORD goes here>"; // wifi password

BlynkTimer timer;

int fireState = 0;
int lastfireState = 0;

void Reading()
{
  fireState = digitalRead(fireSensor);
  
  if (!fireState && !lastfireState)
  {
    Serial.println("Blynk notification: Fire!");
    Blynk.logEvent("fire", "Fire Alert");
    lastfireState = 1;
    tone(Buzzer, 1000);
    delay(1000);
  }
  
  if (!fireState && lastfireState)
  {
    Serial.println("Fire Alert, Continuous");
    tone(Buzzer, 2000);
    delay(5000);
  }
  
  if (fireState)
  {
    Serial.println("No Fire");
    lastfireState = 0;
    noTone(Buzzer);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(led, OUTPUT);
  Serial.println("Please wait.... Sensor activation");
  delay(1000);
  Serial.println("Please wait for Blynk Server connection");
  pinMode(fireSensor, INPUT);
  pinMode(Buzzer, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(led, HIGH);
    delay(250);
  }
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, Reading);
}

void loop()
{
  Blynk.run();
  timer.run();
}

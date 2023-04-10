#define BLYNK_TEMPLATE_ID "TMPL38yR_clE"
#define BLYNK_DEVICE_NAME "Fire Alarm 3"
#define BLYNK_AUTH_TOKEN "6qVODjUwNl7cnyd-aiz1GAz1B0t8XbMh"

#define BLYNK_PRINT Serial

  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
  #define fireSensor D5
  #define led D4
  #define Buzzer D6

char auth[] = BLYNK_AUTH_TOKEN;
/*
// Home config
char ssid[] = "MON";  // wifi name
char pass[] = "abcd1234";  // wifi password 
*/
// Mirror config
char ssid[] = "Redmi Note 8 Pro";  // wifi name
char pass[] = "12345678";  // wifi password                      

 BlynkTimer timer;

int fireState = 0;
int lastfireState = 0;
unsigned long old =0;
unsigned long current =0;
int interval=0;

void Reading()
{
 
  fireState = digitalRead(fireSensor);
  if (fireState == 0 && lastfireState == 0) {
  Serial.println("Blynk notification: Fire!");
  Blynk.logEvent("fire","Fire Alert");
  lastfireState = 1;
  tone(Buzzer,1000);
  delay(1000);
  } 
  if (fireState == 0 && lastfireState == 1) {
  
  	Serial.println("Fire Alert, Continous");
  	tone(Buzzer,2000);
  	delay(5000);

  	}
  if (fireState == 1) {
   Serial.println("No Fire");
    lastfireState = 0;
  noTone(Buzzer);
    
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(led,OUTPUT);
  Serial.println("Please wait.... Sensor activation");
  delay(1000);
  Serial.println("Please wait for Blynk Server connection");
  pinMode(fireSensor, INPUT);
  pinMode(Buzzer,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led,LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(led,HIGH);
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

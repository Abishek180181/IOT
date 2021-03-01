#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
char auth[] = "Ng8pYkwxhjF-AXIkz6xn8E64mxpnu8Az"; // Authentication code sent by Blynk
char ssid[] = "Samsungs10"; // WIFI Name
char pass[] = "nepal123"; // WIFI Password
int thrase_hold=120;

 


BlynkTimer timer; //Blynk timer call
 
int mq2 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 
int Buzzer=D0;
int led=D3;

 

void getSendData()
{
data = analogRead(mq2); 
Serial.println(data);
  Blynk.virtualWrite(V2, data);
 
  if (data > thrase_hold )
  {
    Serial.println("Alert:Gas Leakage Detected!");
    Blynk.notify("Alert:Gas Leakage Detected!"); 
    digitalWrite(Buzzer,HIGH);
    for(int i=0; i<10; i++)
    {
      digitalWrite(led,HIGH);
      delay(500);
      digitalWrite(led,LOW);
      delay(500);
    }
  }else{
    Serial.println("not detected");
    digitalWrite(Buzzer,LOW);
    digitalWrite(led,LOW);
    
  }
 
}

 

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(Buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(mq2,INPUT_PULLUP);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run(); // Initiates BlynkTimer
  Blynk.run();
}

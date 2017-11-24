#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "takimyildizi-652f0.firebaseio.com"
#define FIREBASE_AUTH "1ygiXXsbtqilUYDGKh34EqKxnEMQBZCZ0UfoMuPt"
#define WIFI_SSID "***"
#define WIFI_PASSWORD "***"
#define LED LED_BUILTIN

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("baglaniyor");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("baglandi, ip: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.setInt("LEDStatus",0);
}

void loop() {
  Serial.println(Firebase.getInt("LEDStatus"));
  if(Firebase.getInt("LEDStatus"))
  {  
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  if (Firebase.failed())
 {
      Serial.print("HATA:");
      Serial.println(Firebase.error());  
      return;
  }  
  delay(100);
}


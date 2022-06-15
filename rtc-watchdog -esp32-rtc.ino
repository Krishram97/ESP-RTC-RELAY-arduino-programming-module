#include<Wire.h>
#include"RTClib.h"
#include<esp_task_wdt.h>
int WDT_TIMEOUT = 3;
int RELAY_PIN = 12;
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday","Monday","Tuesday","Wednesday","Thursday", "Friday", "Saturday"};
void setup() {
  Serial.begin(57600);
  Serial.println("Configuring WDT...");
  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);
  pinMode(RELAY_PIN, OUTPUT);
 #ifndef ESP32
    while(!Serial);
 #endif

    if (!rtc.begin()){
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
    }
    if(rtc.lostPower()){
    Serial.println("RTC low power, SET TIME!!");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    }
}
int i = 0;
int last = millis();


void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();

  digitalWrite(RELAY_PIN, HIGH);
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    DateTime future (now + TimeSpan(7,12,30,6));
    Serial.println();
    delay(1000);
     if(millis()-last >= 30000 && i< 1){
       Serial.println("Watchdog Timer Resetting ....:)");
       esp_task_wdt_reset();
       last = millis();
       i++;
       if(i==1){
        Serial.println("Reboot is yours!! // 3s");
       }
       
   } 
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Could not Display Time");
    delay(1000);

   
}

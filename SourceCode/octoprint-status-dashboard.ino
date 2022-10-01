#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

unsigned int ledState =  0;

byte PBedCool = 7;
byte PBedHeat = 6;
byte PBedOnTemp = 5;
byte PToolCool = 4;
byte PToolHeat = 3;
byte PToolOnTemp = 2;
byte PReady = 1;
byte PPrinting = 0;
byte PPer10 = 15;
byte PPer20 = 14;
byte PPer30 = 13;
byte PPer40 = 12;
byte PPer50 = 11;
byte PPer60 = 10;
byte PPer70 = 9;
byte PPer80 = 8;
byte PPer90 = 23;
byte PPer100 = 22;
byte PTime5m = 21;
byte PTime15m = 20;
byte PTime30m = 19;
byte PTime1h = 18;
byte PTime2h = 17;

int latchPin = D1;
int clockPin = D2;
int dataPin = D3;

int pwmPin = D8;

//settings that NEEEDS to be change
char ssid[] = "alderan";
char password[] = "J5j5xcewzzka";
char apiKey[] = "204CEDC92D3B4F88A0CA845F2F724BB6";
char printerAddressApi[] = "http://192.168.0.59/api/printer";
char jobAddressApi[] = "http://192.168.0.59/api/job";

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 50);

  Serial.begin(115200);

  ledState = ~ledState;
  sendOut();
  delay(3000);
  ledState = 0;
  sendOut();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    
    if (http.begin(client, printerAddressApi)) {  // HTTP
      http.addHeader("X-Api-Key", apiKey);
      int httpCode = http.GET();
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        DynamicJsonDocument doc(1024);
        auto error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return;
        } else {
          double actualBedTemp = doc["temperature"]["bed"]["actual"];
          double targetBedTemp = doc["temperature"]["bed"]["target"];
          double actualExtTemp = doc["temperature"]["tool0"]["actual"];
          double targetExtTemp = doc["temperature"]["tool0"]["target"];
          boolean rready = doc["state"]["flags"]["ready"];
          boolean printing = doc["state"]["flags"]["printing"];
          
          Serial.println(actualBedTemp);
          Serial.println(targetBedTemp);
          Serial.println(actualExtTemp);
          Serial.println(targetExtTemp);
          bitWrite(ledState, PBedCool, actualBedTemp < 25.0);
          bitWrite(ledState, PBedHeat, targetBedTemp > 0.0);
          bitWrite(ledState, PBedOnTemp, abs(targetBedTemp - actualBedTemp) < 5.0);
          bitWrite(ledState, PToolCool, actualExtTemp < 25.0);
          bitWrite(ledState, PToolHeat, targetExtTemp > 0.0);
          bitWrite(ledState, PToolOnTemp, abs(targetExtTemp - actualExtTemp) < 5.0);
          bitWrite(ledState, PReady, rready);
          bitWrite(ledState, PPrinting, printing);
        }
      } else if (httpCode == 403) {
        Serial.println("Wrong access code");
        ledState = 0;
      } else {
        Serial.print("Unexpected http code:");
        Serial.println(httpCode);
        Serial.printf("error: %s\n", http.errorToString(httpCode).c_str());
        ledState = 0;
      }
      http.end();
    }
    delay(100);
    if (http.begin(client, jobAddressApi)) {  // HTTP
      http.addHeader("X-Api-Key", apiKey);
      int httpCode = http.GET();
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        DynamicJsonDocument doc(1024);
        auto error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return;
        } else {
          Serial.println(payload);
          double progress = doc["progress"]["completion"];
          double ttime = doc["progress"]["printTimeLeft"];
          bitWrite(ledState, PPer10, progress >= 10);
          bitWrite(ledState, PPer20, progress >= 20);
          bitWrite(ledState, PPer30, progress >= 30);
          bitWrite(ledState, PPer40, progress >= 40);
          bitWrite(ledState, PPer50, progress >= 50);
          bitWrite(ledState, PPer60, progress >= 60);
          bitWrite(ledState, PPer70, progress >= 70);
          bitWrite(ledState, PPer80, progress >= 80);
          bitWrite(ledState, PPer90, progress >= 90);
          bitWrite(ledState, PPer100, progress >= 100);
          bitWrite(ledState, PTime5m, ttime/6
          Serial.println(ttime);
          Serial.println(ttime);
        }
      } else if (httpCode == 403) {
        Serial.println("Wrong access code");
        ledState = 0;
      } else {
        Serial.print("Unexpected http code:");
        Serial.println(httpCode);
        Serial.printf("error: %s\n", http.errorToString(httpCode).c_str());
        ledState = 0;
      }
      http.end();
    }
/*    if(Serial.read() > 0) {
      Serial.println("AAAAA");
      if ((WiFiMulti.run() == WL_CONNECTED)) {
        WiFiClient client;
        HTTPClient http;
        if (http.begin(client, "http://192.168.0.206/api/printer/bed")) {  // HTTP
          http.addHeader("Content-Type","application/json");
          http.addHeader("X-Api-Key", "FED534BA73F64A64B41B00AC29F6F045");
          int httpCode = http.POST("{\"command\":\"target\", \"target\":60}");
          if(httpCode == HTTP_CODE_OK) {
            Serial.println("CODE_OK");
          } else {
            Serial.print("ERROR");
            Serial.println(httpCode);
          }
        }
      }

    }
    Serial.println("CCC");
*/
    }

Serial.println(ledState, BIN);
  sendOut();
  delay(10000);
}

void sendOut() {
  Serial.println((byte) ledState, BIN);
  Serial.println((byte) (ledState / 256), BIN);
  Serial.println((byte) (ledState / (256 * 256)), BIN);
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, ~ (byte) (ledState / (256 * 256)));
  shiftOut(dataPin, clockPin, MSBFIRST, ~ (byte) (ledState / 256));
  shiftOut(dataPin, clockPin, MSBFIRST, ~ (byte) ledState);
  digitalWrite(latchPin, 1);
}

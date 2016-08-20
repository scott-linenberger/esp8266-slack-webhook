/*
  SlackWebhook.cpp - Library for connecting Adafruit Huzzah to Slack Webhooks
  Created by Scott Linenberger, August 19, 2016
*/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "SlackWebhook.h"

SlackWebhook::SlackWebhook(const char* _host, String _url, const char* _fingerprint){
  host = _host;
  url = _url;
  fingerprint = _fingerprint;
}

boolean SlackWebhook::postMessageToSlack(String postData){
    Serial.println("Creating client connection to host..");
    WiFiClientSecure client;

    if(!client.connect(host, 443)){
      Serial.println("SlackWebhook: could not connect to host");
      Serial.print("Host: ");
      Serial.print(host);

      return false;
    }
    Serial.println("Client connection successful!");
    Serial.print("Connected to ");
    Serial.print(host);
    Serial.println();
    
    Serial.println("Verifying SSL fingerprint..");
    //Ignore the error here
    client.verify(fingerprint, host);

    //fingerprint verification complete
    //build POST request..        
    int dataLength = postData.length();
      
    //build the POST string..
    String POST =    "POST " + url +" HTTP/1.1\r\n"
                     "Host: " + host + "\r\n"
                     "User-Agent: ArduinoIoT/1.0\r\n"
                     "Connection: close\r\n"
                     "Content-Type: application/x-www-form-urlencoded\r\n"
                     "Content-Length: " + dataLength + "\r\n\r\n"
                     "" + postData;

    Serial.println("Writing POST request to client..");
    client.print(POST);
    delay(500);

    Serial.println();
    while(client.available()) {
      Serial.println(client.readStringUntil('\r'));
    }

    delay(500);
    Serial.print("POST request complete!");
    return true;
}

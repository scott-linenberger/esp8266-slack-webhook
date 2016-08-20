/*
  SlackWebhook.h - Library for connecting Adafruit Huzzah to Slack Webhooks
  Created by Scott Linenberger, August 19, 2016
*/
#ifndef SLACKWEBHOOK_H
#define SLACKEWBHOOK_H

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

class SlackWebhook{
  const char* host;
  String url;
  const char* fingerprint;
  
  public:
    SlackWebhook(const char*, String, const char*);
    boolean postMessageToSlack(String);
  
};
  
#endif


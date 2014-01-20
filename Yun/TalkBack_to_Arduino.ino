/*

 TalkBack --> Arduino Yun via Wi-Fi
 
 The TalkBack App sketch is designed for the Arduino Yun connected to a
 Wi-Fi network and the Arduino 1.5.4 IDE or newer. This sketch allows the
 Arduino to request commands stored by a ThingSpeak TalkBack via the
 TalkBack API (https://thingspeak.com/docs/talkback).
  
 Getting Started with ThingSpeak:
 
   * Sign Up for New User Account - https://www.thingspeak.com/users/new
   * Create a new Channel by selecting Channels and then Create New Channel
   * Create a TalkBack by selecting Apps, TalkBack, and New TalkBack
   * Enter the TalkBack API Key in this sketch under "ThingSpeak Settings"
   * Enter the TalkBack ID in this sketch under "ThingSpeak Settings"
 
 Arduino Requirements:
 
   * Arduino Yun
   * Arduino 1.5.4 IDE or newer
   
  Network Requirements:

   * Router with Wi-Fi
   * DHCP enabled on Router
 
 Created: Jan 30, 2014 by Hans Scharler (http://www.iamshadowlord.com)
 
 Additional Credits:
 Example sketches from Arduino team, ThingSpeak and Yun Example by Tenet Technetronics
 
*/

#include "Bridge.h"
#include "HttpClient.h"

//ThingSpeak Settings 
String thingSpeakAPI = "api.thingspeak.com";
String talkBackAPIKey = "XXXXXXXXXXXXXX";
String talkBackID = "YYYY";
const int checkTalkBackInterval = 60 * 1000;      // Time interval in milliseconds to check TalkBack (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;

void setup()
{
  // Setup On-board LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);
}

void loop()
{
  // Check ThingSpeak for TalkBack Commands
  if(millis() - lastConnectionTime > checkTalkBackInterval)
  {
    checkTalkBack();
  }
}

void checkTalkBack()
{
  HttpClient client;
   
  String talkbackURL =  "https://" + thingSpeakAPI + "talkbacks/" + talkBackID + "/commands/execute?api_key=" + talkBackAPIKey;
  
  // Make a HTTP GET request to the TalkBack API:
  client.get(talkbackURL);
  
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.flush();
 
  lastConnectionTime = millis();
}
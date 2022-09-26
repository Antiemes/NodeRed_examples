#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#include "secret.h"

//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const char* ssid = SSID;
const char* password = PSK;

const char* mqtt_server = MQTT_BROKER;

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPin 12
#define ledRingPIN 14

const int lamp = 4;

DHT dht(DHTPin, DHTTYPE);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, ledRingPIN, NEO_GRB + NEO_KHZ800);

long now = millis();
long lastMeasure = 0;

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
	{
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(String topic, byte* message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.write(message, length);
  Serial.println();

  //for (unsigned i = 0; i < length; i++)
	//{
  //  Serial.print((char)message[i]);
  //  messageTemp += (char)message[i];
  //}

  //if(topic=="room/lamp")
	//{
  //  String messageTemp;
  //   Serial.print("Changing Room lamp to ");
  //   if(messageTemp == "on")
	//	 {
  //     digitalWrite(lamp, HIGH);
  //     Serial.print("On");
  //   }
  //   else if(messageTemp == "off")
	//	 {
  //     digitalWrite(lamp, LOW);
  //     Serial.print("Off");
  //   }
  //}
  if(topic=="leds")
	{
    uint8_t red, green, blue, lednr;
    Serial.println("Changing LEDs ");
    
    StaticJsonDocument<256> doc;
    deserializeJson(doc, message, length);
    
    red =   doc["red"];
    green = doc["green"];
    blue =  doc["blue"];
    lednr = doc["lednr"];

    strip.setPixelColor(lednr, strip.Color(red, green, blue));
	  strip.show();
  }
}

void reconnect()
{
  while (!client.connected())
	{
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD))
		{
      Serial.println("connected");  
      client.subscribe("room/lamp");
      client.subscribe("leds");
    }
		else
		{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(lamp, OUTPUT);
  
  strip.begin();
  strip.setBrightness(10);
  strip.clear();
  strip.show();
  
  dht.begin();
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
	{
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  if (now - lastMeasure > 30000)
	{
    lastMeasure = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
		{
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    static char temperatureTemp[7];
    dtostrf(t, 6, 2, temperatureTemp);
    
    static char humidityTemp[7];
    dtostrf(h, 6, 2, humidityTemp);

    client.publish("room/temperature", temperatureTemp);
    client.publish("room/humidity", humidityTemp);
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.println(" *C ");
//	  for (uint8_t i=0; i<5; i++)
//	  {
//      uint8_t red;
//      uint8_t green;
//      uint8_t blue;
//
//      red=rand() % 256;
//      green=rand() % 256;
//      blue=rand() % 256;
//
//	  	//strip.setPixelColor(i, strip.Color(red, green, blue));
//	  }
//	  strip.show();
  }
} 

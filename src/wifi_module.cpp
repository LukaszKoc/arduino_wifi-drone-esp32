 
#include "Arduino.h" 
#include <wifi_module.h> 
#include <WiFi.h>

Wifi_module wifi;

void Wifi_module::begin(void (*controlCallback)(int list[Tank::DATA_CHANNELS_COUNT]))
{
  static WebServer server(WEBSERVER_PORT);
  this->server = &server;
  wifiNodeConfig();
  this->beginWebServer(this->server);
  this->server->begin();
  this->controlCallback = controlCallback;
}

void Wifi_module::wifiNodeConfig() {
  Serial.println(String("Waiting for WiFi to connect... ") + WIFI_SSID);
  WiFi.setHostname(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(String(" connected to ") + WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void Wifi_module::aPConfig() {
  WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  WiFi.setHostname(WIFI_AP_SSID);
  WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void Wifi_module::loop()
{
  this->server->handleClient();
}

void Wifi_module::beginWebServer(WebServer * server)
{
  server->on("/", onRoot);
  server->on(CONTROL_PATH, onControl);
}

void Wifi_module::onRoot()
{
  wifi.server->send(200, "text/html", INDEX_HTML);
}

void Wifi_module::onControl()
{
  static int list[Tank::DATA_CHANNELS_COUNT];
  for(int i = 0; i < Tank::DATA_CHANNELS_COUNT; i++)
  {
    String argName = String(i);
    int value = Tank::DEFAULT_CONTROL_VALUE;
    if(wifi.server->hasArg(argName)) {
      int incommingValue = wifi.server->arg(argName).toInt();
      // if(incommingValue >= Tank::MIN_CONTROL_VALUE && incommingValue <= Tank::MIN_CONTROL_VALUE) {
        value = incommingValue;
      // }
    }
    list[i] = value;
  }
  wifi.controlCallback(list);
  wifi.server->send(200, "text/plain", "");
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "secrets.h"

ESP8266WebServer server(80);
/*const char* ssid = "miRed";
const char* password = "miClave";
--todo esto esta ensecrets.h
*/

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Control de LED</h1>";
  html += "<a href=\"/on\">Encender LED</a><br>";
  html += "<a href=\"/off\">Apagar LED</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/plain", "LED encendido");
}

void handleOff() {
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "LED apagado");
}



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conexión WiFi establecida");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

// Ustawienia sieci Wi-Fi
const char* ssid = "StealthNet";
const char* password = "Gt%>SB#sW:EuS@qu_5A$w";

// Ustawienia serwera WWW
ESP8266WebServer server(80);

// Ustawienia wyświetlacza
LiquidCrystal_I2C lcd(0x27, 16, 2);

String text = ""; // Zmienna przechowująca wpisany tekst

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Arduino WiFi - Wyświetlacz</h1>";
  html += "<form method='get' action='/submit'>";
  html += "<input type='text' name='text'>";
  html += "<input type='submit' value='OK'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  if (server.hasArg("text")) {
    text = server.arg("text");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  lcd.begin(16, 2);
  lcd.print("Arduino WiFi");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected to WiFi");
  lcd.setCursor(0, 1);
  lcd.print("IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
}

void loop() {
  server.handleClient();
}

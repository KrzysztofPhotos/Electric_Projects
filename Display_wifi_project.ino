#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>

// Ustawienia sieci Wi-Fi
const char* ssid = "StealthNet";
const char* password = "Gt%>SB#sW:EuS@qu_5A$w";

// Ustawienia serwera WWW
ESP8266WebServer server(80);

// Ustawienia wyświetlacza
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Adres w pamięci EEPROM, w którym przechowywany będzie tekst
int address = 512;

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

    // Zapisz tekst w pamięci EEPROM
    int length = text.length() + 1; // Długość tekstu, włącznie z końcowym znakiem null
    for (int i = 0; i < length; ++i) {
      EEPROM.write(address + i, text[i]);
    }
    EEPROM.commit(); // Potwierdź zapis do pamięci EEPROM
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  lcd.init(); // initialize the lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("Ywrobot Arduino!");

  delay(5000);

  lcd.begin(20, 4);
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

  // Odczytaj tekst z pamięci EEPROM
  char character;
  int i = 0;
  while ((character = EEPROM.read(address + i)) != '\0') {
    text += character;
    i++;
  }

  lcd.setCursor(0, 2);
  lcd.print("Last text: ");
  lcd.setCursor(0, 3);
  lcd.print(text);

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
}

void loop() {
  server.handleClient();
}

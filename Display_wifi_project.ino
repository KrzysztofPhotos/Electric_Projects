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

// Adresy w pamięci EEPROM, w których przechowywane będą teksty
int address_line1 = 0;
int address_line2 = 32; // Przesunięcie o 32 bajty dla drugiej linii

String text_line1 = ""; // Zmienna przechowująca wpisany tekst dla pierwszej linii
String text_line2 = ""; // Zmienna przechowująca wpisany tekst dla drugiej linii

void handleRoot() {
  lcd.clear();
  String html = "<html><body>";
  html += "<h1>Arduino WiFi - Wyświetlacz</h1>";
  html += "<form method='get' action='/submit'>";
  html += "<input type='text' name='text_line1' placeholder='Line 1'>";
  html += "<br>";
  html += "<input type='text' name='text_line2' placeholder='Line 2'>";
  html += "<br>";
  html += "<input type='submit' value='OK'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  lcd.clear();
  if (server.hasArg("text_line1")) {
    text_line1 = server.arg("text_line1");
    lcd.setCursor(0, 0);
    lcd.print(text_line1);

    // Zapisz tekst dla pierwszej linii w pamięci EEPROM
    int length_line1 = text_line1.length();
    for (int i = 0; i < length_line1; ++i) {
      EEPROM.write(address_line1 + i, text_line1[i]);
    }
    EEPROM.write(address_line1 + length_line1, '\0'); // Zapisz znak null na końcu
    EEPROM.commit(); // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line2")) {
    text_line2 = server.arg("text_line2");
    lcd.setCursor(0, 1);
    lcd.print(text_line2);

    // Zapisz tekst dla drugiej linii w pamięci EEPROM
    int length_line2 = text_line2.length();
    for (int i = 0; i < length_line2; ++i) {
      EEPROM.write(address_line2 + i, text_line2[i]);
    }
    EEPROM.write(address_line2 + length_line2, '\0'); // Zapisz znak null na końcu
    EEPROM.commit(); // Potwierdź zapis do pamięci EEPROM
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  lcd.init(); // Inicjalizacja wyświetlacza
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("Welcome!");

  delay(1000);

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
  delay(3000); // Wyświetlaj adres IP przez 3 sekundy

  lcd.clear(); // Wyczyść ekran

  // Odczytaj tekst dla pierwszej linii z pamięci EEPROM
  char character_line1;
  int i = 0;
  while ((character_line1 = EEPROM.read(address_line1 + i)) != '\0') {
    text_line1 += character_line1;
    i++;
  }

  // Odczytaj tekst dla drugiej linii z pamięci EEPROM
  char character_line2;
  i = 0;
  while ((character_line2 = EEPROM.read(address_line2 + i)) != '\0') {
    text_line2 += character_line2;
    i++;
  }

  lcd.setCursor(0, 2);
  lcd.print("Line 1: " + text_line1);
  lcd.setCursor(0, 3);
  lcd.print("Line 2: " + text_line2);

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
}

void loop() {
  server.handleClient();
}

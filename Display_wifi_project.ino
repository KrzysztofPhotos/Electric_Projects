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

// Ustawienia wyświetlaczy
LiquidCrystal_I2C lcd1(0x27, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 20, 4);

// Adresy w pamięci EEPROM, w których przechowywane będą teksty
int address_line1 = 0;
int address_line2 = 32;  // Przesunięcie o 32 bajty dla drugiej linii
int address_line3 = 64;  // Przesunięcie o 64 bajty dla trzeciej linii
int address_line4 = 96;  // Przesunięcie o 96 bajtów dla czwartej linii

String text_line1 = "";  // Zmienna przechowująca wpisany tekst dla pierwszej linii
String text_line2 = "";  // Zmienna przechowująca wpisany tekst dla drugiej linii
String text_line3 = "";  // Zmienna przechowująca wpisany tekst dla trzeciej linii
String text_line4 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii

unsigned long previousMillis = 0;
const unsigned long interval = 5000;  // Interwał 5 sekund

void handleRoot() {
  lcd1.clear();
  String html = "<html><body>";
  html += "<h1>Arduino WiFi - Wyświetlacz</h1>";
  html += "<form method='get' action='/submit'>";
  html += "<input type='text' name='text_line1' placeholder='Line 1' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line2' placeholder='Line 2' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line3' placeholder='Line 3' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line4' placeholder='Line 4' maxlength='16'>";
  html += "<br>";
  html += "<input type='submit' value='OK'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  lcd1.clear();
  if (server.hasArg("text_line1")) {
    text_line1 = server.arg("text_line1");
    lcd1.setCursor(0, 0);
    lcd1.print(text_line1);

    // Zapisz tekst dla pierwszej linii w pamięci EEPROM
    int length_line1 = text_line1.length();
    for (int i = 0; i < length_line1; ++i) {
      EEPROM.write(address_line1 + i, text_line1[i]);
    }
    EEPROM.write(address_line1 + length_line1, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line2")) {
    text_line2 = server.arg("text_line2");
    lcd1.setCursor(0, 1);
    lcd1.print(text_line2);

    // Zapisz tekst dla drugiej linii w pamięci EEPROM
    int length_line2 = text_line2.length();
    for (int i = 0; i < length_line2; ++i) {
      EEPROM.write(address_line2 + i, text_line2[i]);
    }
    EEPROM.write(address_line2 + length_line2, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line3")) {
    text_line3 = server.arg("text_line3");
    lcd2.setCursor(0, 0);
    lcd2.print(text_line3);

    // Zapisz tekst dla trzeciej linii w pamięci EEPROM
    int length_line3 = text_line3.length();
    for (int i = 0; i < length_line3; ++i) {
      EEPROM.write(address_line3 + i, text_line3[i]);
    }
    EEPROM.write(address_line3 + length_line3, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line4")) {
    text_line4 = server.arg("text_line4");
    lcd2.setCursor(0, 1);
    lcd2.print(text_line4);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line4 = text_line4.length();
    for (int i = 0; i < length_line4; ++i) {
      EEPROM.write(address_line4 + i, text_line4[i]);
    }
    EEPROM.write(address_line4 + length_line4, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  lcd1.init();  // Inicjalizacja pierwszego wyświetlacza
  lcd1.backlight();
  lcd1.setCursor(0, 0);
  lcd1.print("Welcome!");
  lcd1.setCursor(0, 1);
  lcd1.print(":D");

  lcd2.init();  // Inicjalizacja drugiego wyświetlacza
  lcd2.backlight();
  lcd2.setCursor(0, 0);
  lcd2.print("Welcome!");
  lcd2.setCursor(0, 1);
  lcd2.print(":D");

  delay(500);

  lcd1.begin(20, 4);
  lcd1.print("Arduino WiFi");
  lcd1.setCursor(0, 1);
  lcd1.print("Waiting for WiFi");

  lcd2.begin(20, 4);
  lcd2.print("Arduino WiFi");
  lcd2.setCursor(0, 1);
  lcd2.print("Waiting for WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Connected to WiFi");
  lcd1.setCursor(0, 1);
  lcd1.print("IP:" + WiFi.localIP().toString());
  delay(3000);  // Wyświetlaj adres IP przez 3 sekundy

  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Connected to WiFi");
  lcd2.setCursor(0, 1);
  lcd2.print("IP:" + WiFi.localIP().toString());
  delay(3000);  // Wyświetlaj adres IP przez 3 sekundy

  EEPROM.begin(512);  // Inicjalizacja pamięci flash jako pamięci EEPROM

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

  // Odczytaj tekst dla trzeciej linii z pamięci EEPROM
  char character_line3;
  i = 0;
  while ((character_line3 = EEPROM.read(address_line3 + i)) != '\0') {
    text_line3 += character_line3;
    i++;
  }

  // Odczytaj tekst dla czwartej linii z pamięci EEPROM
  char character_line4;
  i = 0;
  while ((character_line4 = EEPROM.read(address_line4 + i)) != '\0') {
    text_line4 += character_line4;
    i++;
  }

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(text_line1);
  lcd1.setCursor(0, 1);
  lcd1.print(text_line2);

  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print(text_line3);
  lcd2.setCursor(0, 1);
  lcd2.print(text_line4);

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Odczytaj tekst dla pierwszej linii z pamięci EEPROM
    char character_line1;
    int i = 0;
    text_line1 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line1 = EEPROM.read(address_line1 + i)) != '\0') {
      text_line1 += character_line1;
      i++;
    }

    // Odczytaj tekst dla drugiej linii z pamięci EEPROM
    char character_line2;
    i = 0;
    text_line2 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line2 = EEPROM.read(address_line2 + i)) != '\0') {
      text_line2 += character_line2;
      i++;
    }

    // Odczytaj tekst dla trzeciej linii z pamięci EEPROM
    char character_line3;
    i = 0;
    text_line3 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line3 = EEPROM.read(address_line3 + i)) != '\0') {
      text_line3 += character_line3;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line4;
    i = 0;
    text_line4 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line4 = EEPROM.read(address_line4 + i)) != '\0') {
      text_line4 += character_line4;
      i++;
    }

    lcd1.clear();
    lcd1.setCursor(0, 0);
    lcd1.print(text_line1);
    lcd1.setCursor(0, 1);
    lcd1.print(text_line2);

    lcd2.clear();
    lcd2.setCursor(0, 0);
    lcd2.print(text_line3);
    lcd2.setCursor(0, 1);
    lcd2.print(text_line4);

  }

  delay(1000);
  Serial.println("Line 1: " + text_line1);
  Serial.println("Line 2: " + text_line2);
  Serial.println("Line 3: " + text_line3);
  Serial.println("Line 4: " + text_line4);
}

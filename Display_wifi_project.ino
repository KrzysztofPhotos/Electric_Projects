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
LiquidCrystal_I2C lcd1(0x24, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 20, 4);
LiquidCrystal_I2C lcd3(0x25, 20, 4);
LiquidCrystal_I2C lcd4(0x27, 20, 4);
LiquidCrystal_I2C lcd5(0x23, 20, 4);

// Adresy w pamięci EEPROM, w których przechowywane będą teksty
int address_line1 = 0;
int address_line2 = 32;  // Przesunięcie o 32 bajty dla drugiej linii
int address_line3 = 64;  // Przesunięcie o 64 bajty dla trzeciej linii
int address_line4 = 96;  // Przesunięcie o 96 bajtów dla czwartej linii

int address_line5 = 128;  // Przesunięcie o 96 bajtów dla czwartej linii
int address_line6 = 160;  // Przesunięcie o 96 bajtów dla czwartej linii
int address_line7 = 192;  // Przesunięcie o 96 bajtów dla czwartej linii
int address_line8 = 224;  // Przesunięcie o 96 bajtów dla czwartej linii
int address_line9 = 256;  // Przesunięcie o 96 bajtów dla czwartej linii
int address_line10 = 288;  // Przesunięcie o 96 bajtów dla czwartej linii

String text_line1 = "";  // Zmienna przechowująca wpisany tekst dla pierwszej linii
String text_line2 = "";  // Zmienna przechowująca wpisany tekst dla drugiej linii
String text_line3 = "";  // Zmienna przechowująca wpisany tekst dla trzeciej linii
String text_line4 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii

String text_line5 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii
String text_line6 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii
String text_line7 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii
String text_line8 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii
String text_line9 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii
String text_line10 = "";  // Zmienna przechowująca wpisany tekst dla czwartej linii

unsigned long previousMillis = 0;
const unsigned long interval = 5000;  // Interwał 5 sekund

void handleRoot() {
  lcd1.clear();

  lcd2.clear();
  lcd3.clear();
  lcd4.clear();
  lcd5.clear();
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

  html += "<input type='text' name='text_line5' placeholder='Line 5' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line6' placeholder='Line 6' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line7' placeholder='Line 7' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line8' placeholder='Line 8' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line9' placeholder='Line 9' maxlength='16'>";
  html += "<br>";
  html += "<input type='text' name='text_line10' placeholder='Line 10' maxlength='16'>";
  html += "<br>";

  html += "<input type='submit' value='OK'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  lcd1.clear(); // wyczyść ekran 
  lcd2.clear();
  lcd3.clear();
  lcd4.clear();
  lcd5.clear();
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

  if (server.hasArg("text_line5")) {
    text_line4 = server.arg("text_line5");
    lcd3.setCursor(0, 0);
    lcd3.print(text_line5);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line5 = text_line5.length();
    for (int i = 0; i < length_line5; ++i) {
      EEPROM.write(address_line5 + i, text_line5[i]);
    }
    EEPROM.write(address_line5 + length_line5, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line6")) {
    text_line6 = server.arg("text_line6");
    lcd3.setCursor(0, 1);
    lcd3.print(text_line6);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line6 = text_line6.length();
    for (int i = 0; i < length_line6; ++i) {
      EEPROM.write(address_line6 + i, text_line6[i]);
    }
    EEPROM.write(address_line6 + length_line6, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line7")) {
    text_line7 = server.arg("text_line7");
    lcd4.setCursor(0, 0);
    lcd4.print(text_line7);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line7 = text_line7.length();
    for (int i = 0; i < length_line7; ++i) {
      EEPROM.write(address_line7 + i, text_line7[i]);
    }
    EEPROM.write(address_line7 + length_line7, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line8")) {
    text_line8 = server.arg("text_line8");
    lcd4.setCursor(0, 1);
    lcd4.print(text_line8);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line8 = text_line8.length();
    for (int i = 0; i < length_line8; ++i) {
      EEPROM.write(address_line8 + i, text_line8[i]);
    }
    EEPROM.write(address_line8 + length_line8, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }


  if (server.hasArg("text_line9")) {
    text_line9 = server.arg("text_line9");
    lcd5.setCursor(0, 0);
    lcd5.print(text_line9);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line9 = text_line9.length();
    for (int i = 0; i < length_line9; ++i) {
      EEPROM.write(address_line9 + i, text_line9[i]);
    }
    EEPROM.write(address_line9 + length_line9, '\0');  // Zapisz znak null na końcu
    EEPROM.commit();  // Potwierdź zapis do pamięci EEPROM
  }

  if (server.hasArg("text_line10")) {
    text_line10 = server.arg("text_line10");
    lcd5.setCursor(0, 1);
    lcd5.print(text_line10);

    // Zapisz tekst dla czwartej linii w pamięci EEPROM
    int length_line10 = text_line10.length();
    for (int i = 0; i < length_line10; ++i) {
      EEPROM.write(address_line10 + i, text_line10[i]);
    }
    EEPROM.write(address_line10 + length_line10, '\0');  // Zapisz znak null na końcu
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

  lcd3.init();  // Inicjalizacja drugiego wyświetlacza
  lcd3.backlight();

  lcd4.init();  // Inicjalizacja drugiego wyświetlacza
  lcd4.backlight();

  lcd5.init();  // Inicjalizacja drugiego wyświetlacza
  lcd5.backlight();

  delay(500);

  lcd1.begin(20, 4);
  lcd1.print("Arduino WiFi");
  lcd1.setCursor(0, 1);
  lcd1.print("Waiting for WiFi");

  lcd2.begin(20, 4);
  lcd2.print("Arduino WiFi");
  lcd2.setCursor(0, 1);
  lcd2.print("Waiting for WiFi");

  lcd3.begin(20, 4);
  lcd3.print("Arduino WiFi");
  lcd3.setCursor(0, 1);
  lcd3.print("Waiting for WiFi");

  lcd4.begin(20, 4);
  lcd4.print("Arduino WiFi");
  lcd4.setCursor(0, 1);
  lcd4.print("Waiting for WiFi");

  lcd5.begin(20, 4);
  lcd5.print("Arduino WiFi");
  lcd5.setCursor(0, 1);
  lcd5.print("Waiting for WiFi");

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

  lcd3.clear();
  lcd3.setCursor(0, 0);
  lcd3.print("Connected to WiFi");
  lcd3.setCursor(0, 1);
  lcd3.print("IP:" + WiFi.localIP().toString());
  delay(3000);  // Wyświetlaj adres IP przez 3 sekundy

  lcd4.clear();
  lcd4.setCursor(0, 0);
  lcd4.print("Connected to WiFi");
  lcd4.setCursor(0, 1);
  lcd4.print("IP:" + WiFi.localIP().toString());
  delay(3000);  // Wyświetlaj adres IP przez 3 sekundy

  lcd5.clear();
  lcd5.setCursor(0, 0);
  lcd5.print("Connected to WiFi");
  lcd5.setCursor(0, 1);
  lcd5.print("IP:" + WiFi.localIP().toString());
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

  // Odczytaj tekst dla piątej linii z pamięci EEPROM
  char character_line5;
  i = 0;
  while ((character_line5 = EEPROM.read(address_line5 + i)) != '\0') {
    text_line5 += character_line5;
    i++;
  }

  // Odczytaj tekst dla szóstej linii z pamięci EEPROM
  char character_line6;
  i = 0;
  while ((character_line6 = EEPROM.read(address_line6 + i)) != '\0') {
    text_line6 += character_line6;
    i++;
  }

  // Odczytaj tekst dla siódmej linii z pamięci EEPROM
  char character_line7;
  i = 0;
  while ((character_line7 = EEPROM.read(address_line7 + i)) != '\0') {
    text_line7 += character_line7;
    i++;
  }

  // Odczytaj tekst dla ósmej linii z pamięci EEPROM
  char character_line8;
  i = 0;
  while ((character_line8 = EEPROM.read(address_line8 + i)) != '\0') {
    text_line8 += character_line8;
    i++;
  }

  // Odczytaj tekst dla dziewiątej linii z pamięci EEPROM
  char character_line9;
  i = 0;
  while ((character_line9 = EEPROM.read(address_line9 + i)) != '\0') {
    text_line9 += character_line9;
    i++;
  }

  // Odczytaj tekst dla dziesiątej linii z pamięci EEPROM
  char character_line10;
  i = 0;
  while ((character_line10 = EEPROM.read(address_line10 + i)) != '\0') {
    text_line10 += character_line10;
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

  lcd3.clear();
  lcd3.setCursor(0, 0);
  lcd3.print(text_line5);
  lcd3.setCursor(0, 1);
  lcd3.print(text_line6);

  lcd4.clear();
  lcd4.setCursor(0, 0);
  lcd4.print(text_line7);
  lcd4.setCursor(0, 1);
  lcd4.print(text_line8);

  lcd5.clear();
  lcd5.setCursor(0, 0);
  lcd5.print(text_line9);
  lcd5.setCursor(0, 1);
  lcd5.print(text_line10);

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

    // Odczytaj tekst dla piątej linii z pamięci EEPROM
    char character_line5;
    i = 0;
    text_line5 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line5 = EEPROM.read(address_line5 + i)) != '\0') {
      text_line5 += character_line5;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line6;
    i = 0;
    text_line6 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line6 = EEPROM.read(address_line6 + i)) != '\0') {
      text_line6 += character_line6;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line7;
    i = 0;
    text_line7 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line7 = EEPROM.read(address_line7 + i)) != '\0') {
      text_line7 += character_line7;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line8;
    i = 0;
    text_line8 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line8 = EEPROM.read(address_line8 + i)) != '\0') {
      text_line8 += character_line8;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line9;
    i = 0;
    text_line9 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line9 = EEPROM.read(address_line9 + i)) != '\0') {
      text_line9 += character_line9;
      i++;
    }

    // Odczytaj tekst dla czwartej linii z pamięci EEPROM
    char character_line10;
    i = 0;
    text_line10 = "";  // Wyczyść zmienną przechowującą tekst
    while ((character_line10 = EEPROM.read(address_line10 + i)) != '\0') {
      text_line10 += character_line10;
      i++;
    }


    // lcd1.clear();
    // lcd1.setCursor(0, 0);
    // lcd1.print(text_line1);
    // lcd1.setCursor(0, 1);
    // lcd1.print(text_line2);

    // lcd2.clear();
    // lcd2.setCursor(0, 0);
    // lcd2.print(text_line3);
    // lcd2.setCursor(0, 1);
    // lcd2.print(text_line4);

  }

  delay(10000);
  Serial.println("Line 1: " + text_line1);
  Serial.println("Line 2: " + text_line2);
  Serial.println("Line 3: " + text_line3);
  Serial.println("Line 4: " + text_line4);
  Serial.println("Line 5: " + text_line5);
  Serial.println("Line 6: " + text_line6);
  Serial.println("Line 7: " + text_line7);
  Serial.println("Line 8: " + text_line8);
  Serial.println("Line 9: " + text_line9);
  Serial.println("Line 10: " + text_line10);
}

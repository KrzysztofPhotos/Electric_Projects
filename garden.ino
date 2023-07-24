#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <DHT.h>
#define DHTPIN 13      // Pin, do którego podłączony jest czujnik DHT11
#define DHTTYPE DHT11  // Określenie typu czujnika

DHT dht(DHTPIN, DHTTYPE);

const int button1Pin = 0;   // Pin podłączony do przelacznika 1
const int button2Pin = 6;   // Pin podłączony do przelacznika 2
const int controlPin = 10;  // Pin, który ma zmieniać stan (wysoki/niski) wlacza/wylacza LEDY

int prevButton1;  // Zmienna do przechowywania poprzedniego stanu przycisku 1
int prevButton2;  // Zmienna do przechowywania poprzedniego stanu przycisku 2

void setup() {
  //Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(button1Pin, INPUT);   // Przycisk 1 jako wejście
  pinMode(button2Pin, INPUT);   // Przycisk 2 jako wejście
  pinMode(controlPin, OUTPUT);  // Pin sterujący jako wyjście


  
  int prevButton1 = digitalRead(button1Pin);
  int prevButton2 = digitalRead(button2Pin);
}

void loop() {
  //Serial.println(digitalRead(0));
  //.println(digitalRead(1));

  if (digitalRead(button1Pin) != prevButton1){
    digitalWrite(controlPin, !digitalRead(controlPin));
    prevButton1 = digitalRead(button1Pin);
  }
  if (digitalRead(button2Pin) != prevButton2){
    digitalWrite(controlPin, !digitalRead(controlPin));
    prevButton2 = digitalRead(button2Pin);
  }
  



  // Odczytanie temperatury i wilgotności
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Sprawdzenie, czy odczyt się powiódł
  if (isnan(temperature) || isnan(humidity)) {
    //lcd.setCursor(0,0);
    //lcd.print("ERROR");
  } else {
    // Wyświetlenie temperatury i wilgotności na monitorze szeregowym
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Wilg: ");
    lcd.print(humidity);
    lcd.print("%");
  }

  delay(200);

}

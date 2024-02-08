#include <LiquidCrystal.h>
#include <Servo.h>

const int buttonPin = A4;  
const int ledPin = 6;

#define SIGNAL_PIN A5
#define POWER_PIN  7

Servo myservo;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int value = 0; 
int pos = 0;
int moistureLevel = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  myservo.attach(9);
  myservo.write(90);
  pinMode(POWER_PIN, OUTPUT);   
  digitalWrite(POWER_PIN, LOW); 
  lcd.begin(16, 2);
  lcd.print("System Starting..");
  delay(1000);
  lcd.clear();
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  
  delay(10);                      
  value = analogRead(SIGNAL_PIN); 
  moistureLevel = map(value, 100, 800, 0, 100);
  digitalWrite(POWER_PIN, LOW);   
  lcd.setCursor(0, 0);
  lcd.print("Moisture Level");
  lcd.setCursor(0, 1);
  lcd.print(moistureLevel);
  lcd.print(" %");

  delay(2000);

  if (moistureLevel <= 30) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Watering...");
    lcd.setCursor(0, 1);
    lcd.print("Please wait");
    for (pos = 90; pos >= 0; pos -= 1) { 
      myservo.write(pos);              
      delay(15);                       
    }

    delay(2000);

    for (pos = 0; pos <= 90; pos += 1) { 
      myservo.write(pos);              
      delay(15);  
    }
    delay(3000);
    lcd.clear();
    digitalWrite(ledPin, HIGH);

    delay(10000);
  }

  if (analogRead(buttonPin) > 500) {
    digitalWrite(ledPin, LOW); 
  }

}

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial bolt(10, 11);
LiquidCrystal_I2C lcd(0x3F,16,2);

int count = 0;
int buzzer = 4;

void setup()
{
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600);
  bolt.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Leave Buddy");
}

void loop() {
  String Name = "";
  while (bolt.available() > 0) {
    char c =char(bolt.read());
    Name = Name + c;
  }
  Name.trim();
  if (Name != "") {
    alert(Name);
  }
}

void alert(String person_name) {
  if (person_name == "RESET") {
    count = 0;
    return;
  }
  count++;
  Serial.println(count);
  if (count > 4) {
  digitalWrite(buzzer,HIGH);
  lcd.setCursor(1,0);
  lcd.print(person_name);
  delay(4000);
  digitalWrite(buzzer,LOW);
  delay(10000);
  lcd.clear();
  }
  else {
  lcd.setCursor(1,0);
  lcd.print(person_name);
  delay(10000);
  lcd.clear();
  }
}

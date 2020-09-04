#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int touch = 5;
int dht = 8;
int sonic = 4;
int buzz = 3;
int but = 2;
int relay = 6;
bool flag = 0;
int duration = 0;

void setup(){
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 255);
  lcd.print("hello world");
  pinMode(but, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(dht, INPUT);
  attachInterrupt(digitalPinToInterrupt(but), button, RISING);
  Serial.begin(9600);
}

void loop(){
  pinMode(sonic, OUTPUT);
  digitalWrite(sonic, LOW);
  delayMicroseconds(2);
  digitalWrite(sonic, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonic, LOW);

  pinMode(sonic, INPUT);
  duration = pulseIn(sonic, HIGH);
  duration = duration /29 /2;
  Serial.print(duration);

  if(flag == 1){
    lcd.setCursor(0, 0);
    lcd.print("Distance is:");
    lcd.setCursor(0, 1);
    lcd.print(duration);
    lcd.setCursor(4, 1);
    lcd.print("cm");
    buzztone(duration);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("                        ");
    lcd.setCursor(0, 1);
    lcd.print("Press button");
  }
  delay(500);
  lcd.clear();
  delay(100);
  relayfuc();
}

void button(){
  flag = !flag;
}

void buzztone(int distance){
  if(distance > 60){
    tone(buzz, 1000, 100);
    delay(1000);
    noTone(buzz);
  }
  else if(distance > 30 && distance <= 60){
    tone(buzz, 1000, 100);
    delay(500);
    noTone(buzz);
  }
  else if(distance <= 30){
    tone(buzz, 1000);
  }
  else{
    Serial.print("");
  }
}

void relayfuc(){
  if(digitalRead(touch) == 1){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
}

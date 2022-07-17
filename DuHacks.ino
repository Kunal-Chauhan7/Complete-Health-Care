#include <Servo.h>
#define echoPin 9 
#define trigPin 8 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int sensor = 10;              
int state = LOW;             
int val = 0;   
long duration; 
int distance;   
int servoPin = 6; 
int servoPin2 = 7;
Servo Servo1;
Servo Servo2;  
void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    Servo1.attach(servoPin); 
    Servo2.attach(servoPin2);
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(sensor, INPUT);    
    Serial.begin(9600); 
}

void loop()
{
    char command;
    while (Serial.available() > 0)
    {
        command = Serial.read();
        // Water
        if (command == 'W')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning On Water supply");
            delay(5000);
            digitalWrite(2, HIGH);
        }
        else if (command == 'w')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning On Water supply");
            delay(5000);
            display.clearDisplay();          
            digitalWrite(2, LOW);
        }
        // fan
        else if (command == 'F')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning On Fan");
            delay(5000);
            display.clearDisplay();          
            digitalWrite(3, HIGH);
        }
        else if (command == 'f')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning Off Fan");
            delay(5000);
            display.clearDisplay();
            digitalWrite(3, LOW);
        }
        // Light
        else if (command == 'L')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning On Light");
            delay(5000);
            display.clearDisplay();            
            digitalWrite(4, HIGH);
        }
        else if (command == 'l')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Turning Off Fan");
            delay(5000);
            display.clearDisplay();            
            digitalWrite(4, LOW);
        }
        // assisatance
        else if (command == 'A')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("Calling Assistance");
            delay(5000);
            display.clearDisplay();          
            digitalWrite(5, HIGH);
        }
        else if (command == 'a')
        {
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("cancelling assistance");
            delay(5000);
            display.clearDisplay();          
            digitalWrite(5, LOW);
        }
        // servo 6,7
        else if (command == 'S'){
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("Locking...");
          delay(5000);
          display.clearDisplay();
          Servo2.write(0);
          delay(1000); 
          Servo1.write(0); 
          delay(1000);   
          Servo1.write(180);
          delay(1000);
        }
        else if(command == 's'){
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("Unlocking");
          delay(5000);
          display.clearDisplay();          
          Servo1.write(0);
          delay(1000);
          Servo2.write(0); 
          delay(1000);   
          Servo2.write(180); 
          delay(1000);
        }
    }
    // Ultasonic Sound Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<25){
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("An object Is approching");
          display.println(distance);
          delay(500);
          display.clearDisplay();          
              
  }
  // PIR Sensor 
    val = digitalRead(sensor);   
  if (val == HIGH) {           
    delay(500);
  } 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Motion Detected");
      delay(500);
      display.clearDisplay();            
    } 
  else {
      delay(500);             
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Motion Stopped");
        delay(500);
        display.clearDisplay();            
               
    }
  }
    
}

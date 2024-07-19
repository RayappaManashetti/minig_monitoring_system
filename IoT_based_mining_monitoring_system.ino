// Example testing sketch for various DHT humidity/temperature sensors
// Tech at Home
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#include "DHT.h"
int buzzer = 3;
#define DHTPIN 2     // what pin we're connected to
int smoke_detector = A0;
#define sensorPin A1


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
    lcd.backlight();
    pinMode(buzzer,  OUTPUT);
 
  Serial.println("DHTxx test!");
  pinMode(smoke_detector, INPUT);
  dht.begin();
}

void loop() {
 // lcd.clear();
  // Wait a few seconds between measurements.
  delay(2000);
  int level;
    level = analogRead(2);
    Serial.print("Analog output: ");
    Serial.println(level);
    
  
  int sensor_read = analogRead(smoke_detector); 
   Serial.print("Smoke  Density: ");
 Serial.println(sensor_read);
 // moist less then 700 temp more than less than 30 gas sensor gas greater then 300 if(level<700 || t>30 || t<30 || sensor_read>300)
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
lcd.clear();
  Serial.print("Humidity: ");
  Serial.print(h);
   lcd.setCursor(0,0);
  lcd.print("H: ");
  lcd.setCursor(3,0);
  lcd.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
   lcd.setCursor(9,0);
  lcd.print("T: ");
  lcd.setCursor(12,0);
  lcd.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  lcd.setCursor(0,1);
  lcd.print("M: ");
  lcd.setCursor(3,1);
  lcd.print(level);
  // Gas data
   lcd.setCursor(9,1);
  lcd.print("G: ");
  lcd.setCursor(12,1);
  lcd.print(sensor_read);
  //if(level<700 || t>35 || t<30 || sensor_read>400){
    // digitalWrite(buzzer,HIGH);
     // tone(buzzer,500, 100); //piezo rings
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("Buzzer On");
    //delay(10000);
    //digitalWrite(buzzer,LOW);
    //}
    //else{
      //digitalWrite(buzzer,LOW);
   //noTone(buzzer); 
  //  }
    if(level<700)
    {
      lcd.clear();
      digitalWrite(buzzer,HIGH);
      lcd.setCursor(0,0);
  lcd.print("BUZZER ON");
  lcd.setCursor(0,1);
  lcd.print("Water level INC");
  delay(10000);
  digitalWrite(buzzer,LOW);
    }
  else if(t>35|| t<30){
     lcd.clear();
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,0);
  lcd.print("BUZZER ON");
  lcd.setCursor(0,1);
  lcd.print("Temperature INC");
   delay(10000);
  digitalWrite(buzzer,LOW);
  }
  else if(sensor_read>400){
     lcd.clear();
    digitalWrite(buzzer,HIGH);
   lcd.setCursor(0,0);
  lcd.print("BUZZER ON");
  lcd.setCursor(0,1);
  lcd.print("Gas level INC");
   delay(10000);
  digitalWrite(buzzer,LOW);
}
}

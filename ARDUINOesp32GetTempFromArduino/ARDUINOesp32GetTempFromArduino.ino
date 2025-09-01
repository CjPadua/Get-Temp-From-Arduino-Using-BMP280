#include <SoftwareSerial.h>

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define RX, TX pins for SoftwareSerial
SoftwareSerial mySerial(2, 3); // RX = 2, TX = 3

// BMP280 SPI pins
#define BMP_SCK   13
#define BMP_MISO  12
#define BMP_MOSI  11
#define BMP_CS    10

// Initialize BMP280 using SPI
Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

// Initialize LCD (check address: usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 24, 4);

void setup() {
  Serial.begin(9600);     // Debug via USB
  mySerial.begin(9600);   // For ESP32 communication
  Serial.println("Arduino ready!");

  // LCD init
  lcd.init();
  lcd.backlight();

  // BMP280 init
  if (!bme.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("BMP280 not found!");
    while (1);
  }

  lcd.setCursor(0, 0);
  lcd.print("BMP280 Ready!");

  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Waiting for ESP32");
}

void loop() {
  // Check for message from ESP32
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');

    Serial.print("Received from ESP32: ");
    Serial.println(data);

    data.trim();

    if(data == "get_temp") {

      // indicate in the lcd that request from esp32 is received
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Request Received");

      // get temperature from sensor
      float temperature = bme.readTemperature();

      // display in serial
      Serial.print("Temp: ");
      Serial.print(temperature);
      Serial.println(" °C");   

      // display in lcd
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temperature, 1);
      lcd.print((char)223);  // degree symbol
      lcd.print("C    ");      

      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(temperature, 1);
      lcd.print((char)223);  // degree symbol
      lcd.print("C");        
      lcd.print(" Sent to ESP32");

      mySerial.println(temperature);
    }

    if(data == "201"){
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Status Code: " + data);

      lcd.setCursor(0, 1);
      lcd.print("POST Request Success");
    }

    delay(2000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Waiting for ESP32");
  }
}

# Arduino + ESP32 Temperature Monitoring System (BMP280 + LCD + HTTP Post)

This project demonstrates how to interface an **Arduino Uno** with a **BMP280 temperature sensor** and an **I2C LCD**, while communicating with an **ESP32** over serial. The ESP32 forwards the sensor data to a backend server using HTTP POST requests.

---

## 📌 Features
- Reads **temperature data** from a BMP280 sensor (via SPI).
- Displays system status and temperature values on an **I2C LCD**.
- Allows the ESP32 to request data from the Arduino via **UART communication**.
- ESP32 sends temperature readings to a backend server using **WiFi + HTTP POST**.
- Displays request status (`201` response, etc.) back on the Arduino LCD.

---

## 🛠️ Hardware Components
- Arduino Uno / Nano
- ESP32 Dev Module
- BMP280 sensor (SPI mode)
- I2C LCD Display (tested with 0x27 address, 24x4)
- Jumper wires & breadboard

---

## 🔌 Pin Connections

### Arduino Uno
- **SoftwareSerial (for ESP32)**
  - RX → Pin 2  
  - TX → Pin 3  
- **BMP280 (SPI mode)**
  - SCK → Pin 13  
  - MISO → Pin 12  
  - MOSI → Pin 11  
  - CS → Pin 10  
- **LCD (I2C)**
  - SDA → A4  
  - SCL → A5  

### ESP32
- **UART1 (to Arduino)**
  - RX → GPIO 16  
  - TX → GPIO 17  

---

## ▶️ How to Run

1. **Install Arduino IDE** and make sure you have the Arduino Uno and ESP32 board packages.  
   - For ESP32: add `https://dl.espressif.com/dl/package_esp32_index.json` under **Preferences → Additional Board Manager URLs**.  

2. **Clone this repository** or download the `.ino` files.  

3. **Install required libraries** (see Dependencies section).  

4. **Upload to Arduino Uno**:
   - Select **Arduino Uno** board in Arduino IDE.  
   - Upload the Arduino sketch (`arduino_temp_bmp280.ino`).  

5. **Upload to ESP32**:
   - Select **ESP32 Dev Module** in Arduino IDE.  
   - Upload the ESP32 sketch (`esp32_http_client.ino`).  

6. **Connect wiring** according to Pin Connections.  

7. **Open Serial Monitor** on ESP32 (baud rate 115200).  
   - Type `get_temp` and press Enter.  
   - Arduino reads the temperature, shows it on the LCD, and sends it back.  
   - ESP32 forwards it to the backend server.  

8. **Check backend server** for posted data.  

---

## ✅ Dependencies

### Arduino Uno
Install these via **Arduino IDE → Library Manager**:  
- [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)  
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)  
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)  
- [Wire](https://www.arduino.cc/en/Reference/Wire)  
- [SPI](https://www.arduino.cc/en/reference/SPI)  

### ESP32
Install these via **Arduino IDE → Library Manager** or manually:  
- [ArduinoJson](https://arduinojson.org/) (v6 recommended)  
- [NES_HTTPClient](https://github.com/) *(custom HTTP client wrapper, place in `libraries/` folder)*  
- **WiFi** (already included with ESP32 core)  

---

## 📋 Example JSON Sent
```json
{
  "groupName": "Padua",
  "temp": "28.4"
}

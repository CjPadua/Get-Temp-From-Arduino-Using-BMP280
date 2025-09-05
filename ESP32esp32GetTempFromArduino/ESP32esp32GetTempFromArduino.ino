// ESP32 has multiple UARTs, we can simulate SoftwareSerial using HardwareSerial
#include <HardwareSerial.h>

HardwareSerial arduinoSerial(1); // Use UART1 (we can assign pins)

#define RXD2 16   // ESP32 RX
#define TXD2 17   // ESP32 TX

// include library for sending data to sir gobilab
#include <ArduinoJson.h>
#include "NES_HTTPClient.h"

// credentials
const char* ssid = "HUAWEI-KtkH";
const char* password = "K5GKU7Vm";
const char* serverName = "http://192.168.18.28:2000/esp32/data";

// create a nes instance
NES_HTTPClient nesClient(ssid, password, serverName);

void setup() {
  Serial.begin(115200);               // Debugging
  arduinoSerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // Custom pins for Serial

  nesClient.connectWiFi();
  Serial.println(WiFi.localIP());

  Serial.println("ESP32 ready!");
}

void loop() {

  // read serial input
  if(Serial.available() > 0) {

    // Read the incoming byte
    String input = Serial.readStringUntil('\n'); // read until Enter (newline)
    
    // Print back the input
    Serial.print("You typed: ");
    Serial.println(input);

    if(input == "get_temp") {
      arduinoSerial.println(input);   

      // Receive from Arduino
      if (arduinoSerial.available()) {
        String temperature = arduinoSerial.readStringUntil('\n');
        Serial.print("Received from Arduino: ");
        Serial.println(temperature);

        if(nesClient.isConnected()) {

          StaticJsonDocument<200> postDoc;
          postDoc["groupName"] = "Padua";
          postDoc["temp"] = temperature;

          // Approach ni Sir
          // String jsonStr;
          // serializeJson(postDoc, jsonStr);  // print JSON for debugging
          // Serial.println(jsonStr);

          // Approach ni chatgpt
          serializeJson(postDoc, Serial);  // print JSON for debugging
          Serial.println();

          int response = nesClient.sendJSON(postDoc);
          Serial.printf("POST Response code: %d\n", response);

          // send success response code to arduino
          arduinoSerial.println(response);

        } else {
          Serial.println("Error: Not connected to WiFi");
        }
      }   
    }
  }
}

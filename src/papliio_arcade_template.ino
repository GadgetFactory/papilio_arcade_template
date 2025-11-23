// ESP32-S3 Arduino Example for Controlling FPGA RGB LED via SPI
// Controls RGB LED via Wishbone SPI interface

#include <SPI.h>
#include "RGBLed.h"

// SPI Pin Configuration for ESP32-S3
// Adjust these pins based on your actual hardware connections
#define SPI_CLK   12   // SCK - connects to FPGA esp_clk
#define SPI_MOSI  11   // MOSI - connects to FPGA esp_mosi
#define SPI_MISO  9   // MISO - connects from FPGA esp_miso
#define SPI_CS    10   // CS - connects to FPGA esp_cs_n

SPIClass * fpgaSPI = NULL;

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("ESP32-S3 FPGA RGB LED Control Example");
  
  // Initialize SPI for FPGA communication
  fpgaSPI = new SPIClass(HSPI);
  fpgaSPI->begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS);
  
  
  // Configure CS pin
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);  // CS idle high
  // Initialize RGB LED library (it will initialize the Wishbone SPI helper)
  RGBLed::begin(fpgaSPI, SPI_CS);
  
  // Initialize Serial2 for UART debug from FPGA (on MISO pin)
  Serial2.begin(115200, SERIAL_8N1, SPI_MISO, -1);  // RX on MISO pin, no TX
  
  Serial.println("SPI initialized");
  Serial.println("UART debug initialized on MISO pin");
  delay(100);
  
  // Set RGB LED to green
  RGBLed::setColor(RGBLed::COLOR_GREEN);
  Serial.println("LED set to GREEN");
}

void loop() {
  // Read and forward UART debug data from FPGA
  // while (Serial2.available()) {
  //   Serial.write(Serial2.read());
  // }
  
  // Example: Cycle through colors every 2 seconds
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_RED);
  Serial.println("LED: RED");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_BLUE);
  Serial.println("LED: BLUE");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_GREEN);
  Serial.println("LED: GREEN");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_YELLOW);
  Serial.println("LED: YELLOW");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_CYAN);
  Serial.println("LED: CYAN");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_MAGENTA);
  Serial.println("LED: MAGENTA");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_PURPLE);
  Serial.println("LED: PURPLE");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_ORANGE);
  Serial.println("LED: ORANGE");
}


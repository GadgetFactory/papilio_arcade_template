// ESP32-S3 Arduino Example for Controlling FPGA RGB LED via SPI
// Controls RGB LED via Wishbone SPI interface

#include <SPI.h>
#include "RGBLed.h"
#include <HDMIController.h>

// SPI Pin Configuration for ESP32-S3
// Adjust these pins based on your actual hardware connections
#define SPI_CLK   12   // SCK - connects to FPGA esp_clk
#define SPI_MOSI  11   // MOSI - connects to FPGA esp_mosi
#define SPI_MISO  9   // MISO - connects from FPGA esp_miso
#define SPI_CS    10   // CS - connects to FPGA esp_cs_n

SPIClass * fpgaSPI = NULL;
HDMIController *hdmi = NULL;

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

  // Initialize HDMI controller (make it persistent so it remains active)
  hdmi = new HDMIController(fpgaSPI, SPI_CS, SPI_CLK, SPI_MOSI, SPI_MISO);
  if (hdmi) {
    hdmi->begin();
    hdmi->setVideoPattern(1); // Example: set video pattern
    Serial.println("HDMI: initialized and pattern set to 1");
  } else {
    Serial.println("HDMI: failed to allocate controller");
  }

  Serial.println("SPI initialized");
  delay(100);

  // Set RGB LED to green
  RGBLed::setColor(RGBLed::COLOR_GREEN);
  Serial.println("LED set to GREEN");
}

void loop() {
  // Cycle through colors and HDMI patterns every 2 seconds
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_RED);
  if (hdmi) hdmi->setVideoPattern(0);
  Serial.println("LED: RED | HDMI: color bar");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_BLUE);
  if (hdmi) hdmi->setVideoPattern(1);
  Serial.println("LED: BLUE | HDMI: net grid");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_GREEN);
  if (hdmi) hdmi->setVideoPattern(2);
  Serial.println("LED: GREEN | HDMI: gray");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_YELLOW);
  if (hdmi) hdmi->setVideoPattern(3);
  Serial.println("LED: YELLOW | HDMI: single color");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_CYAN);
  if (hdmi) hdmi->setVideoPattern(0);
  Serial.println("LED: CYAN | HDMI: color bar");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_MAGENTA);
  if (hdmi) hdmi->setVideoPattern(1);
  Serial.println("LED: MAGENTA | HDMI: net grid");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_PURPLE);
  if (hdmi) hdmi->setVideoPattern(2);
  Serial.println("LED: PURPLE | HDMI: gray");
  
  delay(2000);
  RGBLed::setColor(RGBLed::COLOR_ORANGE);
  if (hdmi) hdmi->setVideoPattern(3);
  Serial.println("LED: ORANGE | HDMI: single color");
}


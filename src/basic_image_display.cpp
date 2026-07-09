// Required Libraries
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"


// Pin Mapping

#define R1_PIN 25 
#define G1_PIN 26 
#define B1_PIN 27 
#define R2_PIN 14 
#define G2_PIN 12 
#define B2_PIN 32 
#define A_PIN 21 
#define B_PIN 19 
#define C_PIN 5 
#define D_PIN 17 
#define E_PIN 33   
#define LAT_PIN 15 
#define OE_PIN 16 
#define CLK_PIN 4

// Config Object
HUB75_I2S_CFG::i2s_pins defined_pins = { R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN };
HUB75_I2S_CFG mxconfig(
  64,    // Matrix width
  64,    // Matrix height
  1,     // chain length
  defined_pins  // pin mapping
);




// Matrix Object
MatrixPanel_I2S_DMA *dma_display = nullptr;

void setup() {
    Serial.begin(115200);
    

    mxconfig.driver = HUB75_I2S_CFG::FM6124; //For my specific Panel
    mxconfig.clkphase = false;
    mxconfig.latch_blanking = 4;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    dma_display->begin();
    dma_display->clearScreen();
    
    
    dma_display->setBrightness(155);

    dma_display->setCursor(10,15);
    dma_display->setTextSize(1);
    dma_display->setTextColor(0xFFFF);
    dma_display->print("WHITE");
    dma_display->setTextColor(0x1811);
    dma_display->setCursor(10,22);
    dma_display->print("TIGER");
    
}




void loop() {
  
    
    

}


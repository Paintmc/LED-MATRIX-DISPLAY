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
#define LAT_PIN 4 
#define OE_PIN 15 
#define CLK_PIN 16 

// Config Object
HUB75_I2S_CFG mxconfig;

// Matrix Object
MatrixPanel_I2S_DMA *dma_display = nullptr;

void setup() {
    
    // Assigning attributes of mxconfig
    mxconfig.mx_width = 64;
    mxconfig.mx_height = 64;
    mxconfig.gpio.r1 = R1_PIN;
    mxconfig.gpio.g1 = G1_PIN;
    mxconfig.gpio.b1 = B1_PIN;
    mxconfig.gpio.r2 = R2_PIN;
    mxconfig.gpio.g2 = G2_PIN;
    mxconfig.gpio.b2 = B2_PIN;
    mxconfig.gpio.a = A_PIN;
    mxconfig.gpio.b = B_PIN;
    mxconfig.gpio.c = C_PIN;
    mxconfig.gpio.d = D_PIN;
    mxconfig.gpio.e = E_PIN;
    mxconfig.gpio.lat = LAT_PIN;
    mxconfig.gpio.oe = OE_PIN;
    mxconfig.gpio.clk = CLK_PIN;
    mxconfig.chain_length = 1; 

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    dma_display->begin();
    dma_display->setBrightness(100);
    



}

// 

void loop() {
  
    dma_display->fillScreen(0x0000);

}

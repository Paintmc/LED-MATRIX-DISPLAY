// Required Libraries
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include <array>
#include "LittleFS.h"
#include "AnimatedGIF.h"

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


// Creating the draw function which will take an array of arrays of color values as input
// and light up the corresponding LED's of the matrix

void draw_animation(uint16_t (*animation)[64][64], int frame_count) {
    // size of one frame is already known (64x64) <- must change if your panel is of different size
    for (int f = 0; f < frame_count; f++) {
      for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 64; x++) {

          dma_display->drawPixel(x, y, animation[f][y][x]);
        }
      }
      delay(33); // <-- delay frames if you wish (change 33 to a value that suits your use)
    } 
}


void setup() {

    Serial.begin(115200);
    

    mxconfig.driver = HUB75_I2S_CFG::FM6124; //For my specific Panel
    mxconfig.clkphase = false;
    mxconfig.latch_blanking = 4;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    dma_display->begin();
    dma_display->clearScreen();
    
    //SET BRIGHTNESS:
    dma_display->setBrightness(155);

}


void loop() {
  // if frame count == 1 dont keep looping so have an if that has no code in it
  // or if you want gif to loop then put draw_animation in here
  //draw_animation();
}


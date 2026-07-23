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


AnimatedGIF gif;



// Creating the draw function which will take an array of arrays of color values as input
// and light up the corresponding LED's of the matrix

void draw_image(uint16_t image[]) {
    // size of one frame is already known (64x64) <- must change if your panel is of different size
    int x = 0;
    int y = 0;
    for (int t = 0; t < 4096 ; t++) {
      dma_display->drawPixel(x, y, image[t]);
      x++;
      if (x == 64) {
        x = 0;
        y++;
      }
    }
    delay(33); // <-- delay frames if you wish (change 33 to a value that suits your use)
}


void GIFDraw(GIFDRAW *draw) {

    //Prevents a crash that I was experiencing
    if (dma_display == nullptr) return;


  uint8_t *s = draw->pPixels;
  uint16_t *colors = draw->pPalette;
  int y = draw->iY + draw->y; //iY is band or chunk of a frame (0,10,...) and y is line in that chunk (0,1,2,...)
  
  for (int x = 0; x < draw->iWidth; x++) {

    dma_display->drawPixel(x, y, colors[s[x]]);

  }

}

void setup() {

    Serial.begin(115200);

    //Setting up the matrix
    mxconfig.driver = HUB75_I2S_CFG::FM6124; //For my specific Panel
    mxconfig.clkphase = false;
    mxconfig.latch_blanking = 4;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    dma_display->begin();
    dma_display->clearScreen();
    
    //SET BRIGHTNESS:
    dma_display->setBrightness(155);

    //Setting up LittleFS on the esp32
    LittleFS.begin(true);
    gif.begin(LITTLE_ENDIAN_PIXELS);

}
  




void loop() {
    
  if (gif.open("/ezgif.com-gif-maker.gif", GIFDraw)) { 
      Serial.println("GIF opened. Playing frames...");
        
      while (gif.playFrame(true, NULL)) {
      }
}
}
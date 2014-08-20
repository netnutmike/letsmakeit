#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, PIN, NEO_GRB + NEO_KHZ800);                        
                          
uint32_t image_x2[257] = { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                          1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
                          0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,
                          0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,
                          0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,
                          0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,
                          0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                          0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
                          0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
                          0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                          0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,
                          0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,
                          0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,
                          0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,
                          1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
                          1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 };
                          
prog_uint32_t PROGMEM image_check[257] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
                             0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,
                             0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
                             0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
                             0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
                             1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
                             1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
                             1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,
                             0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,
                             0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
                             0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0 };
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //colorWipe(strip.Color(0, 0, 0), 1);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  rainbow(20);
  rainbowCycle(20);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 2, 20, 200);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 3, 20, 200);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 4, 20, 200);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 5, 20, 200);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 6, 20, 200);
  colorwalk2(strip.Color(255, 0, 0), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk2(strip.Color(100, 100, 0), strip.Color(0, 100, 100), 4, 20, 200);
  colorwalk2(strip.Color(10, 20, 0), strip.Color(20, 10, 0), 4, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), 2, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), 3, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), 4, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(0, 255, 255), 5, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(0, 255, 255), 6, 20, 200);
  colorwalk3(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 255, 0), 4, 20, 200);
  colorwalk3(strip.Color(100, 100, 0), strip.Color(0, 100, 100), strip.Color(100, 0, 100), 4, 20, 200);
  colorwalk3(strip.Color(30, 50, 0), strip.Color(50, 30, 0), strip.Color(10, 50, 30),4, 20, 200);
  
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), strip.Color(0, 0, 0), 2, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), strip.Color(0, 0, 0), 3, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(0, 255, 255), strip.Color(0, 0, 0), 5, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(0, 255, 255), strip.Color(0, 0, 0), 6, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk4(strip.Color(100, 100, 0), strip.Color(0, 100, 100), strip.Color(100, 0, 100), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk4(strip.Color(30, 50, 0), strip.Color(50, 30, 0), strip.Color(10, 50, 30), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(255, 255, 255), strip.Color(0, 0, 0), 4, 20, 200);
  colorwalk4(strip.Color(255, 0, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 255), strip.Color(0, 255, 0), 4, 20, 200);
  
  //drawmonoimage(strip.Color(255, 0, 0), strip.Color(0, 0, 0), image_x2);
  monoimageblink(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(255, 0, 0), strip.Color(0, 0, 0), 10, 500, image_x2);

  monoimageblink(strip.Color(0, 255, 0), strip.Color(0, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 5, 0), 10, 500, (uint32_t*)pgm_read_word(&(image_check[0])));
  monoimageblink(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(255, 0, 0), strip.Color(20, 5, 0), 10, 500, image_x2);
  monoimageblink(strip.Color(255, 0, 0), strip.Color(0, 0, 0), strip.Color(255, 0, 0), strip.Color(255, 0, 0), 10, 500, image_x2);
  monoimageblink(strip.Color(255, 0, 0), strip.Color(255, 255, 255), strip.Color(255, 255, 255), strip.Color(255, 0, 0), 10, 500, image_x2);
  colorWipe(strip.Color(0, 0, 0), 1);  // off
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


void colorwalk2(uint32_t color1, uint32_t color2, int width, int repeat, uint8_t wait) {
  uint32_t ccolor = color1;
  int l1, l2, l3, crow;
  
  for (l1=0; l1<repeat; ++l1) {
    crow=0;
    while (crow < 16) {
      for (l2=0; l2<width; ++l2) {
        for (l3=0; l3<16; ++l3) {
          strip.setPixelColor((crow*16)+(l2*16)+l3, ccolor);
        }
      }
      
      crow += width;
      if (crow < 16) {
        if (ccolor == color1)
          ccolor = color2;
        else
          ccolor = color1;
      }
    }
    strip.show();
    delay(wait);
  }
}

void colorwalk3(uint32_t color1, uint32_t color2, uint32_t color3, int width, int repeat, uint8_t wait) {
  uint32_t ccolor = color1;
  uint32_t scolor = color1;
  int l1, l2, l3, crow;
  
  for (l1=0; l1<repeat; ++l1) {
    crow=0;
    ccolor = scolor;
    while (crow < 16) {
      for (l2=0; l2<width; ++l2) {
        for (l3=0; l3<16; ++l3) {
          strip.setPixelColor((crow*16)+(l2*16)+l3, ccolor);
        }
      }
      
      crow += width;
      //if (crow < 16) {
        if (ccolor == color1)
          ccolor = color2;
        else if (ccolor == color2)
          ccolor = color3;
        else 
          ccolor = color1;
      //}
    }
    strip.show();
    if (scolor == color1)
      scolor = color2;
    else if (scolor == color2)
      scolor = color3;
    else 
      scolor = color1;
    
      
    delay(wait);
  }
}

void colorwalk4(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t color4, int width, int repeat, uint8_t wait) {
  uint32_t ccolor = color1;
  uint32_t scolor = color1;
  int l1, l2, l3, crow;
  
  for (l1=0; l1<repeat; ++l1) {
    crow=0;
    ccolor = scolor;
    while (crow < 16) {
      for (l2=0; l2<width; ++l2) {
        for (l3=0; l3<16; ++l3) {
          strip.setPixelColor((crow*16)+(l2*16)+l3, ccolor);
        }
      }
      
      crow += width;
      //if (crow < 16) {
        if (ccolor == color1)
          ccolor = color2;
        else if (ccolor == color2)
          ccolor = color3;
        else if (ccolor == color3)
          ccolor = color4;
        else 
          ccolor = color1;
      //}
    }
    strip.show();
    if (scolor == color1)
      scolor = color2;
    else if (scolor == color2)
      scolor = color3;
    else if (scolor == color3) 
      scolor = color4;
    else
      scolor = color1;
    
      
    delay(wait);
  }
}

void monoimageblink(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t color4, int repeat, int dly, uint32_t dimg[]) {

  for (int l = 0; l<repeat; ++l) {
    drawmonoimage(color1, color2, dimg);
    delay(dly);
    drawmonoimage(color3, color4, dimg);
    delay(dly);
  }
}

void drawmonoimage(uint32_t color1, uint32_t color2, uint32_t image[]) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
      if (image[j] == 1) {
        strip.setPixelColor(j, color1);
      } else {
        strip.setPixelColor(j, color2);
      }
    }
  strip.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


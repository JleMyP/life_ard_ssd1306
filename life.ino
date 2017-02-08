#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
 
 
 
const uint16_t map_w = 128;
const uint16_t map_h = 64;
const uint16_t size  = map_w * map_h;

uint8_t surf[size]; // = calloc(size, 1);
uint8_t nsurf[size]; // = calloc(size, 1);


Adafruit_SSD1306 display(A2);



void setup() {
  randomSeed(analogRead(0));
  display.begin();
  generate();
}


void loop() {
  step();
  draw();
}


void generate() {
  for (uint16_t p = 0; p < size; ++p) surf[p] = random(2);
}


void step() {
  uint16_t x;
  uint16_t y;
  
  uint16_t ypos;
  uint16_t pos
  
  uint8_t sum;
  
  for (y = 0; y < map_h; ++y) {
    ypos = y * map_w;
    
    for (x = 0; x < map_w; ++x) {
      pos = ypos + x;
      sum = get_sum_mur(x, y);
      
      nsurf[pos] = (sum == 3 || surf[pos] && sum == 2);
    }
  }
  
  for (y = 0; y < map_h; ++y) {
    ypos = y * map_w;
    
    for (x = 0; y < map_w; ++x) surf[ypos + x] = nsurf[ypos + x];
  }
}


uint8_t get_sum_mur(int16_t x, int16_t y) {
  int16_t xx;
  int16_t yy;
  
  uint8_t sum = 0;
  
  for (xx = x - 1; xx < x + 2; ++xx) {
    for (yy = y - 1; yy < y + 2; ++yy) sum += get(xx, yy);
  }
  
  return sum;
}

uint8_t get(int16_t x, int16_t y) {
  if (x == map_w) x = 0;
  else if (x == -1) x = map_w - 1;
  
  if (y == map_h) y = 0;
  else if (y == -1) y = map_h - 1;
  
  return surf[y * map_w + x];
}


void draw() {
  uint16_t x;
  uint16_t y;
  uint16_t ypos;
  
  for (y = 0; y < map_h; ++y) {
    ypos = y * map_w;
  
    for (x = 0; x < map_w; ++x) display.drawPixel(x, y, surf[ypos + x]);
  }
  
  display.display();
}

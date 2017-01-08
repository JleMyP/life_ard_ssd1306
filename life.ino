#include <Wire.h>
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
 
#define map_w 128
#define map_h 64
#define size map_w*map_h

Adafruit_SSD1306 display(A2);

bool surf[size];// = calloc(size, 1);
bool nsurf[size];// = calloc(size, 1);




void setup(){
  randomSeed(analogRead(0));
  display.begin();
  generate();
}


void loop(){
  step();
  draw();
}


void generate(){
  for(uint16_t p=0; p<size; p++) surf[p] = random(2)?true:false;
}


void step(){
  for(int16_t x=0; x<map_w; x++){
    for(int16_t y=0; y<map_h; y++){
      uint16_t pos = y*map_w+x;
      byte sum = get_sum_mur(x, y);
      if(sum == 3 or surf[pos] && sum == 2) nsurf[pos] = true;
      else nsurf[pos] = false;
    }
  }
  
  for(byte x=0; x<map_w; x++){
    for(byte y=0; y<map_h; y++) surf[y*map_w+x] = nsurf[y*map_w+x];
  }
}


byte get_sum_mur(int16_t x, int16_t y){
  byte sum = 0;
  for(int16_t xx=x-1; xx<x+2; xx++){
    for(int16_t yy=y-1; yy<y+2; yy++) sum += (byte)get(xx, yy);
  }
  return sum;
}

bool get(int16_t x, int16_t y){
  if(x == map_w) x = 0;
  else if(x == -1) x = map_w-1;
  if(y == map_h) y = 0;
  else if(y == -1) y = map_h-1;
  return surf[y*map_w+x];
}


void draw(){
  for(int16_t x=0; x<map_w; x++){
    for(int16_t y=0; y<map_h; y++){
      display.drawPixel(x, y, surf[y*map_w+x]);
    }
  }
  display.display();
}
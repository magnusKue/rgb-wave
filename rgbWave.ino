#include <FastLED.h>
#include "GPLC_Pins.h"

#define NUM_LEDS 120
#define DATA_PIN 5
#define LED_TYPE WS2812B

#define SPEEDCREASE 2

CRGB leds[NUM_LEDS];
int i = 0;
int speed_ = 6;

bool lastUp = false;
bool lastDown = false;
bool lastPause = false;

bool pause_ = false;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
  randomSeed(analogRead(0));
  Serial.begin(9600);

  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_G, INPUT);
  pinMode(BUTTON_B, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  if (!pause_)
    updateLEDs();

  handlePins();
  delay(30);
  Serial.println(speed_);
}

void handlePins() {
  if (digitalRead(BUTTON_R) && !pause_) {
    if (!lastUp) {
      speed_++;
      Serial.println("UP");
      lastUp = true;
    }
  }
  else if (digitalRead(BUTTON_G) && !pause_) {
    if (!lastDown) {
      speed_ = max(speed_ - SPEEDCREASE, 1);
      Serial.println("DOWN");
      lastDown = true;
    }
  }
  else if (digitalRead(BUTTON_B)) {
    if (!lastPause) {
      pause_ = !pause_;
      Serial.println("PAUSE");
      lastPause = true;
    }
  }
  else {
    lastUp = false; 
    lastDown = false;
    lastPause = false;
  }

  digitalWrite(LED_R, lastUp);
  digitalWrite(LED_G, lastDown);
  digitalWrite(LED_B, pause_);
}

void updateLEDs() {
  leds[0] = getWaveAtIndex(i);  
  shift();

  FastLED.show();

  if (i+speed_ <= 255) {
    i+=speed_;
  }
  else {
    i = 0;
  }
}

void clearStripe() {
  for (int x = 0; x <= NUM_LEDS; x++) {
    leds[x] = CRGB(0,0,0);
  }
}

CRGB getWaveAtIndex(float i) {
  float t = i / 255;
  float w = lerp(380, 840, i/255);
  float R = 0.0;
  float G = 0.0;
  float B = 0.0;

  if (w >= 380 and w < 440){
        R = -(w - 440.) / (440. - 380.);
        G = 0.0;
        B = 1.0;
  }
  else if (w >= 440 and w < 490){
      R = 0.0;
      G = (w - 440.) / (490. - 440.);
      B = 1.0;
  }
  else if (w >= 490 and w < 510){
      R = 0.0;
      G = 1.0;
      B = -(w - 510.) / (510. - 490.);
  }
  else if (w >= 510 and w < 580){
      R = (w - 510.) / (580. - 510.);
      G = 1.0;
      B = 0.0;
  }
  else if (w >= 580 and w < 645){
      R = 1.0;
      G = -(w - 645.) / (645. - 580.);
      B = 0.0;
  }
  else if (w >= 645 and w <= 780){
      R = 1.0;
      G = 0.0;
      B = 0.0;
  }
  else if (w >= 780 and w <= 840){
      R = 1.0;
      G = 0.0;
      B = (w - 780.) / (840. - 780.);
  }
  else{
      R = 0.0;
      G = 0.0;
      B = 0.0;
  }
  
  return CRGB((R*255), (G*255), (B*255));
}

void shift() {
  for (int x = NUM_LEDS; x >= 1; x--) {
    leds[x] = leds[x-1];
  }
}

int clamp(int x, int minV, int maxV) {
  return max(min(x, maxV), minV);
}

float lerp(float a, float b, float t)
{
    return a * (1.0 - t) + (b * t);
}

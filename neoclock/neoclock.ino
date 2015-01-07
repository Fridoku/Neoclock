#include <HSBColor.h>
#include <Adafruit_NeoPixel.h>
#include <Time.h>

byte secColor[3]={
  0,0,255};
byte minColor[3]={
  0,255,0};
byte hourColor[3]={
  255,0,0};

byte leds[3][60];

long t;


byte mode=0; //0=Clock

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);


void setup()
{
  strip.begin();
  strip.show();
  Serial.begin(9600);
  setTime(11,25,55,29,12,2014);
}

void loop()
{
  time();
}



void time()
{
  while (mode==0)
  {

    Serial.println(second(t));
    if(now()!=t)
    {
      clearBuffer();
      t=now();

      for(byte i=hourFormat12(t)*5-1;i<hourFormat12(t)*5+2;i++)
      {
        addPixelColor(i,hourColor);
      }

      addPixelColor(minute(t),minColor);
      addPixelColor(second(t),secColor);
      writeOut();
    }
  }
}

void addPixelColor(int n,byte* c)
{
  if(n<0) n=n+60;
  if(n>59) n=n-60;
  leds[0][n]=(leds[0][n]+c[0])/2;
  leds[1][n]=(leds[1][n]+c[1])/2;
  leds[2][n]=(leds[2][n]+c[2])/2;
}



void writeOut()
{
  for(int i=0;i<60;i++)
  {
    strip.setPixelColor(i,leds[0][i],leds[1][i],leds[2][i]);
  }
  strip.show();
}

void clearBuffer()
{
  for(int i=0;i<60;i++)
  {
    leds[0][i]=0;
    leds[1][i]=0;
    leds[2][i]=0;
  }
}





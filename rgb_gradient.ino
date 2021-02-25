// a program for an RGB diode for changing its colours in a fading loop (rgb, yellow, aqua, purple)
int redPin = 13;
int greenPin = 12;
int bluePin = 11;
 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
  setColor(255, 255, 0);  // red
  delay(2000);
  setColor(0, 255, 0);  // green
  delay(2000);
  setColor(0, 0, 255);  // blue
  delay(2000);
  setColor(0, 255, 0);  // yellow
  delay(2000);  
  setColor(80, 0, 80);  // purple
  delay(2000);
  setColor(0, 255, 255);  // aqua
  delay(2000);
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

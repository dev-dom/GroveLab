/*
/* Grove Temperature Sensor with output to Grove LCD  v1.0
*  This sensor detects the environment temperature,
*  output is directed to the LCD screen (connected to a I2C port).
*  Connect the signal of this sensor to A0, then  
*  output the reading to the Grove LCD RGB Backlight.
*  By: devdom4g@gmail.com
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>;

rgb_lcd lcd;

int a;
float temperature;
int B=3975;                  //B value of the thermistor
float resistance;
 
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
}
 
void loop()
{
  a=analogRead(0);
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet&nbsp;;
  delay(1000);
  lcd.clear();
  lcd.setRGB(0, 0,255);
  lcd.print("Temperature is: ");
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  if(temperature > 20)
  {
    lcd.print(" Nice :-) ");
  } else { lcd.print( " It's cold!"); }
 }

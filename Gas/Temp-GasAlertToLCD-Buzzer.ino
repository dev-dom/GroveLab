/*
 * Grove on Arduino - Gas and Temperature Sensor with Buzzer Alert v1.0
 * 
 * The Temperature and Gas sensors send data to Arduino 
 * Arduino sends out the readings to the LCD
 *
 * The Gas Sensor detects the Gas density, 
 * Arduino get the result by anologread. The gas Density is 
 * 0~1, larger the output is, the denser the gas.
 *
 * Connect the Temperature Sensor to A0;
 * Connect the Gas Sensor to A1;
 * Connect the buzzer to D3
 * 
 * When the gas reading is above 0.3 of density, the buzzer
 * will alert for gas
 *
 *
 * By: dev-dom4g@gmail.com
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>;

rgb_lcd lcd;

// Initialize variables for temperature sensor
int a;
float temperature;
int B=3975;                  //B value of the thermistor
float resistance;

// Initialize variable for the Buzzer
int speakerPin = 3;                  // Grove Buzzer connect to D3
int length = 15;                     // the number of notes
char notes[] = "ccggaagffeeddc ";    // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

// Function playtone
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

// Function playNote
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}


void setup() 
{
    // set up the buzzer  
    pinMode(speakerPin, OUTPUT);
     // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}
 
void loop() 
{

  // Read Temperature
  a=analogRead(0);
  resistance=(float)(1023-a)*10000/a;                      //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15; //convert to temperature via datasheet;
  // Read Gas density (and stored it in sensorvalue) 
  float vol;
  int sensorValue = analogRead(A1);
  vol=(float)sensorValue/1024;

  lcd.clear();
  lcd.setRGB(0, 0,255);
  lcd.print("Temperature");
  lcd.print(temperature);
  
  lcd.setCursor(0, 1);
  lcd.print("Gas Density ");
  lcd.print(vol);
  if(vol > 0.30)
  {
     for (int i = 0; i < length; i++) 
    {
        if (notes[i] == ' ')
        {
            delay(beats[i] * tempo); // rest
        }
        else
        {
            playNote(notes[i], beats[i] * tempo);
        }
        // pause between notes
        delay(tempo / 2);
    }
  }
    delay(1000 );
}

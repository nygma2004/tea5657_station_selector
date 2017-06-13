/*
   This example was based on the TEA5767 library published by 
   Marcos R. Oliveira at: https://github.com/mroger/TEA5767

   This example was provided by Csongor Varga watch a video on this
   example at: https://youtu.be/yp0HVGjakMs

   This example is available at: https://github.com/nygma2004/tea5657_station_selector


   Copyright 2014 Marcos R. Oliveira

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Wire.h>
#include <TEA5767N.h>


//Constants:
TEA5767N Radio = TEA5767N(); // Using standard I2C pins A4 and A5

#define MUTEPIN    2         // D2 pin
#define STATIONPIN 3         // D3 pin

//Variables:
int flag=0;
double stations[] = {89.5, 94.8, 90.9}; // Your station presets
int currentstation = 0;
int maxstation = 2; // Last item in the stations array (zero indexed)
bool mutestate = 0;

void setup () {
  //Init
  Serial.begin(9600);
  Serial.println("Arduino FM radio example");

  pinMode(MUTEPIN, INPUT); 
  pinMode(STATIONPIN, INPUT); 
  
  Radio.selectFrequency(stations[currentstation]); //power on with the first station
  delay(250); // Added this delay to ensure tuning stats read from the module are correct - module has time to tune properly

}

void loop () {
  
  if (digitalRead(MUTEPIN)==LOW) {
    mutestate = !mutestate;
    if (mutestate) {
      Serial.println("Muting radio");
      Radio.mute();
    } else {
      Serial.println("Unmuting radio");
      Radio.turnTheSoundBackOn();
    }
  }

  if (digitalRead(STATIONPIN)==LOW) {
    Serial.println("Tuning to next station");
    currentstation++;
    if (currentstation>maxstation) {
      currentstation = 0;
    }
    Radio.selectFrequency(stations[currentstation]); 
    flag = 0; // Flag to fetch stats and display over serial
    delay(250); // Added this delay to ensure tuning stats read from the module are correct - module has time to tune properly  
  }

  if (flag == 0) {
    Serial.print("Current freq: ");
    Serial.print(Radio.readFrequencyInMHz());
    Serial.print("MHz Signal: ");
    Serial.print(Radio.isStereo() ? "STEREO" : "MONO");
    Serial.print(" ");
    Serial.print(Radio.getSignalLevel());
    Serial.println("/15");
    flag=1;
  }
   
  delay(100); // General delay
   
}

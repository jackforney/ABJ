/* SD Analog Datalogger
 * Datalogger that allows the user to write analog data the µSD card.
 * Current performance is around 7.7ms/sample.
 * 
 * Next steps: multiple analogs, improve sample rate, improve reliability
 * 
 * Teensy 3.2 | SD Reader/Hardware |
 *    Pin 0  -> GND Pin
 *    Pin 5  -> Button
 *    Pin 7  -> Red LED     
 *    Pin 8  -> CS Pin
 *    Pin 9  -> CD Pin
 *    Pin 11 -> DI Pin
 *    Pin 12 -> DO Pin
 *    Pin 13 -> SCK Pin
 *    Pin 18 -> Green LED
 *    3.3V   -> VCC Pin
 *    AGND   -> Analog Device
 *    A0     -> Analog Device
 * 
 * Jack Forney
 * ME195A Assistive Bionic Joint Project
 * 06Nov16
 */

#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"
SdFat SD;

File data;
char fileName[] = "data.txt"; 

const uint8_t chipSelect = 8;
const uint8_t cardDetect = 9;
const uint8_t recordButton = 5;
const uint8_t redLED = 7;
const uint8_t greenLED = 18;
const uint8_t pot = A0;
//const byte delay_interval = 10;

bool alreadyBegan = false;

////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  while (!Serial);  // Wait for serial port to connect
  
  pinMode(cardDetect, INPUT);
  pinMode(recordButton, INPUT_PULLUP);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED, LOW);
  
  initializeCard();
}

////////////////////////////////////////////////////////////////////////////////
void loop()
{
  // Make sure the SD card is still there
  if (!digitalRead(cardDetect)){
    initializeCard();
  }
  
  // if the button is pressed, start recording
  if (digitalRead(recordButton) == LOW){
      Serial.print("Button Pressed. ");
      while(digitalRead(recordButton)==LOW); // wait until button is released to start recording.
      delay(1000);
      recordData();
    }
  }



////////////////////////////////////////////////////////////////////////////////
// Subroutine borrowed from SD reader example
// Do everything from detecting card through opening the demo file
////////////////////////////////////////////////////////////////////////////////
void initializeCard(void){
  Serial.print(F("Initializing SD card..."));

  // Is there even a card?
  if (!digitalRead(cardDetect))
  {
    Serial.println(F("No card detected. Waiting for card."));
    while (!digitalRead(cardDetect));
    delay(250); // 'Debounce insertion'
  }

  // Card seems to exist.  begin() returns failure
  // even if it worked if it's not the first call.
  if (!SD.begin(chipSelect) && !alreadyBegan){  // begin uses half-speed...
    Serial.println(F("Initialization failed!"));
    initializeCard(); // Possible infinite retry loop is as valid as anything
  }
  else{
    alreadyBegan = true;
  }
  
  Serial.println(F("Initialization done."));

  Serial.print(fileName);
  
  if (SD.exists(fileName)){
    Serial.println(F(" exists."));
  }
  
  else{
    Serial.println(F(" doesn't exist. Creating."));
  }

  Serial.print("Opening file: ");
  Serial.println(fileName);

  digitalWrite(greenLED,HIGH);
  Serial.println(F("Press Button to start recording data"));
}


// Records data from the analong input pins and writes them to the SD card
void recordData(){
  byte pot_val;
  unsigned long start_time, interval_time;
  String dataString;
  
  start_time = micros();
  Serial.println("Recording...");
  data.write("New dataset");
  //byte count = 0;
  while(digitalRead(recordButton)==HIGH){
    digitalWrite(redLED,HIGH);
    dataString = "";
    pot_val = analogRead(pot);
    interval_time = micros()-start_time;
    //count++;

    //dataString += String(count); // display count just for debug purposes
    //dataString += ": ";
    dataString += String(interval_time);
    dataString += ",";
    dataString += String(pot_val);
    
    
    data = SD.open(fileName, FILE_WRITE);
    if (data){
      data.println(dataString);
      //delay(delay_interval);
      data.close();
      Serial.println(dataString);
    }
    else {Serial.println("Could not open file");}
    
  }
  Serial.println("File closed.");
  digitalWrite(redLED, LOW);
  delay(1000);
  return;    
  }


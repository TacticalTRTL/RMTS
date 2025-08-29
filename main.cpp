#include <Arduino.h>
#include <HX711.h>
#include <cmath>

HX711 scale;

int force = 0;

const int dtPin = 2; //data pin (input)
const int sckPin = 4; // clock pin (output)

int startTime = 0;//start time
int currentTime = 0; //current time 
const int durationTime = 10000; //units are ms
const int durationTimeSec = 10;
const int sampleInterval = 100;//ms

//initializing
void setup() {
    Serial.begin(9600);//baud rate
    pinMode(dtPin, INPUT);//sets dtPin as input
    pinMode(sckPin, OUTPUT);//sets clock pin as input
    Serial.println("Initializing: ");//lets you know its starting

    scale.begin(dtPin, sckPin);
    scale.set_scale();//needs known weight to calibrate 
    scale.tare();//zeroes but still calibrated for known weight

    unsigned long startTime = millis();//stores a clock from time of initialization in ms
    startTime = startTime/1000;
    Serial.println("Initializiation Complete: ");//states when set up is done
}

void loop() {
    unsigned long currentTime = millis();
    currentTime = currentTime/1000;

    if (currentTime >= durationTimeSec) {//checks if thrust is over
        Serial.println("Complete"); //lets you know it is done measuring
        while (true) {} //does nothing to prevent a bunch of 0's
    }

    if (currentTime <= durationTimeSec) {//loop that measures the thrust
        int rawReading = scale.read();
        //int negTarWeight = scale.get_value(); //not sure if needed yet
        //float force = scale.read_average(10);//takes 10 ADC samples increase samples to reduce noise
        //int force = scale.get_units();//gets calibrated units
        Serial.print(currentTime);//print current time
        Serial.print(": ");
        Serial.println(rawReading);//prints the thrust
        delay(sampleInterval);//I think removing delay and doing average read will be better.
    }
    
}
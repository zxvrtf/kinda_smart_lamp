#include <Arduino.h>

#define pwmPin 5

enum lampState {
    IDLE,
    CHANGE_BRIGHTNESS,
};

lampState programState = IDLE;

void setup() {
    Serial.begin(9600);
    pinMode(pwmPin, OUTPUT);
}


void loop() {
   if (Serial.available() && programState == IDLE) {
       char c = Serial.read();
       if (c == '?') {
           Serial.println("LAMP");
       } else if (c == 'b') {
           programState = CHANGE_BRIGHTNESS;
       }
   } else if (Serial.available() && programState == CHANGE_BRIGHTNESS) {
       analogWrite(pwmPin, Serial.read());
       programState = IDLE;
   }
}

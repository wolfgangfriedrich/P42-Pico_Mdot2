/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 11 Aug 2024
  by Wolfgang Friedrich for M.2 Pico

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <Arduino.h>

#include "P42-Pico-mdot2.h"

uint8_t Blink_TPs[] = {TP1, TP2, TP3, TP4, TP5, TP6, TP8, TP10, TP11, TP12, TP13, TP14, TP15, TP17, TP19, TP21 };


// the setup function runs once when you press reset or power the board
void setup() {

uint32_t i;

	// initialize digital pins.
	pinMode(LED, OUTPUT);
  for ( i=0; i<sizeof(Blink_TPs); i++ ) {
    pinMode( Blink_TPs[i], OUTPUT );
  }
	//pinMode(TP11, OUTPUT);

	Serial.begin(115200);
	//while (!Serial) ;
	delay(1000);    // wait for serial port to be configured

	Serial.println("");
	Serial.print(F("P42 Pico M.2 Tester V"));
	Serial.println(PICO_MDOT2_VERSION);


}

// the loop function runs over and over again forever
void loop() {

uint32_t  i,j;
uint8_t   b_IncomingByte = 0;   // for incoming serial data

	digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  for ( i=0; i<sizeof(Blink_TPs); i++ ) {
    digitalWrite( Blink_TPs[i], LOW );
  }
	// digitalWrite(TP11, LOW);  // turn TP11 off
	delay(1000);                      // wait for a second
	digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  for ( i=0; i<sizeof(Blink_TPs); i++ ) {
    digitalWrite( Blink_TPs[i], HIGH );
  }
	// digitalWrite(TP11, HIGH);  // turn TP11 on
	delay(1000);                      // wait for a second
}

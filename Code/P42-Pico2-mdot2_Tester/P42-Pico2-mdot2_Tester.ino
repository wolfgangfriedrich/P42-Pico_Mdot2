/*
  Tester

  Testing all functions of the P42-Pico2-m.2 board
  
  Version
  0.1: 27. Jan 2025
       Moved code to RP2350 Pico2 board
  0.2: 11. Mar 2025
       Added proper I2C command: bus scan
       Test function is data write and read from I2C EEPROM 24C02
	   
*/
#include <Arduino.h>
#include <Wire.h>
// for SD card
#include <SPI.h>
#include <SD.h>
#include "tools.h"
#include "P42-Pico2-mdot2.h"

//uint8_t TPs[] = {TP1, TP2, TP3, TP4, TP5, TP6, TP8, TP10, TP11, TP12, TP13, TP14, TP15, TP17, TP19, TP21 };
uint8_t TPs[] = {TP1, TP2, TP6, TP8, TP9, TP11, TP12, TP13, TP14, TP15, TP17, TP19, TP21 }; // Rev 2 without QWIIC and Serial2
// uint8_t TPs[] = {TP1, TP2 }; // test

uint32_t start_time = 0;
uint32_t current_time = 0;
bool SDcard_present = false;
File root;





// the setup function runs once when you press reset or power the board
void setup() {

uint32_t i;

	current_time = millis();
	start_time = current_time;

	Serial.begin(19200);
  Serial.setTimeout(10000);   // set timeout to 10 sec
	//Terminal program need local echo now!
	delay(1000);    // wait for serial port to be configured

	Serial.println("");
	Serial.print(F("P42 Pico2 M.2 Tester"));
	Serial.println(PICO_MDOT2_VERSION);

  // Board IOs
 	pinMode(LED, OUTPUT);
  digitalWrite( LED, HIGH );
 	pinMode(ENABLE, INPUT);

Serial.println(F(" [OK] Board GPIO config done."));

// Serial config
// UART0 in schematic is Serial1 in code
// UART1 in schematic is Serial2 in code

  // assign pin numbers for Serial2
  Serial2.setTX(M2_UART_TXD);  
  Serial2.setRX(M2_UART_RXD);
  Serial2.begin(19200);
  Serial2.println("P42 Pico M.2 UART1");

//Serial2.setTX(TX2);  
//Serial2.setRX(RX2);
//Serial2.begin(19200);    // slow baud rate to make the transfer visible on DMM
//Serial2.println("P42 Pico M.2 UART2");

Serial.println(F(" [OK] Serial config done."));


// I2C config
// I2C0 in schematic is Wire in code
// I2C1 in schematic is Wire1 in code
  Wire1.setSDA(QWIIC_SDA);
  Wire1.setSCL(QWIIC_SCL);
  Wire1.begin(); // join i2c bus as master
  // Serial.print(".");
  Wire1.onReceive(receiveEvent1); // register event


  Wire.setSDA(M2_I2C_SDA);
//Serial.print(".");
  Wire.setSCL(M2_I2C_SCL);
//Serial.print(".");
  // Wire.begin(I2C_ADR); // join i2c bus (address optional for master)
  Wire.begin(); // join i2c bus (address optional for master)
//Serial.print(".");
Wire.onReceive(receiveEvent); // register event

  Serial.println(F(" [OK] I2C config done."));


// M.2 Signals
pinMode (N_UART_WAKE, OUTPUT);
digitalWrite(N_UART_WAKE, HIGH);
pinMode (N_I2C_ALERT, OUTPUT);
digitalWrite(N_I2C_ALERT, HIGH);
pinMode (N_LED1, INPUT);
pinMode (N_LED2, INPUT);
pinMode (N_DISABLE1, INPUT_PULLUP);
pinMode (N_DISABLE2, INPUT_PULLUP);

Serial.println(F(" [OK] M.2 GPIO config done."));

// uSD card
SPI1.setRX(SD_DI);
SPI1.setCS(SD_CS);
SPI1.setSCK(SD_CLK);
SPI1.setTX(SD_DO );

Serial.print(F(" SPI config SPI1 /"));
Serial.print(F(" SPI CS: "));
Serial.print(SD_CS);
Serial.print(F(" / SPI CLK: "));
Serial.print(SD_CLK);
Serial.print(F(" / SPI DO: "));
Serial.print(SD_DO);
Serial.print(F(" / SPI DI: "));
Serial.println(SD_DI);

pinMode (SD_DETECT, INPUT_PULLUP);

if ( digitalRead(SD_DETECT) == HIGH) {
  Serial.println(F(" [!!] No uSD card present!"));
  SDcard_present = false;
}
else {
  Serial.println(F(" [OK] SDcard config done."));
  // https://github.com/earlephilhower/arduino-pico/discussions/925
  sd_cardInit();
  sd_cardInfo();
  root = SD.open("/");
  printDirectory(root, 0);

  SDcard_present = true;

  // for exFAT cards, use:
  // https://github.com/greiman/SdFat
}
//  sd_cardInit();

	Serial.print(F("Config done. READY.\n\r>") );
  digitalWrite( LED, LOW );

}

 // the loop function runs over and over again forever until it doesn't
void loop() {

uint32_t  i,j, result;
uint8_t   b_IncomingByte = 0;   // for incoming serial data

char cmd[32];
char pin = 0xff;
char c;

  if (!SDcard_present && (digitalRead(SD_DETECT) == LOW) ) {
    SDcard_present = true;
    sd_cardInit();
    Serial.print(">");
  }
  else if (SDcard_present && (digitalRead(SD_DETECT) == HIGH)) {
    SDcard_present = false;
    Serial.println(F("uSD Card removed!"));
    Serial.print(">");
  }

	while (Serial2.available() != 0) {
		b_IncomingByte = Serial2.read();
    Serial.print((char)b_IncomingByte);

  }

	if (Serial.available() != 0) {

		//b_IncomingByte = Serial.read();
     result = Serial.readBytesUntil(13, cmd, 31); 
     cmd[result] = 0;     // terminate


		switch (cmd[0]) {

			case CMD_LED:
        // Serial.print(CMD_LED);
				// read next byte 
				//while (Serial.available() == 0) {};
				//b_IncomingByte = Serial.read();
        pinMode(LED, OUTPUT);

        if (cmd[1] == '0') {
          Serial.println("0\r\nLED off");
          digitalWrite( LED, LOW );
        }
        else if (cmd[1] == '1') {
          Serial.println("1\r\nLED on");
          digitalWrite( LED, HIGH );
        }
        else {
          Serial.println("\r\nBad argument. Try again!");
        };

			break;

			case CMD_VERSION:
        //Serial.print(CMD_VERSION);
				Serial.print(F("\r\nPier42 Pico2 M.2 (c) "));
				Serial.print(PICO_MDOT2_VERSION_DATE);
				Serial.println(PICO_MDOT2_VERSION);
			break;

			case CMD_HELP:
        //Serial.print(CMD_HELP);
				Serial.println(F("\r\nl[0/1] Turn LED on or off"));
				Serial.println(F("v      Show Version"));
				Serial.println(F("u      UART test - M.2 TX RX - UART1 loopback"));
				Serial.println(F("i[0/1] I2C bus scan"));
				Serial.print(F("g[0.."));
        c = sizeof(TPs)+'A'-11;
        Serial.print(c);
//        Serial.print((char)sizeof(TPs)+'A'-11);
        Serial.println(F("][0/1] GPIOs go tooooogle."));
				Serial.println(F("s      uSD card test"));
				Serial.println(F("d      uSD card root directory"));
				Serial.println(F("m      Scan all M.2 Interface GPIOs"));
				Serial.println(F("t      runs unspecified test code"));
				Serial.println(F("?      This help command"));
			break;

			case CMD_UART:
      // Serial1 is M.2 UART port connected to  external USB-UART adapter 
      // Keys entered in the external USB-UART adapter before entering the 'u' command in the Tester terminal will be displayed. 
      // FIFO size = 16 bytes
        //Serial.println(CMD_UART);

				// Serial.println(F("\r\nSerial1:"));
//        Serial1.flush(); // not a loopback so no flush() allowed to display character that are received.
        // Serial1.println("[OK] Test Serial1.");
        delay (100);    // wait 10msec for some data to arrive
				// while (Serial1.available() != 0) {
				  // b_IncomingByte = Serial1.read();
          // Serial.write(b_IncomingByte);
        // };
        // some subcommands:
        // loopback: send something and expect the same back
        // send cmd to expect ascii '0'-'9' back
        // send cmd to expect 0x55 0xaa 0xaf 0xfe back
        // send cmd to expect 0xc0 0xff 0xee back

        //Serial2 is a simple loopback, all received chars to be sent to Tester Serial command port terminal
        Serial2.flush();
        delay (100);
        // manual flush
        while(Serial2.available() > 0) {
          char t = Serial2.read();
        }
  			Serial.println(F("\r\nSerial2:"));
        Serial2.println("Test 1234567890.");
        delay (200);    // wait 200msec for some data to arrive
				while (Serial2.available() != 0) {
				  b_IncomingByte = Serial2.read();
          Serial.write(b_IncomingByte);
        };

			break;

			case CMD_I2C:
        //  Test when m.2 I2C is wired to QWIIC, careful with the voltages.
        //Serial.print(CMD_I2C);
				Serial.printf(("\r\nI2C Scan Wire%d \r\n"),cmd[1]-'0');

        if (cmd[1] == '0') {
    		  I2C_scan(0);
        }
        else if (cmd[1] == '1') {
    		  I2C_scan(1);
        }
        else {
          Serial.println("\r\nBad argument. Try again!");
        };

		
			break;

			case CMD_GPIO:
        //Serial.print(CMD_GPIO);
				Serial.println(F("\r\nGPIO test."));
        if ( cmd[1] >= 'a' && cmd[1] <= 'f' ) 
          pin = cmd[1]-'a' + 10;
        else if ( cmd[1] >= 'A' && cmd[1] <= 'F' ) 
          pin = cmd[1]-'A' + 10;
        else if ( cmd[1] >= '0' && cmd[1] <= '9' ) 
          pin = cmd[1]-'0';
        else {
          Serial.println("Bad pin. Try again!");
          break;
        }

        if (pin > (sizeof( TPs ) - 1) ) {
          pin = 0xff;
          Serial.println("Bad pin. Try again!");
          break;
        }
        else {
          pin = TPs[pin];
        }

        if (cmd[2] == '0') {
          Serial.print("GP");
          Serial.print( (int)pin );
          Serial.println(" off");
          pinMode (pin, OUTPUT);
          digitalWrite( pin, LOW );
        }
        else if (cmd[2] == '1') {
          Serial.print("GP");
          Serial.print( (int)pin );
          Serial.println(" on");
          pinMode (pin, OUTPUT);
          digitalWrite( pin, HIGH );
        }
        else {
          Serial.println("Bad argument. Try again!");
        };



			break;

			case CMD_SD:
        //Serial.print(CMD_SD);
				Serial.println(F("\r\nSDcard test."));
        if ( digitalRead(SD_DETECT) == HIGH) {
          Serial.println(F("No uSD card present!"));
        }
        else {
  				// https://github.com/earlephilhower/arduino-pico/discussions/925
          sd_cardTest();
          sd_cardSpeedTest();

          // for exFAT cards, use:
          // https://github.com/greiman/SdFat
        }

//          sd_cardTest();
        
        // write speed test
//        sd_cardSpeedTest();


			break;

			case CMD_DIR:
        //Serial.print(CMD_SD);
				Serial.println(F("\r\nSDcard root directory."));
				if ( !SDcard_present) {
				  Serial.println(F("No uSD card present!"));
				}
				else {
					root = SD.open("/");
					printDirectory(root, 0);
				}
			break;

			case CMD_MDOT2:
				
        //Serial.print(CMD_SD);
				Serial.println(F("\r\nM.2-GPIO Control/Status signal check."));
				Serial.println(F("\r\n3 = HIGH / -3 = LOW / 0 = TRI-STATE"));
				Serial.printf("nDISABLE1 (GP%d):\t%d\r\n", N_DISABLE1, Mdot2_IO_scan(N_DISABLE1)); 
				Serial.printf("nDISABLE2 (GP%d):\t%d\r\n", N_DISABLE2, Mdot2_IO_scan(N_DISABLE2)); 
				Serial.printf("nI2C_ALERT (GP%d):\t%d\r\n", N_I2C_ALERT, Mdot2_IO_scan(N_I2C_ALERT)); 
				Serial.printf("nUART_WAKE (GP%d):\t%d\r\n", N_UART_WAKE, Mdot2_IO_scan(N_UART_WAKE)); 
				Serial.printf("nLED2 (GP%d):\t%d\r\n", N_LED2, Mdot2_IO_scan(N_LED2)); 
				Serial.printf("nLED1 (GP%d):\t%d\r\n", N_LED1, Mdot2_IO_scan(N_LED1)); 
				
				Serial.println(F("\r\n\r\nGPIO signal check."));
				for (i=0; i < sizeof(TPs); i++){
					Serial.printf("TP%d (GP%d):\t%d\r\n", i, TPs[i], Mdot2_IO_scan(TPs[i])); 
				}
				
				
			break;

      case CMD_TEST:
        test_code();
      break;

      default:
	  		Serial.println(F("\r\nNo Command :("));
	    break;
    } // switch
    cmd[0] = 0;
		Serial.print(F(">"));
		while (Serial.available()) { Serial.read(); };    // flush serial input
  } // if serial
  else {
  
  };

}

// from https://wiki-content.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent1(int howMany)
{
  while(1 < Wire1.available()) // loop through all but the last
  {
    char c = Wire1.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire1.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}


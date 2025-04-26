// Support File for P42 Pico2 M.2 Tester
// SDcard 
// I2C scanner
// GPIO scanner
// Test function
// (c) Pier42 Electronics Design

// written by
// Wolfgang Friedrich
// Last change: 2025/Mar/11

#include <stdlib.h>

#include <Arduino.h>
#include <Wire.h>
// for SD card
#include <SPI.h>
#include <SD.h>

#include "P42-Pico2-mdot2.h"

#include "tools.h"


//----------------------------------------------------------------------
void sd_cardInit(void){
    Serial.println("Initializing SD card...");
delay (2000);
    if (!(SD.begin(SD_CS, SPI1))) {
        Serial.println("initialization failed!");
       // while (1);
       
    }
    else {
      Serial.println(" SD initialization done.");
    }
}

File myFile;

//----------------------------------------------------------------------
void sd_cardTest(void) {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.seek(0);
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.print(myFile.read());
    }
    // close the file:
    myFile.close();
    Serial.println();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


//----------------------------------------------------------------------
void sd_cardSpeedTest(void) {

uint8_t data_8bit=8;
uint16_t data_16bit=16;
uint32_t data_32bit=3141;

char array512[513];

uint32_t StartTime;
uint32_t CurrentTime;

uint32_t i = 0;
uint32_t FileSize = 0;

  Serial.println("SD Card Speed Test...");

  if ( SD.exists("byte.txt") ) {
    SD.remove("byte.txt");
  }
  if ( SD.exists("16bit.txt") ) {
    SD.remove("16bit.txt");
  }
  if ( SD.exists("32bit.txt") ) {
    SD.remove("32bit.txt");
  }
  if ( SD.exists("speed.txt") ) {
    SD.remove("speed.txt");
  }

// 8-bit write test
  myFile = SD.open("byte.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to byte.txt...");
    StartTime = millis();
    for (i=0; i < 1024*1024; i++) {
      myFile.print (data_8bit);           // writes number of digits worth of bytes
//      data_8bit = (data_8bit++);// % 10;
    };
    Serial.println("done.");
    CurrentTime = millis();
    FileSize = myFile.size();

    // close the file:
    myFile.close();
    Serial.print("Duration [millisec]: ");
    Serial.println(CurrentTime - StartTime);
    Serial.print("FileSize [bytes]: ");
    Serial.println(FileSize);
    Serial.print("Write Speed(8bit) [KByte/sec]: ");
    Serial.println((FileSize/1024)/((CurrentTime - StartTime)/1000  ) );
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening byte.txt");
  }

  myFile = SD.open("16bit.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to 16bit.txt...");
    StartTime = millis();
    for (i=0; i < 1024*1024; i++) {
      myFile.print (data_16bit);           // writes number of digits worth of bytes
//      data_8bit = (data_8bit++);// % 10;
    };
    Serial.println("done.");
    CurrentTime = millis();
    FileSize = myFile.size();

    // close the file:
    myFile.close();
    Serial.print("Duration [millisec]: ");
    Serial.println(CurrentTime - StartTime);
    Serial.print("FileSize [bytes]: ");
    Serial.println(FileSize);
    Serial.print("Write Speed(16bit) [KByte/sec]: ");
    Serial.println((FileSize/1024)/((CurrentTime - StartTime)/1000  ) );
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening 16bit.txt");
  }

//32-bit write test
  myFile = SD.open("32bit.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to 32bit.txt...");
    StartTime = millis();
    for (i=0; i < 1024*1024; i++) {
      myFile.print (data_32bit);           // writes number of digits worth of bytes
//      data_8bit = (data_8bit++);// % 10;
    };
    Serial.println("done.");
    CurrentTime = millis();
    FileSize = myFile.size();

    // close the file:
    myFile.close();
    Serial.print("Duration [millisec]: ");
    Serial.println(CurrentTime - StartTime);
    Serial.print("FileSize [bytes]: ");
    Serial.println(FileSize);
    Serial.print("Write Speed(32bit) [KByte/sec]: ");
    Serial.println((FileSize/1024)/((CurrentTime - StartTime)/1000  ) );
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening 32bit.txt");
  }

  //high speed write test
  for (i=0; i<512; i++) {
    array512[i] = (char) (i && 0xff);
  }
  array512[513] = '\0';

  myFile = SD.open("speed.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to speed.txt...");
    StartTime = millis();
    for (i=0; i < 8*1024; i++) {
      array512[0] = i;
      myFile.print ( array512);           // writes number of digits worth of bytes
//      data_8bit = (data_8bit++);// % 10;
    };
    Serial.println("done.");
    CurrentTime = millis();
    FileSize = myFile.size();

    // close the file:
    myFile.close();
    Serial.print("Duration [millisec]: ");
    Serial.println(CurrentTime - StartTime);
    Serial.print("FileSize [bytes]: ");
    Serial.println(FileSize);
    Serial.print("Write Speed(32bit) [KByte/sec]: ");
    Serial.println((FileSize/1024)/((CurrentTime - StartTime)/1000  ) );
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening speed.txt");
  }



}

//----------------------------------------------------------------------
void sd_cardInfo() {
  // 0 - SD V1, 1 - SD V2, or 3 - SDHC/SDXC
  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (SD.type()) {
    case 0:
      Serial.println("SD1");
      break;
    case 1:
      Serial.println("SD2");
      break;
    case 3:
      Serial.println("SDHC/SDXC");
      break;
    default:
      Serial.println("Unknown");
  }

  Serial.print("Cluster size:          ");
  Serial.println(SD.clusterSize());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(SD.blocksPerCluster());
  Serial.print("Blocks size:  ");
  Serial.println(SD.blockSize());

  Serial.print("Total Blocks:      ");
  Serial.println(SD.totalBlocks());
  Serial.println();

  Serial.print("Total Cluster:      ");
  Serial.println(SD.totalClusters());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(SD.fatType(), DEC);

  volumesize = SD.totalClusters();
  volumesize *= SD.clusterSize();
  volumesize /= 1000;
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.print("Card size:  ");
  Serial.println((float)SD.size() / 1000);

  FSInfo fs_info;
  SDFS.info(fs_info);

  Serial.print("Total bytes: ");
  Serial.println(fs_info.totalBytes);

  Serial.print("Used bytes: ");
  Serial.println(fs_info.usedBytes);

}

//----------------------------------------------------------------------
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      time_t cr = entry.getCreationTime();
      time_t lw = entry.getLastWrite();
      struct tm* tmstruct = localtime(&cr);
      Serial.printf("\tCREATION: %d-%02d-%02d %02d:%02d:%02d", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
      tmstruct = localtime(&lw);
      Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    }
    entry.close();
  }
}


//----------------------------------------------------------------------
int8_t I2C_scan( uint8_t bus_nr )
{
  byte error, address;
  int nDevices;
 
  // Serial.print("Scanning Wire");
  // Serial.println(bus_nr);
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    if ( bus_nr == 0) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
    }
    else if ( bus_nr == 1) {
      Wire1.beginTransmission(address);
      error = Wire1.endTransmission();
    }
    else
      return -1;

 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(".");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found.");
  else
    Serial.println("done.");

  return nDevices;
 
}


//----------------------------------------------------------------------
// Scan the GPIO pin for level high, low or open
// return 2(hi),-1(lo),0(open)
// !!! VERY EXPERIMENTAL !!!
// with work-around for E9 Erratum 
int8_t Mdot2_IO_scan(int8_t GPIO)
{
int8_t GPIO_level, GPIO_value;

  GPIO_level = 0;

  // pinMode(GPIO, OUTPUT);
  // digitalWrite(GPIO, '0');
  // delay(10);

  pinMode(GPIO, INPUT_PULLUP);
  GPIO_value = digitalRead(GPIO);
//  delay(100);
  // Serial.printf("%d", GPIO_value);
  switch (GPIO_value) {
    case HIGH:
      GPIO_level ++;
      break;
    case LOW:
      GPIO_level --;
      break;
    default:
      break;
  }

  // pinMode(GPIO, OUTPUT);
  // digitalWrite(GPIO, '1');
  // delay(10);

  pinMode(GPIO, INPUT_PULLDOWN);
  GPIO_value = digitalRead(GPIO);
//  delay(100);
  // Serial.printf("%d", GPIO_value);
  switch (GPIO_value) {
    case HIGH:
      GPIO_level ++;
      break;
    case LOW:
      GPIO_level --;
      break;
    default:
      break;
  }
  if ( GPIO_level != 0 ) {
    pinMode(GPIO, INPUT);
	GPIO_value = digitalRead(GPIO);
//    delay(100);
  // Serial.printf("%d", GPIO_value);
    switch (GPIO_value) {
      case HIGH:
        GPIO_level ++;
        break;
      case LOW:
        GPIO_level --;
        break;
      default:
        break;
    } 
  };
  // else
	// Serial.printf(".");

  return GPIO_level;
}


//----------------------------------------------------------------------
void test_code()
							  
								 
{

  byte incomingByte = 0;   // for incoming serial data
  unsigned long i,j = 0;

	// Serial.println(F("Press Key to Start!"));		// This is to stop the program when a new one is compiling and overwrite the content
  // while (Serial.available() == 0) {};
  // incomingByte = Serial.read();
  

  // I2C EEPROM memory test

  // check if device is connected
  Wire.beginTransmission(0x50);		// 7bit address without R/W bit
  if (Wire.endTransmission() == 0) {




  Wire.beginTransmission(0x50);		// 7bit address without R/W bit
//  incomingByte = Wire.write(0x04);					// memory address
//  	Serial.print(incomingByte, HEX);
  Wire.write(0x00);					// memory address
  Wire.write(0xaf); 					// DPO2COMP 
  Wire.write(0xfe); 					// DPO2COMP 
  Wire.write(0xd0); 					// DPO2COMP 
  Wire.write(0x0f); 					// DPO2COMP 
  Wire.write( (uint8_t) random(0,255) ); 					// DPO2COMP 
  Wire.write( (uint8_t) random(0,255) ); 					// DPO2COMP 
  Wire.write( (uint8_t) random(0,255) ); 					// DPO2COMP 
  Wire.write( (uint8_t) random(0,255) ); 					// DPO2COMP 
  // Wire.write('D'); 					// DPO2COMP 
  // Wire.write('P'); 
  // Wire.write('O'); 
  // Wire.write('4'); 
  // Wire.write('E'); 
  // Wire.write('M'); 
  // Wire.write('B'); 
  // Wire.write('D'); 
  // Wire.write(0x00); 
  Wire.endTransmission();
  
  delay(100);
   
 
  // Wire.begin(); // wake up I2C bus
  Wire.beginTransmission(0x50);
  Wire.write(0x00); // memory address 0
  Wire.endTransmission();
  delay(1);

  incomingByte = 0x00;
  for (i=0; i<=0x0d; i++) {
    Wire.requestFrom(0x50, 1); // 7-bit addres without R/W bit
    delay(1);
    while(!Wire.available()) 
      {}
    incomingByte = Wire.read();
	  // incomingByte = Wire1.read(); // first received byte stored 
      if (incomingByte<16)
        Serial.print("0");
	  Serial.print(incomingByte, HEX);
	  Serial.print(' ');
	}
  Serial.println();

  Serial.println(F("done EEPROM."));
  }
  else {
    Serial.println(F("No EEPROM on bus."));
  }

}

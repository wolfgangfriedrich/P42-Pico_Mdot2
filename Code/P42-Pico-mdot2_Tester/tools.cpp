// Support File for P42 Pico M.2 Tester
// SDcard and I2C scanner
// (c) Pier42 Electronics Design

// written by
// Wolfgang Friedrich
// Last change: 2025/Jan/30

#include <Arduino.h>
#include <Wire.h>
// for SD card
#include <SPI.h>
#include <SD.h>

#include "P42-Pico-mdot2.h"

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
uint8_t I2C_scan()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();
 
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
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  return nDevices;
 
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
  Wire1.begin(); // wake up I2C bus
  Wire1.beginTransmission(0x50);		// 7bit address without R/W bit
 incomingByte = Wire1.write(0x04);					// memory address
 	Serial.print(incomingByte, HEX);
  Wire1.write('D'); 					// DPO2COMP 
  Wire1.write('P'); 
  Wire1.write('O'); 
  Wire1.write('4'); 
  Wire1.write('E'); 
  Wire1.write('M'); 
  Wire1.write('B'); 
  Wire1.write('D'); 
  Wire1.write(0x00); 
  Wire1.endTransmission();
  
  delay(100);
   
  // Wire1.begin(); // wake up I2C bus
  // Wire1.beginTransmission(0x52);		// 7bit address without R/W bit
  // Wire1.write(0x04);					// memory address
  // Wire1.write('D'); 					// DPO2EMBD 
  // Wire1.write('P'); 
  // Wire1.write('O'); 
  // Wire1.write('4'); 
  // Wire1.write('C'); 
  // Wire1.write('O'); 
  // Wire1.write('M'); 
  // Wire1.write('P'); 
  // Wire1.write(0x00); 
  // Wire1.endTransmission();
  
  // delay(1000);

  Wire1.begin(); // wake up I2C bus
  Wire1.beginTransmission(0x50);
  Wire1.write(0x00); // memory address 0
  Wire1.endTransmission();

  incomingByte = 0x00;
  Wire1.requestFrom(0x50, 0x0d); // 7-bit addres without R/W bit
  for (i=0; i<=0x0d; i++) {
	incomingByte = Wire1.read(); // first received byte stored 
	Serial.print(incomingByte, HEX);
	Serial.print(' ');
  }
  Serial.println();

  // delay(250);

  // Wire1.begin(); // wake up I2C bus
  // Wire1.beginTransmission(0x52);
  // Wire1.write(0x00); // memory address 0
  // Wire1.endTransmission();

  // incomingByte = 0x00;
  // Wire1.requestFrom(0x52, 0x0d); // 7-bit addres without R/W bit
  // for (i=0; i<=0x0d; i++) {
	// incomingByte = Wire1.read(); // first received byte stored 
	// Serial.print(incomingByte, HEX);
	// Serial.print(' ');
  // }
  Serial.println();

  Serial.println(F("done EEPROM."));
  
  while (Serial.available() == 0) {};
  incomingByte = Serial.read();


	delay(1);
}

#include <Arduino.h>
#include <Wire.h>


void setup() {



  // put your setup code here, to run once:

	Serial.begin(19200);

delay(2000);
  Serial.println("\r\nP42 Pico M.2 Serial1 Wire Tester");

//!!!!! M.2 Pico - NOT Pico2 !!!!!
#define M2_UART_TXD   16
#define M2_UART_RXD   17

  Serial1.setTX(M2_UART_TXD);  
  Serial1.setRX(M2_UART_RXD);
  Serial1.begin(19200);
  Serial1.println("P42 Pico M.2 UART1");

//!!!!! M.2 Pico - NOT Pico2 !!!!!
#define M2_I2C_SDA    20
#define M2_I2C_SCL    21

  Wire.setSDA(M2_I2C_SDA);
//Serial.print(".");
  Wire.setSCL(M2_I2C_SCL);
//Serial.print(".");
  Wire.begin(40); // join i2c bus (address optional for master)
  // Wire.setClock(100000);

Wire.onReceive(receiveEvent); // register event

I2C_scan();

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




void loop() {
  // put your main code here, to run repeatedly:
uint8_t   b_IncomingByte = 0;   // for incoming serial data
uint8_t   i;

i++;

	while (Serial1.available() != 0) {
		b_IncomingByte = Serial1.read();
    Serial.print( (char) b_IncomingByte );
  }

Serial1.println("M.2 UART data");

        Wire.beginTransmission(0x42);  // transmit to device #4
        Wire.write("M.2 I2C 3.1)");         // sends bytes, last on is printed ASCII code!
        Wire.endTransmission();     // stop transmitting

Serial.print(".");

	delay(5000);    // wait for serial port to be configured

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
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
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

// PicoM.2Tools header file
// (c) Pier42 Electronics Design
//     https://www.tindie.com/stores/pier42/

// written by
// Wolfgang Friedrich
// Rev Start 2025/Jan/30
// Last change: 2025/Jan/30

#ifndef Mdot2Tools_h
#define Mdot2Tools_h

//File myFile;
//File root;


void sd_cardInit(void);
void sd_cardTest(void);
void sd_cardSpeedTest(void);
void sd_cardInfo();
void printDirectory(File dir, int numTabs);
int8_t I2C_scan( uint8_t bus_nr );
int8_t Mdot2_IO_scan(int8_t GPIO);
void test_code();

#endif

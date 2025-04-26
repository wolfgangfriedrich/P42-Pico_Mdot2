// Pico_M.2 header file for all P42-Pico2-M.2 project Rev2 and up  
// (c) Pier42 Electronics Design
//     https://www.tindie.com/stores/pier42/


// written by
// Wolfgang Friedrich
// Rev Start 2024/Aug/08
// Last change: 2025/Mar/11

#ifndef P42Pico2_mdot2_h
#define P42Pico2_mdot2_h

#define PICO_MDOT2_VERSION " V1.0"
#define PICO_MDOT2_VERSION_DATE "26. April 2025"

// Board Features
#define TP15           0
#define TP14           1
#define QWIIC_SDA      2
#define TP5            2
#define QWIIC_SCL      3
#define TP4            3
#define TP12           4
#define SD_DETECT      5
#define TP3            5
#define ENABLE         6
#define TP2            6
#define LED            7
#define TP1            7
#define TP6            8
#define TP8            9
#define SD_CS         13
#define SD_DI         12
#define SD_DO         11
#define SD_CLK        10
#define TP9           14
#define TP11          15
#define TP13          16
#define TP17          17
#define N_DISABLE1    18
#define N_DISABLE2    19
#define M2_I2C_SDA    20
#define M2_I2C_SCL    21
#define N_I2C_ALERT   22
#define N_UART_WAKE   23
#define M2_UART_TXD   24
#define M2_UART_RXD   25
#define N_LED2        26
#define N_LED1        27
#define TP19          28
#define TP21          29

#define ADC0          26
#define ADC1          27
#define ADC2          28
#define ADC3          29

// UART pins for testing Pico UART0 on GP0(TX) and GP1(RX)
#define TX2 0
#define RX2 1

// I2C
#define M2_I2C_ADR     0x42
#define QWIIC_I2C_ADR  0x43


// Commands
#define CMD_LED       'l'    // l[0/1]
#define CMD_VERSION   'v'
#define CMD_HELP      '?'
#define CMD_UART      'u'
#define CMD_I2C       'i'
#define CMD_GPIO      'g'
#define CMD_SD        's'
#define CMD_DIR       'd'
#define CMD_MDOT2     'm'
#define CMD_TEST      't'

#endif
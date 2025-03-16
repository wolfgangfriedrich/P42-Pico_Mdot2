// Pico_M.2 header file for all P42-Pico-M.2 projects 
// (c) Pier42 Electronics Design
//     https://www.tindie.com/stores/pier42/


// written by
// Wolfgang Friedrich
// Rev Start 2024/Aug/08
// Last change: 2025/Feb/1

#ifndef P42Pico_mdot2_h
#define P42Pico_mdot2_h

#define PICO_MDOT2_VERSION " V0.5"
#define PICO_MDOT2_VERSION_DATE "1. Feb 2025"

#define Board_SN1 1
//#define Board_SN2  2
//#define Board_SN3  3

// Board Features
//      Signal         GPx
#define TP15           0
#define TP13           1
#define TP11           2
#define SD_DETECT      3
#define TP3            3
#define QWIIC_SDA      4
#define TP4            4
#define QWIIC_SCL      5
#define TP5            5
#define ENABLE         6
#define TP2            6
#define LED            7
#define TP1            7
#define TP6            8
#define TP8            9
#define SD_CS         13//17
#define SD_DI         12//16
#define SD_DO         11//19
#define SD_CLK        10//18
#define TP10          14
#define TP12          15
#define M2_UART_TXD   16  // Pico UART0 TX
#define M2_UART_RXD   17  // Pico UART0 RX
#define N_DISABLE1    18
#define N_DISABLE2    19
#define I2C_SDA       20
#define I2C_SCL       21
#define N_I2C_ALERT   22
#define N_UART_WAKE   23
#define N_LED2        24
#define N_LED1        25
#define TP14          26
#define TP21          27
#define TP19          28
#define TP17          29

#define ADC0          26
#define ADC1          27
#define ADC2          28
#define ADC3          29

// UART pins for testing Pico UART1 on GP8(TX) and GP9(RX)
#define TX2 8
#define RX2 9


// Commands
#define CMD_LED       'l'    // l[0/1]
#define CMD_VERSION   'v'
#define CMD_HELP      '?'
#define CMD_UART      'u'
#define CMD_I2C       'i'
#define CMD_GPIO      'g'
#define CMD_SD        's'
#define CMD_DIR       'd'
#define CMD_TEST      't'

#endif
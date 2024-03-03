#ifndef REG51_H
#include "reg51.h"
#endif

#include "Timer.h"
 
 
#define UART_ENABLE 				0x01
#define UART_DISABLE				0x00


#define UART_MODE0 					0x00
#define UART_MODE1					0x40
#define UART_MODE2 					0x80
#define UART_MODE3					0xC0
#define UART_SCON_REN				0x10
#define UART_SCON_TB8				0x08
#define UART_SCON_TR8				0x04
#define UART_SCON_TI 				0x02
#define UART_SCON_RI				0x01

/*
 * Macros for selecting Baud Rate
 */
#define UART_BAUD_57600			0xFF
#define UART_BAUD_28800    	0xFE
#define UART_BAUD_9600 			0xFD
#define UART_BAUD_4800 			0xFA
#define UART_BAUD_2400 			0xF4
#define UART_BAUD_1200 			0xE8

static char* pTxBuffer;
static char* pRxBuffer;


void UART_Config(unsigned int,unsigned int);
void UART_EnableOrDisable(unsigned int);
void UART_SendData(char);
void UART_SendString(char*);
char UART_ReceiveData(void);
void UART_SendMemoryData(unsigned int, unsigned int);

void UART_InterruptHandler(void);
void UART_SendDataInt(char*);
void UART_SendStringInt(char*);
char* UART_ReceiveDataInt(void);
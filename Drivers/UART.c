#ifndef UART_H
#include "UART.h"
#define UART_H
#endif

/*
 * Configuring UART 
 */
void UART_Config(unsigned int mode,unsigned int baud_rate){
//	Timer_Handle_t clock_gen;
//	clock_gen.timer=TIMER1;
//	clock_gen.mode=TIMER_MODE2;
	
	if (mode==UART_MODE0)		
		SCON=UART_MODE0;
	else if(mode==UART_MODE1)
		SCON=UART_MODE1;
	else if(mode==UART_MODE2)	
		SCON=UART_MODE2;
	else if(mode==UART_MODE3)
		SCON=UART_MODE3;
	
//	Timer_Config(clock_gen);
	TMOD|=0x20;
	TH1 = baud_rate;	TL1=baud_rate;
	TR1=1;
	if (baud_rate==UART_BAUD_57600){
		PCON|=(1<<7);
	}
	
}

/*
 * API for enabling and disabling the UART peripheral.
 */
void UART_EnableOrDisable(unsigned int status){
	if (status==UART_ENABLE)
		SCON|=UART_SCON_REN;
	else if (status==UART_DISABLE)
		SCON&=~UART_SCON_REN;
}

/*
 * Send Data API.
 */
void UART_SendData(char val){
	SBUF=val;
	while(TI==0); 
	TI=0;
}
/*
 *	Send String API.
 */
void UART_SendString(char* string){
	while(*string != '\0'){
		UART_SendData(*string);
		string++;
	}
}

/*
 * Receive Data API.
 */
char UART_ReceiveData(void){
	char rec_data;
	while(RI==0); 
	RI=0;
	rec_data=SBUF;
	return rec_data;
}

/*
 *	API for sending _data_ to serial port from a specified location.
 */
void UART_SendMemoryData(unsigned int base_addr,unsigned int len){
	
	unsigned int offset=0;
	char* mem_addr;
	
	while(len>0){
		mem_addr=(char*)(base_addr+offset);
		UART_SendData(mem_addr);
		offset++;		len--;
	}
}


/**************************************************************
 *																														*	
 *								API's for UART Interrupt										*		
 *																														*
 **************************************************************/

/*
 *	Branched Interrupt Handler.
 */
void UART_InterruptHandler(void){
	if (TI==1){
		TI=0;
		if (*pTxBuffer!='\0'){
			SBUF=*pTxBuffer;
			pTxBuffer++;
		}
	}
	else if(RI!=0){
		RI=0;
		*pRxBuffer=SBUF;
	}
	else{
		UART_EnableOrDisable(UART_DISABLE);
	}
}
/*
 * Send Data with Interrupt.
 */
void UART_SendDataInt(char *val){
	SBUF=*val;
	if (!(IE&0x10)){
		while(TI==0); 
		TI=0;
	}
}

/*
 *	Send String with Interrupt.
 */
void UART_SendStringInt(char* string){
	while(*string != '\0'){
		UART_SendDataInt(string);
		string++;
		if ((IE&0x10)){
			pTxBuffer=string;
			break;
		}
	}
}

/*
 * Receive Data with Interupt.
 */
char* UART_ReceiveDataInt(void){
	if (!(IE&0x10)){
		while(RI==0); 
		RI=0;
		*pRxBuffer=SBUF;
	}
	return pRxBuffer;
}



	
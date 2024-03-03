#ifndef INTERRUPT_H
#include "Interrupt.h"
#define INTERRUPT_H
#endif

void Interrupt_Config(unsigned int interrupt_type){
	IE|=interrupt_type;
}

void Interrupt_EnableOrDisable(unsigned int status){
	if (status)
		IE|=INTERRUPT_IE_EA;
	else
		IE&=~INTERRUPT_IE_EA;
}
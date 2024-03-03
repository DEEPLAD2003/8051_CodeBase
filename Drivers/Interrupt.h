#ifndef REG51_H
#include "reg51.h"
#endif

#define INTERRUPT_IE_EA						0x80
#define INTERRUPT_IE_EXT0					0x01
#define INTERRUPT_IE_ET0					0x02
#define INTERRUPT_IE_EXT1					0x04
#define INTERRUPT_IE_ET1					0x08
#define INTERRUPT_IE_ES						0x10

#define INTERRUPT_IP_PX0					0x01
#define INTERRUPT_IP_PT0					0x02
#define INTERRUPT_IP_PX1					0x04
#define INTERRUPT_IP_PT1					0x08
#define INTERRUPT_IP_PS						0x10
#define INTERRUPT_IP_PT2					0x20

void Interrupt_Config(unsigned int interrupt_type);
void Interrupt_EnableOrDisable(unsigned int status);


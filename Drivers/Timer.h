#ifndef REG51_H
#include "reg51.h"
#endif

#define TIMER0								0x00
#define TIMER1								0x01

/*
 *	Bit Addressing Macros
 */
#define TIMER_MODE0 					0x00
#define TIMER_MODE1 					0x01
#define TIMER_MODE2 					0x02
#define TIMER_MODE3 					0x03
#define TIMER_TMOD_CT					0x40
#define TIMER_TMOD_GATE				0x80

typedef struct{
	unsigned int timer;
	unsigned int mode;
}Timer_Handle_t;

static unsigned int	count_on;
static unsigned int	count_off;


void Timer_Config(Timer_Handle_t);
void Timer_Delay(Timer_Handle_t,unsigned int);
void Timer_GenerateDelay0(Timer_Handle_t , unsigned int);
void Timer_GenerateDelay1(Timer_Handle_t , unsigned int );
void Timer_GenerateWave(unsigned int,unsigned int);
void Timer_ContinueWave();

#ifndef TIMER_H
#include "Timer.h"
#define TIMER_H
#endif

/*
 *		API for configuring the Timer peripheral.
 */
void Timer_Config(Timer_Handle_t timer_handle){
	if (timer_handle.timer==TIMER0){
		TMOD|=timer_handle.mode;
	}
	else if(timer_handle.timer==TIMER1){
		TMOD|=(timer_handle.mode<<4);
	}
}

/*
 *	API to generate Delay (in milisec)
 */
void Timer_Delay(Timer_Handle_t timer_handle,unsigned int delay_time){			// Delay time is in milisec.
	unsigned int count;
	
	count = (delay_time)/(1.085);
	
	/****************
	* 	Timer 0			*
	*****************/
	if (timer_handle.timer==TIMER0){
		Timer_GenerateDelay0(timer_handle,count);
	}
	/****************
	* 	Timer 1			*
	*****************/
	if (timer_handle.timer==TIMER1){
		Timer_GenerateDelay1(timer_handle,count);
	}
}

/*
 *		API for generating the delay for TIMER0.
 */
void Timer_GenerateDelay0(Timer_Handle_t timer_handle,unsigned int count){
	unsigned int count_div;
	unsigned int count_mod;
	unsigned int i;
	/*
	 ******	Mode 1	******
	 */
		if (timer_handle.mode==TIMER_MODE1){
			count=(0xFFFF-count)+1;
			TH0=((count>>8)&0xFF);
			TL0=(count&0xFF);
			TR0=1;
			while(TF0==0);
			TR0=0;	TF0=0;
		}
		/*
		 ******	Mode 2	******
		*/
		else if (timer_handle.mode==TIMER_MODE2){
			if (count<0xFF){
				count=(0xFF-count)+1;
				TH0=count;		TL0=count;
				TR0=1;
				while(TF0==0);
				TR0=0;	TF0=0;
			}
			else{
				count_div=(count/0xFF);		count_mod=(count%0xFF);
				for (i=0;i<count_div;i++){
					TH0=0x00;		TL0=0x00;
					TR0=1;
					while(TF0==0);
					TF0=0;
				}
				count_mod=(0xFF-count_mod)+1;
				TH0=count_mod;		TL0=count_mod;
				while(TF0==0);
				TR0=0;		TF0=0;
			}
		}
}

/*
 *		API for generating the delay for TIMER1.
 */
void Timer_GenerateDelay1(Timer_Handle_t timer_handle,unsigned int count){
	unsigned int count_div;
	unsigned int count_mod;
	unsigned int i;
	
	/*
		 ******	Mode 1	******
		*/
		if (timer_handle.mode==TIMER_MODE1){
			count=(0xFFFF-count)+1;
			TH1=((count>>8)&0xFF);
			TL1=(count&0xFF);
			TR1=1;
			while(TF1==0);
			TR1=0;	TF1=0;
		}
		/*
		 ******	Mode 2	******
		*/
		if (timer_handle.mode==TIMER_MODE2){
			//			Checking Overflow condition.
			if (count<0xFF){
				count=(0xFF-count)+1;
				TH1=count;		TL1=count;
				TR1=1;
				while(TF1==0);
				TR1=0;	TF1=0;
			}
			else{
				count_div=(count/0xFF);		count_mod=(count%0xFF);
				for (i=0;i<count_div;i++){
					TH1=0x00;		TL1=0x00;
					TR1=1;
					while(TF1==0);
					TF1=0;
				}
				count_mod=(0xFF-count_mod)+1;
				TH1=count_mod;		TL1=count_mod;
				while(TF1==0);
				TR1=0;		TF1=0;
			}
		}
}

/*
 *		API for generating square wave.
 *		(Frequency in KHz, duty_cycle in (%))
 */
void Timer_GenerateWave(unsigned int frequency,unsigned int duty_cycle){
	unsigned int count=(1000000/(frequency))/1.085;
	count_on=count/100*duty_cycle;
	count_off=count/100*(100-duty_cycle);
	
	count_on=((0xFFFF-count_on)+1);
	count_off=((0xFFFF-count_off)+1);

	P1=~P1;
	TH0=((count_on>>8)&0xFF);
	TL0=(count_on&0xFF);
	TR0=1;
}
/*
 *		API for generating square wave.
 *	 (Frequency in KHz, duty_cycle in (%))
 */
void Timer_ContinueWave(){
	TR0=0;	TF0=0;
  P1=~P1;
	if (P1==0xFF){
		TH0=((count_on>>8)&0xFF);
		TL0=(count_on&0xFF);
	}
	else{
		TH0=((count_off>>8)&0xFF);
		TL0=(count_off&0xFF);
	}
	TR0=1;
}


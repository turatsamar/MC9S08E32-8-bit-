#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <mc9s08el32.h> 
#include "LED.h"

#define PRESCALAR 7
#define MODULUS		32768
#define DUTY75		(MODULUS-(MODULUS/4))
#define DUTY25		(MODULUS/4)
#define VNkeyboard	22

  interrupt VNkeyboard void intSW1()
  {
	  LED1 = SW4;
	  PTBSC_PTBACK = 1;// ack interrupt
  }

void main(void) {
  EnableInterrupts;
  /* include your code here */
  
  
//setup switch pin 
  PTBDD = 0; //set  as input(Data Direction Register)
  PTBPE = 0xf0; //set Pin B upper bit to pull up
  //set LED pins output direct
  PTADD = 0x0f; //set PIN A as output
  LED1 = 0; // set to 0
  LED2 = 0;
  LED3 = 0;
  LED4 = 0;
  
  //Initialize timer TPM1 chanal
  TPM1SC_CLKSA = 1;// set CLK to A Bus clock TPM1 in status control register
  TPM1SC_CLKSB = 0;// off B clock in status control register
  TPM1SC_PS = PRESCALAR; // clock sours divided by prescalar 
  TPM1MOD = MODULUS; // set Counter modulus 
  //configure PWM mode and  pulse
  TPM1C0SC_MS0B = 1; //MS0B = 1; MS0A = 0;  << Edge align PWM
  TPM1C0SC_ELS0A = 1; //edge level select bit input capture event
  TPM1C0V = DUTY25;
  LED4 = ON;
  
  PTBPE_PTBPE4 = 1; //Internal Pull Enable for Port B Bit 4
  PTBSC_PTBIF = 1;
  
 
  for(;;) 
  {
    __RESET_WATCHDOG();	/* feeds the dog */  
    LED2 = SW2;
    
    if(SW3==DOWN)
    {
    	if(SW4==DOWN)
    	{
    		TPM1C0V = DUTY75;
    		LED3 = ON;
    		LED4 = OFF;
    	}
    	else
    	{
    		TPM1C0V = DUTY25;
    		LED3 = OFF;
    		LED4 = ON;
    	}
    }
  } /* loop forever */
  /* please make sure that you never leave main */
}

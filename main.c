#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <mc9s08el32.h>


#define OFF 0
#define ON 1

#define UP 1
#define DOWN 0

#define LED1	PTAD_PTAD0
#define LED2	PTAD_PTAD1
#define LED3	PTAD_PTAD2
#define LED4	PTAD_PTAD3


#define SW1		PTBD_PTBD4
#define SW2		PTBD_PTBD5
#define SW3		PTBD_PTBD6
#define SW4		PTBD_PTBD7


void main(void) {
  EnableInterrupts;
  /* include your code here */
//setup switch pin 
  PTBDD = 0; //set  as input(Data Direction Register)
  PTBPE = 0xf0; //set Pin B upper bit to pull up
  //set LED pins output direct
  PTADD = 0x0f; //set PIN A as output
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;
  LED4 = 0;
 
  for(;;) 
  {
    __RESET_WATCHDOG();	/* feeds the dog */
    
    LED1 = SW1;
  } /* loop forever */
  /* please make sure that you never leave main */
}

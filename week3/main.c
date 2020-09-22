#include "stm32f10x.h"

#define RCC_APB2_ENR *(volatile unsigned int *)0x40021018

#define GPIOC_CRL *(volatile unsigned int *)0x40011000
#define GPIOD_CRL *(volatile unsigned int *)0x40011400

#define GPIOC_IDR *(volatile unsigned int *)0x40011008
#define GPIOD_BSRR *(volatile unsigned int *)0x40011410
int main(void)
{

   
  RCC_APB2_ENR = 0x00000030; // Port C,D Clock enable 
 
  GPIOC_CRL = 0x00888800; // Joystick(Port D 2,3,4,5) Pull-up/Pull-down Input mode set 
  // GPIOC_CRL = GPIOC_CRL ^ 0x44CCCC44 (bit 연산 사용)
  
  GPIOD_CRL = 0x10011100; // LED(Port C 2,3,4,7) Output mode set
  // GPIOD_CRL = GPIOD_CRL ^ 0x54455544  (bit 연산 사용)
   
  while(1) {
    
    if((~GPIOC_IDR & 0x00000020)) { //UP, Input data register value check(if 0)
      GPIOD_BSRR = 0x00000080; //LED(Port D 7) BSRR register set
    } // Joystick UP
    
    else if((~GPIOC_IDR & 0x00000004)) { //DOWN, Input data register value check(if 0)
      GPIOD_BSRR = 0x00000008; //LED(Port D 3) BSRR register set 
    } // Joystick DOWN
    
    else if((~GPIOC_IDR & 0x00000010)) { //RIGHT, Input data register value check(if 0)
      GPIOD_BSRR = 0x00000004; //LED(Port D 2) BSRR register set
    } // Joystick RIGHT    
    
    else if((~GPIOC_IDR & 0x00000008)) { //LEFT, Input data register value check(if 0)
      GPIOD_BSRR = 0x00000010; //LED(Port D 4) BSRR register set
    } // Joystick LEFT
 
    else {
      GPIOD_BSRR = 0x009C0000; //LED(Port D 2,3,4,7) BSRR register reset
    } // Joystick STOP
  }
}

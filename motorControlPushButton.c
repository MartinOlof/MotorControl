#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define IN_A PORTB |= (1 << PB5)
#define IN_B PORTB |= (1 << PB3)
#define PWM PORTB |= (1 << PB0)
#define CS PORTB |= (1 << PB4)
#define SEL0 PORTB |= (1 << PB2)
#define PUSH_BUTTON

uint_8t buttonCount = 0;

// Push button connected PB1

// have a count on push button up to 3, if button count == 1, close it, if button count == 2 open it, reset count after each interation


void motorControl();

int main(void){

  while(1){
  
  }
}

void motorControl(){
  if(buttonCount == 1){
    
  }

}

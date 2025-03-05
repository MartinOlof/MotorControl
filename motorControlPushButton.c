#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define IN_A PORTB |= (1 << PB5)
#define IN_B PORTB |= (1 << PB3)
#define STOP_A PORTB &= ~(1 << PB5)
#define STOP_B PORTB &= ~(1 << PB3)
#define PUSH_BUTTON PB4

volatile uint8_t buttonCount = 0;

void motorControl();
void initButtonInterrupt();

int main(void) {
    // Configure PB5 and PB3 as outputs
    DDRB |= (1 << PB5) | (1 << PB3);
    
    // Configure PB4 as input with pull-up resistor
    DDRB &= ~(1 << PUSH_BUTTON);
    PORTB |= (1 << PUSH_BUTTON);
    
    // Initialize button interrupt
    initButtonInterrupt();
    sei(); // Enable global interrupts
    
    while (1) {
        // Main loop does nothing, all handled in ISR
    }
}

void initButtonInterrupt() {
    GIMSK |= (1 << PCIE);   // Enable pin change interrupt
    PCMSK |= (1 << PUSH_BUTTON); // Enable interrupt for PB4
}

ISR(PCINT0_vect) {
    if (!(PINB & (1 << PUSH_BUTTON))) { // Check if button is pressed
        _delay_ms(50); // Simple debounce
        if (!(PINB & (1 << PUSH_BUTTON))) {
            buttonCount++;
            if (buttonCount > 2) buttonCount = 1;
            motorControl();
        }
    }
}

void motorControl() {
    if (buttonCount == 1) {
        // Extend actuator
        IN_A;
        STOP_B;
    } else if (buttonCount == 2) {
        // Retract actuator
        IN_B;
        STOP_A;
    }
}

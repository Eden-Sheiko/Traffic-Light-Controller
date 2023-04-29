#include <avr/io.h>
#include <avr/interrupt.h>

// Pin definitions
#define RED_PIN (1 << DDB3)
#define YELLOW_PIN (1 << DDB4)
#define GREEN_PIN (1 << DDB5)

// State duration definitions
#define RED_ONLY_DURATION 5
#define RED_AND_YELLOW_DURATION 2
#define GREEN_ONLY_DURATION 5
#define YELLOW_ONLY_DURATION 1

// Timer1 settings
#define VAL 15623
#define TIMER_PRESCALER_BITS ((1 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER_CONFIGURE_CTC  (1 << WGM12)
#define TIMER_COMPARE_MATCH  (1 << OCIE1A)

// Traffic light state enumeration
enum TrafficLightState {
  RED_ONLY,
  RED_AND_YELLOW,
  GREEN_ONLY,
  YELLOW_ONLY
};

// Global variables
volatile TrafficLightState currentState = RED_ONLY;
volatile uint16_t stateCounter = 0;

void setup() {
  // Configure pins 11 (PB3), 12 (PB4), and 13 (PB5) as outputs
  DDRB |= (1 << DDB5) | (1 << DDB4) | (1 << DDB3);

  // Disable interrupts
  cli();

  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;

  // Set Timer1 counter value to 15623 to call the interrupt immediately
  TCNT1 = VAL;

  // Set Timer1 prescaler to 1024
  TCCR1B |= TIMER_PRESCALER_BITS;

  // Configure CTC Mode where TOP = OCR1A
  TCCR1B |= TIMER_CONFIGURE_CTC;

  // Set the value for the output compare register
  OCR1A = VAL;

  // Enable Timer1 compare match interrupt
  TIMSK1 |= TIMER_COMPARE_MATCH;

  // Enable interrupts
  sei();
}

// Interrupt Service Routine (ISR) for Timer1 compare match interrupt
ISR(TIMER1_COMPA_vect) {
  stateCounter++;

  switch (currentState) {
    case RED_ONLY:
      PORTB = (PORTB & ~(GREEN_PIN | YELLOW_PIN)) | RED_PIN;
      if (stateCounter >= RED_ONLY_DURATION) {
        currentState = RED_AND_YELLOW;
        stateCounter = 0;
      }
      break;

    case RED_AND_YELLOW:
      PORTB = (PORTB & ~GREEN_PIN) | RED_PIN | YELLOW_PIN;
      if (stateCounter >= RED_AND_YELLOW_DURATION) {
        currentState = GREEN_ONLY;
        stateCounter = 0;
      }
      break;

    case GREEN_ONLY:
      PORTB = (PORTB & ~(RED_PIN | YELLOW_PIN)) | GREEN_PIN;
      if (stateCounter >= GREEN_ONLY_DURATION) {
        currentState = YELLOW_ONLY;
        stateCounter = 0;
      }
      break;

    case YELLOW_ONLY:
      PORTB = (PORTB & ~(RED_PIN | GREEN_PIN)) | YELLOW_PIN;
      if (stateCounter >= YELLOW_ONLY_DURATION) {
        currentState = RED_ONLY;
        stateCounter = 0;
      }
      break;
  }
}

void loop() {
  // All timing and pin toggling is handled by the Timer1 compare match interrupt
}

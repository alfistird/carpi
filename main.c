/*
    piswitch
    Copyright (C) 2016  fabian nedoluha - finga [at] onders org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define OFF_TIME 30
static volatile unsigned long int count = 0;

// interrupt on pin change
ISR(PCINT0_vect) {
  if ((PINB & (1 << PB3)) == 0) {
    // enable timer interrupts
    TIMSK0 = _BV(TOIE0);

    // enable timer0 with prescaler to CPU/1024
    TCCR0B = _BV(CS02)|_BV(CS00);
  }
}

// interrupt on timer overflow
ISR(TIM0_OVF_vect) {
  count++;
  if (count > OFF_TIME) {
    PORTB ^= _BV(PB4);
    count = 0;
    TIMSK0 = 0;
    /* GIMSK = 0; */
  }
}

// startup function
void init(void) {
  // disable pullup on pin 3
  DDRB = _BV(DDB4);

  // pin 3 needs to be set to high
  PORTB = _BV(PB4);

  // enable pin change interrupts
  GIMSK = _BV(PCIE);

  // turn on interrupts for pin PB3
  PCMSK = _BV(PCINT3);

  // enable global interrupts
  sei();
}

int main(void) {
  init();

  for(;;);
}

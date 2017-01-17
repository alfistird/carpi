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

#define OFF_TIME 1
unsigned long int i = 0;

// interupt on timer overflow
ISR(TIM0_OVF_vect)
{
  i++;
  if (i > OFF_TIME) {
    PORTB ^= _BV(PB4);
    i = 0;
  }
}

// startup function
void init(void) {
  // set pulldown to pin 3
  DDRB = _BV(DDB4);

  // set Timer0 prescaler to CPU/1024
  TCCR0B |= (1 << CS02)|(1 << CS00);

  // enable Timer Interrupts
  TIMSK0 = _BV(TOIE0);

  // enable Pin Change Interrupts
  GIMSK = _BV(PCIE);
  sei();
}

int main(void) {
  init();

  for(;;);
}

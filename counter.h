/* Justin Goff */
#ifndef COUNTER_H
#define COUNTER_H

#include "config.h"
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pins.h"

#define gate_open() GATE_PORT |= _BV(GATE_PIN);
#define gate_close() GATE_PORT &= ~_BV(GATE_PIN);

extern uint16_t counter_ovf;
extern uint32_t count; 

extern void clear_count(void);
extern void read_count(void);
extern void sched_cnt(void);
extern void sched_cap(void);

#endif

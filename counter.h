/* Justin Goff */
#ifndef COUNTER_H
#define COUNTER_H

#include "config.h"
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "pins.h"


extern uint16_t counter_ovf;
extern uint32_t count; 

extern void clear_count(void);
extern void read_count(void);
extern void gate_open(void);
extern void gate_close(void);
extern void start_cnt(void);
extern void stop_cnt(void);
extern void stop_cap(void);
extern void sched_cnt(void);
extern void sched_cap(void);

#endif

/* Justin Goff */

#include "counter.h"
#include "globals.h"

/* quick stuff */
#define cnt_clr_delay()   __asm__ __volatile__( "rjmp 1f\n 1:" );   //#define lcd_e_delay() __asm__ __volatile__( "rjmp 1f\n 1: rjmp 2f\n 2:" );
#define cnt_clr_high()    CNTCLR_PORT |= _BV(CNTCLR_PIN);
#define cnt_clr_low()    CNTCLR_PORT &= ~_BV(CNTCLR_PIN);
#define cnt_clr_toggle toggle_clr()

/* global software counter overflow */
uint16_t counter_ovf;
/* counter after all added together */
uint32_t count; 

/* clear the external counter */
static void toggle_clr(void)
{
    cnt_clr_high();
    cnt_clr_delay();
    cnt_clr_low();
}

/* clear internal, software and external count to zero */
/* have gate closed well before zeroing out */
void clear_count(void)
{
    gate_close();
    counter_ovf = 0; /* msb */
    TCNT1 = 0; /* middle */
    toggle_clr(); /* lsb */
}

/* read count from  multiple counters and append the results */
void read_count(void)
{
    uint8_t data = 0;
    /* counter isn't attached with consecutive pins */
    if (bit_is_clear(CNTQ0_IN, CNTQ0_PIN)) data |= 0x01;
    if (bit_is_clear(CNTQ1_IN, CNTQ1_PIN)) data |= 0x02;
    if (bit_is_clear(CNTQ2_IN, CNTQ2_PIN)) data |= 0x04;
    if (bit_is_clear(CNTQ3_IN, CNTQ3_PIN)) data |= 0x08;
    if (bit_is_clear(CNTQ4_IN, CNTQ4_PIN)) data |= 0x10;
    if (bit_is_clear(CNTQ5_IN, CNTQ5_PIN)) data |= 0x20;
    if (bit_is_clear(CNTQ6_IN, CNTQ6_PIN)) data |= 0x40;
    if (bit_is_clear(CNTQ7_IN, CNTQ7_PIN)) data |= 0x80;

    /* TODO */
    /* see if bit mashing could be sped up without using big maths */
    count = ((uint32_t)counter_ovf<<24) | ((uint32_t)TCNT1<<8) | data;
}

/* set up next count */
void sched_cnt(void)
{
    gate_close();
    cli();
    trigflags.cntstart = 1;
    sei();
}

/* set up next capture */
void sched_cap(void)
{
    /* TODO */ 
    /* set pins for capture and start timer for timestamp */
    cli();
    trigflags.capstart = 1;
    sei();
}


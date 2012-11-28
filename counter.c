/* Justin Goff */

#include "counter.h"

uint16_t counter_ovf;
uint32_t count; 

void clear_count(void)
{
    gate_close();
    count = 0;
    counter_ovf = 0;
    /*TODO*/
}

void read_count(void)
{
    /*TODO*/
}

void gate_open(void)
{
    /*TODO*/
}

void gate_close(void)
{
    /*TODO*/
}

void start_cnt(void)
{
    /*TODO*/
}

void stop_cnt(void)
{
    /*TODO*/
}

void stop_cap(void)
{
    /*TODO*/
}

void sched_cnt(void)
{
    /*TODO*/
}

void sched_cap(void)
{
    /*TODO*/
}


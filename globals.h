#ifndef GLOBALS_H
#define GLOBALS_H

/* Top ISR flags for main to process */
/* write by isr, clear by main */
extern volatile struct isrstruct
{
    uint8_t jiffyfifth :1;
    uint8_t tx :1;
    uint8_t rx :1;
    uint8_t cntdone: 1;
    uint8_t capdone: 1;
} isrflags;

/* write by main, clear by isr */
extern volatile struct trigstruct
{
    uint8_t cntstart: 1;
    uint8_t capstart: 1;
} trigflags;

/* temp storage for counting isr */
volatile uint16_t jiffies;
volatile uint8_t runcount;

#endif

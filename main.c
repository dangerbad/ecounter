/* Justin Goff */

#include "config.h"
#include <stdint.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "globals.h"
#include "pins.h"
#include "lcd.h"
#include "counter.h"

/* Declare globals */

volatile struct isrstruct isrflags;
volatile struct trigstruct trigflags;

/* temp storage for lcd routine */

char sfreq[16];
char sjif[16];

/* LCD status strings */
char gate_str[][5] PROGMEM = 
{
    "10S",
    "1S",
    "1/5S",
    ".01S",
    "RECP"
};

struct param {
    uint8_t div;
    uint8_t ovf;
    uint16_t jff;
};

/* 8 bit counters for gate time
 * 10 sec = 20M/256 ovf 125 0x83 jff 6250 err 0%
 * 1 sec = 20M/256 ovf 125 0x83 jff 625 err 0%
 * 1/5 sec = 20M/256 ovf 125 0x83 jff 125 err 0%
 * .0016 sec = 20M/256 ovf 125 0x83 jff 0 err 0%
 */

struct param parms[] =
{
{.div = DIV256, .ovf=125, .jff=6250},
{.div = DIV256, .ovf=125, .jff=625},
{.div = DIV256, .ovf=125, .jff=125},
{.div = DIV256, .ovf=125, .jff=0},
};

volatile uint8_t mode;
uint8_t avg;

void oca_open(void);
void oca_close(void);
void oca_none(void);
void updisplay(void);
uint8_t debounce(uint8_t b);

/* update jiffies and operate gate */
ISR(TIMER1_COMPA_vect)
{

}

/* update count */
/* used for direct counting only */
ISR(TIMER0_OVF_vect)
{
    static uint8_t state = CSTART;
    static uint16_t jstart;
    static uint16_t jend;
    static uint16_t jff;
    jff++;
    if ((uint8_t)jff==0)
        isrflags.jiffyfifth = 1;
    jiffies=jff;

    switch (state)
    {
        case CSTART:
            jff=0;
            break;
        case CSETUP:
            jstart = jff+2;
            jend = jff+2+parms[mode].jff;
            oca_open();
            gate_close();
            state=CRUN;
            break;
        case CRUN: 
            if (jff==jend)
            {
                oca_close();
                gate_close();
                state=CEND;
            };
            if (jff==jstart)
            {
                gate_open();
                oca_none();
            }
            break;
        case CEND: 
            /* signal to have main read value */
            isrflags.cntdone = 1;
            gate_close();
            oca_none();
            if (trigflags.cntstart == 1 )
            {
                trigflags.cntstart = 0;
                state=CSETUP;
            }
            break;
        default:
            state = CSTART; 
    }
}

/* disable oca1 gate control */
void oca_none(void)
{
    TCCR0A &= ~(_BV(COM0B1) | _BV(COM0B1));
}

/* open gate on next oca1 */
void oca_open(void)
{
    TCCR0B |= _BV(FOC0B);
    TCCR0A |= _BV(COM0B1) | _BV(COM0B1);
}

/* close gate on next oca1 */
void oca_close(void)
{
    TCCR0B &= ~_BV(FOC0B);
    uint8_t t;
    t = TCCR0A & ~(_BV(COM0B1) | _BV(COM0B1));
    TCCR0A |= _BV(COM0B1); 
}

void updisplay(void)
{
    lcd_clrscr();
    lcd_puts_p(PSTR("Freq:"));
    lcd_puts(sfreq);
    lcd_gotoxy(0,1);
    lcd_puts_p(PSTR("Mode:"));
    lcd_puts_p(gate_str[mode]);
    lcd_puts_p(PSTR(" J:"));
    ultoa(jiffies,sjif,10);
    lcd_puts(sjif);
}


/* configure hardware on startup */
void ioinit(void)
{
    /* Set up ports */
    /*TODO*/

    /* set 8bit counter0 to div/64 prescale */

    TCCR0B |= _BV(CS01) | _BV(CS00); 
    /* set 8bit counter0 to mode 2 */
    TCCR0A |= WGM01;
    /* set trigger at 250 count */
    OCR0B = 125;
    TIMSK0 |= _BV(OCIE0B);
    /* start watchdog */
    WDTCSR |= _BV(WDE)| _BV(WDIE) | _BV(WDP2) | _BV(WDP0);
}

void nextmode(void)
{

    mode++;
    switch (mode)
    {
        case MODE_10SEC:
        case MODE_1SEC:
        case MODE_100MS:
        case MODE_10MS:
            sched_cnt();
            break;
        case MODE_RECIP:
            sched_cap();
            break;
        default:
            mode = 0;
            sched_cnt();
    }
}

#define BBCNT 3 /* count to change button state to pushed */
#define BHCNT 8 /* count to change button state to held */
#define BUTTONS 2

uint8_t readbutton(uint8_t b)
{
    uint8_t r=0;
    if (b==BTN_0)
        r = (bit_is_clear(BTN0_PORT, BTN0_PIN));
    if (b==BTN_1)
        r = (bit_is_clear(BTN1_PORT, BTN1_PIN));

    return r;
}

uint8_t debounce(uint8_t b)
/* Finite State Machine */
/* states
 * none -> pushed
 * released -> none
 * pushed -> held, released
 * held -> none
 *
 */
{
    static int8_t count[BUTTONS];
    static uint8_t state[BUTTONS] = {BSTART};
    static uint8_t last[BUTTONS] = {BNONE};

    uint8_t button;

    button = readbutton(b); /*TODO*/ /*button is pressed */

    /* zero state vars on state change */
    if (state[b] != last[b])
        count[b] = 0;
    last[b] = state[b];
    switch (state[b])
    {
        case BNONE: /* escape to pushed if count > BBCNT */
            if (button)
                count[b]++;
            else
                count[b] = 0;
            if (count[b] > BBCNT)
                state[b] = BPUSH;
            break;
        case BRELS: /* escape after one count */
            state[b] = BNONE;
            break;
        case BPUSH: /* escape if button released or escape if held */
            if (!button)
                state[b] = BRELS;
            else 
                if (++count[b] > BHCNT)
                    state[b] = BHELD;
            break;
        case BHELD: /* escape if button released */
            if (!button)
                state[b] = BNONE;
            break;
        default: /* opps */
            state[b] = BNONE;
            break;
    }
    return state[b];
}

int main(void)
{
    uint8_t i;
    uint8_t mode;

    mode = 0;
    avg = 0;

    /* wait a bit for clock to stableize */
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts_p(PSTR("Freqcount"));
    for(i=1;i<100;i++)
        _delay_ms(1000);
    ioinit();
    sei();
    for(;;)
    {
        wdt_reset();
        if (isrflags.jiffyfifth)
        {
            isrflags.jiffyfifth = 0;
            switch (debounce(BTN_0))
            {
                case BRELS:
                    nextmode();
                    break;
                case BHELD:
                    avg  = !avg;
                    break;
                default: ;
                    /* NOTHING */
            }
            switch (debounce(BTN_1))
            {
                case BRELS:
                    break;
                case BHELD:
                    break;
                default: ;
                    /* NOTHING */
            }

        };

        if (isrflags.cntdone)
        {
            read_count();
            isrflags.cntdone = 0;
            updisplay();
            sched_cnt();
        };

        if (isrflags.capdone)
        {
            isrflags.capdone = 0;
            updisplay();
            sched_cap();
        }

        sleep_mode();
    }
}

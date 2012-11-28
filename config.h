#ifndef CONFIG_H
#define CONFIG_H

#include "pins.h"

#define F_CPU 10000000

#define MODE_10SEC 0
#define MODE_1SEC 1
#define MODE_100MS 2
#define MODE_10MS 3
#define MODE_RECIP 4

#define BTN_0 0
#define BTN_1 1

#define BSTART 0
#define BNONE 1
#define BRELS 2
#define BPUSH 3
#define BHELD 4

#define CSTART 0
#define CSETUP 1
#define CRUN 2
#define CEND 3

#define DIV8 0
#define DIV16 1
#define DIV64 2
#define DIV256 3
#endif


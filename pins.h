#ifndef PINS_H
#define PINS_H

#define LCD_DDR DDRC
#define LCD_PORT PORTC

#define SCALE_DDR DDDD
#define SCALE_PORT PORTD
#define SCALE_PIN PD7

#define GATE_DDR DDRD
#define GATE_PORT PORTD
#define GATE_PIN PB6

#define CNTQ0_DDR DDRB
#define CNTQ0_PORT PORTB
#define CNTQ0_PIN PB3
#define CNTQ1_DDR DDRB
#define CNTQ1_PORT PORTB
#define CNTQ1_PIN PB4
#define CNTQ2_DDR DDRC
#define CNTQ2_PORT PORTC
#define CNTQ2_PIN PC0
#define CNTQ3_DDR DDRC
#define CNTQ3_PORT PORTC
#define CNTQ3_PIN PC1
#define CNTQ4_DDR DDRC
#define CNTQ4_PORT PORTC
#define CNTQ4_PIN PC2
#define CNTQ5_DDR DDRC
#define CNTQ5_PORT PORTC
#define CNTQ5_PIN PC3
#define CNTQ6_DDR DDRC
#define CNTQ6_PORT PORTC
#define CNTQ6_PIN PC4
#define CNTQ7_DDR DDRC
#define CNTQ7_PORT PORTC
#define CNTQ7_PIN PC5

#define CNTRCO_DDR DDRD
#define CNTRCO_PORT PORTD
#define CNTRCO_PIN PD5

#define CNTCLR_DDR DDRB
#define CNTCLR_PORT PORTB
#define CNTCLR_PIN PB5

#define CNTE_DDR DDRB
#define CNTE_PORT PORTB
#define CNTE_PIN PB1

#define BTN0_DDR DDRD
#define BTN1_DDR DDRD
#define BTN0_PORT PORTD
#define BTN1_PORT PORTD
#define BTN0_PIN PD2
#define BTN1_PIN PD3

#endif

/*
pd2 scaler-en
pd3 cnt-q1
pd4 t0 cnt-rco
pd5 t1 cnt-q0
pd7 lcd-e o
pb0 cnt-g
pc5 cnt-q7
pc4 cnt-q6
pc3 lcd-d3 cnt-q5
pc2 lcd-d2 cnt-q4
pc1 lcd-d1 cnt-q3
pc0 lcd-d0 cnt-q2
pb5 sck lcd-rw
pb4 miso lcd-rs
pb3 mosi cnt-clr
pb2 ss oc1b
pb1 cnt-cken oc1a 
*/

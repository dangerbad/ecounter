

Frequency counter with external 8bit prescale counter.

This is an avr project wrote in c for the gnu-avrlibc cross compiler. While I
may get a schematic uploaded, in the mean time the pinout is listed in
"pins.txt".

The purpose of putting this in a public repo was to shame myself into
finishing the project and makeing it sorta documented and nice.

External counter is a 74HC590 8 bit binary counter with 3-state output. It has
a rated speed for up to a minimal 33Mhz at 4.5 volt may operate easily up to
around 60Mhz. Without driving the output until after the gate is closed I
hope to maximize the upper frequency limit. For the AVR alone the maximum
freqency is the [clock rate]/4, so around 5Mhz. The external chip greatly
extends this.

There is a pin dedicated for use with an VHF/UHF/SHF prescaler. Drive this
pin low when an additinal scaling of DIV64 is used. Displayed count is to be
the calculated result.

There is a pin dedicated to enable a reciprical mode for low frequency
mesurement. Max frequency for reciprical mode is limited by the 16bit counter
and the synchronizer at running at 20Mhz. Software count is an additinal 16
bits for a total of 32bit accurate reciprical counter.  The limit for 
reciprical method would be around 2Mhz until accuracy would be effected. If 
there is a need for more accurate mean of mesuring low frequency the code with 
be completed.



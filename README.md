# SimPanel-Autopilot

An autopilot panel for use with FSX and Link2FS, running on a Particle Photon


## Notes on interrupts

### Shared Interrupt pins:
* D1, A4
* D2, A0, A3
* D3, DAC
* D4, A1

### Other non-interrupt pins:
* D0, D7, A5

### Therefore unique interrupt pins are:
* D1, D2, D3, D4, D5, D6
* A2, WKP, RX, TX

### Suitable for non-interrupt:
* D0, D7, A0, A1, A3, A4, A5, DAC


## Copywrite notices
Link2FS is from here

http://www.jimspage.co.nz/Link2fs_Multi.htm

QueueArray is Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)

https://playground.arduino.cc/Code/QueueArray

Encoder is Copyright (c) 2011,2013 PJRC.COM, LLC - Paul Stoffregen <paul@pjrc.com>

http://www.pjrc.com/teensy/td_libs_Encoder.html

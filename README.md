Dire_Cobra
==========

This project interfaces with the DIY-k108 "Serial Isolated Input/Ouptut Module"
(ref: www.hobbyengineering.com/specs/DIY-k108.pdf). The module uses an ATMEL 
AT89C2051 microcontroller with pre-programmed firmware to control 8 relay outputs.
It is also capable of reading 4 TTL inputs.

This project wraps the interface so that the module can be accessed through C
routines, instead of requiring the use of terminal emulation software (such as
minicom or hyperterminal).

The code is still underdevelopment, so there is a lot of polish missing.

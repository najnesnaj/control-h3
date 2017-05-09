control the H3 allwinner SOC directly by writing to registers (orange pi)

search the net for Allwinner_H3_Datasheet_V1.1 (1).pdf (here you'll find data and control registers)

compile : gcc blinky.c -o test


blinky writes to the PWM control register 
and enables PA5 (which is the pin in the middle of the system-serial-port)

by connecting a led to ground and PA5, you get a blinking LED

there's a script for reading the switch on the orange pi pc board


I included the "fex" file for my orange pi 2E board
(I run the system from emmc, but am still able to read from the sd card)


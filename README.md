pixelboard
==========

Arduino sketch and libriaries to run the Adafruit 16x32 LED Matrix

pixelboard.py - python program that sends command from a host to the board from the commandline. Requires pySerial

pixelboard_v2.ino - Arduino sketch. 
Setup to run with the MEGA wiring shown at https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/wiring-the-16x32-matrix

This sketch is a memory hog and needs to be running on a Mega.
Once running, the sketch takes serial input in the form of a 
carriage return or newline terminated string.

The string includes controls and text and will continue to scroll across the 
pixelboard until replaced with a new command. Send just \n or \r to stop the 
display. You can send a new command any time. It will be displayed once the 
current scroll reaches its conclusion.

Controls:
	/0       - text displayed full height
	/1       - text displayed on line 1
	/1       - text displayed on line 2
	/#RRGGBB - change following text color to RRGGBB
	         - 000000 will cause color to rotate
	/LX      - display logo X ( 1-ESI, 2-Scotia, 3-Esso, 4-Sobeys,
                   5-Arduino, 6-RaspberryPi )

Examples:
	/l1/1Exchange/2Solutions

If you want to display a /, escape it with another. // displays /

There are limits.  512 characters in a command string. 30 screen elements.
These limits are not well enforced by the code. "Bad things" happen when you
break them.


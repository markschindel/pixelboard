import serial
import time

def help () :
	print """

Pixelboard command is a carriage return or newline terminated string.
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

\q - quit
"""

ser = serial.Serial(
	port='COM8',
	baudrate=38400,
	timeout=0
)

print "\nInitializing Pixelboard.\n"
time.sleep(5)
print "\n"

running = 1

while running:
	msg = raw_input("Pixelboard command (\h for help): ")
	if len(msg) == 0:
		ser.write("\n")
	else:
		if msg[0] == "\\": 
			if msg[1] == "q":
				ser.write("\0\n")
				running = 0
			elif msg[1] == "h":
				help()
			else:
				print "unknown command\n"
		else:
			ser.write(msg+"\n")

exit()

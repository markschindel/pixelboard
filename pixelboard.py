import serial
import time
import pyreadline as readline

def help () :
	print """

Pixelboard command is a carriage return or newline terminated string.
The string includes controls and text and will continue to scroll across the 
pixelboard until replaced with a new command. Send just \\n or \\r to stop the 
display. You can send a new command any time. It will be displayed once the 
current scroll reaches its conclusion.

Controls:
	/0       - text displayed full height
	/1       - text displayed on line 1
	/1       - text displayed on line 2
	/#RRGGBB - change following text color to RRGGBB
	           000000 will cause color to rotate
	/LX      - display logo X ( 1-ESI, 2-Arduino, 3-RaspberryPi )
	/UX      - upload new logo into slot X. 
	           Will replace existing logo until reset.
	           The next 512 bytes read are the 16x16 rgb565 pixmap.
	           delay 100ms after /UX command.
	/R1      - control repeat behavior. 
	           default is no repeat /r0. to repeat after scroll /r1

Example: /l1/1Exchange/2Solutions

If you want to display a /, escape it with another. // displays /
There are limits.  512 characters in a command string. 30 screen elements.
These limits are not well enforced by the code. "Bad things" happen when you
break them.

pixelboard.py Commands:
	\q           - quit
	\h           - this message
	\uX filename - load raw pixmap file into logo slot X
	\\r filename  - read command strings and wait times from file. 
	               line starts with wait followed by the command string.
"""

def uploadfile (logopos, filename) :
	ser.write("/u"+logopos+"\n")
	time.sleep(0.05)
	sendfile(filename)

def sendfile (filename) :
	with open(filename, "rb") as f:
		bytes = f.read(512)
		ser.write(bytes)
		f.close()

def readfile (filename) :
	with open(filename) as f:
		for line in f.readlines():
			wait,msg = line.split(" ",1)
			ser.write(msg)
			print("waiting "+wait+"\n")
			time.sleep(float(wait))
		f.close()
		ser.write("\n")

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
			elif msg[1] == "r":
				readfile(msg.split(" ")[1])
			elif msg[1] == "u":
				uploadfile(msg[2],msg.split(" ")[1])
			else:
				print "unknown command\n"
		else:
			ser.write(msg+"\n")

exit()

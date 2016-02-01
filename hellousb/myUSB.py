import hellousb as usb1
import time

myusb = usb1.hellousb()

while(1):
	time.sleep(1)
	myusb.set_vals(4,3)
	print myusb.get_vals()
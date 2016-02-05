import encodertest as encoder
import struct
import time

myencoder = encoder.encodertest()
myencoder.toggle_led2()
myencoder.toggle_led1()
ENC_MAG = 0x3FFE
ENC_ANGLE = 0x3FFF
print 2**14
while(1):

#	mag = myencoder.enc_readReg(ENC_MAG)
#	mag =  struct.unpack('<h',mag)[0]
#	mag = bin(mag)[2:]
#	print mag

	angle = myencoder.enc_readReg(ENC_ANGLE)
	angle = struct.unpack('<H',angle)[0]

	

	angle = bin(angle)
	angle = angle[4:].zfill(14)
	angle = int(angle,2)
	#print "int = ",angle
	angle = (angle*360.0)/(2**14)
	print "angle = ", angle

	time.sleep(1)
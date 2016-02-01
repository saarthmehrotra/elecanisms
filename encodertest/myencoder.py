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
	angle = struct.unpack('<h',angle)[0]
	angle = bin(angle)[2:]
	angle = int(angle,2)
	angle = angle*360.0/2**14
	if angle > 360:
		angle = angle-360
	print angle

	time.sleep(1)
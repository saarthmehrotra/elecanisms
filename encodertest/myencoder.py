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

	pack = myencoder.enc_readReg(ENC_ANGLE)
	origAngle = struct.unpack('<H',pack)[0]

	

	binAngleOrig = format(origAngle, '#018b')
	binAngle = binAngleOrig[4:]
	intAngle = int(binAngle,2)
	#print "int = ",angle
	angle = (intAngle*360.0)/(2**14)
	if binAngleOrig[3] == "0":
		print "angle = ", angle, "  intAngle = ", intAngle, "   binAngle = ", binAngle, "   binAngleTruncated = ", binAngleOrig[4:], "   binAngleOrig = ", binAngleOrig, "   origAngle = ", origAngle 
	else:
		print "error"
		#print "angle = ", angle, "  intAngle = ", intAngle, "   binAngle = ", binAngle, "   binAngleOrig = ", binAngleOrig

	time.sleep(1)
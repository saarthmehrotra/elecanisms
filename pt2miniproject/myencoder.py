import encodertest as encoder
import struct
import time
import csv
import time


myencoder = encoder.encodertest()
myencoder.toggle_led2()
myencoder.toggle_led1()
ENC_MAG = 0x3FFE
ENC_ANGLE = 0x3FFF
print 2**14
angleList = []
#f = open('data.csv', 'w')
while(1):

#	mag = myencoder.enc_readReg(ENC_MAG)
#	mag =  struct.unpack('<h',mag)[0]
#	mag = bin(mag)[2:]
#	print mag
# 	time.sleep(1)



# 	totalAngle = revs*256+Angle/256;
# 	cumalativeAngle = cumalativeAngle + abs(totalAngle)/4;
#  	uint16_t pidDuty = MAXDUTY - cumalativeAngle/iConstant - pConstant*totalAngle - dConstant*abs(Angle-prevAngle)/256;
	x = 1
	y = 1

	z = raw_input("Press 1 to Change pConstant and 2 to change iConstant")
	if z == 1:
		x = input("Enter pConstant Value (0 to 255):")
	if z == 2:
		y = input("Enter iConstant Value (1/x and x = 0 to 16):")

	myencoder.set_vals(x,y)
	print myencoder.get_vals()
	pack = myencoder.enc_readReg(ENC_ANGLE)


	origAngle = struct.unpack('<H',pack)[0]


	# #Use 18 bits b/c want 16 bits and 2 for padding
	binAngleOrig = format(origAngle, '#018b')
	binAngle = binAngleOrig[4:]
	intAngle = int(binAngle,2)
	#print "int = ",angle
	angle = (intAngle*360.0)/(2**14)
	#if binAngleOrig[3] == "0":
		#print "angle = ", angle, "  intAngle = ", intAngle, "   binAngle = ", binAngle, "   binAngleTruncated = ", binAngleOrig[4:], "   binAngleOrig = ", binAngleOrig, "   origAngle = ", origAngle 
		#print angle
		#time.sleep(1)
		#f.write(str(angle)+',')
	# angleList.append(angle)





	#else:
	#	print "error"
		#print "angle = ", angle, "  intAngle = ", intAngle, "   binAngle = ", binAngle, "   binAngleOrig = ", binAngleOrig


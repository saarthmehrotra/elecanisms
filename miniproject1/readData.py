import csv
import matplotlib.pyplot as plt
import numpy as np
with open('data.csv', 'rb') as f:
    reader = csv.reader(f)
    your_list = list(reader)

dataArray = []
for item in your_list[0]:
	#print item
	dataArray.append(int(float(item)))


plt.plot(dataArray)
plt.title('Angle vs Time')
plt.xlabel('Time')
plt.ylabel('Angle of Motor')
plt.show()

revolutionArray = []
revolutions = 0
num = 0
degreeDiff = 0
for i in range(len(dataArray)):
	if num == 300:
		num = 0
		revolutionArray.append(revolutions)
		revolutions = 0
	else:
		num = num+1

	if dataArray[i]>=dataArray[i-1]:
		degreeDiff= degreeDiff+dataArray[i]-dataArray[i-1]
	else:		
		degreeDiff = degreeDiff+360 - dataArray[i-1]+dataArray[i]

	#print dataArray[i],dataArray[i-1], degreeDiff, revolutions

	if degreeDiff>360:
		revolutions = revolutions+1
		degreeDiff = degreeDiff-360



print revolutionArray

plt.plot(revolutionArray)
plt.title('Revolutions vs Time')
plt.xlabel('Time')
plt.ylabel('# of Revolutions')
plt.show()
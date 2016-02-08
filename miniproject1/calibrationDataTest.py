import matplotlib.pyplot as plt

#data1 = 275.7, 119.5, 296.6, 130.4, 299.0, 128.8, 305.4, 124.7, 308.7, 136.4, 316.8, 166.3, 291.2, 174.9, 18.6, 209.8, 67.3, 242.3
# data = 	187.4, 1.6, 191.4, 9.4, 214.2, 57.2, 234.5, 75.7, 258.2, 102.8, 287.5, 129.6, 314.6, 142.0, 349.3, 171.0, 20.0

# errorList = []
# for i in range(len(data)):
# 	if i == 0:
# 		angle = data[0]
# 	else:
# 		if data[i] < data[i-1]:
# 			angle = 360 - data[i-1] + data[i]
# 		else:
# 			angle = (data[i] - data[i-1])
# 	errorList.append(angle-174.8)
# print errorList	


data = 119.7, 166.5, 207.2, 254.6, 298.4, 345.2, 28.45, 78.4
angles = [119.7]
for i in range(len(data)):
	angles.append((angles[i]+45)%360)
	print angles[i], data[i]

plt.plot(angles[:8],data,'ro')
plt.xlabel('angles')
plt.ylabel('data')
plt.show()
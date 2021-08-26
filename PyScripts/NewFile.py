
import os
path = "C:\\Users\\Snion\\Desktop\\玩具小车外盖\\"
for i in range(1,10):
	npath = path + str(i) + ".txt"
	with open(npath,'w') as fp:
		fp.write("nihao")
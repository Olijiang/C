import os
path = "D:\\Study\\HTMl\\static\\img\\"
path = "D:\\FAVORITE\\baidu\\"
path = 'D:\\FAVORITE\\New\\'

imgs = os.listdir(path)

n = 1
pre = "c"
for i in imgs:
	old_path = path + i
	new_path = path +pre + str(n) + i[-4:]
	n = n + 1 
	#print(old_path)
	#print(new_path)
	try:
		os.rename(old_path,new_path)
	except Exception as e:
		print(e)
		exit()
	
import os, shutil
#path = "D:\\Study\\HTMl\\static\\img\\"
path = "F:\\925101646\\"
path = "F:\\BaiduNetdiskDownload\\5500词配套视频\\"

files = os.listdir(path)

n = 2
s = '更多内容关注“恋词”公众号'
for i in files:
	oldname = path + i
	i = i.replace(s,'')
	newname = path + i
	os.rename(oldname,newname)
files = os.listdir(path)
for i in files:
	fs = os.listdir(path + i)
	for j in fs:
		oldname = path + i + '\\' + j
		j = j.replace(s,'')
		newname = path + i + '\\' + j
		os.rename(oldname,newname)

'''
for i in files:
	fs = os.listdir(path + i)
	for j in fs:
		if j[-3:] == 'mp4':
			oldname = path + i +'\\' + j
			newname = path + i +'\\' + 'Unit' +str(n) +'.mp4'
			os.rename(oldname,newname)
			#shutil.move(newname,path)
			#n = n + 1
'''
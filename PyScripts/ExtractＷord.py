import os, re
text = []
path = 'C:\\Users\\Snion\\Desktop\\word.txt'

with open(path, 'r' ,encoding='utf-16') as fp:
    t = fp.readlines()

pattern =  re.compile(r'\d, .{1,20}  ')
res = pattern.findall(str(t))
for i in range(len(res)):
    res[i] = res[i][3:-2]

path = 'C:\\Users\\Snion\\Desktop\\word-ok.txt'
with open(path, 'w' ,encoding='utf-16') as fp:
    for i in range(len(res)):
        fp.write(res[i])
        fp.write("\n")
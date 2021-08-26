
import requests,re,time 
from bs4 import BeautifulSoup
Homepage = "http://www.kaoyan365.cn/yingyu/cihui/229303.html"

ua = 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.25 Safari/537.36 Core/1.70.3861.400 QQBrowser/10.7.4313.400'
headers = {'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8', 'Accept-Language': 'zh-CN,zh;q=0.9', 'User-Agent': ua}


def get_content(url):
    try:
        response = requests.get(url, headers=headers)
        response.encoding = 'gb2312'
        if(response.status_code==200):
            return response.text
        else:print("ERROR URL:{0}".format(url))
    except:
        print("ERROR URL:{0}".format(url))

html = get_content(Homepage)
soup = BeautifulSoup(html,'html.parser')
#print(soup)
targetURL = soup.select('tbody')[1].select('td a') #提取单词链接所在的标签,是一个列表

with open("test.txt","w", encoding='utf-8') as fp:
    for i in targetURL:
        subURL = str(i)[9:57]
        Cuid = i.text
        subhtml = get_content(subURL)
        pattern = re.compile('<p>\d\d .{0,50}</p>')
        result = pattern.findall(subhtml)
        for w in result:
            word = w[6:-4]
            fp.write(word+"\n")
        print("{0} is OK".format(Cuid))
        time.sleep(0.1)


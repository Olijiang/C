# coding = 'utf-8'
import urllib.request
import re
import random

def get_html(url, header):
    req = urllib.request.Request(url, headers=header)
    html = urllib.request.urlopen(req)

    head_type = html.headers['Content-Type'].split('=')[-1]
    status = html.getcode()

    return html, head_type, status   # 分别得到html, 编码方式， 访问状态码


headers = [{'User-Agent':'Mozilla/5.0 (Windows NT 6.3 WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Maxthon/4.4.8.1000 Chrome/30.0.1599.101 Safari/537.36'},{'User-Agent':"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:45.0) Gecko/20100101 Firefox/45.0"},{'User-Agent': 'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 10.0; WOW64; Trident/7.0)'}]


keyword =input('请输入要搜索的资源名:')
keyword = urllib.request.quote(keyword.encode('utf-8'))
url = "http://www.wangpansou.cn/s.php?wp=0&ty=gn&op=gn&q="+keyword+"&q="+keyword
header = random.choice(headers)

f_html, f_head_type, f_status = get_html(url, header)

if f_status == 200:
    f_html = f_html.read()
    f_html = f_html.decode(f_head_type)

    pattern = re.compile('<a href="(.+)"><div class="cse-search-result_paging_num " tabindex="\d{1,3}">\d{1,3}</div></a>')
    content = pattern.findall(f_html)   # 得到所有有相关结果的页面链接

    url_list = []
    url_head = 'http://www.wangpansou.cn/'
    for i in content:
        i = url_head +i # 因为正匹配出来的只有一部分,所以把前面的一部分加上,开成完整的链接
        if not i in url_list:   # 去掉重复的,网页确实有两分,所以去重.
            url_list.append(i)   # 得到所有 有搜索结果的页面网址列表
    first_url = url_list[0][:-2] + '0'  # 加上第一页
    url_list.insert(0,first_url)

count = 0
for each_url in url_list:
    header = random.choice(headers)
    s_html, s_head_type, s_status = get_html(each_url, header)

    if s_status == 200:
        s_html = s_html.read()
        s_html = s_html.decode(s_head_type)
        s_pattern = re.compile('<a class=".+" href="(.+)" rel.+')
        s_content = s_pattern.findall(s_html) # 分享的链接

        t_pattern = re.compile('<div id=".+" class="cse-search-result_content_item_mid">\s+(.+)')
        t_content = t_pattern.findall(s_html) # 文件信息
    else:
        print('Website Error!')

    for i in range(0, len(s_content)):
        count += 1
        print(str(count) + ':' + t_content[i] + '\n' + s_content[i])
        print()



print('共搜索到%d个资源,已经全部爬取完毕！' % count)
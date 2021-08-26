import requests
url = "https://www.bilibili.com/read/cv2217892"
html = requests.get(url).text

print(html[9000:15000])
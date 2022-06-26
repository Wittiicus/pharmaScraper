from curses.ascii import BS
from email import header
from socketserver import ForkingMixIn
from termios import BS0
from bs4 import BeautifulSoup
import urllib.request, requests 
import pandas as pd 

nameData = []
pNumberData = []

url = 'https://www.yellowpages.ca/search/si/1/Pharmacies/Canada'

headers = {'Accept-Encoding' : 'gzip, deflate, br', 
            'user-agent': 'Mozilla/5.0', 
            'Host' : 'www.yellowpages.com',
            }

html = requests.get('https://www.yellowpages.ca/search/si/1/Pharmacies/Canada', headers=headers)

with urllib.request.urlopen(url) as response:
    html = response.read()

soup = BeautifulSoup(html, 'html.parser')

articles = soup.find_all('div', class_ = 'listing listing--bottomcta')

for item in articles:
    phoneNumber = item.find_all('li', class_ = 'mlr__submenu__item')
    for items in phoneNumber:
        pNumberData.append(items.text.replace('\n',''))
    companyName = item.find('div', class_ = 'listing__title--wrap').text
    streetAddress = item.find('span', {'itemprop': 'streetAddress'}).text.strip()

    print(companyName, pNumberData, streetAddress)
    pNumberData = []



writer = pd.ExcelWriter('demo.xlsx', engine='xlsxwriter')
writer.save()
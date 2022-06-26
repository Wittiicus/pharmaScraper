from curses.ascii import BS
from email import header
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

articles = soup.find_all('div', class_ = 'listing__title--wrap')
Links = soup.find_all('li', class_ = 'mlr__submenu__item')


for pnums in Links:
    pNumberData.append(pnums.text.strip())


for items in articles:
    nameData.append(items.text.strip())

print(len(nameData), len(pNumberData))

df = pd.DataFrame({'Pharmacy Name' : nameData, 'Pharmacy Website' : pNumberData})
df.columns = ['Pharmacy Name', 'Pharmacy Website']


writer = pd.ExcelWriter('demo.xlsx', engine='xlsxwriter')
writer.save()
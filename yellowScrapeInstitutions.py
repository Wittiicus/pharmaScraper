from curses.ascii import BS
from email import header
from socketserver import ForkingMixIn
from termios import BS0
from bs4 import BeautifulSoup
import urllib.request, requests 
import pandas as pd 
from tabulate import tabulate

nameData = []
pNumberData = []
companyName = []
streetAddress = []
postalCode = []
city = []
province = []
numbersForCompany = []


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
webby = soup.find_all('li', class_ = 'mlr__item mlr__item--website')
#for i in webby:
    #print(i.find('a').get('href'))

       

for item in articles:

    phoneNumber = item.find_all('li', class_ = 'mlr__submenu__item')
    for items in phoneNumber:
        pNumberData.append(items.text.replace('\n',''))
    numbersForCompany.append(pNumberData)
    try:
        companyName.append(item.find('div', class_ = 'listing__title--wrap').text)
    except:
        companyName.append('Unavailable')
    try:
        streetAddress.append(item.find('span', {'itemprop': 'streetAddress'}).text.strip())
    except:
        streetAddress.append('Unavailable')
    try:
        postalCode.append(item.find('span', {'itemprop': 'postalCode'}).text.strip())
    except:
        postalCode.append('Unavailable')
    try:
        city.append(item.find('span', {'itemprop': 'addressLocality'}).text.strip())
    except:
        city.append('Unavailable')
    try: 
        province.append(item.find('span', {'itemprop': 'addressRegion'}).text.strip())
    except:
        province.append('Unavailable')
    pNumberData = []


dict = {'Company Name': companyName,
        'Street Address':streetAddress,
        'City': city,
        'Province': province,
        'Postal Code': postalCode,
        'Phone Numbers': numbersForCompany}


df = pd.DataFrame(dict)
  
# displaying the DataFrame
print(tabulate(df, headers = 'keys', tablefmt = 'psql'))


writer = pd.ExcelWriter('demo.xlsx', engine='xlsxwriter')
writer.save()
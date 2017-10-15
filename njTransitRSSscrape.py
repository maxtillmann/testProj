#Need to install some packages to run this:

#sudo apt-get install python
#sudo apt-get install python-pip
#pip install requests
#pip install bs4
#pip install lxml



import requests
from bs4 import BeautifulSoup

url  = "https://www.njtransit.com/rss/BusAdvisories_feed.xml"
resp = requests.get(url)
soup = BeautifulSoup(resp.content, features="xml")


busDesc  = soup.findAll('title')		#bus number, time of alert
alertMsg = soup.findAll('description')          #alert message
moreInfo = soup.findAll('link')			#link to more detailed description

       


f = open('/home/max/Desktop/Alerts.txt','w')	#remember to change filepath
f.write('Bus_Number,Alert_time,Alert_Msg,External_Link'+'\n')
for msg in range (1,len(alertMsg)):
	fullTitle = busDesc[msg].text.split()	#splits title element into 
	time = False				#bus number and time for
	for word in fullTitle:			#data table
		if word.isdigit():
			f.write(word)
			f.write(',')
			time = True
		elif time:
			f.write(word)
			f.write(' ')
	
	f.write(',')
	
	f.write(alertMsg[msg].text + ',' + moreInfo[msg].text + '\n')
	


f.close()


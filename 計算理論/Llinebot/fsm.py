from transitions.extensions import GraphMachine
from selenium import webdriver
from pyquery import PyQuery as pq #name PyQuery as pq
from tabulate import tabulate
import time
from selenium.webdriver.common.by import By
from utils import send_text_message

# get the website
driver = webdriver.Chrome("D:\\chromedriver_win32\chromedriver") # open the chrome by chromedriver
driver.get("https://www.railway.gov.tw/tra-tip-web/tip/tip001/tip112/gobytime") # open the page of 台鐵網站
html = driver.find_element(By.CSS_SELECTOR,"*").get_attribute("outerHTML") # locate element by css selector
doc = pq(html) # can get all nodes

# start_station cities
cities_startStation = {}
citiesSort_startStation = {}

# start_station 
StationSort_startStation = {}

# end_station cities
cities_endStation = {}

# end_station
stationSort_endStation = {}

# result of trains
result_trans = []

# original page
last_url = ''

class TocMachine(GraphMachine):
    def __init__(self, **machine_configs):
        self.machine = GraphMachine(model=self, **machine_configs)

    def is_going_to_search(self, event):
        text = event.message.text
        return text.lower() == "查詢班次"

# the start_station ============================================================================================================
# print("縣市: ")
# count = 2
# for city in doc("#mainline > div:nth-child(1) > ul > li:nth-child(n+2)").items():# cities name in doc
#     print(city.text()) # print all start station cities
#     temp_city_id = doc("#mainline > div:nth-child(1) > ul > li:nth-child("+ str(count) +") > button").attr("data-type")
#     citiesSort_startStation[city.text()] = count
#     cities_startStation[city.text()] = temp_city_id # get city id
#     count +=1
    def on_enter_search(self, event):
        print('search')
        reply_token = event.reply_token
        send_text_message(reply_token, "縣市: ")
        count = 2
        for city in doc("#mainline > div:nth-child(1) > ul > li:nth-child(n+2)").items():# cities name in doc
            send_text_message(reply_token, city.text()) # print all start station cities
            temp_city_id = doc("#mainline > div:nth-child(1) > ul > li:nth-child("+ str(count) +") > button").attr("data-type")
            citiesSort_startStation[city.text()] = count
            cities_startStation[city.text()] = temp_city_id # get city id
            count +=1
        self.go_back()

    def is_going_to_state2(self, event):
        text = event.message.text
        return text.lower() == "go to state2"

    

    def on_exit_state1(self):
        print("Leaving state1")

    def on_enter_state2(self, event):
        print("I'm entering state2")

        reply_token = event.reply_token
        send_text_message(reply_token, "Trigger state2")
        self.go_back()

    def on_exit_state2(self):
        print("Leaving state2")

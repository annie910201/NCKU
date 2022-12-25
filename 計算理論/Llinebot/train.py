from selenium import webdriver
from transitions.extensions import GraphMachine
from pyquery import PyQuery as pq #name PyQuery as pq
from tabulate import tabulate
import time
from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError
from selenium.webdriver.common.by import By
from linebot.models import *

class Find_the_train(GraphMachine):
    # start_station cities
    def __init__(self):
        self.cities = set()
        self.stations = set()
        self.mode = 1
        self.cities_startStation ={}
        self.citiesSort_startStation ={}
        # start_station 
        self.StationSort_startStation={}
        self.count =0
        # end_station cities
        self.cities_endStation ={}

        # end_station
        self.stationSort_endStation={} 

        # result of trains
        self.result_trans =[]

        # original page
        self.last_url =''
        self.input_startStationCity =""

    def find_the_web(self):
        # get the website
        self.driver = webdriver.Chrome("D:\\chromedriver_win32\chromedriver") # open the chrome by chromedriver
        # print(type(self.driver))
        self.driver.get("https://www.railway.gov.tw/tra-tip-web/tip/tip001/tip112/gobytime") # open the page of 台鐵網站
        self.html = self.driver.find_element(By.CSS_SELECTOR,"*").get_attribute("outerHTML") # locate element by css selector
        self.doc = pq(self.html) # can get all nodes

# the start_station ============================================================================================================                                 
    def find_the_start_city(self):
        # click the startstation button
        self.driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[1]/div[2]/div[2]/button[1]").click()
        # choose the city
        self.driver.find_element(By.XPATH, "//*[@id='mainline']/div[1]/ul/li[{0}]/button".format(self.citiesSort_startStation[self.input_startStationCity])).click()

    def find_the_start_station(self):
        # click the start station
        self.driver.find_element(By.XPATH, "//*[@id='{0}']/ul/li[{1}]/button".format(self.cities_startStation[self.input_startStationCity],self.StationSort_startStation[self.input_startStation])).click()

# the end_station ============================================================================================================    
    def find_the_end_city(self):    
        # click the end station button
        self.driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[1]/div[4]/div[2]/button[1]").click()
        # choose the city
        self.driver.find_element(By.XPATH, "//*[@id='mainline']/div[1]/ul/li[{0}]/button".format(self.citiesSort_startStation[self.input_endStationCity])).click()

    def find_the_end_station(self):        
        # click the end station 
        self.driver.find_element(By.XPATH, "//*[@id='{0}']/ul/li[{1}]/button".format(self.cities_startStation[self.input_endStationCity],self.stationSort_endStation[self.input_endStation])).click()
# choose the date and time =====================================================================================================================================
    def find_the_date(self):
        self.driver.execute_script("document.getElementById('rideDate').value='{0}'".format(self.input_date))
    def find_the_begin(self):
        self.driver.execute_script("document.getElementById('startTime').value='{0}'".format(self.input_startTime))
    def find_the_end(self):
        self.driver.execute_script("document.getElementById('endTime').value='{0}'".format(self.input_endTime))
        # click search button
        self.last_url = self.driver.current_url
        self.element = self.driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[3]/div[2]/input").click()
        # wait for page jump (most 30 times)
        self.retry_count = 30
        self.errorMessage = ''
        while self.last_url == self.driver.current_url and self.retry_count > 0:
            self.retry_count -=1
            if self.doc("#errorDiv").attr('style') != "display: none":
                self.errorMessage = self.doc("#errorDiv .mag-error").text()
                break
        # print the table
        if self.doc("#errorDiv").attr('style') == "display: none" and self.errorMessage == "":
            self.result_html = self.driver.find_element(By.CSS_SELECTOR,"*").get_attribute("outerHTML")
            self.result_doc = pq(self.result_html)
            self.alterMessage = self.result_doc("#content > div.alert.alert-warning").text()
            if self.alterMessage != '':
                print(self.alterMessage)
            else:
                self.result_doc("#pageContent > div > table > tbody > tr.trip-column")
                    
    # exit
    # time.sleep(2)
    # driver.quit()
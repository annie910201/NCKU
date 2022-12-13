from selenium import webdriver
from pyquery import PyQuery as pq #name PyQuery as pq
from tabulate import tabulate
import time
from selenium.webdriver.common.by import By

global driver
global html
global doc

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

class train_parser():
    def open_driver():
        # get the website
        driver = webdriver.Chrome("D:\\chromedriver_win32\chromedriver") # open the chrome by chromedriver
        driver.get("https://www.railway.gov.tw/tra-tip-web/tip/tip001/tip112/gobytime") # open the page of 台鐵網站
        html = driver.find_element(By.CSS_SELECTOR,"*").get_attribute("outerHTML") # locate element by css selector
        doc = pq(html) # can get all nodes
        # the start_station ============================================================================================================
        print("縣市: ")
        count = 2
        for city in doc("#mainline > div:nth-child(1) > ul > li:nth-child(n+2)").items():# cities name in doc
            print(city.text()) # print all start station cities
            temp_city_id = doc("#mainline > div:nth-child(1) > ul > li:nth-child("+ str(count) +") > button").attr("data-type")
            citiesSort_startStation[city.text()] = count
            cities_startStation[city.text()] = temp_city_id # get city id
            count +=1
        input_startStationCity = input("請輸入出發縣市: ")
        time.sleep(3)

        # click the startstation button
        driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[1]/div[2]/div[2]/button[1]").click()
        time.sleep(1)

        # choose the city
        driver.find_element(By.XPATH, "//*[@id='mainline']/div[1]/ul/li[{0}]/button".format(citiesSort_startStation[input_startStationCity])).click()
    def input_start_station():
    # print the station in the city
        print("站名: ")
        stationCount = 1
        for station in doc("#{0} > ul > li:nth-child(n+1) > button".format(cities_startStation[input_startStationCity])).items():
            StationSort_startStation[station.text()] = stationCount
            print(station.text())
            stationCount+=1
            
        # input the end station
        input_startStation = input("請輸入出發站: ")
        time.sleep(1)

        # click the start station
        driver.find_element(By.XPATH, "//*[@id='{0}']/ul/li[{1}]/button".format(cities_startStation[input_startStationCity],StationSort_startStation[input_startStation])).click()
    def input_end_city():
        # the end_station ============================================================================================================
        input_endStationCity = input("請輸入抵達縣市: ")
        time.sleep(3)

        # click the end station button
        driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[1]/div[4]/div[2]/button[1]").click()
        time.sleep(1)

        # choose the city
        driver.find_element(By.XPATH, "//*[@id='mainline']/div[1]/ul/li[{0}]/button".format(citiesSort_startStation[input_endStationCity])).click()
    def input_end_station():
        # print the station
        print("站名: ")
        endStationCount = 1
        for station in doc("#{0} > ul > li:nth-child(n+1) > button".format(cities_startStation[input_endStationCity])).items():
            stationSort_endStation[station.text()] = endStationCount
            print(station.text())
            endStationCount+=1
            
        input_endStation = input("請輸入抵達站: ")
        time.sleep(1)
        # click the end station =>後面被蓋住了
        driver.find_element(By.XPATH, "//*[@id='{0}']/ul/li[{1}]/button".format(cities_startStation[input_endStationCity],stationSort_endStation[input_endStation])).click()
    def input_date():
        # choose the date and time =====================================================================================================================================
        input_date = input("請輸入日期(西元年/月/日): ")
        driver.execute_script("document.getElementById('rideDate').value='{0}'".format(input_date))
    def input_start_time():
        input_startTime = input("請輸入出發時間(起): ")
        driver.execute_script("document.getElementById('startTime').value='{0}'".format(input_startTime))
    def input_end_time():
        input_endTime = input("請輸入出發時間(迄): ")
        driver.execute_script("document.getElementById('endTime').value='{0}'".format(input_endTime))
        # click search button
        last_url = driver.current_url
        element = driver.find_element(By.XPATH, "//*[@id='queryForm']/div/div[3]/div[2]/input").click()
        time.sleep(1)

        # wait for page jump (most 30 times)
        retry_count = 30
        errorMessage = ''
        while last_url == driver.current_url and retry_count > 0:
            retry_count -=1
            if doc("#errorDiv").attr('style') != "display: none":
                errorMessage = doc("#errorDiv .mag-error").text()
                break
        time.sleep(1)

        # print the table
        if doc("#errorDiv").attr('style') == "display: none" and errorMessage == "":
            result_html = driver.find_element(By.CSS_SELECTOR,"*").get_attribute("outerHTML")
            result_doc = pq(result_html)
            
            alterMessage = result_doc("#content > div.alert.alert-warning").text()
            if alterMessage != '':
                print(alterMessage)
            else:
                result_doc("#pageContent > div > table > tbody > tr.trip-column")
                
                for train in result_doc("#pageContent > div > table > tbody > tr.trip-column").items():
                    temp_train_number = train.find("ul.train-number a").text()
                    temp_departure_time = train.children("td").eq(1).text()
                    temp_arrival_time = train.children("td").eq(2).text()
                    result_trans.append({'車次': temp_train_number, '出發時間':temp_departure_time, '抵達時間': temp_arrival_time})
                print(tabulate(result_trans, headers='keys', tablefmt="grid"))
        else:
            print(errorMessage)

        # exit
        time.sleep(2)
        driver.quit()
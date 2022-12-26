from transitions.extensions import GraphMachine
from utils import send_text_message
# import scrapy
from geopy.geocoders import Nominatim
from linebot.models import *
from train import *
from utils import * 
# from fsm import TocMachine

train = Find_the_train()
train.cities = set()
train.stations = set()
train.arrive = 0
train.city = 0
train.mode = 0

class TocMachine(GraphMachine):

    def __init__(self, **machine_configs):
        self.machine = GraphMachine(model=self, **machine_configs)
    ############### is going to ########################
    def is_going_to_start(self, event):
        text = event.message.text
        return True

    def is_going_to_search(self, event):
        text = event.message.text
        return text.lower() == '查詢'
    
    def is_going_to_location(self, event):
        return event.message.type == 'location'
    
    def is_going_to_link(self, event):
        text = event.message.text
        return text.lower() == '訂位連結'
    
    def is_going_to_input_start_city(self, event):
        text = event.message.text
        return text in train.cities
    
    def is_going_to_input_start_station(self, event):
        text = event.message.text
        return text in train.stations

    def is_going_to_input_end_city(self, event):
        text = event.message.text
        return text in train.cities
    
    def is_going_to_input_end_station(self, event):
        text = event.message.text
        return text in train.stations
    
    def is_going_to_input_date(self, event):
        text = event.message.text
        return train.time == 1
    
    def is_going_to_input_start_time(self, event):
        text = event.message.text
        return train.time == 2
    
    def is_going_to_input_end_time(self, event):
        text = event.message.text
        return train.time == 3
    
    def restart(self, event, correct_text):
        text = event.message.text
        if(text != correct_text):
            return True
        else:
            return False
    ################# on enter ###########################
    def on_restart(mode):
        train.mode = mode
    def on_enter_start(self,event):
        user_name = ""
        greet_send_button_message(event.reply_token, user_name)
    def on_enter_search(self, event):
        send_text_message(event.reply_token, '請輸入出發縣市:')
    
    def on_enter_location(self, event):
        UserId = str(event.source.user_id)
        geolocator = Nominatim(user_agent = f'{UserId}')
        location = geolocator.reverse(f'{event.message.latitude}, {event.message.longitude}')
        text=f'Get location message!\nYour User ID is [ {UserId} ]\n==-==-==-==-==-==-==-==-==-==-==\nCurrent location:\n{location.address}\n==-==-==-==-==-==-==-==-==-==-==\n{round(location.latitude, 6)}, {round(location.longitude, 6)}\n==-==-==-==-==-==-==-==-==-==-=='
        send_text_message(event.reply_token, text)
    
    def on_enter_link(self, event):
        text = 'https://www.railway.gov.tw/tra-tip-web/tip/tip001/tip121/query'
        send_text_message(event.reply_token, text)
        
    def on_enter_start_city(self, event):
        send_text_message(event.reply_token, '請輸入出發站:')
    
    def on_enter_start_station(self, event):
        send_text_message(event.reply_token, '請輸入抵達縣市:')

    def on_enter_end_city(self, event):
        send_text_message(event.reply_token, '請輸入抵達站:')
    
    def on_enter_end_station(self, event):
        send_text_message(event.reply_token, '請輸入日期(西元年/月/日): ')
    
    def on_enter_date(self, event):
        send_text_message(event.reply_token, '請輸入出發時間(起): ')
    
    def on_enter_start_time(self, event):
        send_text_message(event.reply_token, '請輸入出發時間(迄): ')
    
    def on_enter_end_time(self, event):
        reply = ""
        for result in train.result_doc("#pageContent > div > table > tbody > tr.trip-column").items(): 
            temp_train_number = result.find("ul.train-number a").text()
            temp_departure_time = result.children("td").eq(1).text()
            temp_arrival_time = result.children("td").eq(2).text()
            reply += f"{temp_train_number}:\n出發: {temp_departure_time} | 抵達: {temp_arrival_time}\n"
        send_text_message(event.reply_token, reply)

machine =TocMachine(
    states = ['user','start', 'search', 'location', 'link', 'start_city', 'start_station', 'end_city', 'end_station', 'date', 'start_time', 'end_time'],
    transitions = [
        {
            'trigger': 'advance', 
            'source': 'user', 
            'dest': 'start', 
            'conditions': 'is_going_to_start'
        },
        {
            'trigger': 'advance', 
            'source': 'user', 
            'dest': 'location', 
            'conditions': 'is_going_to_location'
        },
        {
            'trigger': 'advance', 
            'source': 'location', 
            'dest': 'start', 
            'conditions': 'is_going_to_start'
        },
        {
            'trigger': 'advance', 
            'source': 'start', 
            'dest': 'search', 
            'conditions': 'is_going_to_search'
        },
        {
            'trigger': 'advance', 
            'source': 'start', 
            'dest': 'link', 
            'conditions': 'is_going_to_link'
        },
        {
            'trigger': 'advance', 
            'source': 'search', 
            'dest': 'start_city', 
            'conditions': 'is_going_to_start_city'
        },
        {
            'trigger': 'advance', 
            'source': 'start_city', 
            'dest': 'start_station', 
            'conditions': 'is_going_to_start_station'
        },
        {
            'trigger': 'advance', 
            'source': 'start_city', 
            'dest': 'start_city', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'start_station', 
            'dest': 'start_station', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'start_station', 
            'dest': 'end_city', 
            'conditions': 'is_going_to_end_city'
        },
        {
            'trigger': 'advance', 
            'source': 'end_city', 
            'dest': 'end_station', 
            'conditions': 'is_going_to_end_station'
        },
        {
            'trigger': 'advance', 
            'source': 'end_city', 
            'dest': 'end_city', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'end_station', 
            'dest': 'end_station', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'end_station', 
            'dest': 'date', 
            'conditions': 'is_going_to_date'
        },
        {
            'trigger': 'advance', 
            'source': 'date', 
            'dest': 'date', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'date', 
            'dest': 'start_time', 
            'conditions': 'is_going_to_start_time'
        },
        {
            'trigger': 'advance', 
            'source': 'start_time', 
            'dest': 'end_time', 
            'conditions': 'is_going_to_end_time'
        },
        {
            'trigger': 'advance', 
            'source': 'start_time', 
            'dest': 'start_time', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': 'end_time', 
            'dest': 'end_time', 
            'conditions': 'restart'
        },
        {
            'trigger': 'advance', 
            'source': ['start','location', 'search', 'link', 'start_city', 'start_station', 'end_city', 'end_station', 'date', 'start_time', 'end_time'], 
            'dest': 'location', 
            'conditions': 'is_going_to_location'
        },
        { # back to user
            'trigger': 'go_back', 
            'source': ['start', 'search', 'link', 'start_city', 'start_station', 'end_city', 'end_station', 'date', 'start_time', 'end_time'],
            'dest': 'start', 
        },
    ],
    title = 'fsm',
    initial='user',
    auto_transitions=False,
    show_conditions=True,
)

machine.get_graph().draw('fsm.png', prog='dot', format='png')
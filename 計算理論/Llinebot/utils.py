import os

from linebot import LineBotApi, WebhookParser
from linebot.models import MessageEvent, TextMessage, TextSendMessage


channel_access_token = "P06zDUOQ8R/xqpUs270JwhvW7r3EWcjUSL2XHDL2xoEdEI8N5k80pukBo2b9wd4FLtoyvq6LoI84BAolfstYSaVMcmGNZ9pLvTs66tTJ/pgZdqA4vFBG5zcGj6qSINrYKWC/eq2AYK9PEoIwv2QXKQdB04t89/1O/w1cDnyilFU="


def send_text_message(reply_token, text):
    line_bot_api = LineBotApi(channel_access_token)
    line_bot_api.reply_message(reply_token, TextSendMessage(text=text))
    return "OK"

"""
def send_image_url(id, img_url):
    

def send_button_message(id, text, buttons):
    pass
"""

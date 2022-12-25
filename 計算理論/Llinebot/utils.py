from linebot import LineBotApi
from linebot.models import *
from env import *

channel_access_token = "P06zDUOQ8R/xqpUs270JwhvW7r3EWcjUSL2XHDL2xoEdEI8N5k80pukBo2b9wd4FLtoyvq6LoI84BAolfstYSaVMcmGNZ9pLvTs66tTJ/pgZdqA4vFBG5zcGj6qSINrYKWC/eq2AYK9PEoIwv2QXKQdB04t89/1O/w1cDnyilFU="


def send_text_message(reply_token, text):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(reply_token, TextSendMessage(text=text))
    return "OK"
def send_button_message(reply_token):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(  # 回復傳入的訊息文字
                reply_token,
                TemplateSendMessage(
                    alt_text='Buttons template',
                    template=ButtonsTemplate(
                        title='User Mode',
                        text='請選擇以下功能或者按左下角"+"提供您目前位置',
                        actions=[
                            MessageTemplateAction(
                                label='查詢',
                                text='查詢'
                            ),
                            MessageTemplateAction(
                                label='訂位連結',
                                text='訂位連結'
                            ),
                        ]
                    )
                )
            )
def error_send_button_message(reply_token):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(  # 回復傳入的訊息文字
                reply_token,
                TemplateSendMessage(
                    alt_text='Buttons template',
                    template=ButtonsTemplate(
                        title='User Mode',
                        text='錯誤可能:\n輸入有誤\n查無資料\n無此狀態或兩狀態間無transition\n請選擇以下功能或者按左下角"+"提供您目前位置',
                        actions=[
                            MessageTemplateAction(
                                label='查詢',
                                text='查詢'
                            ),
                            MessageTemplateAction(
                                label='訂位連結',
                                text='訂位連結'
                            ),
                            
                        ]
                    )
                )
            )
"""
def send_image_url(id, img_url):
    

def send_button_message(id, text, buttons):
    pass
"""

from linebot import LineBotApi
from linebot.models import *
from env import *

def send_text_message(reply_token, text):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(reply_token, TextSendMessage(text=text))
    return "OK"
def greet_send_button_message(reply_token, user_name):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(  # 回復傳入的訊息文字
                reply_token,
                TemplateSendMessage(
                    alt_text='Buttons template',
                    template=ButtonsTemplate(
                        title='Start Mode',
                        text='哈囉' + user_name + '~~~\n' + '請選擇以下功能或者按左下角"+"提供您目前位置',
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
def send_button_message(reply_token):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(  # 回復傳入的訊息文字
                reply_token,
                TemplateSendMessage(
                    alt_text='Buttons template',
                    template=ButtonsTemplate(
                        title='Start Mode',
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
def error_send_button_message(reply_token, error_text):
    linebot_api = LineBotApi(LINE_CHANNEL_ACCESS_TOKEN)
    linebot_api.reply_message(  # 回復傳入的訊息文字
                reply_token,
                TemplateSendMessage(
                    alt_text='Buttons template',
                    template=ButtonsTemplate(
                        title='Start Mode',
                        text=error_text + '\n\n將回到開始模式\n請選擇以下功能或者按左下角"+"提供您目前位置',
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


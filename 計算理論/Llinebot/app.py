from flask import Flask
import scrapy
from flask import request, abort
from linebot import LineBotApi, WebhookHandler
from linebot.exceptions import InvalidSignatureError
from linebot.models import *
from test import train_parser
app = Flask(__name__)

# set the channel access token and channel secret
linebot_api = LineBotApi('P06zDUOQ8R/xqpUs270JwhvW7r3EWcjUSL2XHDL2xoEdEI8N5k80pukBo2b9wd4FLtoyvq6LoI84BAolfstYSaVMcmGNZ9pLvTs66tTJ/pgZdqA4vFBG5zcGj6qSINrYKWC/eq2AYK9PEoIwv2QXKQdB04t89/1O/w1cDnyilFU=')
handler = WebhookHandler('878b68de24c168d0214b691aa795f679')

train = train_parser()
# check the data correct
@app.route('/callback',  methods= ['POST'])
def callback():
    signature = request.headers["X-Line-Signature"]
    body = request.get_data(as_text=True)
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        abort(400)
    return 'OK'

# if receive the user message, 
@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    message_text = event.message.text
    if message_text == "查詢":
        linebot_api.reply_message(event.reply_token, TextSendMessage(text = '請輸入您最近的火車站名稱'))
    
        
if __name__ == '__main__':
    app.run()
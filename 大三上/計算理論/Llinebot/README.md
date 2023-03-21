# TOC 2022
## Linebot
![](https://i.imgur.com/KbHJ8Rd.png)

## 製作動機
因為每次回家都需要坐火車，想製作一個機器人可以即時查詢班次

## Finite State Machine
![](https://i.imgur.com/OkWslGn.png)


- state:
    - ```user```: 初始模式，使用者無論輸入甚麼都會直接進入start
    - ```start```: 開始模式，若有資料輸入錯誤或打back回到此模式
    - ```search```: 開始查詢台鐵班次
    - ```location```: 返回使用者目前所處地址以及經緯度
    - ```link```: 給使用者台鐵訂位連結
    - ```start_city```: 獲取起始城市
    - ```start_station```: 獲取起始站
    - ```end_city```: 獲取抵達城市
    - ```end_station```: 獲取抵達站
    - ```date```: 獲取日期
    - ```start_time```: 獲取預計起始時間
    - ```end_time```: 獲取預計抵達時間
- 執行講解: 
    - 一開始執行app.py會進入user mode
    - 隨意輸入之後會進入start mode並選擇想要的功能
    - 進入search之後若有資料輸入錯誤便會跳回start mode
        - 若出發.抵達站或城市的資料輸入錯誤會重新回到該模式
        - 若日期.時間的資料格式輸入錯誤可以重新回到該模式(若輸入錯誤資料會等到最後到end_station才跳回)
    - link可以回傳台鐵訂票網站連結並回到start mode
    - location可在任何模式時切入，輸出完資料後會回到start mode
    - 在任意mode皆可輸入back回到start mode
- 模擬圖
    :::spoiler 起始狀態
    ![](https://i.imgur.com/RVNKvXt.jpg)
    :::
    :::spoiler 查詢台鐵班次
    ![](https://i.imgur.com/67rCRsd.jpg)
    :::
    :::spoiler 回傳定位
    ![](https://i.imgur.com/saKNC3V.jpg)
    :::
    :::spoiler 提供訂位網站
    ![](https://i.imgur.com/oX6k0Sn.jpg)
    :::
    :::spoiler back
    ![](https://i.imgur.com/7iHdjnz.jpg)
    :::
    :::spoiler 錯誤訊息
    站名或城市輸入錯誤
    ![](https://i.imgur.com/25YI3Ug.jpg)

    時間或日期格式輸入錯誤
    ![](https://i.imgur.com/jJkmIMV.jpg)

    查無班次
    ![](https://i.imgur.com/NmwOu1D.jpg)

    不存在的指令
    ![](https://i.imgur.com/KvdKCEU.jpg)
    :::

## Setup
### Prerequisite
- Python 3.7
- Pipenv
#### Install Dependency
- pipenv
```
pip3 install pipenv
pipenv --three
pipenv install
pipenv shell 
```
- 有關爬蟲
```
pip install pyquery
pip install tabulate
pip install selenium
```
- other
```
pip install -r requirements.txt
```
#### Secret Data
```LINE_CHANNEL_SECRET``` and ```LINE_CHANNEL_ACCESS_TOKEN``` is put in env.py, but the handled version is no both of them

#### Run Locally
- ngrok

    ```ngrok http 8000```
## Reference
example:[TOC-project-2020](https://github.com/NCKU-CCS/TOC-Project-2020)

flask: [ Flask 網站應用程式](https://ithelp.ithome.com.tw/m/articles/10294686)

爬蟲: [python網路爬蟲](https://www.youtube.com/watch?v=_tv-CNbX7aw)

template: [Line Messaging API 的各種訊息格式](https://ithelp.ithome.com.tw/articles/10198142?sc=rss.qu)

圖文選單 & 互動式文字: [2022 iThome 鐵人賽 軟體工程師的自我學習分享筆記系列](https://ithelp.ithome.com.tw/users/20151681/ironman/5688 )

GraphMachine: [transitions](https://github.com/pytransitions/transitions)

button: [按鈕樣板訊息(Buttons template message)](https://www.learncodewithmike.com/2020/07/line-bot-buttons-template-message.html)

user id: [用 Python 暢玩 Line bot - 22：使用者資訊](https://ithelp.ithome.com.tw/articles/10282156)

字串處理: [Python split 字串分割用法與範例](https://shengyu7697.github.io/python-split/)

圖片來源: [material icon](https://fonts.google.com/icons)

pygraphviz 安裝問題:

    step1: 安裝graphviz
        https://graphviz.org/download/
    step2: 點選下列網址，選擇自己的python版本
        https://github.com/CristiFati/Prebuilt-Binaries/tree/master/PyGraphviz/v1.5
    step3: 安裝後將.whl放入Graphviz資料夾內(預設C:\Program Files\Graphviz)
        打開終端機執行 pip install .whl檔名稱
    step4: 到vscode終端機安裝  pip install pygraphviz 
    step5: python app.py
    

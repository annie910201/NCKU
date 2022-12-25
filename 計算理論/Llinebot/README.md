flask: https://ithelp.ithome.com.tw/m/articles/10294686
template: https://ithelp.ithome.com.tw/articles/10198142?sc=rss.qu
好用的東東: https://ithelp.ithome.com.tw/users/20151681/ironman/5688

install: 
    pip install pyquery
    pip install selenium
    pip install tabulate
    
pygraphviz 安裝問題:
    step1: 安裝graphviz
        https://graphviz.org/download/
    step2: 點選下列網址，選擇自己的python版本
        https://github.com/CristiFati/Prebuilt-Binaries/tree/master/PyGraphviz/v1.5
    step3: 安裝後將.whl放入Graphviz資料夾內(預設C:\Program Files\Graphviz)
        打開終端機執行 pip install .whl檔名稱
    step4: 到vscode終端機安裝  pip install pygraphviz 
    step5: python app.py

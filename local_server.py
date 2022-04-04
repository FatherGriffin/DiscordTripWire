from flask import Flask
from pyautogui import press, typewrite

app = Flask(__name__)

#mute variable
mutestat = False

#default url route
@app.route("/")
def home():
    return "Home! <h1>Home<h1>"

#url path used for http requests
@app.route("/silence")
def door():
    press('-')
    global mutestat
    if mutestat is False:
        mutestat = True
        print("MUTED")
        return "<h1>Muted<h1>"
    else:
        mutestat = False
        print("UNMUTED")
        return "Unmuted"
        
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=7999)
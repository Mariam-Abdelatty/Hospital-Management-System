import pyttsx3
import pywhatkit
import pywhatkit as kt
import serial
import speech_recognition as sr
import datetime
import psutil
import pyjokes

listener = sr.Recognizer()
microphone = sr.Microphone()
r = sr.Recognizer()
my_mic = sr.Microphone(device_index=1)
engine = pyttsx3.init()

try:
    port = serial.Serial("COM3", 9600)
    print("Phycial body, connected.")
except:
    print("Unable to connect to my physical body")


def talk(s):
    engine.say(s)
    engine.runAndWait()


def take_command():
    try:
        with microphone as source:
            print('listening....')
            voice = r.listen(source)
            command = listener.recognize_google(voice, language='en-US')
            command = command.lower()

    except Exception as e:
        print(e)
        print("Say that again sir")
        return "None"

    return command


def voice_rate(Rate):
    newVoiceRate = Rate
    engine.setProperty('rate', newVoiceRate)


def time():
    Time = datetime.datetime.now().strftime("%I:%M:%S")
    talk("The current time is")
    talk(Time)


def date():
    year = datetime.datetime.now().year
    month = datetime.datetime.now().month
    date = datetime.datetime.now().day
    talk("Today's date is")
    talk(date)
    talk(month)
    talk(year)


def battery():
    battery = psutil.sensors_battery()
    talk("battery is at" + str(battery.percent))


def joke():
    voice_rate(140)
    talk(pyjokes.get_joke(language="en", category="all"))
    voice_rate(160)


def wishMe():
    hour = int(datetime.datetime.now().hour)
    if 0 <= hour < 12:
        talk("Good Morning Sir !")

    elif 12 <= hour < 18:
        talk("Good Afternoon Sir !")

    else:
        talk("Good Evening Sir !")


def run_alexa():
    command = take_command()
    print(command)
    if 'play' in command:
        song = command.replace('play', '')
        port.write(b'u')
        port.write(b'l')
        talk('playing ' + song)
        pywhatkit.playonyt(song)
        port.write(b'C')

    elif 'find' in command:
        info = command.replace('find', '')
        talk('finding ' + info)
        port.write(b'u')
        port.write(b'l')
        kt.search(info)

    elif 'time' in command:
        time()
    elif 'date' in command:
        date()

    elif 'battery' in command:
        battery()

    elif 'joke' in command:
        joke()

    elif 'how are you' in command:
        talk("I am fine, Thank you")
        talk("How are you, Sir")

    elif 'fine' in command or "good" in command:
        talk("It's good to know that your fine")

    elif 'what is your name' in command or 'what\'s your name' in command:
        talk("my name is zeko, your desktop assistant, how can i help you")

    elif 'uppercut' in command:
        port.write(b'U')

    elif 'kick' in command:
        port.write(b's')

    elif 'smash' in command:
        port.write(b'p')
        port.write(b'C')

    elif 'close' in command:
        talk("okay sir shutting down")
        exit()


wishMe()
talk("My name is Zeko, How can i help you")
while True:
    run_alexa()

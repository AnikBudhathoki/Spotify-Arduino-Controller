import serial
import pyautogui
from SwSpotify import spotify, SpotifyNotRunning
import time

old_song = ""
old_artist = ""


ard = serial.Serial('COM5', 9600) #Establish connection between Serial port and the Arduino. COM 5 is the port and 9600 is the baude rate
time.sleep(2)   #Wait 2 seconds for the connection to establish

#Function get_song takes two strings, old song and old artist, and updates them if there is a new song
def get_song(old_song, old_artist):

    # get current song
    current_song = spotify.song() +"\n"
    current_artist = spotify.artist() + "\n"

    #if new song write the new song to arduino and update the old song variable
    if current_song != old_song:
        ard.write(bytes(current_song, "utf-8"))
    old_song = current_song

    #if new artist, write the new artist to arduino and update global old artist variable
    if current_artist != old_artist:
        ard.write(bytes(current_artist, "utf-8"))

    old_artist = current_artist

#Function joystick gets input from joystick of arduino and translates it into spotify functions
def joystick():
    ard.flush()
    ser_bytes = ard.readline()
    decoded_bytes = ser_bytes[0:len(ser_bytes) - 2].decode("utf-8")
    if decoded_bytes == "Left":
        print("Left")
        pyautogui.hotkey('ctrl', 'left')
        time.sleep(0.2)
    elif decoded_bytes == "Right":
        pyautogui.hotkey('ctrl', 'right')
        time.sleep(0.2)
    elif decoded_bytes == "Up":
        pyautogui.press('volumeup')
        time.sleep(0.2)
    elif decoded_bytes == "Down":
        pyautogui.press('volumedown')
        time.sleep(0.2)

while True:
        get_song(old_song, old_artist)
        time.sleep(0.3)
        joystick()
        time.sleep(0.3)


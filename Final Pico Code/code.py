# using circuit py for easier audio use
# wav files must be 22kHz (or less), 16bit, and mono

import board
import random
from audiocore import WaveFile
from audiopwmio import PWMAudioOut as AudioOut
import digitalio

audio = AudioOut(board.GP15)
path = "sounds/"
active = digitalio.DigitalInOut(board.GP0)
active.direction = digitalio.Direction.INPUT
#if there is no connection to the source,
#it will be active with a pull up
active.pull = digitalio.Pull.UP

#we need to let the arduino know when the sound is done playing
audioActive = digitalio.DigitalInOut(board.GP2)
audioActive.direction = digitalio.Direction.OUTPUT
audioActive.value = False

def play_sound(filename):
    with open(path + filename, "rb") as wave_file:
        wave = WaveFile(wave_file)
        audioActive.value = True
        audio.play(wave)
        while audio.playing:
            pass
        audioActive.value = False # send signal to arduino to stop lights

#put system in a loop that will always
#run and if the active signal is true
#it will play a random audio file
while (True):
    if (active.value):
        #give a bigger number range and mod
        #by 4 so that it is more random,
        #I noticed the random class wasn't very good
        randomInt = random.randint(0, 1000)
        randomInt = randomInt % 5
        if (randomInt == 0):
            #22kHz, 16 bits, mono
            play_sound("dad1.wav")
        elif (randomInt == 1):
            play_sound("amy.wav")
        elif (randomInt == 2):
            play_sound("dad2.wav")
        elif (randomInt == 3):
            play_sound("matthew.wav")
        elif (randomInt == 4):
            play_sound("mom.wav")
# using circuit py for easier audio use
# wav files must be 22kHz (or less), 16bit, and mono

import board
import random
from audiocore import WaveFile
from audiopwmio import PWMAudioOut as AudioOut

audio = AudioOut(board.GP15)
path = "sounds/"

def play_sound(filename):
    with open(path + filename, "rb") as wave_file:
        wave = WaveFile(wave_file)
        audio.play(wave)
        while audio.playing:
            pass

#give a bigger number range and mod
#by 4 so that it is more random,
#I noticed the random class wasn't very good
randomInt = random.randint(0, 1200)
randomInt = randomInt % 6
if (randomInt == 0):
    #22kHz, 16 bits, mono
    play_sound("growl.wav")
elif (randomInt == 1):
    play_sound("amy.wav")
elif (randomInt == 2):
    play_sound("laughD.wav")
elif (randomInt == 3):
    play_sound("laughH.wav")
elif (randomInt == 4):
    play_sound("mom.wav")
elif (randomInt == 5):
    play_sound("matthew.wav")

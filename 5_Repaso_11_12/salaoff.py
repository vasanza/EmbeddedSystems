#!/usr/bin/env python3
import os

mytext='apagando sala'
os.system("pico2wave -l es-ES -w L.wav \""+mytext+"\"")
os.system("aplay L.wav")




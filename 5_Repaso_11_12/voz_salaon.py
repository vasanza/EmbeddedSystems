#!/usr/bin/env python3

import os

mytext='encendiendo sala'
os.system("pico2wave -l es-ES -w L.wav \""+mytext+"\"")
os.system("aplay L.wav")




import os
import pyautogui as gui
import time

os.system('./run < input.txt &')
gui.press('g')
time.sleep(10)
gui.press('q')
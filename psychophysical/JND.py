#!/usr/bin/env python3
import serial
import time
import keyboard
import random
import csv

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()

    distance_list = []

    for i in range(5):
        distance_list.append("a")
    for i in range(5):
        distance_list.append("b")
    for i in range(5):
        distance_list.append("c")
    for i in range(5):
        distance_list.append("d")
    for i in range(5):
        distance_list.append("e")
    for i in range(5):
        distance_list.append("f")
    for i in range(5):
        distance_list.append("g")
    for i in range(5):
        distance_list.append("h")
    for i in range(5):
        distance_list.append("i")
    for i in range(5):
        distance_list.append("j")
    for i in range(5):
    	distance_list.append("k")
    for i in range(5):
    	distance_list.append("l")

    
    row_list = [["first_pwm_value", "Input"]]

    random_state = None

    while True:
        test = ser.readline().decode()
        print(test)
        if "yes" in test or "no" in test:
            if len(distance_list) >= 1:
                row_list.append([random_state, test])
                with open('jnd1.csv', 'w', newline='') as file:
                    writer = csv.writer(file)
                    writer.writerows(row_list)
                random_state = random.choice(distance_list)
                distance_list.remove(random_state)
                data = random_state.encode('utf-8')
                print(data)
                print(len(distance_list))
                ser.write(data)
            else:
                print("TEST OVER!!")
        else:
            print(row_list[-1])
    
    

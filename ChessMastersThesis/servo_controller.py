import RPi.GPIO as GPIO
import time
import serial
from square import *
from force import *
from controller import *
from square_pins import *


class ServoController():

    startMarker = 60
    endMarker = 62

    serPort = "/dev/ttyUSB1"
    serPort2 = "/dev/ttyUSB0"
    serPort3 = "/dev/ttyACM0"
    baudRate = 9600
    
    old_mode = 0
    current_mode = 0

    try:

        ser = serial.Serial(serPort, baudRate, timeout=1)
        ser1 = serial.Serial(serPort2, baudRate, timeout=1)
        ser2 = serial.Serial(serPort3, baudRate, timeout=1)
        print("Serial port 1 " + serPort + " opened  Baudrate " + str(baudRate))
        print("Serial port 2 " + serPort2 + " opened  Baudrate " + str(baudRate))
        print("Serial port 3 " + serPort3 + " opened  Baudrate " + str(baudRate))

    except KeyboardInterrupt:
        self.closeSer()

    def __init__(self, c):

        self.controller = c

        self.squares = square_pins.initialize()
        

    def read_loop(self):
        index = 0
        try:
            read = self.read_input_arduino()
            read_list = re.findall(r'.', read)
        except TypeError:
            return
        self.current_mode = read_list[0]
        if(len(read_list) > 65 or len(read_list) < 63):
            return
        for square in self.squares:
            index_read = read_list[index + 1]
            index = index + 1
            isNowOccupied = True if index_read == '1' else False
            if isNowOccupied != self.squares[square]["state"]["occupied"]:
                self.squares[square]["state"]["occupied"] = isNowOccupied
                if isNowOccupied is True:
                    self.controller.board_placed_square(square)
                else:
                    self.controller.board_lifted_square(square)
        self.old_mode = self.current_mode
        return

    def send_led_string(self, send_string):
        self.sendToArduino(f'8{self.current_mode}{send_string}9')


    def sendToArduino(self, sendStr):
        print(sendStr)
        self.ser.write(sendStr.encode('utf-8'))

    def read_input_arduino(self):
        try:
            first_part = self.ser1.readline().decode('utf-8').replace(">","").replace("<", "").replace("\r", "")
            second_part = self.ser2.readline().decode('utf-8').replace(">","").replace("<", "").replace("\r", "")
        except UnicodeDecodeError:
            return
        return f'{first_part}{second_part}'


    def closeSer(self):
        print("Closing serial connection")
        self.ser.close()
        self.ser1.close()
        self.ser2.close()

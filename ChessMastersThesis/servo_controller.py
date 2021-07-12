from chessboard import Board
import time
import serial
from square import *
from force import *
from controller import *
from square_pins import *
from board_controller import *
from GUI import *

import _thread
import board
import neopixel
import busio
import time
import math
from adafruit_pca9685 import PCA9685


class ServoController():

    def __init__(self, c):

        self.controller = c

        self.squares = square_pins.initialize()

    baton = _thread.allocate_lock()

    i2c_bus = busio.I2C(board.SCL, board.SDA)

    pixels_len = 128
    pixels = neopixel.NeoPixel(board.D10, pixels_len)

    pca1 = PCA9685(i2c_bus, address=0x40)
    pca2 = PCA9685(i2c_bus, address=0x41)
    pca3 = PCA9685(i2c_bus, address=0x42)
    pca4 = PCA9685(i2c_bus, address=0x43)
    pca5 = PCA9685(i2c_bus, address=0x44)
    pca6 = PCA9685(i2c_bus, address=0x45)
    pca7 = PCA9685(i2c_bus, address=0x46)
    pca8 = PCA9685(i2c_bus, address=0x47)
    pca9 = PCA9685(i2c_bus, address=0x48)
    pca10 = PCA9685(i2c_bus, address=0x49)
    pca11 = PCA9685(i2c_bus, address=0x4A)
    pca12 = PCA9685(i2c_bus, address=0x4B)

    pca1.frequency = 1600
    pca2.frequency = 1600
    pca3.frequency = 1600
    pca4.frequency = 1600
    pca5.frequency = 1600
    pca6.frequency = 1600
    pca7.frequency = 1600
    pca8.frequency = 1600
    pca9.frequency = 1600
    pca10.frequency = 1600
    pca11.frequency = 1600
    pca12.frequency = 1600

    pca_list = [pca1, pca2, pca3, pca4, pca5, pca6, pca7, pca8, pca9, pca10, pca11, pca12]

    startMarker = 60
    endMarker = 62

    serPort2 = "/dev/ttyUSB0"
    serPort3 = "/dev/ttyACM0"
    baudRate = 9600
    
    old_mode = 0
    current_mode = 0

    try:

        ser1 = serial.Serial(serPort2, baudRate, timeout=1)
        ser2 = serial.Serial(serPort3, baudRate, timeout=1)
        print("Serial port 2 " + serPort2 + " opened  Baudrate " + str(baudRate))
        print("Serial port 3 " + serPort3 + " opened  Baudrate " + str(baudRate))

    except KeyboardInterrupt:
        print("closing")
        

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
        self.sendToArduino(f'{self.current_mode}{send_string}')

    def sendToArduino(self, sendStr):
        self.updateBoard(sendStr)

    def read_input_arduino(self):
        try:
            first_part = self.ser1.readline().decode('utf-8').replace(">","").replace("<", "").replace("\r", "")
            second_part = self.ser2.readline().decode('utf-8').replace(">","").replace("<", "").replace("\r", "")
        except UnicodeDecodeError:
            return
        return f'{first_part}{second_part}'

    
    def updateBoard(self, Board_string):
        if Board_string[0] is '0':
            self.turn_off_visual()
            self.turn_off_magnet()
        elif Board_string[0] is '1':
            self.demo_mode()
        elif Board_string[0] is '2':
            self.turn_off_visual()
            self.turn_off_magnet()
        elif Board_string[0] is '3':
            self.update_led(Board_string)
        elif Board_string[0] is '4':
            self.turn_off_visual()
            self.update_magnet(Board_string)
        elif Board_string[0] is '5':
            self.update_led(Board_string)
            self.update_magnet(Board_string)
        elif Board_string[0] is '6':
            self.gui.startPos()
            

    def turn_off_visual(self):
        self.pixels.fill((0, 0, 0))
    
    def turn_off_magnet(self):
        for i in range(12):
            self.pca_list[i].channels[0].duty_cycle = 0
            self.pca_list[i].channels[1].duty_cycle = 0
            self.pca_list[i].channels[2].duty_cycle = 0
            self.pca_list[i].channels[3].duty_cycle = 0
            self.pca_list[i].channels[4].duty_cycle = 0
            self.pca_list[i].channels[5].duty_cycle = 0
            self.pca_list[i].channels[6].duty_cycle = 0
            self.pca_list[i].channels[7].duty_cycle = 0
            self.pca_list[i].channels[8].duty_cycle = 0
            self.pca_list[i].channels[9].duty_cycle = 0
            self.pca_list[i].channels[10].duty_cycle = 0
            self.pca_list[i].channels[11].duty_cycle = 0
            self.pca_list[i].channels[12].duty_cycle = 0
            self.pca_list[i].channels[13].duty_cycle = 0
            self.pca_list[i].channels[14].duty_cycle = 0
            self.pca_list[i].channels[15].duty_cycle = 0

    def update_led(self, update_string):
        for i in range(63):
            if update_string[i + 1] is '1' or update_string[i + 1] is '2':
                self.pixels[i * 2] = (100,100,100)
            else:
                self.pixels[i * 2] = (0,0,0)
        
    
    def update_magnet(self, update_string):
        for i in range(63):
            board_number_1 = math.floor(i * 3 / 16)
            board_number_2 = math.floor(board_number_1)
            board_number_3 = math.floor(board_number_1)
            pin_number_1 = math.floor(i * 3 % 16)
            pin_number_2 = math.floor(pin_number_1 + 1)
            pin_number_3 = math.floor(pin_number_1 + 2)

            if pin_number_2 > 15:
                board_number_2 = math.floor(board_number_1 + 1)
                pin_number_2 = math.floor(((i * 3) + 1) % 16)

            if pin_number_3 > 15:
                board_number_3 = math.floor(board_number_1 + 1)
                pin_number_3 = math.floor(((i * 3) + 2) % 16)
            if update_string[i + 1] is '2': # Attraction
                self.pca_list[board_number_1].channels[pin_number_1].duty_cycle = 0
                self.pca_list[board_number_2].channels[pin_number_2].duty_cycle = 0xffff
                self.pca_list[board_number_3].channels[pin_number_3].duty_cycle = 0xffff
            elif update_string[i + 1] is '3': # Repulsion
                self.pca_list[board_number_1].channels[pin_number_1].duty_cycle = 0xffff
                self.pca_list[board_number_2].channels[pin_number_2].duty_cycle = 0
                self.pca_list[board_number_3].channels[pin_number_3].duty_cycle = 0xffff
            elif update_string[i + 1] is '4': # Hold pieces in place 50% strength
                continue
            else: # Turn off magnets for neutral moves
                self.pca_list[board_number_1].channels[pin_number_1].duty_cycle = 0
                self.pca_list[board_number_2].channels[pin_number_2].duty_cycle = 0
                self.pca_list[board_number_3].channels[pin_number_3].duty_cycle = 0

    def demo_mode(self):
        
        self.pca4.frequency = 60
        self.pca5.frequency = 60  
        self.pca6.frequency = 60
        self.pca7.frequency = 60

        # A4: Neutral
        self.pixels[48] = ((100, 100, 100))
        self.pca_list[4].channels[8].duty_cycle = 0
        self.pca_list[4].channels[9].duty_cycle = 0
        self.pca_list[4].channels[10].duty_cycle = 0

        # B5: Repulsion feedback
        self.pixels[66] = ((100, 100, 100))
        self.pca_list[6].channels[3].duty_cycle = 0xffff
        self.pca_list[6].channels[4].duty_cycle = 0
        self.pca_list[6].channels[5].duty_cycle = 0xffff

        # C4: Repulsive vibration pattern
        self.pixels[52] = ((100, 100, 100))
        self.pca_list[4].channels[14].duty_cycle = 0xffff
        self.pca_list[4].channels[15].duty_cycle = 0
        self.pca_list[5].channels[0].duty_cycle = 0xffff

        # D5 Attrative feedback
        self.pixels[70] = ((100, 100, 100))
        self.pca_list[6].channels[3].duty_cycle = 0
        self.pca_list[6].channels[4].duty_cycle = 0xffff
        self.pca_list[6].channels[5].duty_cycle = 0xffff

        # E4 
        self.pixels[56] = ((100, 100, 100))
        self.pca_list[5].channels[4].duty_cycle = 0
        self.pca_list[5].channels[5].duty_cycle = 0xffff
        self.pca_list[5].channels[6].duty_cycle = 0xffff


        



    def closeSer(self):
        print("Closing serial connection")
        self.ser1.close()
        self.ser2.close()

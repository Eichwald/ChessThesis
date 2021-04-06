import RPi.GPIO as GPIO
import time
import serial
from square import *
from force import *
from controller import *
from square_pins import *
import threading


class ServoController(threading.Thread):

    startMarker = 60
    endMarker = 62

    serPort = "/dev/ttyACM0"
    serPort2 = "/dev/ttyUSB0"
    baudRate = 9600
    try:
        ser = serial.Serial(serPort, baudRate)
        ser1 = serial.Serial(serPort2, baudRate)
        print("Serial port " + serPort + " opened  Baudrate " + str(baudRate))
        print("Serial port " + serPort2 + " opened  Baudrate " + str(baudRate))
    except KeyboardInterrupt:
        ser.close()

    def __init__(self, c):

        self.controller = c

        self.squares = square_pins.initialize()
        
        threading.Thread.__init__(self)

        self.start()


    '''def run(self):
        pass
        return
        for square in self.squares:
            read = GPIO.input(self.squares[square]["pins"]["photoResistor"])
            isNowOccupied = False if read == 1 else True
            if isNowOccupied != self.squares[square]["state"]["occupied"]:
                self.squares[square]["state"]["occupied"] = isNowOccupied
                if isNowOccupied:
                    # self.squares[square]["servo"].ChangeDutyCycle(NORTH)
                    self.controller.board_placed_square(square)
                else:
                    # self.squares[square]["servo"].ChangeDutyCycle(SOUTH)
                    self.controller.board_lifted_square(square)'''

    def run(self):
        time.sleep(5)
        while True:
            index = 0
            for square in self.squares:
                read = self.read_input_arduino()
                read_list = re.findall(r'.', read)
                index_read = read_list[index + 1]
                isNowOccupied = False if index_read == 1 else True
                if isNowOccupied != self.squares[square]["state"]["occupied"]:
                    self.squares[square]["state"]["occupied"] = isNowOccupied
                    if isNowOccupied:
                        # self.squares[square]["servo"].ChangeDutyCycle(NORTH)
                        self.controller.board_placed_square(square)
                    else:
                        # self.squares[square]["servo"].ChangeDutyCycle(SOUTH)
                        self.controller.board_lifted_square(square)


    def setLed(self, square, attackable):
        return
        if attackable:
            GPIO.output(self.squares[square]["pins"]["led"], GPIO.HIGH)
        else:
            GPIO.output(self.squares[square]["pins"]["led"], GPIO.LOW)

    def setForce(self, square: Square, force: Force):
        return
        currentForce = self.squares[square]["state"]["force"]
        if currentForce == force:
            return

        self.squares[square]["state"]["force"] = force

        if force == Force.neutral:
            self.squares[square]["servo"].ChangeDutyCycle(MID)
        elif force == Force.pull:
            self.squares[square]["servo"].ChangeDutyCycle(NORTH)
        elif force == Force.push:
            self.squares[square]["servo"].ChangeDutyCycle(SOUTH)

    def send_led_string(self, send_string):
        self.sendToArduino(send_string)
    # ======================================

    def sendToArduino(self, sendStr):
        self.ser.write(sendStr.encode('utf-8'))  # change for Python3

    # ======================================

    def recvFromArduino(self):

        ck = ""
        x = "z"  # any value that is not an end- or startMarker
        byteCount = -1  # to allow for the fact that the last increment will be one too many

        # wait for the start character
        while ord(x) != self.startMarker:
            x = self.ser.read()

        # save data until the end marker is found
        while ord(x) != self.endMarker:
            if ord(x) != self.startMarker:
                ck = ck + x.decode("utf-8")  # change for Python3
                byteCount += 1
            x = self.ser.read()
        return(ck)

    def read_input_arduino(self):
        return self.recvFromArduino2()

    def recvFromArduino2(self):

        ck = ""
        x = "z"  # any value that is not an end- or startMarker
        byteCount = -1  # to allow for the fact that the last increment will be one too many

        # wait for the start character
        while ord(x) != self.startMarker:
            x = self.ser1.read()

        # save data until the end marker is found
        while ord(x) != self.endMarker:
            if ord(x) != self.startMarker:
                ck = ck + x.decode("utf-8")  # change for Python3
                byteCount += 1
            x = self.ser1.read()
        return(ck)

    # ============================

    def waitForArduino(self):

        # wait until the Arduino sends 'Arduino Ready' - allows time for Arduino reset
        # it also ensures that any bytes left over from a previous message are discarded

        msg = ""
        while msg.find("Arduino is ready") == -1:

            while self.ser.inWaiting() == 0:
                pass

            msg = self.recvFromArduino()

            print(msg)  # python3 requires parenthesis
            print()

    def waitForArduino2(self):

        # wait until the Arduino sends 'Arduino Ready' - allows time for Arduino reset
        # it also ensures that any bytes left over from a previous message are discarded

        msg = ""
        while msg.find("Arduino2 is ready") == -1:

            while self.ser1.inWaiting() == 0:
                pass

            msg = self.recvFromArduino2()

            print(msg)  # python3 requires parenthesis
            print()

    # ======================================

    def closeSer(self):
        print("Closing serial connection")
        self.ser.close()

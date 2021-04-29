import RPi.GPIO as GPIO
import time
from square import *
from force import *
from controller import *
from square_pins import *


class square_pins():

        def initialize():
            square = {
                # 1
                Square.A1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H1: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 2
                Square.A2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H2: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 3
                Square.A3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H3: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 4
                Square.A4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H4: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 5
                Square.A5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H5: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 6
                Square.A6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H6: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 7
                Square.A7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H7: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # 8
                Square.A8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H8: {
                    "state": { "occupied": False, "force": Force.neutral }
                },
            }
            return square

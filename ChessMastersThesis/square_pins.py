import RPi.GPIO as GPIO
import time
from square import *
from force import *
from controller import *
from square_pins import *


class square_pins():

        def initialize():
            square = {
                # A
                Square.A1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26},
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 27 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.A8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # B
                Square.B1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.B8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # C
                Square.C1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.C8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # D
                Square.D1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.D8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # E
                Square.E1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.E8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # F
                Square.F1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.F8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # G
                Square.G1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.G8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                # H
                Square.H1: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H2: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H3: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H4: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H5: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H6: {
                    "pins": { "photoResistor": 9, "led": 1, "servo": 13 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H7: {
                    "pins": { "photoResistor": 15, "led": 2, "servo": 26 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
                Square.H8: {
                    "pins": { "photoResistor": 11, "led": 12, "servo": 19 },
                    "state": { "occupied": False, "force": Force.neutral }
                },
            }
            return square

from tkinter import *
from square import *
from piece import *
from color import *
from force import *

class Board(Frame):

    def __init__(self, parent, listener):
        Frame.__init__(self, parent)

        self.listener = listener
        self.board = Frame(parent)
        self.board.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankEight = Frame(self.board)
        rankEight.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankSeven = Frame(self.board)
        rankSeven.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankSix = Frame(self.board)
        rankSix.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankFive = Frame(self.board)
        rankFive.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankFour = Frame(self.board)
        rankFour.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankThree = Frame(self.board)
        rankThree.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankTwo = Frame(self.board)
        rankTwo.pack(side = TOP, fill = BOTH, expand = TRUE)

        rankOne = Frame(self.board)
        rankOne.pack(side = TOP, fill = BOTH, expand = TRUE)

        self.leds = {}
        self.labels = {}
        self.forceLabels = {}

        self._createSquare(rankOne, Square.A1)
        self._createSquare(rankOne, Square.B1)
        self._createSquare(rankOne, Square.C1)
        self._createSquare(rankOne, Square.D1)
        self._createSquare(rankOne, Square.E1)
        self._createSquare(rankOne, Square.F1)
        self._createSquare(rankOne, Square.G1)
        self._createSquare(rankOne, Square.H1)

        self._createSquare(rankTwo, Square.A2)
        self._createSquare(rankTwo, Square.B2)
        self._createSquare(rankTwo, Square.C2)
        self._createSquare(rankTwo, Square.D2)
        self._createSquare(rankTwo, Square.E2)
        self._createSquare(rankTwo, Square.F2)
        self._createSquare(rankTwo, Square.G2)
        self._createSquare(rankTwo, Square.H2)

        self._createSquare(rankThree, Square.A3)
        self._createSquare(rankThree, Square.B3)
        self._createSquare(rankThree, Square.C3)
        self._createSquare(rankThree, Square.D3)
        self._createSquare(rankThree, Square.E3)
        self._createSquare(rankThree, Square.F3)
        self._createSquare(rankThree, Square.G3)
        self._createSquare(rankThree, Square.H3)

        self._createSquare(rankFour, Square.A4)
        self._createSquare(rankFour, Square.B4)
        self._createSquare(rankFour, Square.C4)
        self._createSquare(rankFour, Square.D4)
        self._createSquare(rankFour, Square.E4)
        self._createSquare(rankFour, Square.F4)
        self._createSquare(rankFour, Square.G4)
        self._createSquare(rankFour, Square.H4)

        self._createSquare(rankFive, Square.A5)
        self._createSquare(rankFive, Square.B5)
        self._createSquare(rankFive, Square.C5)
        self._createSquare(rankFive, Square.D5)
        self._createSquare(rankFive, Square.E5)
        self._createSquare(rankFive, Square.F5)
        self._createSquare(rankFive, Square.G5)
        self._createSquare(rankFive, Square.H5)

        self._createSquare(rankSix, Square.A6)
        self._createSquare(rankSix, Square.B6)
        self._createSquare(rankSix, Square.C6)
        self._createSquare(rankSix, Square.D6)
        self._createSquare(rankSix, Square.E6)
        self._createSquare(rankSix, Square.F6)
        self._createSquare(rankSix, Square.G6)
        self._createSquare(rankSix, Square.H6)
        
        self._createSquare(rankSeven, Square.A7)
        self._createSquare(rankSeven, Square.B7)
        self._createSquare(rankSeven, Square.C7)
        self._createSquare(rankSeven, Square.D7)
        self._createSquare(rankSeven, Square.E7)
        self._createSquare(rankSeven, Square.F7)
        self._createSquare(rankSeven, Square.G7)
        self._createSquare(rankSeven, Square.H7)

        self._createSquare(rankEight, Square.A8)
        self._createSquare(rankEight, Square.B8)
        self._createSquare(rankEight, Square.C8)
        self._createSquare(rankEight, Square.D8)
        self._createSquare(rankEight, Square.E8)
        self._createSquare(rankEight, Square.F8)
        self._createSquare(rankEight, Square.G8)
        self._createSquare(rankEight, Square.H8)

    def _piece(self, piece: Piece, color: Color):
        pieces = {
            Piece.K: "♚" if color == Color.black else "♔",
            Piece.Q: "♛" if color == Color.black else "♕",
            Piece.R: "♜" if color == Color.black else "♖",
            Piece.B: "♝" if color == Color.black else "♗",
            Piece.N: "♞" if color == Color.black else "♘",
            Piece.P: "♟" if color == Color.black else "♙"
        }
        return pieces[piece]

    def _background(self, square: Square):
        if "1" in square.name:
            return ("#%02x%02x%02x" % (0, 102, 0)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (191, 170, 134))
        elif "2" in square.name:
            return ("#%02x%02x%02x" % (191, 170, 134)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (0, 102, 0))
        elif "3" in square.name:
            return ("#%02x%02x%02x" % (0, 102, 0)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (191, 170, 134))
        elif "4" in square.name:
            return ("#%02x%02x%02x" % (191, 170, 134)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (0, 102, 0))
        elif "5" in square.name:
            return ("#%02x%02x%02x" % (0, 102, 0)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (191, 170, 134))
        elif "6" in square.name:
            return ("#%02x%02x%02x" % (191, 170, 134)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (0, 102, 0))
        elif "7" in square.name:
            return ("#%02x%02x%02x" % (0, 102, 0)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (191, 170, 134))
        elif "8" in square.name:
            return ("#%02x%02x%02x" % (191, 170, 134)) if square.value % 2 != 0 else ("#%02x%02x%02x" % (0, 102, 0))
        
    def _foreground(self, color: Color):
        return 'white' if color == Color.white else 'black'

    def _createSquare(self, parent: Frame, square: Square):

        bg = self._background(square)

        label = Label(parent, text = " ", bg = bg, font=("Courier", 30))
        label.pack(side = LEFT, expand = TRUE, fill = BOTH)
        label.bind("<Button-1>", lambda e: self._squareClicked(square))
        self.labels[square] = label

        forceLabel = Label(label, text = Force.neutral.value, fg = 'white', bg = bg)
        forceLabel.place(relx= 1, rely = 1, y = -2, anchor = SE)
        self.forceLabels[square] = forceLabel

        led = Label(label, text = "", fg = 'red', bg = bg)
        led.place(relx=0.1, rely = 0.1, y = -2, anchor = N)
        self.leds[square] = led

    def setForce(self, square: Square, force: Force):
        self.forceLabels[square].configure(text = force.value)

    def attackable(self, isAttackable: bool, square: Square):
        self.leds[square].configure(text = "◉" if isAttackable else "")

    def mark(self, square: Square):
        self.labels[square].configure(bg = ("#%02x%02x%02x" % (0, 64, 255)))
        self.forceLabels[square].configure(bg = ("#%02x%02x%02x" % (0, 64, 255)))
        self.leds[square].configure(bg = ("#%02x%02x%02x" % (0, 64, 255)))

    def demark(self, square: Square):
        self.labels[square].configure(bg = self._background(square))
        self.forceLabels[square].configure(bg = self._background(square))
        self.leds[square].configure(bg = self._background(square))

    def _squareClicked(self, square):
        self.listener.board_clicked(square)

    def place(self, piece: Piece, color: Color, square: Square):
        fg = self._foreground(color)
        p = self._piece(piece, color)
        self.labels[square].config(text = p, fg = fg)
   
    def clear(self, square: Square):
        self.labels[square].config(text = " ")

    def clearAll(self):
        for square in Square:
            self.clear(square)
            self.demark(square)
            self.attackable(False, square)

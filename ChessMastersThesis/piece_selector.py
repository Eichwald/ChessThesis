from tkinter import *
from square import *
from piece import *
from color import *

class PieceSelector(Frame):

    def __init__(self, parent, selector_clicked_listener):
        Frame.__init__(self, parent)

        self.listener = selector_clicked_listener

        selector = Frame(parent)
        selector.pack(side = TOP, fill = BOTH, expand = TRUE)

        self.labels = {
            Color.white: {},
            Color.black: {}
        }

        whites = Frame(selector)
        whites.pack(side = TOP, fill = BOTH, expand = TRUE)

        self._addSelector(whites, Piece.K, Color.white)
        self._addSelector(whites, Piece.Q, Color.white)
        self._addSelector(whites, Piece.R, Color.white)
        self._addSelector(whites, Piece.B, Color.white)
        self._addSelector(whites, Piece.N, Color.white)
        self._addSelector(whites, Piece.P, Color.white)

        blacks = Frame(selector)
        blacks.pack(side = TOP, fill = BOTH, expand = TRUE)

        self._addSelector(blacks, Piece.K, Color.black)
        self._addSelector(blacks, Piece.Q, Color.black)
        self._addSelector(blacks, Piece.R, Color.black)
        self._addSelector(blacks, Piece.B, Color.black)
        self._addSelector(blacks, Piece.N, Color.black)
        self._addSelector(blacks, Piece.P, Color.black)


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

    def _addSelector(self, parent: Frame, piece: Piece, color: Color):

        label = Label(parent, text = self._piece(piece, color), bg = 'gray', font=("Courier", 44))
        label.pack(side = LEFT, expand = TRUE, fill = BOTH)
        label.bind("<Button-1>", lambda e: self._pieceClicked(piece, color))
        self.labels[color][piece] = label

    def mark(self, piece: Piece, color: Color):
        self.labels[color][piece].configure(bg = ("#%02x%02x%02x" % (0, 64, 255)))

    def demark(self, piece: Piece, color: Color):
        self.labels[color][piece].configure(bg = 'gray')

    def _pieceClicked(self, piece: Piece, color: Color):
        self.listener.selector_clicked(piece, color)
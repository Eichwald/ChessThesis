from tkinter import *
from square import *
from piece import *
from color import *
from chessboard import *
from piece_selector import *
import json
import random

PUBLIC_ENUMS = {
    'Square': Square,
    'Color': Color,
    'Piece': Piece
}

class EnumEncoder(json.JSONEncoder):
    def default(self, obj):
        if type(obj) in PUBLIC_ENUMS.values():
            return {"__enum__": str(obj)}
        return json.JSONEncoder.default(self, obj)

def as_enum(d):
    if "__enum__" in d:
        name, member = d["__enum__"].split(".")
        return getattr(PUBLIC_ENUMS[name], member)
    else:
        return d

class GUI:

   def __init__(self, board_controller):

      self.boards = []
      try:
         with open('board_data.json', 'r') as openfile: 
            self.boards = json.load(openfile, object_hook=as_enum)
      except OSError:
         print('Well darn.')
      

      self.window = Tk(className = "Chess admin")
      self.window.geometry("500x700")
      self.window.resizable(False, False)

      self.board_controller = board_controller
      self.board = Board(self.window, board_controller)
      self.board.pack(side = TOP, fill = BOTH, expand = TRUE)
      board_controller.board = self.board

      controls = Frame(self.window, bg = "gray")
      controls.pack(side = BOTTOM, fill = BOTH, expand = TRUE)

      clearButton = Button(controls, text = "Clear", command = self.clear, bg = "white", fg = "black")
      clearButton.pack()

      saveButton = Button(controls, text = "Save", command = self.save, bg = "white", fg = "black")
      saveButton.pack()

      randomButton = Button(controls, text = "Random", command = self.random, bg = "white", fg = "black")
      randomButton.pack()

      startPosButton = Button(controls, text = "StartPos", command = self.startPos, bg = "white", fg = "black")
      startPosButton.pack()

      self.startPos()

   def clear(self):
      self.board_controller.reset()

   def save(self):
      converted = {
         self.newmethod()
      }

      self.boards.append(converted)
      data = json.dumps(self.boards, cls=EnumEncoder)
      
      with open("board_data.json", "w") as outfile: 
         outfile.write(data) 
   
   def random(self):
      def e(s):
         if s == "a1": return Square.A1
         if s == "a2": return Square.A2
         if s == "a3": return Square.A3
         if s == "b1": return Square.B1
         if s == "b2": return Square.B2
         if s == "b3": return Square.B3
         if s == "c1": return Square.C1
         if s == "c2": return Square.C2
         if s == "c3": return Square.C3


      self.board_controller.clearForces()

      randomBoard = random.choice(self.boards)
      for square in randomBoard:
         if randomBoard[square] != None:
            piece = randomBoard[square]['piece']
            color = randomBoard[square]['color']
            self.board_controller.place(piece, color, e(square))
         else:
            self.board_controller.clear(e(square))

   def startPos(self): 
      print("GO TO startpos")
      self.board_controller.reset() 

      white_pawnPos = [Square.A2, Square.B2, Square.C2, Square.D2, Square.E2, Square.F2, Square.G2, Square.H2]
      black_pawnPos = [Square.A7, Square.B7, Square.C7, Square.D7, Square.E7, Square.F7, Square.G7, Square.H7]
      white_rookPos = [Square.A1, Square.H1]
      black_rookPos = [Square.A8, Square.H8]
      white_bishPos = [Square.C1, Square.F1]
      black_bishPos = [Square.C8, Square.F8]
      white_knigPos = [Square.B1, Square.G1]
      black_knigPos = [Square.B8, Square.G8]


      for pos in white_pawnPos:
         self.board_controller.place(Piece.P, Color.white, pos)
      for pos in black_pawnPos:
         self.board_controller.place(Piece.P, Color.black, pos)
      for pos in white_rookPos:
         self.board_controller.place(Piece.R, Color.white, pos)
      for pos in black_rookPos:
         self.board_controller.place(Piece.R, Color.black, pos)
      for pos in white_bishPos:
         self.board_controller.place(Piece.B, Color.white, pos)
      for pos in black_bishPos:
         self.board_controller.place(Piece.B, Color.black, pos)
      for pos in white_knigPos:
         self.board_controller.place(Piece.N, Color.white, pos)
      for pos in black_knigPos:
         self.board_controller.place(Piece.N, Color.black, pos)

      self.board_controller.place(Piece.K, Color.white, Square.E1)
      self.board_controller.place(Piece.K, Color.black, Square.E8)
      
      self.board_controller.place(Piece.Q, Color.white, Square.D1)
      self.board_controller.place(Piece.Q, Color.black, Square.D8)

      self.board_controller.new_game()


   def newmethod(self):
      {
         'a1': self.board_controller.board_data[Square.A1],
         'b1': self.board_controller.board_data[Square.B1],
         'c1': self.board_controller.board_data[Square.C1],
         'd1': self.board_controller.board_data[Square.D1],
         'e1': self.board_controller.board_data[Square.E1],
         'f1': self.board_controller.board_data[Square.F1],
         'g1': self.board_controller.board_data[Square.G1],
         'h1': self.board_controller.board_data[Square.H1],

         'a2': self.board_controller.board_data[Square.A2],
         'b2': self.board_controller.board_data[Square.B2],
         'c2': self.board_controller.board_data[Square.C2],
         'd2': self.board_controller.board_data[Square.D2],
         'e2': self.board_controller.board_data[Square.E2],
         'f2': self.board_controller.board_data[Square.F2],
         'g2': self.board_controller.board_data[Square.G2],
         'h2': self.board_controller.board_data[Square.H2],

         'a3': self.board_controller.board_data[Square.A3],
         'b3': self.board_controller.board_data[Square.B3],
         'c3': self.board_controller.board_data[Square.C3],
         'd3': self.board_controller.board_data[Square.D3],
         'e3': self.board_controller.board_data[Square.E3],
         'f3': self.board_controller.board_data[Square.F3],
         'g3': self.board_controller.board_data[Square.G3],
         'h3': self.board_controller.board_data[Square.H3],

         'a4': self.board_controller.board_data[Square.A4],
         'b4': self.board_controller.board_data[Square.B4],
         'c4': self.board_controller.board_data[Square.C4],
         'd4': self.board_controller.board_data[Square.D4],
         'e4': self.board_controller.board_data[Square.E4],
         'f4': self.board_controller.board_data[Square.F4],
         'g4': self.board_controller.board_data[Square.G4],
         'h4': self.board_controller.board_data[Square.H4],

         'a5': self.board_controller.board_data[Square.A5],
         'b5': self.board_controller.board_data[Square.B5],
         'c5': self.board_controller.board_data[Square.C5],
         'd5': self.board_controller.board_data[Square.D5],
         'e5': self.board_controller.board_data[Square.E5],
         'f5': self.board_controller.board_data[Square.F5],
         'g5': self.board_controller.board_data[Square.G5],
         'h5': self.board_controller.board_data[Square.H5],

         'a6': self.board_controller.board_data[Square.A6],
         'b6': self.board_controller.board_data[Square.B6],
         'c6': self.board_controller.board_data[Square.C6],
         'd6': self.board_controller.board_data[Square.D6],
         'e6': self.board_controller.board_data[Square.E6],
         'f6': self.board_controller.board_data[Square.F6],
         'g6': self.board_controller.board_data[Square.G6],
         'h6': self.board_controller.board_data[Square.H6],

         'a7': self.board_controller.board_data[Square.A7],
         'b7': self.board_controller.board_data[Square.B7],
         'c7': self.board_controller.board_data[Square.C7],
         'd7': self.board_controller.board_data[Square.D7],
         'e7': self.board_controller.board_data[Square.E7],
         'f7': self.board_controller.board_data[Square.F7],
         'g7': self.board_controller.board_data[Square.G7],
         'h7': self.board_controller.board_data[Square.H7],

         'a8': self.board_controller.board_data[Square.A8],
         'b8': self.board_controller.board_data[Square.B8],
         'c8': self.board_controller.board_data[Square.C8],
         'd8': self.board_controller.board_data[Square.D8],
         'e8': self.board_controller.board_data[Square.E8],
         'f8': self.board_controller.board_data[Square.F8],
         'g8': self.board_controller.board_data[Square.G8],
         'h8': self.board_controller.board_data[Square.H8],
      }


   def start(self):
      #self.window.mainloop()
      self.window.update_idletasks()
      self.window.update()

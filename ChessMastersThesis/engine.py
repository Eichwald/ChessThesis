from psutil import cpu_count, virtual_memory
from stockfish import Stockfish
from force import *
import string

class Engine():

    def __init__(self):
        self.stockfish = Stockfish(depth = 3, parameters={
            "Write Debug Log": True,
            "Threads": self._recommended_threads(),
            "Skill Level": 20, 
            "Minimum Thinking Time": 0,
            "Slow Mover": 0,
        })

        self.squares = []

        for rank in string.ascii_lowercase[:8]:
            rank
            for num in range(1,9):
                square = rank + str(num)
                self.squares.append(square)
        
		
    def _recommended_threads(self):
        return cpu_count()-2

    def _recommended_memory(self):
        return virtual_memory().available/(2*1024*1024)		


    def rateSquares(self, board, originPosition, oKingSquare):
        
        squareRatings = {}
        for square in self.squares:
            move = originPosition + square
            self.stockfish.set_fen_position(board)
            print(self.stockfish.get_fen_position) 
            squareRatings[square] = Force.push

            if oKingSquare == square:
                continue

            if self.stockfish.is_move_correct(move):
                self.stockfish.makeMove(move)
                
                eva = self.stockfish.get_evaluation()
                
                if eva['type'] == "mate" and abs(eva['value']) >= 0:
                    # squareRatings[square] = Force.pull
                    print("u sick")
                else:
                    print("no sicko")
                    # squareRatings[square] = Force.neutral
            
        return squareRatings

		
		
#engine = Engine()
#squareRatings = engine.rateSquares("8/8/8/8/8/1RK5/2Q5/k7 w - - 0 1", "c2")
#print(squareRatings)
#print(str(squareRatings["a3"]) + " " + str(squareRatings["b3"]) + " "  + str(squareRatings["c3"]))
#print(str(squareRatings["a2"]) + " " + str(squareRatings["b2"]) + " "  + str(squareRatings["c2"]))
#print(str(squareRatings["a1"]) + " " + str(squareRatings["b1"]) + " "  + str(squareRatings["c1"]))

#stockfish = Stockfish(depth = 3, parameters={
#            "Write Debug Log": True,
#            "Threads": 2,
#            "Skill Level": 20, 
#            "Minimum Thinking Time": 0,
#            "Slow Mover": 0,
#        })

#stockfish.set_fen_position("8/8/8/8/8/1K6/N7/1R6 w - - 0 1")
#print(stockfish.get_evaluation())


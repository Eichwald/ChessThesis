import re
from square import *
from piece import *
from color import *
from force import *
from engine import *
from stockfish import Stockfish

class BoardController():

    def __init__(self, controller):

        self.stockfish = Stockfish(depth = 3, parameters={
            "Write Debug Log": True,
            "Threads": self._recommended_threads(),
            "Skill Level": 20, 
            "Minimum Thinking Time": 0,
            "Slow Mover": 0,
        })
        self.stockfish._start_new_game()

        self.controller = controller


        self.engine = Engine()
        self.board = None
        self.selector = None

        self.selector_selected_piece = None
        self.selector_selected_color = None

        self.board_selected_square = None



        self.board_data = {
            Square.A1: None,
            Square.A2: None,
            Square.A3: None,
            Square.A4: None,
            Square.A5: None,
            Square.A6: None,
            Square.A7: None,
            Square.A8: None,

            Square.B1: None,
            Square.B2: None,
            Square.B3: None,
            Square.B4: None,
            Square.B5: None,
            Square.B6: None,
            Square.B7: None,
            Square.B8: None,

            Square.C1: None,
            Square.C2: None,
            Square.C3: None,
            Square.C4: None,
            Square.C5: None,
            Square.C6: None,
            Square.C7: None,
            Square.C8: None,

            Square.D1: None,
            Square.D2: None,
            Square.D3: None,
            Square.D4: None,
            Square.D5: None,
            Square.D6: None,
            Square.D7: None,
            Square.D8: None,

            Square.E1: None,
            Square.E2: None,
            Square.E3: None,
            Square.E4: None,
            Square.E5: None,
            Square.E6: None,
            Square.E7: None,
            Square.E8: None,

            Square.F1: None,
            Square.F2: None,
            Square.F3: None,
            Square.F4: None,
            Square.F5: None,
            Square.F6: None,
            Square.F7: None,
            Square.F8: None,

            Square.G1: None,
            Square.G2: None,
            Square.G3: None,
            Square.G4: None,
            Square.G5: None,
            Square.G6: None,
            Square.G7: None,
            Square.G8: None,

            Square.H1: None,
            Square.H2: None,
            Square.H3: None,
            Square.H4: None,
            Square.H5: None,
            Square.H6: None,
            Square.H7: None, 
            Square.H8: None,
        }
    

    def _recommended_threads(self):
        return cpu_count()-2

    def _recommended_memory(self):
        return virtual_memory().available/(2*1024*1024)	

    def selector_clicked(self, piece: Piece, color: Color):
        if (self.selector == None): return

        # if a square is marked on the board
        if (self.board_selected_square != None):
            self.board.demark(self.board_selected_square)
            self.place(piece, color, self.board_selected_square)
            self.board_selected_square = None
            return

        # if you mark another piece in the selector
        if (self.selector_selected_piece != None and self.selector_selected_color != None):
            self.selector.demark(self.selector_selected_piece, self.selector_selected_color)
        
        # demark if same selected again
        if (self.selector_selected_piece == piece and self.selector_selected_color == color):
            self.selector_selected_color = None
            self.selector_selected_piece = None
            self.selector.demark(self.selector_selected_piece, self.selector_selected_color)
            return

        self.selector_selected_color = color
        self.selector_selected_piece = piece
        self.selector.mark(piece, color)

    # marking a piece on the board
    def mark(self, square: Square):
        self.board.mark(square)

        if self.board_data[square] != None:
            self.applyForces(square)

    def move(self, fromSquare: Square, toSquare: Square):
        to_string = toSquare.name.lower()
        from_string = fromSquare.name.lower()
        full_string = f'{from_string}{to_string}'
        evaluation = self.stockfish.get_evaluation()
        if self.stockfish.is_move_correct(full_string) is True:
            self.stockfish.makeMove(full_string)
        else:
            print("not a valid move")
            print("witt is cool")
            self.board.demark(fromSquare)
            returnd

        # check for check-mate
        new_evaluation = self.stockfish.get_evaluation()
        if new_evaluation['type'] is 'mate' and new_evaluation['value'] is 0:
        	print(new_evaluation)
        	print("MATE")

        if abs(evaluation['value'] - new_evaluation["value"]) > 100:
        	print(new_evaluation)
        	print("blunder")

        if new_evaluation['type'] is'mate' and new_evaluation['value'] < 4:
        	print(new_evaluation)
        	print("mate in" + new_evaluation["value"])

        #Dont know if i need this yet
        occupied, color, piece = self.get(fromSquare)
        self.board.demark(fromSquare)
        self.clear(fromSquare)
        self.place(piece, color, toSquare)


    def board_clicked(self, square: Square):
        # if a piece is about to be placed
        if (self.selector_selected_piece != None and self.selector_selected_color != None):
            self.place(self.selector_selected_piece, self.selector_selected_color, square)
            self.selector.demark(self.selector_selected_piece, self.selector_selected_color)
            self.selector_selected_color = None
            self.selector_selected_piece = None
            return
        
        # if selecting a piece on the board to move, or moving selection
        if (self.board_selected_square == None):
            self.board_selected_square = square
            self.mark(square)
            return 

         # if deselecting
        if (self.board_selected_square == square):
            self.board.demark(self.board_selected_square)
            self.board_selected_square = None
            
            if self.board_data[square] != None:
                self.clearForces()
            return

        # if moving selection
        if (not self.occupied(self.board_selected_square)):
            self.board.demark(self.board_selected_square)
            self.board.mark(square)
            self.board_selected_square = square
            self.clearForces()
            return
        
        # if performing a move
        self.move(self.board_selected_square, square) 
        self.board_selected_square = None
        self.clearForces()

    def applyForces(self, fromSquare: Square, onlyOnSqaure: Square = None):
        move_to_squares = self.available_moves(fromSquare)
        best_moves = []
        new_best_move = self.stockfish.get_best_move()
        best_moves.append(new_best_move)

        def led(square):
            led_squares = []
            for moves in move_to_squares:
                led_squares.append(re.findall(r'..', moves)[1])
            return True if square.name.lower() in led_squares else False

        def force(square):
            push_force_squares = []
            for moves in move_to_squares:
                push_force_squares.append(re.findall(r'..', moves)[1])

            pull_square = fromSquare.name.lower() + square.name.lower()
            fromColor = self.getColor(fromSquare)
            toColor = self.getColor(square)
            # hvis modsat farve
            if toColor != None and toColor != fromColor:
                return Force.neutral

            if fromSquare.name.lower() + square.name.lower() in best_moves:
                return Force.pull

            if fromColor != toColor:
                return Force.neutral if square.name.lower() not in push_force_squares else Force.neutral #make push - not neutral
            
            else:
                return Force.neutral


	        # TODO:
	        # CHECK HOW FAST WE CAN GET EVAL FOR ALL 64 SQUARES (Maybe only for possible moves with current piece)        
	        # CHECK FOR BLUNDERS
	        # CHECK FOR MATES


        if onlyOnSqaure == None:
            for square in Square:
                self.board.setForce(square, force(square))
                #self.controller.setForce(square, force(square))
                self.board.attackable(led(square), square)
                #self.controller.setLed(square, led(square))
        else:
            self.board.setForce(onlyOnSqaure, force(onlyOnSqaure))
            #self.controller.setForce(onlyOnSqaure, force(onlyOnSqaure))
            self.board.attackable(led(onlyOnSqaure), onlyOnSqaure)
            #self.controller.setLed(onlyOnSqaure, led(onlyOnSqaure))

    def available_moves(self, square: Square):
        test = []
        for to_square in self.board_data:
            to_string = to_square.name.lower()
            from_string = square.name.lower()
            full_string = f'{from_string}{to_string}'
            if self.stockfish.is_move_correct(full_string) is True:
                test.append(full_string)
        return test

    def check_for_mate(self):
    	pass

    def clearForces(self):
        for square in Square:
            self.board.setForce(square, Force.neutral)
            self.controller.setForce(square, Force.neutral)
            self.board.attackable(False, square)
            self.controller.setLed(square, False)


    def clear(self, square: Square):
        self.board_data[square] = None
        self.board.clear(square)

    def occupied(self, square: Square):
        o, _, _ = self.get(square)
        return o

    def get(self, square: Square):
        color = self.getColor(square)
        piece = self.getPiece(square)
        if (piece == None or color == None):
            return False, None, None
        else:
            return True, color, piece
    
    def getCasedPiece(self, square: Square):
        data = self.board_data[square]
        return data["piece"].value if data['color'] == Color.white else data["piece"].value.lower()

    def getColor(self, square: Square):
        data = self.board_data[square]
        if (data == None):
            return None
        else: return data["color"]

    def getPiece(self, square: Square):
        data = self.board_data[square]
        if (data == None):
            return None
        else: return data["piece"]

    def place(self, piece: Piece, color: Color, square: Square):
        self.board.place(piece, color, square)
        self.board_data[square] = {
            "piece": piece,
            "color": color
        }

    def clearAll(self):
        for square in Square:
            self.clear(square)
            self.board.demark(square)
            
    
    def reset(self):
        self.clearAll()
        self.clearForces()

        self.board_selected_square = None

        self.selector_selected_piece = None
        self.selector_selected_color = None
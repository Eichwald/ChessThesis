from square import *
from GUI import *
from controller import *
from board_controller import *
from servo_controller import *
import threading

class App(threading.Thread):

   def __init__(self):
      self.controller = Controller()
      self.sc = ServoController(self.controller)
      self.controller.servo = self.sc
      self.bc = BoardController(self.controller)
      self.controller.board = self.bc
      self.gui = GUI(self.bc)
      threading.Thread.__init__(self)
      self.start()
      try:
         while True:
            # self.sc.run()
            self.gui.start()
      except KeyboardInterrupt:
         self.sc.closeSer()
         print("Bye Bye")

   def run(self):
      print("running")
       


if __name__ == "__main__":
   app = App()
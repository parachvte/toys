import turtle

print '#1: The Giraffe Shuffle'

class Giraffes():
	def rightFootForward(self):
		print('right foot forward')
	def leftFootForward(self):
		print('left foot forward')
	def rightFootBackward(self):
		print('right foot back')
	def leftFootBackward(self):
		print('left foot back')
	def dance(self):
		self.leftFootForward()
		self.leftFootBackward()
		self.rightFootForward()
		self.rightFootBackward()
		self.leftFootBackward()
		self.rightFootBackward()
		self.rightFootForward()
		self.leftFootForward()
reginald = Giraffes()
reginald.dance()
raw_input()

print '#2: turtle pitchfork'
p1 = turtle.Pen()
p1.forward(140)
p1.left(90)
p1.forward(30)
p1.right(90)
p1.forward(30)

p2 = turtle.Pen()
p2.forward(140)
p2.right(90)
p2.forward(30)
p2.left(90)
p2.forward(30)

p3 = turtle.Pen()
p3.forward(100)
p3.left(90)
p3.forward(60)
p3.right(90)
p3.forward(60)

p4 = turtle.Pen()
p4.forward(100)
p4.right(90)
p4.forward(60)
p4.left(90)
p4.forward(60)

raw_input()

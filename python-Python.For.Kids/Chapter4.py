import turtle

t = turtle.Pen()
'''#1 rectangle'''
for i in range(4):
	t.forward(100)
	t.left(90)
raw_input()

'''#2 a triangle'''
t.reset()
for i in range(4):
	t.forward(100)
	t.left(120)
raw_input()

'''#3 a box without corners'''
t.reset()
for i in range(4):
	t.forward(80)
	t.up()
	t.forward(20)
	t.left(90)
	t.forward(20)
	t.down()
raw_input()
	
''' Chapter 11 more turtle graphics
Pen p
p.color(0.5, 0.5, 0.5) #(r,g,b)
p.begin_fill()
p.end_fill()
p.circle(r)
'''
import turtle
t = turtle.Pen()

print '#1: drawing an octagon'
def draw_octagon():
    for i in range(8):
        t.forward(50)
        t.left(45)
draw_octagon()
raw_input()

print '#2: drawing a filled octagon'
def draw_octagon(color):
    t.color(color)
    t.begin_fill()
    for i in range(8):
        t.forward(50)
        t.left(45)
    t.end_fill()
draw_octagon("red")
raw_input()

print '#3: another star-drawing function'
t.reset()
def draw_star(size, points):
    angle = 360.0 / points
    for i in range(points):
        t.forward(size)
        langle = 180.0 - 180.0 / points
        t.left(langle)
        t.forward(size)
        t.right(langle - angle)
draw_star(50, 5)

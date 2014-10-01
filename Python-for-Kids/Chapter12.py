from Tkinter import *
import random

#1 fill the screen with triangles
tk = Tk()
W = H = 600
canvas = Canvas(tk, width = W, height = H)
canvas.pack()
colors = ['red', 'green', 'blue', 'yellow', 'orange', 'black', 'purple']
def random_triangle():
    p1 = random.randrange(W)
    p2 = random.randrange(H)
    p3 = random.randrange(W)
    p4 = random.randrange(H)
    p5 = random.randrange(W)
    p6 = random.randrange(H)
    my_color = random.choice(colors)
    canvas.create_polygon(p1, p2, p3, p4, p5, p6, fill = my_color, outline = "")
for i in range(300): random_triangle()
tk.mainloop()

#2 the moving triangle
#3 the moving photo


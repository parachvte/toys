import Tkinter
import time

class Ball:
    def __init__(self, canvas, paddle, score, color):
        self.canvas = canvas
        self.paddle = paddle
        self.score = score
        self.id = self.canvas.create_oval(-10, -10, 10, 10, fill = color)
        self.canvas.move(self.id, 200, 300)
        self.width = self.canvas.winfo_width()
        self.height = self.canvas.winfo_height()
        self.dx = 3
        self.dy = -3
        self.hit_bottom = False
    
    def move(self):
        self.canvas.move(self.id, self.dx, self.dy)
        pos = self.canvas.coords(self.id)
        if self.dx < 0 and pos[0] <= 0:
            self.dx = -self.dx
            if self.dx > 10: self.dx /= 2
        if self.dx > 0 and pos[2] >= self.width:
            self.dx = -self.dx
            if self.dx < -10: self.dx /= 2
        if pos[1] <= 0:
            self.dy = -self.dy
        if pos[3] >= self.height:
            self.hit_bottom = True
        if self.hit_paddle(pos):
            self.dy = -self.dy * 1.1
            self.score.add()
    
    def hit_paddle(self, pos):
        paddle_pos = self.canvas.coords(self.paddle.id)
        if self.dy < 0: return False
        if pos[2] > paddle_pos[0] and pos[0] < paddle_pos[2]:
            if pos[1] < paddle_pos[1] and paddle_pos[1] < pos[3]:
                self.dx += self.paddle.dx / 2
                return True
        return False

    def destroy(self):
        self.canvas.delete(self.id)

class Paddle:
    def __init__(self, canvas, color):
        self.canvas = canvas
        self.id = self.canvas.create_rectangle(-60, -8, 60, 8, fill = color)
        self.width = canvas.winfo_width()
        self.canvas.move(self.id, self.width / 2, 400)
        self.canvas.bind_all("<KeyPress-Left>", self.turn_left)
        self.canvas.bind_all("<KeyPress-Right>", self.turn_right)
        self.dx = 0
    
    def turn_left(self, evt):
        self.dx -= 5
    
    def turn_right(self, evt):
        self.dx += 5
    
    def move(self):
        pos = self.canvas.coords(self.id)        
        if 0 <= pos[0] + self.dx and pos[2] + self.dx <= self.width:
            self.canvas.move(self.id, self.dx, 0)
        self.dx = 0
    
    def destroy(self):
        self.canvas.delete(self.id)

class Score:
    def __init__(self, canvas, color):
        self.canvas = canvas
        self.score = 0
        self.id = self.canvas.create_text(370, 10, text = "score : " + str(self.score), fill = color)
    
    def add(self):
        self.score += 10
        self.canvas.itemconfig(self.id, text = "score : " + str(self.score))
    
    def destroy(self):
        self.canvas.delete(self.id)

def get_start():
    start_button.config(state = "disabled")
    canvas.itemconfig(game_over_text, state = "hidden")
    score = Score(canvas, "red")
    paddle = Paddle(canvas, "brown")
    ball = Ball(canvas, paddle, score, "red")

    while 1:
        if ball.hit_bottom:
            canvas.itemconfig(game_over_text, state = "normal")
            break
        ball.move()
        paddle.move()
        tk.update_idletasks()
        tk.update()
        time.sleep(0.03)
    
    score.destroy()
    paddle.destroy()
    ball.destroy()
    canvas.itemconfig(start_button, state = "normal")
    start_button.config(state = "normal")

if __name__ == "__main__":
    tk = Tkinter.Tk()
    tk.title("Bounce!")
    tk.resizable(0, 0) #not resizable
    tk.wm_attributes("-topmost", 1)
    W = 400
    H = 500
    canvas = Tkinter.Canvas(tk, width = W, height = H)
    canvas.pack()
    
    start_button = Tkinter.Button(tk, width = 20, text = "Start", command = get_start)
    #canvas.move(start_button, 300, 300)
    start_button.pack()
    end_button = Tkinter.Button(tk, width = 20, text = "Exit", command = tk.destroy)
    end_button.pack()
    
    game_over_text = canvas.create_text(W / 2, H / 2, text = "Game Over", font = ("Times", 18), state = "hidden")
    while 1:
        tk.update()
        
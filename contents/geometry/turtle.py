from turtle import *
S=1000; setworldcoordinates(-S,-S,S,S); ht()
screensize(S); speed(10000000); tp = teleport

def p2(x, y, name=''): tp(x, y); write(name); dot()

def seg(x0, y0, x1, y1): p2(x0, y0); goto(x1, y1); p2(x1, y1)

def circ(x, y, r): tp(x,y-r); circle(r)

seg(0,-S,0,S); seg(-S,0,S,0);
for i in range(-S,S,S//5): p2(i, 0, str(i)) or p2(0, i, str(i))


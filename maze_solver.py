#!/usr/bin/env python3
import sys
import numpy as np
from matplotlib import pyplot as plt

line_list = []
node_list = []
abbrev_dict = { 'l':'left', 'r':'right','u':'up','d':'down'}

def attempt(start_tup,moves,max_x,max_y):
    
    x = start_tup[0]
    y = start_tup[1]
    x_pts = [x]
    y_pts = [y]
    for move in moves:
        if move == 'l':
            new_x = x - 0.5
            new_y = y
            if new_x < 0:
                print("Past left boundary!")
                print(x_pts)
                print(y_pts)
                sys.exit(-1)
            x = new_x
            y = new_y
                
        if move == 'r':
            new_x = x + 0.5
            new_y = y
            if new_x > max_x:
                print("Past right boundary!")
                print(x_pts)
                print(y_pts)
                sys.exit(-1)
            x = new_x
            y = new_y
                
        if move == 'u':
            new_x = x
            new_y = y + 0.5
            if new_y > max_y:
                print("Past upper boundary!")
                print(x_pts)
                print(y_pts)
                sys.exit(-1)
            x = new_x
            y = new_y
                
        if move == 'd':
            new_x = x
            new_y = y - 0.5
            if new_y < 0:
                print("Past lower boundary!")
                print(x_pts)
                print(y_pts)
                sys.exit(-1)
            x = new_x
            y = new_y
                
        x_pts.append(new_x)
        y_pts.append(new_y)
        plt.plot(x_pts,y_pts,c='r')
            
            

def ph(x,xn,y):
    plt.plot([x,xn],[y,y],c='k')
    l = abs(xn-x)
    for i in range(l):
        line_list.append([(x+i,y),(x+i+1,y)])    

def pv(x,y,yn):
    plt.plot([x,x],[y,yn],c='k')
    l = abs(yn-y)
    for i in range(l):
        line_list.append([(x,y+i),(x,y+i+1)])
    
def maze1():
    global line_list, node_list
    line_list = []
    node_list = []
    ph(1,10,5)
    ph(1,2,4)
    ph(4,5,4)
    ph(7,9,4)
    ph(1,4,3)
    ph(5,6,3)
    ph(9,10,3)
    ph(0,1,2)
    ph(3,4,2)
    ph(6,8,2)
    ph(1,3,1)
    ph(5,7,1)
    ph(8,10,1)
    ph(0,9,0)
    pv(0,0,5)
    pv(1,3,4)
    pv(2,2,3)
    pv(3,1,2)
    pv(3,3,5)
    pv(4,0,1)
    pv(4,2,3)
    pv(5,1,2)
    pv(5,3,4)
    pv(6,0,1)
    pv(6,2,3)
    pv(7,1,2)
    pv(7,3,4)
    pv(8,2,4)
    pv(9,2,3)
    pv(10,0,5)
    
def maze2():
    global line_list, node_list
    line_list = []
    node_list = []
    ph(1,10,5)
    ph(1,2,4)
    ph(4,5,4)
    ph(7,9,4)
    ph(1,4,3)
    ph(5,6,3)
    ph(9,10,3)
    ph(0,1,2)
    ph(3,4,2)
    ph(6,8,2)
    ph(1,3,1)
    ph(5,7,1)
    ph(8,10,1)
    ph(0,9,0)
    pv(0,0,5)
    pv(1,3,4)
    pv(2,2,3)
    pv(3,1,2)
    pv(3,3,5)
    pv(4,0,1)
    pv(4,2,3)
    pv(5,1,2)
    pv(5,3,4)
    pv(6,0,1)
    pv(6,2,3)
    pv(7,1,2)
    pv(7,3,4)
    pv(8,2,4)
    pv(9,2,3)
    pv(10,0,5)
    pv(4,4,5)
    
def maze3():
    global line_list, node_list
    line_list = []
    node_list = []
    ph(1,10,5)
    ph(1,2,4)
    ph(4,5,4)
    ph(7,9,4)
    ph(1,4,3)
    ph(5,6,3)
    ph(9,10,3)
    ph(0,1,2)
    ph(3,4,2)
    ph(6,8,2)
    ph(1,3,1)
    ph(5,7,1)
    ph(8,10,1)
    ph(0,9,0)
    pv(0,0,5)
    pv(1,3,4)
    pv(2,2,3)
    pv(3,1,2)
    pv(3,3,5)
    pv(4,0,1)
    pv(4,2,3)
    pv(5,1,2)
    pv(5,3,4)
    pv(6,0,1)
    pv(6,2,3)
    pv(7,1,2)
    pv(7,3,4)
    pv(8,2,4)
    pv(9,2,3)
    pv(10,0,5)
    ph(5,7,4)
    
def check_left(tup):
    (x,y) = tup
    fx = int(x)
    cx = fx
    fy = int(y)
    cy = fy + 1
    return [(fx,fy),(cx,cy)] not in line_list

def check_right(tup):
    (x,y) = tup
    fx = int(x) + 1
    cx = fx
    fy = int(y)
    cy = fy + 1
    return [(fx,fy),(cx,cy)] not in line_list
    
def check_up(tup):
    
    (x,y) = tup
    fx = int(x)
    cx = fx + 1
    fy = int(y) + 1
    cy = fy
    return [(fx,fy),(cx,cy)] not in line_list

def check_down(tup):
    (x,y) = tup
    fx = int(x)
    cx = fx + 1
    fy = int(y)
    cy = fy
    return [(fx,fy),(cx,cy)] not in line_list


def node_init(max_x,max_y):
    k = 0
    for j in range(max_y):
        for i in range(max_x):
            centre = ((2*i+1)/2,(2*j+1)/2)
            avail_directions = []
            if check_left(centre):
                neighbour = k-1
                avail_directions.extend(['l',neighbour])
            if check_right(centre):
                neighbour = k+1
                avail_directions.extend(['r',neighbour])
            if check_up(centre):
                neighbour = k+max_x
                avail_directions.extend(['u',neighbour])
            if check_down(centre):
                neighbour = k-max_x
                avail_directions.extend(['d',neighbour])
            '''if len(avail_directions)>4:
                print("Not a Binary maze")
                sys.exit(-1)'''
            node_list.append([centre,k,avail_directions])
            k+=1
    
    

if len(sys.argv) == 3 and sys.argv[1] == "empty":
    flag = 0
    ch = int(sys.argv[2])
elif len(sys.argv) == 4 and sys.argv[1] == "solution":
    ch = int(sys.argv[3])
    flag = 1
else:
    print("Not enough arguments")
    sys.exit(0)

if ch == 1:  
    maze1()
elif ch == 2:  
    maze2()
elif ch == 3:
    maze3()
else:
    print("Maze not found")
    sys.exit(0)
    
    
node_init(10,5)

f = open("maze.txt",'w')
for k1 in range(5*10):
    sl = node_list[k1]
    avail = sl[2]
    for i in range(int(len(avail)/2)):
        n = avail[2*i+1]


       
        f.write("{}{}\n".format(k1,avail[2*i]))
f.close()

if not flag:
    plt.show()

if flag:

    full_str = sys.argv[2]
    
    moves = []
    moves = list(full_str)
    for i in range(len(moves)):
        if moves[i] == '1':
            moves[i] = 'u'
        if moves[i] == '2':
            moves[i] = 'l'
        if moves[i] == '3':
            moves[i] = 'd'
        if moves[i] == '4':
            moves[i] = 'r'
            
    del moves[-1]

    
    attempt((0.5,4.5),moves,10,5)
            
    plt.show()
    
            
    





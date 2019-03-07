import math as m
import numpy as np

def makecanvas(w, h):
    # Creates an empty array as a canvas, populates array with space characters
    canvas = []
    for i in range(h):
        row = []
        for j in range(w):
            row.append(' ')
        canvas.append(row)
    return canvas
            

class Axes():
    # Functions to keep data on where axes, and their scale
    def __init__(self, j, i, iscale, jscale):
        # Checks for valid scale
        if iscale <= 0 or jscale <= 0:
            raise ValueError
        else:
            self.y = i
            self.yscale = jscale
            self.x = j
            self.xscale = iscale

class Canvas():
    def __init__(self, w, h):
        self.width = w
        self.height = h
        self.canvas = makecanvas(w, h)
        self.axes = ''
        self.haveaxes = False
    
    def plotaxes(self, i, j, iscale = 1, jscale = 1):
        # Draws and creates a set of axes to plot functions on
        self.axes = Axes(j ,i, iscale, jscale)
        # Fills in canvas to display axes visually on canvas
        for n in range(self.width):
            self.canvas[i][n] = '-'
        for m in range(self.height):
            self.canvas[m][j] = '|'
        self.canvas[i][j] = '+'
        self.haveaxes = True
        return
    
    def plotfunction(self, func, c = '@'):
        # Checks for axes to lot on
        if self.haveaxes != True:
            print("Canvas does not have Axes")
            return
        # For loops goes through each column in the canvas
        for n in range(self.width):
            # Changes column into axis value
            x = (n - self.axes.x) * self.axes.xscale
            # Evaluates axis value throught the function
            y = func(x) / self.axes.yscale
            # Changes evaluated value into a canvas value
            m = self.axes.y - y
            ##print(n, x, y, m)
            # Plots the value on the canvas
            if type(m) != complex:
                if m > 0 and m < self.height:
                    m = int(m)
                    self.canvas[m][n] = c
        return

    def plothistogram(self, data, bound_lower = 0, \
                         bound_upper = 0, bin_width = 1):
        # Sets default for upper bound to canvas width
        if bound_lower == bound_upper:
            bound_upper = self.width - 1
        # produces bin list
        bins = []
        for n in range(bound_lower, bound_upper, bin_width):
            bins.append([n, n + bin_width, 0])
        for point in data:
            for bn in bins:
                if point >= bn[0] and point < bn[1]:
                    bn[2] += 1
        # Error checks number of bins
        if len(bins) > self.width:
            print("Too many Bins")
            return
        # Plots the Histogram
        bin_width = m.floor(self.width/len(bins))
        column_line = 0
        for bn in bins:
            for n in range(column_line, column_line + bin_width):
                for o in range(bn[2]):
                    self.canvas[self.height - o - 1][n] = '@'
                column_line += 1
        return
          
    def printcanvas(self):
        # Draws the canvas on command line
        cprint = ''
        for n in self.canvas:
            for m in n:
                cprint += (m + ' ')
            cprint += '\n'
        print(cprint)
        return

def physicssim(self, startpoint, momentum, direction,\
                   friction, generations, show_path = False,\
                   show_generation = False):
        c_x_pos = startpoint[1]
        c_y_pos = startpoint[0]
        g_x_pos = int(startpoint[1]) - 1
        g_y_pos = int(startpoint[0]) - 1
        self.canvas[g_y_pos][g_x_pos] = '@'
        direction = m.radians(direction)
        for n in range(50):
            c.canvas[self.height - 1][n] = '_'
            c.canvas[n][0] = '|'
            c.canvas[n][self.width - 1] = '|'
            c.canvas[0][n] = '_'
        for gen in range(generations):
            moving = True
            c_y_pos += m.sin(direction) * momentum
            c_x_pos += m.cos(direction) * momentum
            while moving == True:
                if c_y_pos > self.height - 1:
                    y_mov_left = c_y_pos - self.height
                    c_y_pos = self.height - y_mov_left
                    direction = -1 * direction
                    
                elif c_y_pos < 0:
                    y_mov_left = -1 * c_y_pos
                    c_y_pos = y_mov_left
                    direction = -1 * direction
                    
                if c_x_pos > self.width - 1:
                    x_mov_left = c_x_pos - self.width
                    c_x_pos = self.width - x_mov_left
                    direction = m.pi - direction
                    
                elif c_x_pos < 0:
                    x_mov_left = -1 * c_x_pos
                    c_x_pos = x_mov_left
                    direction = m.pi - direction
                    
                if c_x_pos <= self.width and c_y_pos <= self.height\
                     and c_x_pos > 0 and c_y_pos > 0:
                    moving = False
            momentum -= friction
            ##print(c_x_pos, c_y_pos, direction)
            if show_path == True:
                self.canvas[g_y_pos][g_x_pos] = '#'
            else:
                self.canvas[g_y_pos][g_x_pos] = ' '
            g_y_pos = int(c_y_pos)
            g_x_pos = int(c_x_pos)
            self.canvas[g_y_pos][g_x_pos] = '@'
            if show_generation == True or gen in show_generation:
                self.printcanvas()

            print(c_x_pos, c_y_pos, direction)

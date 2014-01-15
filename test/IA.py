#!/usr/bin/env python

#******************************************************************************
#
#	IA: simple script to simulate an artificial intelligence algorithm
#		by: Sebastian Bustamante (macsebas33@gmail.com)
#******************************************************************************


#------------------------------------------------------------------------------
#Headers
#------------------------------------------------------------------------------

import numpy as np
import pygame
from pygame.locals import *
import sys


#------------------------------------------------------------------------------
#Classes
#------------------------------------------------------------------------------

class scenario:
    """Scenario class
    
    Class which contains all information related with the scenario for testing
    the IA algorithm
    
    """
    def __init__( self, M, N, percent, screen, background_image, block_image ):
	#Height
	self.M = M
	#Width
	self.N = N
	#Percent occupied by obstacles
	self.percent = percent
	#Scren when will be shown this scenario
	self.screen = screen
	#Pictures of visual elements
	self.background_image = background_image
	self.block_image = block_image
	
	#Initializing matrix
	self.matrix = np.zeros( (M,N) )
	
	
    def random_scenario( self ):
	"""random_scenario
	
	Recreate a random scenario
	
	"""
	#Sweeping the matrix
	for i in xrange(self.M):
	    for j in xrange(self.N):
		element = np.random.rand()
		if element < self.percent: element = 1
		else: element = 0
		self.matrix[i,j] = element
	self.matrix[0,0] = 0
	

    def build_scenario( self ):
	"""build_scenario
	
	Build the graphic windows with the scenario
	
	"""
	#Objects
	self.background = pygame.image.load( self.background_image ).convert()
	self.block = pygame.image.load( self.block_image ).convert()
	#Building the scenario
	self.screen.blit( self.background, (0,0) )
	for i in xrange(M):
	    for j in xrange(N):
		if self.matrix[i,j] == 1:
		    self.screen.blit( self.block, (20*i, 20*j) )

	


#------------------------------------------------------------------------------
#Program
#------------------------------------------------------------------------------		

#Dimension
M = int(sys.argv[1])
N = int(sys.argv[2])
percent = float(sys.argv[3])

#Pictures
background_image = 'background.bmp'
block_image = 'block.bmp'
ball_image = 'ball.bmp'

#Pygame init
pygame.init()

#Screen
screen = pygame.display.set_mode( (20*M, 20*N), 0, 32 )
pygame.display.set_caption("IA test (Finding algorithm): by Sebastian Bustamante")

#Initializing scenario
scene = scenario( M, N, percent, screen, background_image, block_image )
scene.random_scenario()

#Objects
ball = pygame.image.load(ball_image).convert_alpha()


x1 = 0
y1 = 0
displacement = 20
delay = 10

while True:	    
    #Detecting pressed key
    pressed_keys = pygame.key.get_pressed()
    
    #Discrete position of ball object
    i1 = x1/displacement
    j1 = y1/displacement
    
    #Exit
    for event in pygame.event.get():
	if event.type == QUIT:
	    sys.exit()
    if pressed_keys[K_ESCAPE]:	sys.exit()
    #Up
    elif pressed_keys[K_UP]:
	pygame.time.delay(delay)
	if j1>0 and scene.matrix[i1,j1-1] != 1 :	y1 -= displacement
    #Down
    elif pressed_keys[K_DOWN]:	
      	pygame.time.delay(delay)
	if j1+1<N and scene.matrix[i1,j1+1] != 1 :	y1 += displacement
    #Left
    elif pressed_keys[K_LEFT]:	
      	pygame.time.delay(delay)
	if i1>0 and scene.matrix[i1-1,j1] != 1:		x1 -= displacement
    #Right
    elif pressed_keys[K_RIGHT]:	
      	pygame.time.delay(delay)
	if i1+1<M and scene.matrix[i1+1,j1] != 1:	x1 += displacement
	 
    scene.build_scenario()
    screen.blit( ball, (x1, y1) )
    pygame.display.update()
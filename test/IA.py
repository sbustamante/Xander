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
    """scenario class
    
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



class character:
    """character
    
    Class which contains all information related with a character object of the game
    
    """
    def __init__( self, screen, main_image, matrix, x=0, y=0 ):
	#Pictures of visual elements
	self.main_image = main_image
	#Scren and scenario when will be shown this object
	self.screen = screen
	self.matrix = matrix
	#Coordinates
	self.x = x
	self.y = y
	self.i = self.x/20
	self.j = self.y/20

    def up( self ):
	if self.j>0 and self.matrix[self.i,self.j-1] != 1 :
	    self.y -= 20
	    self.j -= 1

    def down( self ):
	if self.j+1<N and self.matrix[self.i,self.j+1] != 1 :
	    self.y += 20
	    self.j += 1

    def left( self ):
      	if self.i>0 and self.matrix[self.i-1,self.j] != 1:
	    self.x -= 20
	    self.i -= 1

    def right( self ):
      if self.i+1<M and self.matrix[self.i+1,self.j] != 1:
	    self.x += 20
	    self.i += 1

    def draw( self ):
	self.main = pygame.image.load( self.main_image ).convert_alpha()
	#Drawing main character
	self.screen.blit( self.main, (self.x,self.y) )


class main(character):
    """main (character)
    
    Class which contains all information related with the main character of the game
    
    """
    None
  
class enemy(character):
    """enemy (character)
    
    Class which contains all information related with the enemy character of the game
    
    """
    def searching( self ):
	num = np.random.rand()
	if num < 0.25: self.up()
	elif 0.25 < num < 0.5: self.down()
	elif 0.5 < num < 0.75: self.left()
	elif 0.75 < num < 1.0: self.right()

#------------------------------------------------------------------------------
#Program
#------------------------------------------------------------------------------		

#Dimension
M = int(sys.argv[1])
N = int(sys.argv[2])
percent = float(sys.argv[3])
frames = float(sys.argv[4])
N_en = int(sys.argv[5])

#Pictures
background_image = 'background.bmp'
block_image = 'block.bmp'
main_image = 'xander.bmp'
enemy_image = 'enemy.bmp'

#Pygame init
pygame.init()
clock = pygame.time.Clock()

#Screen
screen = pygame.display.set_mode( (20*M, 20*N), 0, 32 )
pygame.display.set_caption("IA test (Finding algorithm): by Sebastian Bustamante")

#Initializing scenario and characters
scene = scenario( M, N, percent, screen, background_image, block_image )
scene.random_scenario()
xander = main( screen, main_image, scene.matrix )

enemies = []
for i in xrange(N_en):
    enemies.append( enemy( screen, enemy_image, scene.matrix, (M-1)*20, (N-1)*20 ) )


while True:	    
    #Detecting pressed key
    pressed_keys = pygame.key.get_pressed()

    #Exit
    for event in pygame.event.get():
	if event.type == QUIT:
	    sys.exit()
    if pressed_keys[K_ESCAPE]:	sys.exit()
    #Up
    elif pressed_keys[K_UP]:
	xander.up()
    #Down
    elif pressed_keys[K_DOWN]:	
	xander.down()
    #Left
    elif pressed_keys[K_LEFT]:	
	xander.left()
    #Right
    elif pressed_keys[K_RIGHT]:	
	xander.right()
	
    scene.build_scenario()

    for i in xrange(N_en):
	enemies[i].searching()
	enemies[i].draw( )
	if enemies[i].i == xander.i and enemies[i].j == xander.j:
	    myfont = pygame.font.SysFont("Comic Sans MS", 30)
	    label = myfont.render("You have lost!", 1, (255,0,0) )
	    screen.blit(label, (M*10-100, N*10-20))
	    pygame.display.update()
	    pygame.time.delay(1000)
	    sys.exit()

    xander.draw( )

    msElapsed = clock.tick(frames)
    pygame.display.update()
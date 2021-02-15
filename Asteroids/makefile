###############################################################
# Program:
#     Milestone 10, Asteroids
#     Br. MacBeth, CS165
# Author:
#     Josh Mayberry
# Summary:
#     Asteroids. This game starts with a single ship in the
#	  middle of 5 asteroids. The ship can fire bullets and
#	  destroy the rocks as well as fly around the screen. There
#	  are no boundaries to stay within since the screen wraps.
#	  Big rocks when hit turn into 2 medium rocks and 1 small
#	  rock. Medium rocks turn into 2 small rocks. Small rocks
#	  go away when hit. Stay alive as long as possible.
#
# Above and Beyond
#     This game keeps score based on how many rocks you hit and
#	  display that in the upper righthand corner of the screen.
#	  A large and medium rock will give you 1 point, and a small
#	  rock gives you 3 points.
#
#     The game will display the message of "GAME OVER" in the
#	  middle of the screen when the ship is destroyed.
#
#	  Small rocks return 1 single large rock when destroyed.
#	  This way the game can continue until the the player
#	  crashes and they have the incentive of earning the 
#	  most points in one game.
#
#	  The ship is given a brake/reverse function instead of
#	  only a forward thrust.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o

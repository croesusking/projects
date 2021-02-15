/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H
 #include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"

// TODO: include your bullet and rock classes


#define CLOSE_ENOUGH 15

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game {
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   
   int score;
   
	Ship ship;
	std::vector<Bullet> bullets;
   
   // TODO: declare your rock here (e.g., "Rock * rock;")
	std::vector<Rock*> rocks;

   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
   void advanceBullets();
   void advanceRock();
   void createRock();
   
   void handleCollisions();
   void cleanUpZombies();
   
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   
   /*********************************************
   * Destructor
   * Checks for old Rocks and deletes them
   **********************************************/
   ~Game();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);
   
   /*********************************************
    * Function: getClosestDistance
    * Description: Determine how close these 
    * two objects will get in between the frames.
    **********************************************/
   float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2);
};

#endif /* GAME_H */

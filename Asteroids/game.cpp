/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rocks.h"
#include "bullet.h"
#include "ship.h"


#include <vector>

#define OFF_SCREEN_BORDER_AMOUNT 5
using namespace std;


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2)
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
	score = 0;
	createRock();
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{

   // TODO: Check to see if there is currently a rock allocated
   //       and if so, delete it.
	vector<Rock*> :: iterator It = rocks.begin();
	while (It != rocks.end())
	{
		Rock *tRock = *It;
		delete tRock;
		It = rocks.erase(It);
	}
	
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceBullets();
   advanceRock();
   ship.advance();

   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
	// Move each of the bullets forward if it is alive 
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
		}
	}
}

/**************************************************************************
 * GAME :: ADVANCE ROCK
 *
 * 1. If there is no rock, create one with some probability
 * 2. If there is a rock, and it's alive, advance it
 * 3. Check if the rock has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game :: advanceRock()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->advance();
		}
	}
}
/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock of a random type according to the rules of the game.
 **************************************************************************/
void Game :: createRock()
{
   for (int i = 0; i<5; i++)
   {
		Rock* newRock = new BigRock;
		rocks.push_back(newRock);
   }
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a rock and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
	Point point;
	// FOR LOOP for BULLETS and ROCKS
	for (int i = 0; i < bullets.size(); i++)
	{
		// this bullet is alive, see if its too close
		// check if the rock is at this point (in case it was hit)		
		if (bullets[i].isAlive())
		{
			vector<Rock*> newRocks;
			vector<Rock*> :: iterator rockIt = rocks.begin();
			while (rockIt != rocks.end())
			{
				Rock* tRock = *rockIt;
				if (tRock != NULL && tRock->isAlive())
				{
					float distance = getClosestDistance(bullets[i], *tRock);
					if (distance < tRock->getRadius())
					{
						//we have a hit!
						int points;
						newRocks = tRock->hit(points);
						score += points;
						// the bullet is dead as well
						bullets[i].kill();						
					}
				}
				rockIt++;
			}
			for (vector<Rock*>::iterator rockIt = newRocks.begin(); rockIt != newRocks.end(); rockIt++)
			{
				rocks.push_back(*rockIt);
			}
		}
	}

	//FOR LOOP for the SHIP and ROCKS
    // this bullet is alive, see if its too close
    // check if the rock is at this point (in case it was hit)		
	for (int i = 0; i < rocks.size(); i++)
	{
		float distance = getClosestDistance(ship, *rocks[i]);
		if (distance < rocks[i]->getRadius() && ship.isAlive()) 
		{
			int points;
			ship.kill();
			score -= 20;
			vector<Rock*> newRocks;
			newRocks = rocks[i]->hit(points);
		}
	}
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate rock)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // check for dead rock
	for (vector<Rock*>::iterator rockIt = rocks.begin(); rockIt < rocks.end(); rockIt++)
	{
		if (!(*rockIt)->isAlive())
		{
			//if (!pRock->isAlive())
			Rock *pRock = *rockIt;
		  	delete pRock;
			pRock = NULL;
			
			rockIt = rocks.erase(rockIt);
		}
	}

   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet pBullet = *bulletIt;
      
      if (!pBullet.isAlive())
      {  
         // remove from list and advance 
	     bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
	if (ship.isAlive())
	{
		// Change the direction of the ship
		if (ui.isLeft())
			ship.moveLeft();
   
		if (ui.isRight())
			ship.moveRight();
   
		if (!ui.isUp())
			ship.setThrust(false);
   
		if (ui.isUp())
		{
			ship.moveUp();
			ship.setThrust(true);
		}
   
		if (ui.isDown())
			ship.brake();
   
		// Check for Spacebar
		if (ui.isSpace())
		{
			Bullet newBullet;
			newBullet.fire(ship.getPoint(), ship.getAngle());
      
			bullets.push_back(newBullet);
		}
	}	
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	// draw the rock

	// TODO: Check if you have a valid rock and if it's alive
	// then call it's draw method
	vector<Rock*> :: iterator rockIt = rocks.begin();
	while (rockIt < rocks.end())
	{
		Rock* tRock = *rockIt;
		if (tRock != NULL && tRock->isAlive())
		{
			tRock->draw();
		}
		rockIt++;
	}
  
	// draw the ship
	if (ship.isAlive())
	{
		ship.draw();
	}
   
	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}
   
	// Put the score on the screen
	Point scoreLocation; 
	scoreLocation.setX(topLeft.getX() + 5);
	scoreLocation.setY(topLeft.getY() - 5);
   
	drawNumber(scoreLocation, score);
   
	if (!ship.isAlive())
	{
		Point endSign;
		endSign.setX(topLeft.getX() + 150);
		endSign.setY(topLeft.getY() - 200);
		drawText(endSign, "GAME OVER");
		//Point playAgain;
		//playAgain.setX(topLeft.getX() + 115);
		//playAgain.setY(topLeft.getY() - 375);
		//drawText(playAgain,"Press SPACE to play again");
	}
}

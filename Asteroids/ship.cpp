#define _USE_MATH_DEFINES

#include "ship.h"
#include "uiDraw.h"
#include "game.h"
#include "point.h"
#include "velocity.h"
#include <cmath>

// Put your ship methods here

Ship :: Ship() {
	point.setX(0);
	point.setY(0);
	setAlive(true);
}

void Ship :: moveLeft()
{
	angle += SHIP_MOVE_AMOUNT;
}

void Ship :: moveRight()
{
	angle -= SHIP_MOVE_AMOUNT;
}

void Ship :: moveUp()
{
	float dX = (0.5 * (-cos(3.1415 / 180 * (angle - 90))));
	float dY = (0.5 * (sin(3.1415 / 180 * (angle + 90))));
	velocity.setDx(velocity.getDx() + dX);
	velocity.setDy(velocity.getDy() + dY);
}

void Ship :: brake()
{
	float dX = (0.5 * (-cos(3.1415 / 180 * (angle + 90))));
	float dY = (0.5 * (sin(3.1415 / 180 * (angle - 90))));
	velocity.setDx(velocity.getDx() + dX);
	velocity.setDy(velocity.getDy() + dY);
}

void Ship :: advance()
{
	if(point.getX() <= -200)
		point.setX(200);
	
	if(point.getX() > 200)
		point.setX(-200);
	
	if(point.getY() <= -200)
		point.setY(200);
	
	if(point.getY() > 200)
		point.setY(-200);
	
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}

void Ship :: draw()
{
	drawShip(point, angle);
}

#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include <iostream>

// Put your FlyingObject method bodies here
FlyingObject :: FlyingObject() : alive(true)
{
	point.setX(random(-185.0, 185.0));
	point.setY(random(100.0, 185.0));
}

FlyingObject :: FlyingObject(Point point)
{
	setPoint(point);
}

void FlyingObject :: advance()
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

void FlyingObject :: kill()
{
	alive = false;
}
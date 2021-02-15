#include "bullet.h"
#include "flyingObject.h"
#include "uiDraw.h"

Bullet :: Bullet()
{
	point = getPoint();
	numFrames = BULLET_LIFE;
	alive = true;
}

void Bullet :: draw()
{
	drawDot(point);
	numFrames--;
	if (numFrames == 0)
		kill();
}

void Bullet :: fire(Point point, float angle)
{
	setPoint(point);
	
	velocity.setDx(5 * -(cos(3.1415 / 180 * (angle - 90))));
	velocity.setDy(5 * -(sin(3.1415 / 180 * (angle - 90))));
}

void Bullet :: advance() {
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
#include "rocks.h"
#include "velocity.h"
#include "uiDraw.h"
#include "flyingObject.h"
#include <vector>
#include <iostream>

// Put your Rock methods here
Rock :: Rock() : FlyingObject() {
	setAlive(true);
	point.setX(random(-200, 200));
	point.setY(random(-200, 200));
	
}

BigRock :: BigRock() : Rock() {
	// int r = random(-200, 200);
	// point.setX(r);
	// point.setY(r);
	
	rotation = BIG_ROCK_SPIN;
	alive = true;
	int Vx = random(-1, 2);
	velocity.setDx(Vx);
	int Vy = random(-1, 2);
	velocity.setDy(Vy);
}

MediumRock :: MediumRock() : Rock() {
	// int r = random(-200, 200);
	// point.setX(r);
	// point.setY(r);
	
	rotation = MEDIUM_ROCK_SPIN;
	alive = true;
	int Vx = random(-3, 4);
	velocity.setDx(Vx);
	int Vy = random(-3, 4);
	velocity.setDy(Vy);
}

SmallRock :: SmallRock() : Rock() {
	// int r = random(-200, 200);
	// point.setX(r);
	// point.setY(r);
	
	rotation = SMALL_ROCK_SPIN;
	alive = true;
	int Vx = random(-4, 5);
	velocity.setDx(Vx);
	int Vy = random(-4, 5);
	velocity.setDy(Vy);
}

BigRock :: BigRock(Point &point, int angle) {
	setPoint(point);
	// float dY = (0.5 * (sin(3.1415 / 180 * (angle + 90))));
	// velocity.setDy(velocity.getDy() + dY);
	float dX = (0.5 * (-cos(3.1415 / 180 * (angle - 90))));
	float dY = (0.5 * (sin(3.1415 / 180 * (angle + 90))));
	velocity.setDx(velocity.getDx() + dX);
	velocity.setDy(velocity.getDy() + dY);

}

MediumRock :: MediumRock(Point &point, int angle) {
	setPoint(point);
	// float dY = (2 * (sin(3.1415 / 180 * (angle + 90))));
	// velocity.setDy(velocity.getDy() + dY);
	float dX = (0.5 * (-cos(3.1415 / 180 * (angle - 90))));
	float dY = (0.5 * (sin(3.1415 / 180 * (angle + 90))));
	velocity.setDx(velocity.getDx() + dX);
	velocity.setDy(velocity.getDy() + dY);

}

SmallRock :: SmallRock(Point &point, int angle) {
	setPoint(point);
	// float dX = (3 * (-cos(3.1415 / 180 * (angle - 90))));
	// velocity.setDx(velocity.getDx() + dX);
	float dX = (0.5 * (-cos(3.1415 / 180 * (angle - 90))));
	float dY = (0.5 * (sin(3.1415 / 180 * (angle + 90))));
	velocity.setDx(velocity.getDx() + dX);
	velocity.setDy(velocity.getDy() + dY);
}

vector<Rock*> BigRock :: hit(int &points) {

	vector<Rock*> rocks;
	
	rocks.push_back(new MediumRock(point, 270));
	rocks.push_back(new MediumRock(point, 90));
	rocks.push_back(new SmallRock(point, 0));
	
	points = 1;
	kill();
	
	return rocks;
}

vector<Rock*> MediumRock :: hit(int &points) {
	vector<Rock*> rocks;
	
	rocks.push_back(new SmallRock(point, 45));
	rocks.push_back(new SmallRock(point, 135));
	points = 1;
	kill();
	return rocks;
}

vector<Rock*> SmallRock :: hit(int &points) {
	vector<Rock*> rocks;
	
	//rocks.push_back(new BigRock(point, 315));  // Used to make game unlimited
	points = 3;
	kill();
	return rocks;
}

void BigRock :: draw() {
	drawLargeAsteroid(point, angle);
}

void MediumRock :: draw() {
	drawMediumAsteroid(point, angle);
}

void SmallRock :: draw() {
	drawSmallAsteroid(point, angle);
}

void Rock :: advance() {
	FlyingObject::advance();
	angle += rotation;
}
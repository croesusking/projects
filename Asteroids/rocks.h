#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include <vector>
#include <iostream>
using namespace std;

class Rock : public FlyingObject {
	protected:
		int radius;
		int rotation;
		int points;
	public:
		Rock();
		void advance();
		virtual int getScore() = 0;
		virtual vector<Rock*> hit(int &points) = 0;
		virtual void draw() = 0;
		virtual int getRadius() = 0;
};

class BigRock : public Rock {
	private:
		
	public:
		BigRock();
		BigRock(Point &point, int angle);
		vector<Rock*> hit(int &points);
		void draw();
		int getRadius() {return BIG_ROCK_SIZE;}
		int getScore() {return points;}
};

class MediumRock : public Rock {
	private:
	public:
		MediumRock();
		MediumRock(Point &point, int angle);
		vector<Rock*> hit(int &points);
		void draw();
		int getRadius() {return MEDIUM_ROCK_SIZE;}
		int getScore() {return points;}
};

class SmallRock : public Rock {
	private:
	public:
		SmallRock();
		SmallRock(Point &point, int angle);
		vector<Rock*> hit(int &points);
		void draw();
		int getRadius() {return SMALL_ROCK_SIZE;}
		int getScore() {return points;}
};

#endif /* rocks_h */

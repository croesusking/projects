#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

// Put your Bullet class here
#include "flyingObject.h"
using namespace std;

class Bullet : public FlyingObject {
	private:
		int numFrames;
		
	public:
		Bullet();
		void draw();
		void advance();
		void fire(Point point, float angle);
};

#endif /* bullet_h */

#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define SHIP_MOVE_AMOUNT 6

#include "flyingObject.h"

// Put your Ship class here
class Ship : public FlyingObject {
	private:
		bool thrust;
		
	public:
		Ship();
		void setThrust(bool thrust) { this->thrust = thrust; }
		void moveLeft();
		void moveRight();
		void moveUp();
		void brake();
		void advance();
		void draw();
};

#endif /* ship_h */

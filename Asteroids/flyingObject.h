#ifndef flyingObject_h
#define flyingObject_h

// Put your FlyingObject class here
#include "point.h"
#include "velocity.h"

class FlyingObject {
	protected:
		Point point;
		Velocity velocity;
		bool alive;
		int angle;
		
	public:
		FlyingObject();
		FlyingObject(Point point);
		Point getPoint() 			  const { return point; }
		Velocity getVelocity()  	  const { return velocity; }
		float getAngle() 			  const { return angle; }
		bool isAlive() 				  		{ return alive; }
		void setPoint(Point point)    		{ this->point = point; }
		void setAngle(int angle)      		{ this->angle = angle; }
		void setVelocity(Velocity velocity) { this->velocity = velocity; }
		void setAlive(bool alive) 			{ this->alive = alive; }
		void kill();
		void advance();
		virtual void draw() = 0;
};

#endif /* flyingObject_h */

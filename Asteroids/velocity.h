#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
class Velocity {
private:
	float dX;
	float dY;

public:
	Velocity();
	float getDx() const { return dX; }
	float getDy() const { return dY; }
	void setDx(float dX) { this->dX = dX; }
	void setDy(float dY) { this->dY = dY; }
};

#endif /* velocity_h */

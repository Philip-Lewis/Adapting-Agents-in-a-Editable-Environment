#ifndef SENSOR_H
#define SENSOR_H

class Agent;

#include "../World/World.h"
//#include "../Resource/Resource.h"

class Sensor
{
private:
	ActorType type;
	float	range;

public:
	//constructors
	Sensor(){ type = OBSTACLE; range = 0;}
	Sensor(ActorType t, float r){ type = t; range = r;}
	Sensor(ActorType t, float r, float c){ type = t; range = r;}

	//logic
	Vector2D Detect(World* world, Actor* owner);

	//modifiers
	void adjustRange(float r){ range = r; }
};
#endif
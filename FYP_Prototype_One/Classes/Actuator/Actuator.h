#ifndef ACTUATOR_H
#define ACTUATOR_H

//class Agent;

#include "../Sensor/Sensor.h"

class Actuator
{
	private:
		Agent* owner;
		Sensor* sensor;
		ActorType type;

	public:
		//constructors
		Actuator(){ owner = nullptr; sensor = nullptr; type = OBSTACLE; }
		Actuator(Agent* o, Sensor* s, ActorType t){ owner = o; sensor = s; type = t; }

		//gets
		Agent* getOwner(){ return owner; }
		Sensor* getSensor(){ return sensor; }
		ActorType getType(){ return type; }

		//logic
		Vector2D act();
};
#endif
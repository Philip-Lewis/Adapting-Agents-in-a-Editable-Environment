#ifndef ACTOR_H
#define ACTOR_H

#include "ObjTypes.h"
#include "Enums.h"

class Actor
{
private:
	Vector2D Location;
	int		 placeholder;
	ActorType type;
public:
	//constructors and deconstructor
	Actor(){ Location.x = 0; Location.y = 0; type = OBSTACLE; }
	Actor(float x, float y, ActorType t){ Location.x = x; Location.y = y; type = t; }
	Actor(Vector2D newLoc, ActorType t){ Location = newLoc; type = t; }
	~Actor(){}

	//gets and sets
	Vector2D getLocation(){ return Location; }
	void setLocation(Vector2D newLoc){ Location = newLoc; }
	void setLocation(float x, float y){ Location.x = x; Location.y = y; }
	void setPlaceholder(int newPlaceholder){ placeholder = newPlaceholder; }
	int getPlaceholder(){ return placeholder; }
	ActorType getType(){ return type; }
	void setToNone(){ type = NONE; }

	//virtual functions
	virtual void render() = 0;
	virtual void update(float deltatime) = 0;
};
#endif
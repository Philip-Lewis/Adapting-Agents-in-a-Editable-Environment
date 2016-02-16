#ifndef RESOURCE_H
#define RESOURCE_H

#include "../ObjTypes.h"
#include "../Actor.h"
#include "../../Libraries/GLEW/glew.h"
#include "../../Libraries/freeGLUT/freeglut.h"

class Resource : public Actor
{
private:
	//ActorType type;
	float Quantity;
	float QuanityMax;
	float regenRate;
	bool  bReady;
public:
	Resource() : Actor(){}
	Resource(Vector2D newLoc, float qty, float qtyMax, float regRate, ActorType t) : Actor(newLoc, t)
		{ Quantity = qty; QuanityMax = qtyMax; regenRate = regRate; bReady = true; }
	Resource(float locX, float locY, float qty, float qtyMax, float regRate, ActorType t) : Actor(locX, locY, t)
		{ Quantity = qty; QuanityMax = qtyMax; regenRate = regRate; bReady = true; }
	~Resource(){}

	//rendering
	void render();

	//logic
	void update(float deltaTime);
	float consume(float reductionRate); //decrease quantity
	void regenerateQuantity(float regenAmount); //regenerate quantity
	bool isReady(){ return bReady; } //returns whether resource is currently consumable or not
};
#endif
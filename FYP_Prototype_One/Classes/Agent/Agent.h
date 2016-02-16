#ifndef AGENT_H
#define AGENT_H

#include "../Actuator/Actuator.h"
#include "../../Libraries/GLEW/glew.h"
#include "../../Libraries/freeGLUT/freeglut.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class Agent : public Actor
{
private:
	vector<Actuator*> actuators;
	float hunger, thirst;
	World* world;
	float baseVelocity;
	bool bConsuming;
	Resource* currConsumable;
	float dehydrationTimer;
	float starvationTimer;
	bool bDead;
	Vector2D wanderTarget;

	Vector2D prioritiseVelocity();
	void checkCollision();
	Vector2D wander();

public:
	//constructors
	Agent() : Actor(){ 
		hunger = 1.0f; thirst = 1.0f; baseVelocity = 7.5f;
		bDead = false; wanderTarget.x = 0; wanderTarget.y = 0; 
	}

	Agent(float x, float y, World* w, float wx, float wy) : Actor(x, y, AGENT){
		hunger = 1.0f; thirst = 1.0f; world = w; baseVelocity = 7.5f; 
		bDead = false; wanderTarget.x = wx; wanderTarget.y = wy; 
	}

	Agent(Vector2D loc, World* w, Vector2D wander) : Actor(loc, AGENT){
		hunger = 1.0f; thirst = 1.0f; world = w; baseVelocity = 7.5f; 
		bDead = false; wanderTarget = wander; 
	}

	//gets and sets
	void AddActuator(Actuator* a){ actuators.push_back(a); }
	void AddActuator(Sensor* s, ActorType t){ actuators.push_back(new Actuator(this, s, t)); }
	void setHunger(float h);
	void setThirst(float t);
	float getHunger(){ return hunger; }
	float getThirst(){ return thirst; }
	World* getWorld(){ return world; }
	Vector2D getWanderTarget(){ return wanderTarget; }
	bool isDead(){ return bDead; }
	void setBaseVelocity(float v){ baseVelocity = v; }
	float getBaseVelocity(){ return baseVelocity; }
	void setCurrConsumable(Resource* r){ currConsumable = r; }
	Resource* getCurrConsumable(){ return currConsumable; }
	void setConsuming(bool c){ bConsuming = c; }
	bool isConsuming(){ return bConsuming; }

	//render
	void render();

	//logic
	void update(float deltaTime);

};
#endif
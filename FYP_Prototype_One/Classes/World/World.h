#ifndef WORLD_H
#define WORLD_H

#include "../Actor.h"
#include "../Enums.h"
#include "../Resource/Resource.h"
#include <vector>
#include <math.h>

using namespace std;

class World
{
private:
	vector<Actor*> actors;

public:

	//constructors and deconstructors
	World(){}
	~World(){}

	//manage actors
	bool Spawn(Actor* newActor);
	bool KillActor(Actor* actor);
	vector<Actor*> getAllActorsWithinRadius(Vector2D centre, float radius);
	vector<Actor*> getAllActorsOfTypeWithinRadius(Vector2D centre, float radius, ActorType t);
	Actor* getClosestActorOfTypeWithinRadius(Vector2D centre, float radius, ActorType t);
	Actor* getClosestActorWithinRadius(Vector2D centre, float radius, Actor* caller);
	vector<Actor*> getAllActors();
	void clearAllActors();

	//update world and actors
	void update(float DeltaTime);

	//render world and actors
	void render();
};
#endif
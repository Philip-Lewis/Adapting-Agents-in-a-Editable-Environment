#include "Sensor.h"

Vector2D Sensor::Detect(World* world, Actor* owner)
{
	Actor* closest = nullptr;
	Vector2D temp;

	temp.x = 0;
	temp.y = 0;

	if ((type == FOOD) || (type == WATER)) //check whether sensor detects ready food or water
	{
		closest = world->getClosestActorOfTypeWithinRadius(owner->getLocation(), range, type); //get nearest ready resource

		if (closest != nullptr)
		{
			//work out vector between owner location and resource location
			temp.x = closest->getLocation().x - owner->getLocation().x;
			temp.y = closest->getLocation().y - owner->getLocation().y;

			//float length = sqrtf((temp.x * temp.x) + (temp.y * temp.y));

			temp.x = temp.x / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
			temp.y = temp.y / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
		}

	}
	else if (type == OBSTACLE)
	{
		vector<Actor*> obstacles = world->getAllActorsOfTypeWithinRadius(owner->getLocation(), range, type); // get all obstacles within range

		for each (Actor* a in obstacles)
		{
			//sum up all vector so average direction is produced when normalised 
			temp.x += (a->getLocation().x - owner->getLocation().x);
			temp.y += (a->getLocation().y - owner->getLocation().y);
		}

		if (temp.x != 0 && temp.y != 0)
		{
			temp.x = temp.x / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
			temp.y = temp.y / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
		}

	}
	else if (type == AGENT)
	{
		//Agent* agent = nullptr;
		vector<Actor*> agents = world->getAllActorsOfTypeWithinRadius(owner->getLocation(), range, type); // get all obstacles within range

		for each (Actor* a in agents)
		{
			if (a != owner)
			{
				//sum up all vector so average direction is produced when normalised 
				temp.x += (a->getLocation().x - owner->getLocation().x);
				temp.y += (a->getLocation().y - owner->getLocation().y);
			}
		}

		if (temp.x != 0 && temp.y != 0)
		{
			temp.x = temp.x / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
			temp.y = temp.y / sqrtf((temp.x * temp.x) + (temp.y * temp.y));
		}
	}

	return temp;
}
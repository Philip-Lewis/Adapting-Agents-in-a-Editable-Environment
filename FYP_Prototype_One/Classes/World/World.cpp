#include "World.h"

bool World::Spawn(Actor* newActor)
{
	//newActor->setPlaceholder(actors.size());
	if (newActor != nullptr)
	{
		actors.push_back(newActor);
		return true;
	}
	else
	{
		return false;
	}
}

bool World::KillActor(Actor* actor)
{
	//if ((actor->getPlaceholder() >= 0) && (actor->getPlaceholder() < actors.size())) //check whether placeholder is within bound of actors vector
	//{
	//	if (actor->getPlaceholder() == actors.size() - 1) //check whether actor is at end of list
	//	{
	//		actors.erase(actors.begin() + actor->getPlaceholder());
	//		actors.shrink_to_fit();
	//		return true;
	//	}
	//	else //alter placeholders of actors after killed actor
	//	{
	//		for (int i = actor->getPlaceholder() + 1; i < actors.size(); i++)
	//		{
	//			actors.at(i)->setPlaceholder(i - 1);
	//		}
	//		actors.erase(actors.begin() + actor->getPlaceholder());
	//		actors.shrink_to_fit();
	//		delete actor;
	//		return true;
	//	}
	//}
	//else
	//{
	//	return false;
	//}
	int pos = 0;

	if (actor != nullptr)
	{
		for (int i = 0; i < actors.size(); i++)
		//for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++)
		{
			if (actors.at(i) != actor)
			{
				//pos = i;
				actors.erase(actors.begin() + i);
				return true;
			}
		}

		/*if ((pos >= 0) && (pos < actors.size()))
		{
			actors.erase(actors.begin() + pos);
			return true;
		}
		else
		{*/
			return false;
		//}
	}
	else
	{
		return false;
	}
}

vector<Actor*> World::getAllActorsWithinRadius(Vector2D centre, float radius)
{
	vector<Actor*> actorsWithinRadius;
	Vector2D dist;
	float length = 0;

	for each (Actor* a in actors)
	{
		dist.x = a->getLocation().x - centre.x;
		dist.y = a->getLocation().y - centre.y;

		length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));

		if (length <= radius)
		{
			actorsWithinRadius.push_back(a);
		}
	}

	return actorsWithinRadius;
}

vector<Actor*> World::getAllActorsOfTypeWithinRadius(Vector2D centre, float radius, ActorType t)
{
	vector<Actor*> resourcesWithinRadius;
	Vector2D dist;
	float length = 0;

	for each (Actor* a in actors)
	{
		if (a->getType() == t)
		{
			dist.x = a->getLocation().x - centre.x;
			dist.y = a->getLocation().y - centre.y;

			length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (length <= radius)
			{
				resourcesWithinRadius.push_back(a);
			}
		}
	}

	return resourcesWithinRadius;
}

Actor* World::getClosestActorOfTypeWithinRadius(Vector2D centre, float radius, ActorType t)
{
	Vector2D dist;
	float length = 0;
	Actor* closest = nullptr;
	float closestLength = 0;

	if (t == FOOD || t == WATER)
	{
		for each (Resource* r in actors)
		{
			if (r->getType() == t)
			{
				if (r->isReady())
				{
					dist.x = r->getLocation().x - centre.x;
					dist.y = r->getLocation().y - centre.y;

					length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));

					if (length <= radius)
					{
						if (closest == nullptr)
						{
							closest = r;
							closestLength = length;
						}
						else
						{
							if (length <= closestLength)
							{
								closest = r;
								closestLength = length;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for each (Actor* a in actors)
		{
			if (a->getType() == t)
			{
				dist.x = a->getLocation().x - centre.x;
				dist.y = a->getLocation().y - centre.y;

				length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));

				if (length <= radius)
				{
					if (closest == nullptr)
					{
						closest = a;
						closestLength = length;
					}
					else
					{
						if (length <= closestLength)
						{
							closest = a;
							closestLength = length;
						}
					}
				}
			}
		}
	}

	return closest;
}

Actor* World::getClosestActorWithinRadius(Vector2D centre, float radius, Actor* caller)
{
	Vector2D dist;
	float length = 0;
	Actor* closest = nullptr;
	Resource* temp = nullptr;
	float closestLength = 0;

	for each (Actor* a in actors)
	{
		if (a != caller)
		{
			if (a->getType() == FOOD || a->getType() == WATER)
			{
				temp = (Resource*)a;
				if (temp->isReady())
				{
					dist.x = temp->getLocation().x - centre.x;
					dist.y = temp->getLocation().y - centre.y;

					length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
					if (length <= radius)
					{
						if (closest == nullptr)
						{
							closest = temp;
							closestLength = length;
						}
						else
						{
							if (length <= closestLength)
							{
								closest = temp;
								closestLength = length;
							}
						}
					}
				}
			}
			else
			{
				dist.x = a->getLocation().x - centre.x;
				dist.y = a->getLocation().y - centre.y;

				length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
				if (length <= radius)
				{
					if (closest == nullptr)
					{
						closest = a;
						closestLength = length;
					}
					else
					{
						if (length <= closestLength)
						{
							closest = a;
							closestLength = length;
						}
					}
				}
			}
		}
	}

	return closest;
}

vector<Actor*> World::getAllActors()
{
	return actors;
}

void World::clearAllActors()
{
	actors.clear();
}

void World::update(float deltaTime)
{
	for each (Actor* a in actors)
	{
		if (a->getType() != NONE)
		{
			a->update(deltaTime);
		}
	}
}

void World::render()
{
	for each (Actor* a in actors)
	{
		//if (a->getType() != NONE)
		//{
			a->render();
		//}
	}
}
#include "Actuator.h"
#include "../Agent/Agent.h"

Vector2D Actuator::act()
{
	Vector2D dir;

	dir = sensor->Detect(owner->getWorld(), owner);

	if (type == FOOD)
	{
		dir.x *= (1 - owner->getHunger());
		dir.y *= (1 - owner->getHunger());
	}
	else if (type == WATER)
	{
		dir.x *= (1 - owner->getThirst());
		dir.y *= (1 - owner->getThirst());
	}
	else if ((type == OBSTACLE) || (type == AGENT))
	{
		dir.x *= -1;
		dir.y *= -1;
	}
	//else if (type == AGENT)
	//{
	//	//TO DO: implement actuator behaviour for agents
	//}

	return dir;
}
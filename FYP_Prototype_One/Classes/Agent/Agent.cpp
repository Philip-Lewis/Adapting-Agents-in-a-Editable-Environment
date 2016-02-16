#include "Agent.h"

void Agent::setHunger(float h)
{
	if (h > 1.0f)
	{
		hunger = 1.0f;
	}
	else if (h < 0.0f)
	{
		hunger = 0.0f;
	}
	else
	{
		hunger = h;
	}
}

void Agent::setThirst(float t)
{
	if (t > 1.0f)
	{
		thirst = 1.0f;
	}
	else if (t < 0.0f)
	{
		thirst = 0.0f;
	}
	else
	{
		thirst = t;
	}
}

void Agent::render()
{
	glPushMatrix();
		glTranslatef(getLocation().x, 0, getLocation().y);
		if (bDead)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidSphere(0.1, 10, 10);
		}
		else
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glutSolidSphere(0.25, 10, 10);
		}
	glPopMatrix();
}

void Agent::update(float deltaTime)
{
	Vector2D finalVelocity;
	float foodConsumtion;
	//Vector2D temp;

	finalVelocity.x = 0;
	finalVelocity.y = 0;

	if (!bDead)
	{
		if (isConsuming() && (getCurrConsumable() != nullptr))
		{
			if (getCurrConsumable()->isReady())
			{
				if (getCurrConsumable()->getType() == WATER)
				{
					dehydrationTimer = 0.0f;

					if (getHunger() == 0.0f)
					{
						starvationTimer += deltaTime;
					}

					//setHunger(getHunger() - (0.002f * deltaTime)); //hunger decreases by 5% each day where a day is equal to half a minute
					setHunger(getHunger() - (0.05f * deltaTime)); //hunger decreases by 5% each day where a day is equal to a second
					setThirst(getThirst() + getCurrConsumable()->consume(20 * deltaTime));
					if (getCurrConsumable()->isReady() == false)
					{
						setConsuming(false);
						setCurrConsumable(nullptr);
					}
				}
				else if (getCurrConsumable()->getType() == FOOD)
				{
					starvationTimer = 0.0f;

					foodConsumtion = getCurrConsumable()->consume(20 * deltaTime);
					setHunger(getHunger() + foodConsumtion);
					setThirst(getThirst() + (foodConsumtion * 0.25));
					//setThirst(getThirst() - (0.011f * deltaTime)); //thirst decreases by 33% each day where a day is equal to half a minute
					//setThirst(getThirst() - (0.33f * deltaTime)); //thirst decreases by 33% each day where a day is equal to a second
					if (getCurrConsumable()->isReady() == false)
					{
						setConsuming(false);
						setCurrConsumable(nullptr);
					}
				}
			}
			else
			{
				setConsuming(false);
				setCurrConsumable(nullptr);
			}
		}
		else
		{
			setHunger(getHunger() - (0.05f * deltaTime)); //hunger decreases by 5% each day where a day is equal to a second
			//setHunger(getHunger() - (0.002f * deltaTime)); //hunger decreases by 5% each day where a day is equal to half a minute
			setThirst(getThirst() - (0.33f * deltaTime)); //thirst decreases by 33% each day where a day is equal to a second
			//setThirst(getThirst() - (0.011f * deltaTime)); //thirst decreases by 33% each day where a day is equal to half a minute

			finalVelocity = prioritiseVelocity();

			setLocation(getLocation().x + (finalVelocity.x * deltaTime), getLocation().y + (finalVelocity.y * deltaTime));

			if (getThirst() == 0.0f)
			{
				dehydrationTimer += deltaTime;
				cout << "dehydration: " << dehydrationTimer << endl;
			}

			if (getHunger() == 0.0f)
			{
				starvationTimer += deltaTime;
				cout << "starvation: " << starvationTimer << endl;
			}
		}

		checkCollision();

		if ((dehydrationTimer > 3.0f) || (starvationTimer > 21.0f))
		{
			cout << "agent dead" << endl;
			bDead = true;
			setConsuming(false);
			setCurrConsumable(nullptr);
			setToNone();
		}
	}
}

void Agent::checkCollision()
{
	Actor* closest;
	//closest = nullptr;

	closest = world->getClosestActorWithinRadius(getLocation(), 0.5f, this);

	if (closest != nullptr)
	{
		if ((closest->getType() == WATER) && (getThirst() < 0.5f))
		{
			setConsuming(true);
			setCurrConsumable((Resource*)closest);
		}
		else if ((closest->getType() == FOOD) && (getHunger() < 0.5f))
		{
			setConsuming(true);
			setCurrConsumable((Resource*)closest);
		}
	}
}

Vector2D Agent::prioritiseVelocity()
{
	Vector2D vel;
	Vector2D temp;
	int noOfActs = 0;

	vel.x = 0;
	vel.y = 0;

	temp.x = 0;
	temp.y = 0;

	if ((getThirst() == 0.0f) && (world->getClosestActorOfTypeWithinRadius(getLocation(), 10.0f, WATER) != nullptr))
	{
		for each (Actuator* a in actuators)
		{
			if ((a->getType() == WATER ) || (a->getType() == OBSTACLE) || (a->getType() == AGENT))
			{
				temp = a->act();
				vel.x += temp.x;
				vel.y += temp.y;
				noOfActs++;
			}
		}

		vel.x = (vel.x / noOfActs) * baseVelocity;
		vel.y = (vel.y / noOfActs) * baseVelocity;
	}
	else if ((getHunger() == 0.0f) && (world->getClosestActorOfTypeWithinRadius(getLocation(), 10.0f, FOOD) != nullptr))
	{
		for each (Actuator* a in actuators)
		{
			if ((a->getType() == FOOD) || (a->getType() == OBSTACLE) || (a->getType() == AGENT))
			{
				temp = a->act();
				vel.x += temp.x;
				vel.y += temp.y;
				noOfActs++;
			}
		}

		vel.x = (vel.x / noOfActs) * baseVelocity;
		vel.y = (vel.y / noOfActs) * baseVelocity;
	}
	else
	{
		for each (Actuator* a in actuators)
		{
			temp = a->act();
			vel.x += temp.x;
			vel.y += temp.y;
		}

		temp = wander();
		vel.x += temp.x;
		vel.y += temp.y;

		if (actuators.size() > 0)
		{
			vel.x = (vel.x / (actuators.size() + 1)) * baseVelocity;
			vel.y = (vel.y / (actuators.size() + 1)) * baseVelocity;
		}
	}

	return vel;
}

Vector2D Agent::wander()
{
	Vector2D dir;

	dir.x = 0;
	dir.y = 0;

	srand(time(NULL));

	dir.x = ((rand() % 5 + 1) / 5) * (rand() % 3 - 2);
	dir.y = ((rand() % 5 + 1) / 5) * (rand() % 3 - 2);

	wanderTarget.x += dir.x;
	wanderTarget.y += dir.y;

	dir.x = wanderTarget.x - getLocation().x;
	dir.y = wanderTarget.y - getLocation().y;

	dir.x = dir.x / sqrtf((dir.x * dir.x) + (dir.y * dir.y));
	dir.y = dir.y / sqrtf((dir.x * dir.x) + (dir.y * dir.y));

	return dir;
}
#include "Resource.h"

float Resource::consume(float reductionRate)
{
	float temp;

	if ((Quantity > 0) && (bReady))
	{
		Quantity -= reductionRate;

		if (Quantity <= 0)
		{
			bReady = false;
			temp = (Quantity + reductionRate) / QuanityMax;
			Quantity = 0;
			return temp;
		}
		else
		{
			return reductionRate / QuanityMax;
		}
	}
	else
	{
		return 0;
	}
}

void Resource::regenerateQuantity(float regenAmount)
{
	if ((Quantity < QuanityMax) && (!bReady))
	{
		Quantity += regenAmount;

		if (Quantity >= QuanityMax)
		{
			Quantity = QuanityMax;
			bReady = true;
		}
	}
}

void Resource::render()
{
	glPushMatrix();
		glTranslatef(getLocation().x, 0, getLocation().y);
		if (getType() == FOOD)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else if (getType() == WATER)
		{
			glColor3f(0.0f, 0.0f, 1.0f);
		}
		else
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		//glutSolidCube((Quantity / QuanityMax) / 5);
		glutSolidSphere((Quantity / QuanityMax) / 7.5, 10, 10);
	glPopMatrix();
}

void Resource::update(float DeltaTime)
{
	if (bReady == false)
	{
		regenerateQuantity(regenRate * DeltaTime);
	}
}
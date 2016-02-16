#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Actor.h"
#include "../../Libraries/GLEW/glew.h"
#include "../../Libraries/freeGLUT/freeglut.h"

class Obstacle : public Actor
{
	private:

	public:
		//constructors
		Obstacle() : Actor(){}
		Obstacle(float x, float y) : Actor(x, y, OBSTACLE){}
		Obstacle(Vector2D loc) : Actor(loc, OBSTACLE){}

		//rendering
		void render(){
			glPushMatrix();
				glTranslatef(getLocation().x, 0, getLocation().y);
				glColor3f(0.6f, 0.4f, 0.0f);
				glutSolidCube(0.5);
			glPopMatrix();
		}

		//logic
		void update(float deltaTime){}
};
#endif
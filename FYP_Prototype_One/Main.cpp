#define CATCH_CONFIG_RUNNER
#include "Libraries\GLEW\glew.h"
#include "Libraries\freeGLUT\freeglut.h"
#include "Classes\SimManager\SimManager.h"
#include "Classes\catch.hpp"
#include <iostream>

using namespace std;

/*http://in2gpu.com/2014/10/17/creating-opengl-window/ was used
  as reference for setting up a glut project.*/
SimManager* Simulation;

Camera* SimManager::pCam;
CamEnum SimManager::camType;

float SimManager::fEye[3];
float SimManager::fAim[3];
float SimManager::fUpright[3];

//int	SimManager::mBufType;
int SimManager::winWidth;
int SimManager::winHeight;

static int winWidth;
static int winHeight;

void init()
{
	cout << "init" << endl;
	Simulation = new SimManager();
	Simulation->initScenario();
	winWidth = 800;
	winHeight = 800;
	Simulation->setWinWidth(winWidth);
	Simulation->setWinHeight(winHeight);
	srand(time(NULL));
}
//TO DO: void update()

void renderScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (Simulation != nullptr)
	{
		Simulation->updateScenario();
		Simulation->renderScenario();
	}
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
	if (Simulation != nullptr)
	{
		cout << "key: " << key << " x: " << x << " y: " << y << endl;
		cout << "you have spawned:" << endl;
		switch (key)
		{
			case 'o':
			{
				Simulation->getWorld()->Spawn(new Obstacle(x / 37.5f, y / 37.5f));
				cout << "an Obstacle!" << endl;
				break;
			}
			case 'f':
			{
				Simulation->getWorld()->Spawn(new Resource(x / 37.5f, y / 37.5f, 100, 100, 5, FOOD));
				cout << "some food!" << endl;
				break;
			}
			case 'w':
			{
				Simulation->getWorld()->Spawn(new Resource(x / 37.5f, y / 37.5f, 100, 100, 5, WATER));
				cout << "some water!" << endl;
				break;
			}
			case 'a':
			{
				Agent* a = new Agent(x / 37.5f, y / 37.5f, Simulation->getWorld(), (rand() % 20 + 1), (rand() % 20 + 1));
				a->AddActuator(new Sensor(FOOD, 10.0f), FOOD);
				a->AddActuator(new Sensor(WATER, 10.0F), WATER);
				a->AddActuator(new Sensor(OBSTACLE, 0.75f), OBSTACLE);
				a->AddActuator(new Sensor(AGENT, 1.0f), AGENT);
				Simulation->getWorld()->Spawn(a);
				cout << "an agent!" << endl;
				break;
			}
		}

		//glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	//bool bEndSim = false;
	int res = 0;
	int i = 0;

	cout << "run test or program? 0 for program, 1 for test!" << endl;
	cin >> i;

	if (i == 0)
	{
		init();

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(winWidth, winHeight);
		glutCreateWindow("Adapting Agents in an Editable Environment by Philip Lewis");

		glEnable(GL_DEPTH_TEST);

		Simulation->setupLighting(0.0f, 20.0f, -15.0f);

		glutDisplayFunc(renderScene);

		glutKeyboardFunc(keyPressed);

		glutMainLoop();

		res = 0;
	}
	else if ( i == 1)
	{
		res = Catch::Session().run(argc, argv);
		cin >> i;
	}

	return res;
}
#include "SimManager.h"

void SimManager::initScenario()
{
	tElapsedTime = clock(); //get time that simulation started

	//intialise camera
	camType = ORTHO;
	InitCamera();
	srand(time(NULL));

	//setup pWorld, pWorld's inhabitants, resources and obstacles
	pWorld = new World();
	pWorld->Spawn(new Resource(0, 0, 100, 100, 5, WATER));
	pWorld->Spawn(new Resource(5, 5, 100, 100, 5, FOOD));
	pWorld->Spawn(new Resource(10, 10, 100, 100, 5, WATER));
	pWorld->Spawn(new Resource(15, 15, 100, 100, 5, FOOD));
	pWorld->Spawn(new Resource(20, 20, 100, 100, 5, WATER));
	pWorld->Spawn(new Obstacle(17, 17));
	pWorld->Spawn(new Obstacle(15, 20));
	pWorld->Spawn(new Obstacle(20, 15));
	pWorld->Spawn(new Obstacle(3, 17));
	pWorld->Spawn(new Obstacle(14, 24));
	pWorld->Spawn(new Obstacle(23, 18));
	pWorld->Spawn(new Obstacle(18, 5));
	pWorld->Spawn(new Obstacle(10, 8));
	pWorld->Spawn(new Obstacle(4, 8));
	pWorld->Spawn(new Obstacle(12, 12));
	pWorld->Spawn(new Obstacle(3, 3));
	pWorld->Spawn(new Obstacle(2, 2));
	pWorld->Spawn(new Obstacle(1, 1));
	pWorld->Spawn(new Obstacle(1, 2));
	pWorld->Spawn(new Obstacle(2, 1));
	
	//setup agent, actuators and sensors
	Agent* a = new Agent(20, 10, pWorld, (rand() % 20 + 1), (rand() % 20 + 1));
	a->AddActuator(new Sensor(FOOD, 10.0f), FOOD);
	a->AddActuator(new Sensor(WATER, 10.0F), WATER);
	a->AddActuator(new Sensor(OBSTACLE, 0.75f), OBSTACLE);
	a->AddActuator(new Sensor(AGENT, 1.0f), AGENT);
	pWorld->Spawn(a);
}

void SimManager::updateScenario()
{
	tCurrTime = clock(); //get current time
	float deltaTime = float(tCurrTime - tElapsedTime) / CLOCKS_PER_SEC; //calculate how much time has past since last update
	pWorld->update(deltaTime); //update the virtual world
	tElapsedTime = tCurrTime; //set the elapsed time to the time at begininng of function
}

void SimManager::renderScenario()
{
	//render virtual world
	pWorld->render();

	//render camera
	pCam->Render();
}

void SimManager::InitCamera()
{
	pCam = new Camera(ORTHO);
	camType = ORTHO;

	fUpright[0] = 0.0f;
	fUpright[1] = 0.0f;
	fUpright[2] = -1.0f;

	fAim[0] = 5.0f;
	fAim[1] = -1.0f;
	fAim[2] = 35.0f;

	fEye[0] = 5.0f;
	fEye[1] = 12.0f;
	fEye[2] = 35.0f;

	ReinitCamera(ORTHO, -6.0f, 17.0f, 13.0f, 36.0f, 1.0f, 1000.0f);
}

void SimManager::setCamera(float nvalue, float viewangle)
{
	pCam->SetValue(MNEAR, nvalue);
	pCam->SetValue(YANGLE, viewangle);
}

void SimManager::ReinitCamera(CamEnum newCamType, float newNear, float newFar, float newAngle, float newAspect)
{
	pCam->SetType(newCamType);
	camType = newCamType;

	pCam->SetValue(MNEAR, newNear);
	pCam->SetValue(YANGLE, newAngle);

	pCam->SetValuev(AIMAT, fAim);
	pCam->SetValuev(UPDIRECTION, fUpright);
	pCam->SetValuev(POSITION, fEye);

	pCam->SetValue(MFAR, newFar);
	pCam->SetValue(HEIGHT, winHeight);
	pCam->SetValue(ASPECT, newAspect);
}

void SimManager::ReinitCamera(CamEnum newCamtype, float left, float right, float bottom, float top, float newNear, float newFar)
{
	pCam->SetType(newCamtype);
	camType = newCamtype;

	pCam->SetValue(MLEFT, left);
	pCam->SetValue(MRIGHT, right);
	pCam->SetValue(MTOP, top);
	pCam->SetValue(MBOTTOM, bottom);
	pCam->SetValue(MNEAR, newNear);
	pCam->SetValue(MFAR, newFar);

	pCam->SetValuev(AIMAT, fAim);
	pCam->SetValuev(UPDIRECTION, fUpright);
	pCam->SetValuev(POSITION, fEye);
}

void SimManager::setupLighting(float posX, float posY, float posZ)
{

	GLfloat lightPosition[] = { posX, posY, posZ };

	//Lighting solutions.
	float ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };//Ambient light to illumninate scene.
	float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//Diffuse lighting.
	float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };//Specular lighting.
	float specularReflectance[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glEnable(GL_LIGHTING);								//Enable lighting.

	glEnable(GL_TEXTURE_2D);							//This Enable the Texture mapping
	glShadeModel(GL_SMOOTH);							//Enable smooth shading model - Phong.

	//Set up and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);

	//Set up and enable color material.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
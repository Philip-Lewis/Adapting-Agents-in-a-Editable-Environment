#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#include "../World/World.h"
#include "../Agent/Agent.h"
#include "../Resource/Resource.h"
#include "../Obstacle/Obstacle.h"
#include "../camera/Camera.h"
//#include <time.h>

class SimManager
{
private:
	bool bRunning;
	World* pWorld;

	clock_t tElapsedTime;
	clock_t tCurrTime;

	static Camera* pCam;
	static CamEnum camType;

	static float fEye[3];
	static float fAim[3];
	static float fUpright[3];

	//static int BufType;
	static int winWidth;
	static int winHeight;

public:
	SimManager(){}
	~SimManager(){}
	void initScenario();
	void updateScenario();
	void renderScenario();

	//setup camera
	void InitCamera();
	void setCamera(float nvalue, float viewangle);
	static void ReinitCamera(CamEnum a_cameraType, float a_left, float a_right, float a_bottom, float a_top, float a_near, float a_far);
	static void ReinitCamera(CamEnum a_cameraType, float a_near, float a_far, float a_angle, float a_aspect);

	//set up lighting
	void setupLighting(float posX, float posY, float posZ);

	//gets and sets
	bool isRunning(){ return bRunning; }
	void setCamPointer(Camera* pNewCam) { pCam = pNewCam; }
	void setWinWidth(int newWidth){ winWidth = newWidth; }
	void setWinHeight(int newHeight){ winHeight = newHeight; }
	World* getWorld(){ return pWorld; }
};
#endif
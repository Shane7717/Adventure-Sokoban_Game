#pragma once

#include "BaseState.h"
#include "BaseEngine.h"
#include "CoordinateMapping.h"

class AboutState : public BaseState, public CoordinateMapping
{
public:
	AboutState(BaseEngine* p_engine);
	~AboutState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	void mouseDown(int iButton, int iX, int iY);
	void mouseMoved(int iX, int iY);	
	int initialiseObjects();
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();
	//void virtMouseWheel(int x, int y, int which, int timestamp);
	bool mapCoordinates(double& x, double& y, const SimpleImage& image);
	
protected:
	int aboutPageSelection = -1;
	BaseEngine* engine;
	int m_iOffset = 0;
	CoordinateMappingRotate rotator;

};

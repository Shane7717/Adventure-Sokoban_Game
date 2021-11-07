#pragma once
#include "BaseEngine.h"

class BaseState
{

public: 
	BaseState();
	~BaseState();
	virtual void setupBackgroundBuffer();
	virtual void drawStringsUnderneath();
	virtual void mouseDown(int iButton, int iX, int iY);
	virtual void mouseMoved(int iX, int iY);
	virtual int initialiseObjects();	
	virtual void playMusic();
	virtual void keyDown(int iKeyCode);
	virtual void drawStringsOnTop();
	// This forces a screen redraw every pass through the loop.
	virtual void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	virtual void copyAllBackgroundBuffer();
	// Handle mouse wheel
	virtual void virtMouseWheel(int x, int y, int which, int timestamp);	
	bool mapCoordinates(double& x, double& y, const SimpleImage& image);
};


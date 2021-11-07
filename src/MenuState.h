#pragma once
#include "BaseState.h"
#include "BaseEngine.h"
#include "DrawingFilters.h" 

class MenuState : public BaseState
{
	
public:
	MenuState(BaseEngine* p_engine);
	~MenuState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	void mouseDown(int iButton, int iX, int iY);
	void mouseMoved(int iX, int iY);
	void keyDown(int iKeyCode);
	void playMusic();
	int initialiseObjects();
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();
	void virtMouseWheel(int x, int y, int which, int timestamp);

protected:
	int menuSelection = -1;
	BaseEngine* engine;
	FilterPointsScaling m_filterScaling;
	FilterPointsTranslation m_filterTranslation;
};

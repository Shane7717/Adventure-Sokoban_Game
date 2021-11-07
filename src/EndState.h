#pragma once
#include "BaseState.h"
#include "BaseEngine.h"

class EndState : public BaseState
{

public:	
	EndState(BaseEngine* p_engine);
	~EndState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	void playMusic();
	void mouseDown(int iButton, int iX, int iY);
	void mouseMoved(int iX, int iY);
	int initialiseObjects();
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();

protected:
	int selection = -1;
	BaseEngine* engine;
	int m_iOffset = 0;
};


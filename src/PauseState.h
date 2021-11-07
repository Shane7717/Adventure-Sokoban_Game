#pragma once
#include "BaseState.h"
#include "BaseEngine.h"

class PauseState :	public BaseState
{
	
public:
	PauseState(BaseEngine* p_engine);
	~PauseState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	void keyDown(int iKeyCode);
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();

protected:
	BaseEngine* engine;
	int m_iOffset = 0;

};

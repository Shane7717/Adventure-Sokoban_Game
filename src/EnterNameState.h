#pragma once
#include "BaseState.h"
#include "BaseEngine.h"

using namespace std;

class EnterNameState : public BaseState
{

public:
	EnterNameState(BaseEngine* p_engine);
	~EnterNameState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	void mouseDown(int iButton, int iX, int iY);
	void mouseMoved(int iX, int iY);	
	void keyDown(int iKeyCode);
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();
	
protected:
	int selection = -1;

public:
	string name = " ";
	BaseEngine* engine;
	int m_iOffset = 0;	
};

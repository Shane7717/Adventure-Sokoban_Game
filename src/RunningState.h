#pragma once
#include "BaseState.h"
#include "BaseEngine.h"
#include "CW4TileManager.h"

class RunningState : public BaseState
{
public:
	RunningState(BaseEngine* p_engine);
	~RunningState();
	void setupBackgroundBuffer();
	void drawStringsUnderneath();
	int initialiseObjects();
	void mouseDown(int iButton, int iX, int iY);
	void mouseMoved(int iX, int iY);
	void reset();
	void playMusic();
	void keyDown(int iKeyCode);
	void drawStringsOnTop();
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate();
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer();
		
public:
	CW4TileManager *tm = new CW4TileManager();
	
public:
	int gameSelection = -1;
	static int currentLevel;
	static int currentNumBoxes;
	static int loadOnce;
	static int startPlayTime;
	static int currentTime;
	static int currentScore;
	static int mainX;
	static int mainY;
	BaseEngine* engine;
	int m_iOffset = 0;	
};


#pragma once
#include "BaseEngine.h"
#include "BaseState.h"
#include "RunningState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "EndState.h"
#include "EnterNameState.h"
#include "AboutState.h"
#include "DrawingFilters.h" 
#include "CoordinateMapping.h"

class Scyxw3CW4Engine : public BaseEngine, public CoordinateMapping

{
public:
	Scyxw3CW4Engine();
	~Scyxw3CW4Engine();
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	int virtInitialiseObjects() override;
	void virtDrawStringsUnderneath() override;
	void virtMouseMoved(int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop() override;
	// This forces a screen redraw every pass through the loop.
	void virtMainLoopDoBeforeUpdate() override;
	// Do something special when we copy the background buffer
	void copyAllBackgroundBuffer() override;
	// Handle mouse wheel
	void virtMouseWheel(int x, int y, int which, int timestamp) override;
	int virtInitialise() override;
	bool mapCoordinates(double& x, double& y, const SimpleImage& image) override;
	
public:
	static BaseState* bs;
	static RunningState* runningState;
	static PauseState* pauseState;
	static MenuState* menuState;
	static EndState* endState;
	static EnterNameState* enterNameState;
	static AboutState* aboutState;
};

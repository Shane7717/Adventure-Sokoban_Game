#include "header.h"
#include "Scyxw3CW4Engine.h"
#include "BaseState.h"
#include "MenuState.h"
#include "MainCharacter.h"

Scyxw3CW4Engine::Scyxw3CW4Engine() 	
{	
	menuState = new MenuState(this);
	runningState = new RunningState(this);
	endState = new EndState(this);
	pauseState = new PauseState(this);
	enterNameState = new EnterNameState(this);
	aboutState = new AboutState(this);
	bs = menuState;			
}


Scyxw3CW4Engine::~Scyxw3CW4Engine()
{
	delete menuState;
	delete runningState;
	delete endState;
	delete pauseState;
	delete enterNameState;
	delete aboutState;
}

BaseState* Scyxw3CW4Engine::bs;
RunningState* Scyxw3CW4Engine::runningState;
PauseState* Scyxw3CW4Engine::pauseState;
MenuState* Scyxw3CW4Engine::menuState;
EndState* Scyxw3CW4Engine::endState;
EnterNameState* Scyxw3CW4Engine::enterNameState;
AboutState* Scyxw3CW4Engine::aboutState;

void Scyxw3CW4Engine::virtSetupBackgroundBuffer() {	
	bs->setupBackgroundBuffer();
}

void Scyxw3CW4Engine::virtMouseDown(int iButton, int iX, int iY) {
	bs->mouseDown(iButton, iX, iY);
}

int Scyxw3CW4Engine::virtInitialiseObjects() {
	return bs->initialiseObjects();
}

void Scyxw3CW4Engine::virtDrawStringsUnderneath() {
	bs->drawStringsUnderneath();
}

void Scyxw3CW4Engine::virtMouseMoved(int iX, int iY) {
	bs->mouseMoved(iX, iY);	
}

void Scyxw3CW4Engine::virtKeyDown(int iKeyCode) {
	bs->keyDown(iKeyCode);
}

void Scyxw3CW4Engine::virtDrawStringsOnTop() {
	bs->drawStringsOnTop();
}

void Scyxw3CW4Engine::virtMainLoopDoBeforeUpdate() {
	bs->virtMainLoopDoBeforeUpdate();
}

void Scyxw3CW4Engine::copyAllBackgroundBuffer() {
	bs->copyAllBackgroundBuffer();
}

void Scyxw3CW4Engine::virtMouseWheel(int x, int y, int which, int timestamp) {
	bs->virtMouseWheel(x, y, which, timestamp);
}

int Scyxw3CW4Engine::virtInitialise() {	
	
	// Call base class version
	return BaseEngine::virtInitialise();
}

bool Scyxw3CW4Engine::mapCoordinates(double& x, double& y, const SimpleImage& image) {
	return bs->mapCoordinates(x, y, image);
}
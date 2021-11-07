#include "header.h"
#include "BaseState.h"
#include "BaseEngine.h"

BaseState::BaseState() {
}

BaseState::~BaseState() {
}

void BaseState::setupBackgroundBuffer(){
}

void BaseState::drawStringsUnderneath() {
}

void BaseState::mouseDown(int iButton, int iX, int iY) {
}

void BaseState::mouseMoved(int iX, int iY) {
}

int BaseState::initialiseObjects() {
	return 0;
}

void BaseState::playMusic() {
}

void BaseState::keyDown(int iKeyCode) {
}

void BaseState::drawStringsOnTop() {
}


void BaseState::virtMainLoopDoBeforeUpdate() {
}


void BaseState::copyAllBackgroundBuffer() {
}

void BaseState::virtMouseWheel(int x, int y, int which, int timestamp) {
}

bool BaseState::mapCoordinates(double& x, double& y, const SimpleImage& image) {
	return true;
}
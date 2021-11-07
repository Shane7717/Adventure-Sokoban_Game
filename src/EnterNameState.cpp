#include "header.h"
#include "EnterNameState.h"
#include "BaseEngine.h"
#include "Scyxw3CW4Engine.h"

EnterNameState::EnterNameState(BaseEngine* p_engine) 	
{	
	engine = p_engine;	
}

EnterNameState::~EnterNameState() {
}


void EnterNameState::setupBackgroundBuffer() {
	//Use image to set background 
	SimpleImage backgroundImage = ImageManager::loadImage("menuImage.png", true);
	//backgroundImage = backgroundImage.resizeTo(engine->getWindowWidth(), engine->getWindowHeight());
	backgroundImage.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0,
		engine->getWindowWidth(), engine->getWindowHeight());

	//Draw buttons
	SimpleImage button = ImageManager::loadImage("buttonImage.png", true);
	//button = button.resizeTo(180, 80);
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 560, 564, button.getWidth(), button.getHeight());
}

void EnterNameState::drawStringsUnderneath() {
	//Will change with the player's input
	engine->drawForegroundString(600, 390, name.data(), 0x00ffcc, NULL);

	//Draw an string on the screen
	engine->drawForegroundString(400, 90, "S o k o b a n*", 0x87CEFA, engine->getFont("stocky.ttf", 80));
	engine->drawForegroundString(300, 310, "Please Enter Your Name:", 0x87ffff, engine->getFont("Cornerstone Regular.ttf", 35));

	if (selection == 0)
		engine->drawForegroundString(585, 590, "Enter", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(585, 590, "Enter", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));
}

void EnterNameState::mouseDown(int iButton, int iX, int iY) {	
	if (iX >= 570 && iX <= 730) {
		if (iY >= 590 && iY <= 634) {					
			Scyxw3CW4Engine::bs = Scyxw3CW4Engine::runningState;
			RunningState::startPlayTime = engine->getModifiedTime() / 1000;
			Scyxw3CW4Engine::bs->playMusic();
			engine->lockAndSetupBackground();
			engine->virtInitialiseObjects();
			engine->redrawDisplay();
		}
	}
}

void EnterNameState::mouseMoved(int iX, int iY) {
	int selected = 0;

	if (iX >= 570 && iX <= 730) {
		if (iY >= 590 && iY <= 634) {
			selection = 0;
			selected = 1;
			engine->redrawDisplay();
		}
	}

	if (selected == 0) {
		selection = -1;
		engine->redrawDisplay();
	}
}

void EnterNameState::keyDown(int iKeyCode) {
	if ((iKeyCode >= 'A' && iKeyCode <= 'z') || iKeyCode == SDLK_SPACE)
	{
		name.push_back(iKeyCode);
	}
	if (iKeyCode == SDLK_BACKSPACE)
	{
		if (name.size() > 1)
		{
			name.erase(name.end() - 1);
		}
	}
	engine->redrawDisplay();

}

void EnterNameState::virtMainLoopDoBeforeUpdate() {
	//++m_iOffset;
	//m_iOffset = (m_iOffset + 1) % (engine->getWindowHeight()); 
	//virtSetupBackgroundBuffer(); 
	//engine->redrawDisplay();
}

void EnterNameState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - m_iOffset, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset - engine->getWindowHeight());
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}

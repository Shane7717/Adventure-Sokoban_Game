#include "header.h"
#include "EndState.h"
#include "BaseEngine.h"
#include "SDL_mixer.h"
#include "RunningState.h"
#include "Scyxw3CW4Engine.h"

EndState::EndState(BaseEngine* p_engine) {
	engine = p_engine;
}

EndState::~EndState() {
}

void EndState::setupBackgroundBuffer() {
	//Use image to set background 
	SimpleImage backgroundImage = ImageManager::loadImage("menuImage.png", true);
	//backgroundImage = backgroundImage.resizeTo(engine->getWindowWidth(), engine->getWindowHeight());
	backgroundImage.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0,
		engine->getWindowWidth(), engine->getWindowHeight());

	//Draw buttons
	SimpleImage button = ImageManager::loadImage("buttonImage.png", true);
	//button = button.resizeTo(180, 80);	
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 560, 664, button.getWidth(), button.getHeight());

}

void EndState::drawStringsUnderneath() {	
	engine->drawForegroundString(515, 200, "You Win", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 60));
	engine->drawForegroundString(505, 340, "Your Final Score: ", 0x00ff00, engine->getFont("Cornerstone Regular.ttf", 30));

	//Convert to the correct data type, and draw current score on screen
	char b[11];
	const char *string2 = itoa(RunningState::currentScore, b, 10);
	engine->drawForegroundString(630, 390, b, 0x00ff00, engine->getFont("Cornerstone Regular.ttf", 30));

	if (selection == 0)
		engine->drawForegroundString(605, 690, "Quit", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(605, 690, "Quit", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));

}

void EndState::playMusic() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *sound = Mix_LoadMUS("win.wav");
	Mix_PlayMusic(sound, 3);
	//SDL_Delay(1000);   
}

void EndState::mouseDown(int iButton, int iX, int iY) {
	if (iX >= 570 && iX <= 730) {
		if (iY >= 690 && iY <= 734) {
			engine->setExitWithCode(0);
		}
	}
}

void EndState::mouseMoved(int iX, int iY) {

	int selected = 0;

	if (iX >= 570 && iX <= 730) {
		if (iY >= 690 && iY <= 734) {
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

int EndState::initialiseObjects() {
	//Record the fact that we are about to change the array
	//So it doesn't get used elsewhere without reloading it
	engine->drawableObjectsChanged();

	//Destroy any existing objects
	engine->destroyOldObjects(true);

	return 0;
}

void EndState::virtMainLoopDoBeforeUpdate() {
	//++m_iOffset;
	//m_iOffset = (m_iOffset + 1) % (engine->getWindowHeight()); 
	//virtSetupBackgroundBuffer(); 
	//engine->redrawDisplay();
}

void EndState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - m_iOffset, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset - engine->getWindowHeight());
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}
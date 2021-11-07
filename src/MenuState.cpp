#include "header.h"
#include "MenuState.h"
#include "BaseEngine.h"
#include "Scyxw3CW4Engine.h"
#include "AboutState.h"
#include "RunningState.h"
#include "SDL_mixer.h"

MenuState::MenuState(BaseEngine* p_engine) 
	:m_filterScaling(0, 0, p_engine), m_filterTranslation(0, 0, &m_filterScaling) {

	engine = p_engine;
	(engine->getBackgroundSurface())->setDrawPointsFilter(&m_filterTranslation);
	(engine->getForegroundSurface())->setDrawPointsFilter(&m_filterTranslation);
	playMusic();

}

MenuState::~MenuState() {
	//delete sound;
}

void MenuState::setupBackgroundBuffer() {
	engine->fillBackground(0x000000);
	//Use image to set background 
	SimpleImage backgroundImage = ImageManager::loadImage("menuImage.png", true);
	//backgroundImage = backgroundImage.resizeTo(engine->getWindowWidth(), engine->getWindowHeight());
	backgroundImage.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0,
		engine->getWindowWidth(), engine->getWindowHeight());	

	//Draw an image 
	SimpleImage image = ImageManager::loadImage("menuImage3.png", true);
	image = image.resizeTo(200, 200);
	image.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 553, 220, image.getWidth(), image.getHeight());

	//Draw buttons
	SimpleImage button = ImageManager::loadImage("buttonImage.png", true);
//	button = button.resizeTo(180, 80);	
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 560, 464, button.getWidth(), button.getHeight());
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 560, 564, button.getWidth(), button.getHeight());
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 560, 664, button.getWidth(), button.getHeight());	
	engine->copyBackgroundPixels(0, 0, engine->getWindowWidth(), engine->getWindowHeight());
}

void MenuState::drawStringsUnderneath() {
	//Draw an string on the screen
	engine->drawForegroundString(400, 90, "S o k o b a n*", 0x87CEFA, engine->getFont("stocky.ttf", 80));

	//Draw button strings on the screen
	if (menuSelection == 0)
		engine->drawForegroundString(605, 490, "Play", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(605, 490, "Play", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));
	
	if (menuSelection == 1)
		engine->drawForegroundString(585, 590, "About", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(585, 590, "About", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));

	if (menuSelection == 2)
		engine->drawForegroundString(605, 690, "Quit", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(605, 690, "Quit", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));

}

void MenuState::mouseDown(int iButton, int iX, int iY) {
	if (iX >= 570 && iX <= 730) {
		if (iY >= 490 && iY <= 534) {		
			Scyxw3CW4Engine::bs = Scyxw3CW4Engine::enterNameState;
			engine->lockAndSetupBackground();
			engine->virtInitialiseObjects();
			engine->redrawDisplay();
		}
	}

	if (iX >= 570 && iX <= 730) {
		if (iY >= 590 && iY <= 634) {			
			Scyxw3CW4Engine::bs = Scyxw3CW4Engine::aboutState;
			engine->lockAndSetupBackground();
			engine->virtInitialiseObjects();
			engine->redrawDisplay();
		}
	}

	if (iX >= 570 && iX <= 730) {
		if (iY >= 690 && iY <= 734) {		
			engine->setExitWithCode(0);
		}
	}
}

void MenuState::mouseMoved(int iX, int iY) {
	int selected = 0;
	if (iX >= 570 && iX <= 730) {
		if (iY >= 490 && iY <= 534) {
			menuSelection = 0;
			selected = 1;
			engine->redrawDisplay();			
		}
	}

	if (iX >= 570 && iX <= 730) {
		if (iY >= 590 && iY <= 634) {
			menuSelection = 1;
			selected = 1;
			engine->redrawDisplay();
		}
	}

	if (iX >= 570 && iX <= 730) {
		if (iY >= 690 && iY <= 734) {
			menuSelection = 2;
			selected = 1;
			engine->redrawDisplay();
		}
	}
	if (selected == 0) {
		menuSelection = -1;
		engine->redrawDisplay();
	}
}

void MenuState::playMusic() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *sound = Mix_LoadMUS("menuMusic.mp3");
	Mix_PlayMusic(sound, 10);
	//SDL_Delay(1000); 
}


int MenuState::initialiseObjects() {
	engine->drawableObjectsChanged();
	// Destroy any existing objects
	engine->destroyOldObjects(true);
	return 0;
}

void MenuState::virtMainLoopDoBeforeUpdate() {	
	engine->redrawDisplay();
}

void MenuState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, 0);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, 0 - engine->getWindowHeight());
//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}


void MenuState::virtMouseWheel(int x, int y, int which, int timestamp) {
	int oldCentreX = engine->convertClickedToVirtualPixelXPosition(engine->getWindowWidth() / 2);
	int oldCentreY = engine->convertClickedToVirtualPixelYPosition(engine->getWindowHeight() / 2);

	//Do compression or stretchment when mouse wheels
	if (y < 0) {
		m_filterScaling.compress();
	}	
	else if (y > 0) {
		m_filterScaling.stretch();		
	}
				
	int newCentreX = engine->convertClickedToVirtualPixelXPosition(engine->getWindowWidth() / 2);
	int newCentreY = engine->convertClickedToVirtualPixelYPosition(engine->getWindowHeight() / 2);	
	m_filterTranslation.changeOffset(newCentreX - oldCentreX, newCentreY - oldCentreY);
	
	if (y < 0) {
		m_filterTranslation.changeOffset(500, -350);
	}
	else if (y > 0) {
		m_filterTranslation.changeOffset(-500, 350);
	}
		
	//This must be needed otherwise strange things will happen
	engine->lockAndSetupBackground();
	// Redraw the background
	engine->redrawDisplay(); 
}

void MenuState::keyDown(int iKeyCode) {
	switch (iKeyCode)
	{	
	case SDLK_LEFT:
		m_filterTranslation.changeOffset(-50, 0);
		//This must be needed otherwise strange things will happen
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
		break;
	case SDLK_RIGHT:
		m_filterTranslation.changeOffset(50, 0);
		//This must be needed otherwise strange things will happen
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
		break;
	case SDLK_UP:
		m_filterTranslation.changeOffset(0, -50);
		//This must be needed otherwise strange things will happen
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
		break;
	case SDLK_DOWN:
		m_filterTranslation.changeOffset(0, 50);
		//This must be needed otherwise strange things will happen
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
		break;
	case SDLK_SPACE: // move the top left back to the zero coordinates
		m_filterTranslation.setOffset(0, 0);
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
		break;
	}
}
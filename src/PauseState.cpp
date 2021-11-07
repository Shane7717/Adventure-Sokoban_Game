#include "header.h"
#include "PauseState.h"
#include "BaseEngine.h"
#include "Scyxw3CW4Engine.h"

PauseState::PauseState(BaseEngine* p_engine) {
	engine = p_engine;
}

PauseState::~PauseState() {
}

void PauseState::setupBackgroundBuffer() {
	;
}

void PauseState::drawStringsUnderneath() {
	engine->drawForegroundString(385, 180, "PAUSED, PRESS 'SPACE' TO CONTINUE", 0x00ffff, NULL);
	
	engine->drawForegroundString(400, 50, "S o k o b a n*", 0xff9900, engine->getFont("stocky.ttf", 80));	
	engine->drawForegroundString(1100, 200, "Save", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	engine->drawForegroundString(1100, 300, "Load", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	engine->drawForegroundString(1095, 400, "Reset", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	engine->drawForegroundString(1105, 500, "Quit", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	engine->drawForegroundString(980, 240, "Save current game state", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(992, 340, "Load saved game state", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(978, 440, "Reset current game level", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(1046, 540, "Quit This Game", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));

	//Draw the time on screen 
	char buf[128];
	sprintf(buf, "Time %3d", (Scyxw3CW4Engine::runningState)->currentTime);
	engine->drawForegroundString(engine->getWindowWidth() - 230, 100, buf, 0x66ffcc, NULL);

	//Draw the player's name on screen
	engine->drawForegroundString(45, 290, "Hello, ", 0x00ffcc, engine->getFont("Cornerstone Regular.ttf", 22));
	engine->drawForegroundString(115, 282, (Scyxw3CW4Engine::enterNameState)->name.data(), 0x00ffcc, engine->getFont("Cornerstone Regular.ttf", 32));

	engine->drawForegroundString(30, 360, "Your Current Score: ", 0x66ffff, NULL);
	//Convert to the correct data type, draw current score on screen
	char b[11];
	const char *string2 = itoa((Scyxw3CW4Engine::runningState)->currentScore, b, 10);
	engine->drawForegroundString(155, 390, b, 0x66ffff, NULL);
}

void PauseState::keyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_SPACE:		
		engine->unpause();
		Scyxw3CW4Engine::bs = Scyxw3CW4Engine::runningState;
		engine->redrawDisplay();			
		break;
	}
}

void PauseState::virtMainLoopDoBeforeUpdate() {
	//++m_iOffset;
	//m_iOffset = (m_iOffset + 1) % (engine->getWindowHeight()); 
	//virtSetupBackgroundBuffer(); 
	//engine->redrawDisplay();
}

void PauseState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - m_iOffset, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset - engine->getWindowHeight());
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}
#include "header.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "MonsterObject.h"
#include "FroggerObject.h"

MonsterObject::MonsterObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = getEngine()->getWindowWidth() / 2 - 50 / 2;	//Starting position on the screen
	m_iCurrentScreenY = getEngine()->getWindowHeight() - 200;
}


MonsterObject::~MonsterObject()
{
}

void MonsterObject::virtDraw() {
	SimpleImage image = ImageManager::loadImage("monster.png", true);
	//image = image.resizeTo(50, 50);
	image.renderImageWithMask(getEngine()->getForegroundSurface(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth(), image.getHeight());
}

void MonsterObject::virtDoUpdate(int iCurrentTime) {
	//(xPos, yPos) is the position for object at index 0;
	//int xPos = (getEngine()->getDisplayableObject(0))->getXCentre();
	//int yPos = (getEngine()->getDisplayableObject(0))->getYCentre() + iImageSize;
	
	if (m_iCurrentScreenY >= 600 && m_iCurrentScreenX <= 1100) {
		m_iCurrentScreenX += 2;
	}
	if (m_iCurrentScreenX > 1100 && m_iCurrentScreenY >= 200 - 50) {
		m_iCurrentScreenY -= 2;
	}
	if (m_iCurrentScreenY < 150 && m_iCurrentScreenX >= 200) {
		m_iCurrentScreenX -= 2;
	}
	if (m_iCurrentScreenX < 200 && m_iCurrentScreenY <= 600) {
		m_iCurrentScreenY += 2;
	}
	
	//Adjust position if anything wrong
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - 50)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - 50;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - 50)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - 50;

	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}
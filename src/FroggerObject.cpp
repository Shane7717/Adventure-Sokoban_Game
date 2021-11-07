#include "header.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "FroggerObject.h"

FroggerObject::FroggerObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = 10;
	m_iCurrentScreenY = 10;
}


FroggerObject::~FroggerObject()
{
}

void FroggerObject::virtDraw() {
	SimpleImage image = ImageManager::loadImage("froggerUp.png", true);
	//image = image.resizeTo(iImageSize, iImageSize);
	//Don't use this since memory will increase constantly

	image.renderImageWithMask(getEngine()->getForegroundSurface(), 
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth(), image.getHeight());	
}

void FroggerObject::virtDoUpdate(int iCurrentTime) {
	
	//change position if player presses a key	
	if (getEngine()->isKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 2;
	else if (getEngine()->isKeyPressed(SDLK_s))
		m_iCurrentScreenY += 2;
	else if (getEngine()->isKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 2;
	else if (getEngine()->isKeyPressed(SDLK_d))
		m_iCurrentScreenX += 2;
	else { 
	//Change position if player uses mouse to click
		int iClickedX = getEngine()->getMouseXClickedDown();
		int iClickedY = getEngine()->getMouseYClickedDown();

		if (iClickedX == iLastXpos & iClickedY == iLastYpos)
			;	//do nothing
		else {
			iLastXpos = iClickedX;
			iLastYpos = iClickedY;
			if (iClickedX != m_iCurrentScreenX) 
				m_iCurrentScreenX = iClickedX - 34 / 2;
			if (iClickedY != m_iCurrentScreenY) 	
				m_iCurrentScreenY = iClickedY - 34 / 2;
		}
	}
	
	//Adjust position if anything wrong
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - 34)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - 34;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - 34)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - 34;
	
	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}
#include "header.h"
#include "CollisionObject.h"
#include "ImageManager.h"
#include "BaseEngine.h"
#include "CollisionDetection.h"


CollisionObject::CollisionObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = 100;	//Starting position on the screen
	m_iCurrentScreenY = 100;

	m_dX = m_iCurrentScreenX;
	m_dY = m_iCurrentScreenY;
	// Speed
	xSpeed = 1.5;
	ySpeed = 2.5;
	// And make it visible
	setVisible(true);
}


CollisionObject::~CollisionObject()
{
}

void CollisionObject::virtDraw() {
	SimpleImage image = ImageManager::loadImage("spaceShip.png", true);
	//image = image.resizeTo(50, 50);
	image.renderImageWithMask(getEngine()->getForegroundSurface(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth(), image.getHeight());
}

void CollisionObject :: virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return; // Do nothing if paused

	// Change speed if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP))
		ySpeed -= 0.008;
	if (getEngine()->isKeyPressed(SDLK_DOWN))
		ySpeed += 0.008;
	if (getEngine()->isKeyPressed(SDLK_LEFT))
		xSpeed -= 0.008;
	if (getEngine()->isKeyPressed(SDLK_RIGHT))
		xSpeed += 0.008;

	// Alter position for speed
	m_dX += xSpeed;
	m_dY += ySpeed;

	// Check for bounce off the edge
	if ((m_dX + m_iStartDrawPosX) < 0)
	{
		m_dX = -m_iStartDrawPosX;
		if (xSpeed < 0)
			xSpeed = -xSpeed;
	}
	if ((m_dX + m_iStartDrawPosX) > (getEngine()->getWindowWidth() - 51))
	{
		m_dX = getEngine()->getWindowWidth() - 51 - m_iStartDrawPosX;
		if (xSpeed > 0)
			xSpeed = -xSpeed;
	}
	if ((m_dY + m_iStartDrawPosY) < 0)
	{
		m_dY = -m_iStartDrawPosY;
		if (ySpeed < 0)
			ySpeed = -ySpeed;
	}
	if ((m_dY + m_iStartDrawPosY) > (getEngine()->getWindowHeight() - 51))
	{
		m_dY = getEngine()->getWindowHeight() - 51 - m_iStartDrawPosY;
		if (ySpeed > 0)
			ySpeed = -ySpeed;
	}

	// Set current position - you NEED to set the current positions
	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);

	//printf("Position %f, %f\n", m_dX, m_dY );

	int x1l = (getEngine()->getDisplayableObject(0))->getXCentre();
	int x1r = (getEngine()->getDisplayableObject(0))->getXCentre() + 34;
	int y1t = (getEngine()->getDisplayableObject(0))->getYCentre();
	int y1b = (getEngine()->getDisplayableObject(0))->getYCentre() + 34;
	int x2l = this->getXCentre();
	int x2r = this->getXCentre() + 50;
	int y2t = this->getYCentre();
	int y2b = this->getYCentre() + 50;
	int x3l = (getEngine()->getDisplayableObject(1))->getXCentre();
	int x3r = (getEngine()->getDisplayableObject(1))->getXCentre() + 50;
	int y3t = (getEngine()->getDisplayableObject(1))->getYCentre();
	int y3b = (getEngine()->getDisplayableObject(1))->getYCentre() + 50;

	if (CollisionDetection::checkRectangles(x1l, x1r, y1t, y1b, x2l, x2r, y2t, y2b)) {
		xSpeed = -xSpeed;
		ySpeed = -ySpeed;
		(getEngine()->getDisplayableObject(0))->setPosition(631 - 17, 581 - 17);
	}
	
	if (CollisionDetection::checkRectangles(x3l, x3r, y3t, y3b, x2l, x2r, y2t, y2b)) {
		xSpeed = -xSpeed;
		ySpeed = -ySpeed;
	}


	// Ensure that the object gets redrawn on the display, if something changed
	this->redrawDisplay();
}

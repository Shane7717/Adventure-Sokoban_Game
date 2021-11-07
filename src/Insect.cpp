#include "header.h"
#include "Insect.h"
#include "RunningState.h"

Insect::Insect(BaseEngine *pEngine, int x, int y, CW4TileManager* tileManager)
	: Monster(pEngine, x, y, tileManager) {
	leftImage = ImageManager::loadImage("insectLeft.png", true);
	rightImage = ImageManager::loadImage("insectRight.png", true);
	upImage = ImageManager::loadImage("insectUp.png", true);
	downImage = ImageManager::loadImage("insectDown.png", true);
	mainImage = leftImage;
	tm = tileManager;	
	lastChoice = (rand() + m_iCurrentScreenX + m_iCurrentScreenY) % 4;	
}

Insect::~Insect() {
}

void Insect::virtDraw() {
	int iTick = getEngine()->getModifiedTime() / 150;
	int iFrame = iTick % 6;

	mainImage.renderImageWithMask(getEngine()->getForegroundSurface(),
		mainImage.getWidth() / 6 * iFrame, 0, m_iCurrentScreenX, m_iCurrentScreenY,
		mainImage.getWidth() / 6, mainImage.getHeight());
}

void Insect::virtDoUpdate(int iCurrentTime) {	
	if (getEngine()->isPaused())
		return;

	//0 is up, 1 is down, 2 is left and 3 is right		
	int newChoice = (rand() + m_iCurrentScreenX + m_iCurrentScreenY) % 4;
	int xPosFrog = (getEngine()->getDisplayableObject(0))->getXCentre();
	int yPosFrog = (getEngine()->getDisplayableObject(0))->getYCentre();
	int xTileFrog = tm->getMapXForScreenX(xPosFrog);
	int yTileFrog = tm->getMapYForScreenY(yPosFrog);
	if (xTileFrog == tm->getMapXForScreenX(m_iCurrentScreenX) &&
		yTileFrog == tm->getMapYForScreenY(m_iCurrentScreenY) && createOnce) {
		RunningState::currentScore += 10;
		getEngine()->storeObjectInArray(19, NULL);
		delete this;
		return;		
	}

	if ((m_iCurrentScreenX == requiredXpos) && (m_iCurrentScreenY == requiredYpos)) {
		//satisfies the required position
		lastChoice = newChoice;
		signal = true;		
	}
	else {  //doesn't satisfy the required position
		if (newChoice != lastChoice) {
			newChoice = lastChoice;
		}
	}

	if (signal) {
		if (newChoice == 0) {
			requiredXpos = m_iCurrentScreenX;
			requiredYpos = m_iCurrentScreenY - 40;

			//Check map edges with intelligence
			if (requiredYpos < 155) {
				requiredYpos = requiredYpos + 40;
			}

			//Check walls with intelligence
			int xTempt = tm->getMapXForScreenX(requiredXpos);
			int yTempt = tm->getMapYForScreenY(requiredYpos);
			if (tm->getMapValue(xTempt, yTempt) == 1 || tm->getMapValue(xTempt, yTempt) == 99) {
				requiredYpos = requiredYpos + 40;
				m_iCurrentScreenY += speed;
			}

			signal = false;
		}
		else if (newChoice == 1) {
			requiredXpos = m_iCurrentScreenX;
			requiredYpos = m_iCurrentScreenY + 40;

			//Check map edges with intelligence
			if (requiredYpos == 155 + 15 * 40) {
				requiredYpos = requiredYpos - 40;
			}

			//Check walls with intelligence
			int xTempt = tm->getMapXForScreenX(requiredXpos);
			int yTempt = tm->getMapYForScreenY(requiredYpos);
			if (tm->getMapValue(xTempt, yTempt) == 1 || tm->getMapValue(xTempt, yTempt) == 99) {
				requiredYpos = requiredYpos - 40;
				m_iCurrentScreenY -= speed;
			}

			signal = false;
		}
		else if (newChoice == 2) {
			requiredXpos = m_iCurrentScreenX - 40;
			requiredYpos = m_iCurrentScreenY;

			//Check map edges with intelligence
			if (requiredXpos < 360) {
				requiredXpos = requiredXpos + 40;
			}

			//Check walls with intelligence
			int xTempt = tm->getMapXForScreenX(requiredXpos);
			int yTempt = tm->getMapYForScreenY(requiredYpos);
			if (tm->getMapValue(xTempt, yTempt) == 1 || tm->getMapValue(xTempt, yTempt) == 99) {
				requiredXpos = requiredXpos + 40;
				m_iCurrentScreenX += speed;
			}

			signal = false;
		}
		else if (newChoice == 3) {
			requiredXpos = m_iCurrentScreenX + 40;
			requiredYpos = m_iCurrentScreenY;

			//Check map edges with intelligence
			if (requiredXpos == 360 + 15 * 40) {
				requiredXpos = requiredXpos - 40;
			}

			//Check walls with intelligence
			int xTempt = tm->getMapXForScreenX(requiredXpos);
			int yTempt = tm->getMapYForScreenY(requiredYpos);
			if (tm->getMapValue(xTempt, yTempt) == 1 || tm->getMapValue(xTempt, yTempt) == 99) {
				requiredXpos = requiredXpos - 40;
				m_iCurrentScreenX -= speed;
			}

			signal = false;
		}
	}

	switch (newChoice)
	{
	case 0:   //Up	
		mainImage = upImage;
		m_iCurrentScreenY -= speed;
		break;
	case 1:   //Down
		mainImage = downImage;
		m_iCurrentScreenY += speed;
		break;
	case 2:   //Left
		mainImage = leftImage;
		m_iCurrentScreenX -= speed;
		break;
	case 3:   //Right
		mainImage = rightImage;
		m_iCurrentScreenX += speed;
		break;
	}

	checkTileEdges();

	// Ensure that the objects get redrawn on the display	
	this->redrawDisplay();
}
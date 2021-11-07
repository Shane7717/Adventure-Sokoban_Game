#include "header.h"
#include "BrownMonster.h"
#include "RunningState.h"

BrownMonster::BrownMonster(BaseEngine *pEngine, int x, int y, CW4TileManager* tileManager)
	: Monster(pEngine, x, y, tileManager) {
	leftImage = ImageManager::loadImage("BrownMonsterLeft.png", true);
	rightImage = ImageManager::loadImage("BrownMonsterRight.png", true);
	mainImage = leftImage;
	tm = tileManager;
	lastChoice = (rand() + m_iCurrentScreenX + m_iCurrentScreenY) % 4;	
}

BrownMonster::~BrownMonster() {
}

void BrownMonster::virtDraw() {
	int iTick = getEngine()->getModifiedTime() / 150;
	int iFrame = iTick % 5;

	mainImage.renderImageWithMask(getEngine()->getForegroundSurface(),
	mainImage.getWidth() / 5 * iFrame, 0, m_iCurrentScreenX, m_iCurrentScreenY,
	mainImage.getWidth() / 5, mainImage.getHeight());			
}

void BrownMonster::virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return;
		
	//0 is up, 1 is down, 2 is left and 3 is right		
	//int newChoice = (rand() + m_iCurrentScreenX + m_iCurrentScreenY) % 4;	
	int newChoice = 0;
	int xPosFrog = (getEngine()->getDisplayableObject(0))->getXCentre();
	int yPosFrog = (getEngine()->getDisplayableObject(0))->getYCentre();
	int xTileFrog = tm->getMapXForScreenX(xPosFrog);
	int yTileFrog = tm->getMapYForScreenY(yPosFrog);
	if (xTileFrog == tm->getMapXForScreenX(m_iCurrentScreenX) &&
		yTileFrog == tm->getMapYForScreenY(m_iCurrentScreenY)) {
		(getEngine()->getDisplayableObject(0))->setPosition(
			360 + (RunningState::mainX) * 40, 155 + (RunningState::mainY) * 40 );
		//Reset the position of the player
	}
	
	if (!getToWall && randomTimes <= 0) {		
		//Greedy Algorithm - Add more intelligence to this object	
		int upDistance = squareDistance(xPosFrog, yPosFrog, m_iCurrentScreenX, m_iCurrentScreenY - 40);
		int downDistance = squareDistance(xPosFrog, yPosFrog, m_iCurrentScreenX, m_iCurrentScreenY + 40);
		int leftDistance = squareDistance(xPosFrog, yPosFrog, m_iCurrentScreenX - 40, m_iCurrentScreenY);
		int rightDistance = squareDistance(xPosFrog, yPosFrog, m_iCurrentScreenX + 40, m_iCurrentScreenY);

		oo.setX(upDistance);
		oo.setY(downDistance);
		oo.setJ(leftDistance);
		oo.setK(rightDistance);

		//Operator Overloading: Find the minimum distance and get the corresponding direction
		newChoice = --oo;		
	}
	else {
		newChoice = (rand() + m_iCurrentScreenX + m_iCurrentScreenY) % 4;
		randomTimes--;
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
			getToWall = false;
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
				getToWall = true;
				randomTimes = 5;
			}
			signal = false;
		}
		else if (newChoice == 1) {
			getToWall = false;
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
				getToWall = true;
				randomTimes = 5;
			}
			signal = false;
		}
		else if (newChoice == 2) {
			getToWall = false;
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
				getToWall = true;
				randomTimes = 5;
			}
			signal = false;
		}
		else if (newChoice == 3) {
			getToWall = false;
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
				getToWall = true;
				randomTimes = 5;
			}
			signal = false;
		}
	}

	switch (newChoice)
	{
	case 0:   //Up	
		m_iCurrentScreenY -= speed;
		break;
	case 1:   //Down
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
#include "header.h"
#include "MainCharacter.h"
#include "Scyxw3CW4Engine.h"
#include "RunningState.h"
#include "EndState.h"
#include <fstream>
#include "CW4TileManager.h"
#include "Insect.h"

MainCharacter::MainCharacter(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager)
	: DisplayableObject(pEngine),
	tm(tileManager),
	engine(pEngine)
{

	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;	
	imageUp = ImageManager::loadImage("mainUp.png", true);
	imageDown = ImageManager::loadImage("mainDown.png", true);
	imageLeft = ImageManager::loadImage("mainLeft.png", true);
	imageRight = ImageManager::loadImage("mainRight.png", true);
	mainImage = imageDown;

}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::virtDraw() {
	int iTick = getEngine()->getModifiedTime() / 300;
	int iFrame = iTick % 4;

	mainImage.renderImageWithMask(getEngine()->getForegroundSurface(),
		mainImage.getWidth() / 4 * iFrame, 0, m_iCurrentScreenX, m_iCurrentScreenY,
		mainImage.getWidth() / 4, mainImage.getHeight());

//	mainImage.renderImageWithMask(engine->getForegroundSurface(),
//		0, 0, m_iCurrentScreenX+2, m_iCurrentScreenY+2, imageUp.getWidth(), imageUp.getHeight());	
}

void MainCharacter::virtDoUpdate(int iCurrentTime) {
	if (RunningState::currentTime >= 10 && createOnce) {		
		engine->storeObjectInArray(19, new Insect(engine, 360 + 40 * 2, 155 + 40 * 2, tm));
		createOnce = false;
	}

	if (engine->isPaused())
		return;
	bool homeFlag = false;

	int xTempt = (tm)->getMapXForScreenX(m_iCurrentScreenX);
	int yTempt = (tm)->getMapYForScreenY(m_iCurrentScreenY);
	if (tm->getMapValue(xTempt, yTempt) == 5)
		homeFlag = true;

	//Let the main character move only one tile per press
	if (engine->isKeyPressed(SDLK_w)) {
		mainImage = imageUp;
		wTimes++;
		sTimes = 0;
		aTimes = 0;
		dTimes = 0;
		yTempt -= 1;
		bool canCharacterMove = true;
		bool canBoxMove = true;

		//Check collisions with walls
		if (tm->getMapValue(xTempt, yTempt) == 1)
			yTempt++;

		//Check collisions with only boxes and reset their positions if satisfied
		for (int i = 1; i <= RunningState::currentNumBoxes; ++i) {	

			int xTileBox = tm->getMapXForScreenX((engine->getDisplayableObject(i))->getXCentre());
			int yTileBox = tm->getMapYForScreenY((engine->getDisplayableObject(i))->getYCentre());

			//If one of any boxes is exactly above the main character
			if (yTileBox == yTempt && xTileBox == xTempt && wTimes <= 1) {	

				//If the tile above the box is not a wall
				if (tm->getMapValue(xTileBox, yTileBox - 1) != 1) {
					for (int j = 1; j <= RunningState::currentNumBoxes; ++j) {
						int xTileBox2 = tm->getMapXForScreenX((engine->getDisplayableObject(j))->getXCentre());
						int yTileBox2 = tm->getMapYForScreenY((engine->getDisplayableObject(j))->getYCentre());

						//if two boxes are next to each other
						if (xTileBox == xTileBox2 && (yTileBox - 1) == yTileBox2) {
							canBoxMove = false;
							canCharacterMove = false;
						}							
					}
					if (canBoxMove)
						//The box moves up one tile if the above tile is not a wall
						(engine->getDisplayableObject(i))->setPosition(360 + xTileBox * 40, 155 + (yTileBox - 1) * 40);
				}
				else {
					canCharacterMove = false;
				}
			}	
			
		}

		//Reset position of the main character
		if (wTimes <= 1 && canCharacterMove)
			m_iCurrentScreenY = 155 + yTempt * 40;
	}

	else if (engine->isKeyPressed(SDLK_s)) {
		mainImage = imageDown;
		sTimes++;
		wTimes = 0;
		aTimes = 0;
		dTimes = 0;
		yTempt += 1;
		bool canCharacterMove = true;
		bool canBoxMove = true;

		//Check collisions with walls
		if (tm->getMapValue(xTempt, yTempt) == 1)
			yTempt--;

		//Check collisions with only boxes and reset their positions if satisfied
		for (int i = 1; i <= RunningState::currentNumBoxes; ++i) {

			int xTileBox = tm->getMapXForScreenX((engine->getDisplayableObject(i))->getXCentre());
			int yTileBox = tm->getMapYForScreenY((engine->getDisplayableObject(i))->getYCentre());

			//If one of any boxes is exactly below the main character
			if (yTileBox == yTempt && xTileBox == xTempt && sTimes <= 1) {

				//If the tile below the box is not a wall
				if (tm->getMapValue(xTileBox, yTileBox + 1) != 1) {
					for (int j = 1; j <= RunningState::currentNumBoxes; ++j) {
						int xTileBox2 = tm->getMapXForScreenX((engine->getDisplayableObject(j))->getXCentre());
						int yTileBox2 = tm->getMapYForScreenY((engine->getDisplayableObject(j))->getYCentre());

						//if two boxes are next to each other
						if (xTileBox == xTileBox2 && (yTileBox + 1) == yTileBox2) {
							canBoxMove = false;
							canCharacterMove = false;
						}
					}
					if (canBoxMove)
						//The box moves down one tile if the below tile is not a wall
						(engine->getDisplayableObject(i))->setPosition(360 + xTileBox * 40, 155 + (yTileBox + 1) * 40);
				}
				else {
					canCharacterMove = false;
				}
			}
		}

		//Reset position of the main character
		if (sTimes <= 1 && canCharacterMove)
			m_iCurrentScreenY = 155 + yTempt * 40;
	}

	else if (engine->isKeyPressed(SDLK_a)) {
		mainImage = imageLeft;
		aTimes++;
		wTimes = 0;
		sTimes = 0;
		dTimes = 0;
		xTempt -= 1;
		bool canCharacterMove = true;
		bool canBoxMove = true;

		//Check collisions with walls
		if (tm->getMapValue(xTempt, yTempt) == 1)
			xTempt++;

		//Check collisions with only boxes and reset their positions if satisfied
		for (int i = 1; i <= RunningState::currentNumBoxes; ++i) {

			int xTileBox = tm->getMapXForScreenX((engine->getDisplayableObject(i))->getXCentre());
			int yTileBox = tm->getMapYForScreenY((engine->getDisplayableObject(i))->getYCentre());

			//If one of any boxes is exactly left next to the main character
			if (yTileBox == yTempt && xTileBox == xTempt && aTimes <= 1) {

				//If the tile left next to the box is not a wall
				if (tm->getMapValue(xTileBox - 1, yTileBox) != 1) {
					for (int j = 1; j <= RunningState::currentNumBoxes; ++j) {
						int xTileBox2 = tm->getMapXForScreenX((engine->getDisplayableObject(j))->getXCentre());
						int yTileBox2 = tm->getMapYForScreenY((engine->getDisplayableObject(j))->getYCentre());

						//if two boxes are next to each other
						if ((xTileBox-1) == xTileBox2 && yTileBox == yTileBox2) {
							canBoxMove = false;
							canCharacterMove = false;
						}
					}
					if (canBoxMove)
						//The box moves left one tile if the left tile is not a wall
						(engine->getDisplayableObject(i))->setPosition(360 + (xTileBox-1) * 40, 155 + yTileBox * 40);
				}
				else {
					canCharacterMove = false;
				}
			}
		}

		//Reset position of the main character
		if (aTimes <= 1 && canCharacterMove)
			m_iCurrentScreenX = 360 + xTempt * 40;
	}


	else if (engine->isKeyPressed(SDLK_d)) {
		mainImage = imageRight;
		dTimes++;
		aTimes = 0;
		wTimes = 0;
		sTimes = 0;
		xTempt += 1;
		bool canCharacterMove = true;
		bool canBoxMove = true;

		//Check collisions with walls
		if (tm->getMapValue(xTempt, yTempt) == 1)
			xTempt--;
	
		//Check collisions with only boxes and reset their positions if satisfied
		for (int i = 1; i <= RunningState::currentNumBoxes; ++i) {

			int xTileBox = tm->getMapXForScreenX((engine->getDisplayableObject(i))->getXCentre());
			int yTileBox = tm->getMapYForScreenY((engine->getDisplayableObject(i))->getYCentre());

			//If one of any boxes is exactly right next to the main character
			if (yTileBox == yTempt && xTileBox == xTempt && dTimes <= 1) {

				//If the tile right next to the box is not a wall
				if (tm->getMapValue(xTileBox + 1, yTileBox) != 1) {
					for (int j = 1; j <= RunningState::currentNumBoxes; ++j) {
						int xTileBox2 = tm->getMapXForScreenX((engine->getDisplayableObject(j))->getXCentre());
						int yTileBox2 = tm->getMapYForScreenY((engine->getDisplayableObject(j))->getYCentre());

						//if two boxes are next to each other
						if ((xTileBox + 1) == xTileBox2 && yTileBox == yTileBox2) {
							canBoxMove = false;
							canCharacterMove = false;
						}
					}
					if (canBoxMove)
						//The box moves right one tile if the right tile is not a wall
						(engine->getDisplayableObject(i))->setPosition(360 + (xTileBox + 1) * 40, 155 + yTileBox * 40);
				}
				else {
					canCharacterMove = false;
				}
			}
		}

		//Reset position of the main character
		if (dTimes <= 1 && canCharacterMove)
			m_iCurrentScreenX = 360 + xTempt * 40;
	}

	else {
		wTimes = 0;
		sTimes = 0;
		aTimes = 0;
		dTimes = 0;			 
	}

	//Check Collisions with the whole tile map edges
	if (xTempt < 0) 
		m_iCurrentScreenX = 360 + (++xTempt) * 40;
	if (xTempt > 14) 
		m_iCurrentScreenX = 360 + (--xTempt) * 40;
	if (yTempt < 0)
		m_iCurrentScreenY = 155 + (++yTempt) * 40;
	if (yTempt > 14)
		m_iCurrentScreenY = 155 + (--yTempt) * 40;
	

	//After moving the character, check if the level is finished successfully
	int matchNum = 0;
	for (int k = 1; k <= RunningState::currentNumBoxes; ++k) {
		int xTileBox = tm->getMapXForScreenX((engine->getDisplayableObject(k))->getXCentre());
		int yTileBox = tm->getMapYForScreenY((engine->getDisplayableObject(k))->getYCentre());

		string strFileName = "level" + to_string(RunningState::currentLevel) + "Map.txt";
		ifstream file;
		file.open(strFileName);
		if (!file) {
			cout << "Failed to open the file" << endl;
			exit(1);
		}

		int xPos;
		int yPos;
		int tempLevel;
		int tempType;
		file >> tempLevel;
		file >> xPos;
		file >> yPos;
		file >> tempType;
		while (file) {
			if (xTileBox == xPos && yTileBox == yPos && tempType == 3)
				matchNum++;
			file >> xPos;
			file >> yPos;
			file >> tempType;
		}
	}
	if (matchNum == RunningState::currentNumBoxes) {
		tm->setAndRedrawMapValueAt(13, 0, 0, engine, engine->getBackgroundSurface());
		tm->setAndRedrawMapValueAt(13, 1, 0, engine, engine->getBackgroundSurface());
		tm->setAndRedrawMapValueAt(14, 1, 0, engine, engine->getBackgroundSurface());
	}
	else {
		tm->setAndRedrawMapValueAt(13, 0, 1, engine, engine->getBackgroundSurface());
		tm->setAndRedrawMapValueAt(13, 1, 1, engine, engine->getBackgroundSurface());
		tm->setAndRedrawMapValueAt(14, 1, 1, engine, engine->getBackgroundSurface());
	}
	
	//Win Condition Judgement
	if (homeFlag) {	
		//Calculate the scores that the player will get
		if (RunningState::currentTime <= 10) {
			RunningState::currentScore += 100;
		}
		else if (RunningState::currentTime <= 20) {
			RunningState::currentScore += 90;
		} 
		else if (RunningState::currentTime <= 30) {
			RunningState::currentScore += 80;
		} 
		else if (RunningState::currentTime <= 40) {
			RunningState::currentScore += 70;
		} 
		else if (RunningState::currentTime <= 50) {
			RunningState::currentScore += 60;
		}
		else if (RunningState::currentTime <= 60) {
			RunningState::currentScore += 50;
		}
		else {
			RunningState::currentScore += 40;
		}
						
		RunningState::currentLevel += 1;
		if (RunningState::currentLevel == 9) {			
			Scyxw3CW4Engine::bs = Scyxw3CW4Engine::endState;				
			engine->lockAndSetupBackground();		
			engine->virtInitialiseObjects();
			Scyxw3CW4Engine::bs->playMusic();
			return;
		}
		RunningState::startPlayTime = engine->getModifiedTime() / 1000;
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				tm->setMapValue(i, j, 0);		
			}
		}		
		engine->lockAndSetupBackground();
		engine->virtInitialiseObjects();	
		return;
	}
			
	//Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}
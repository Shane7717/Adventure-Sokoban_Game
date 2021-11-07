#include "header.h"
#include "Monster.h"
#include "Scyxw3CW4Engine.h"
#include "RunningState.h"

Monster::Monster(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;
	tm = tileManager;
}

Monster::~Monster() {
}

void Monster::virtDraw() {
};

void Monster::virtDoUpdate(int iCurrentTime) {	
};

void Monster::checkTileEdges() {
//Check whether or not the object is out of the tile map
	if (m_iCurrentScreenY > 155 + 15 * 40 - 40)
		m_iCurrentScreenY -= 1;
	if (m_iCurrentScreenY < 155)
		m_iCurrentScreenY += 1;
	if (m_iCurrentScreenX < 360) 
		m_iCurrentScreenX += 1;
	if (m_iCurrentScreenX > 360 + 15 * 40 - 40)
		m_iCurrentScreenX -= 1;
}


void Monster::checkTileEdges2() {
	//Check whether or not the object is out of the tile map
	if (m_iCurrentScreenY > 155 + 15 * 40 - 40)
		m_iCurrentScreenY -= 2;
	if (m_iCurrentScreenY < 155)
		m_iCurrentScreenY += 2;
	if (m_iCurrentScreenX < 360)
		m_iCurrentScreenX += 2;
	if (m_iCurrentScreenX > 360 + 15 * 40 - 40)
		m_iCurrentScreenX -= 2;
}

int Monster::squareDistance(int x1, int y1, int x2, int y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

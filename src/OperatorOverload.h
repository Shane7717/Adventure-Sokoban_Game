#pragma once

class OperatorOverload
{
public:
	int x;
	int y;
	int j;
	int k;

	//Find the minimum value among x, y, j and k, and 
	//Return the corresponding direction choice (Operator Overloading)
	int operator --();
	void setX(int x);
	void setY(int y);
	void setJ(int j);
	void setK(int k);
		
};

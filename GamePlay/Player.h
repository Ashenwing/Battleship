#pragma once
#include "GameGrid.h"
#include "Boats.h"
#include <string>

using namespace Boats;
using namespace Matrix;

class Player
{
public:
	Player(void);
	~Player(void);

	void SetBoats(GameGrid* gameGrid, bool direction, int boatSize, string boatName);
	bool ShootEnemy(GameGrid* gameGrid);
	virtual bool DidIWin(GameGrid* gameGrid) =0;
protected:
	string userName;
};


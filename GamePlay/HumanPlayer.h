#pragma once
#include "Player.h"
#include "HumanGameGrid.h"
#include "GoodHit.h"

using namespace Matrix;

class HumanPlayer: public Player
{
public:
	HumanPlayer(string name);
	~HumanPlayer();
	bool DidIWin(GameGrid* gameGrid);
	string GetName();
private:
};


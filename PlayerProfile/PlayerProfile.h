#pragma once
#include "../GamePlay/HumanPlayer.h"
#include "../GamePlay/HumanGameGrid.h"

class PlayerProfile
{
public:
	PlayerProfile(HumanGameGrid&);
	~PlayerProfile(void);
	bool Save();
	HumanGameGrid& Load();
private:
	HumanGameGrid saveGrid;
};


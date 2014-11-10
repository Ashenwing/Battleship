#pragma once
#include "ComputerPlayer.h"
#include "ComputerPlayerExpert.h"
#include "ComputerGameGrid.h"
#include "HumanGameGrid.h"
#include "HumanPlayer.h"

using namespace Matrix;

class PlayGame
{
public:
	static int gameLevel;

	PlayGame(void);
	~PlayGame(void);
	ComputerPlayer* getComputer();
	ComputerGameGrid* getComputerGrid();
	HumanGameGrid* getHumanGrid();
	HumanPlayer* getHuman();
	void Start();
private:
	ComputerGameGrid* pcGrid;
	ComputerPlayer* pcPlayer;
	ComputerPlayerExpert* pcExpert;
	HumanGameGrid* humanGrid;
	HumanPlayer* humanPlayer;


};


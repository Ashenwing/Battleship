#include "PlayGame.h"
#include "Boats.h"
#include "ComputerPlayer.h"
#include "ComputerPlayerExpert.h"
#include "ComputerGameGrid.h"
#include "HumanPlayer.h"
#include "HumanGameGrid.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>


using namespace std;
using namespace Matrix;

int PlayGame::gameLevel = 0;

PlayGame::PlayGame(void)
{
}


PlayGame::~PlayGame(void)
{
	delete pcGrid;
	delete pcPlayer;
	delete humanGrid;
	delete humanPlayer;
}

void PlayGame::Start()
{
	humanPlayer = new HumanPlayer("Vous");
	humanGrid = new HumanGameGrid();

	pcGrid = new ComputerGameGrid();

	srand (time(NULL));

	
	// rand() % 2 va donner un chiffre entre 0 et 1, qui sert de boolean.
	// 1 = true, 0 = false
	if(gameLevel == 1)
	{
		pcPlayer = new ComputerPlayer("Commodore 64");

		pcPlayer->SetBoats(pcGrid, rand() %2, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
		pcPlayer->SetBoats(pcGrid, rand() %2, Boats::STR_BATTLESHIP.back() - 48, Boats::STR_BATTLESHIP);
		pcPlayer->SetBoats(pcGrid, rand() %2, Boats::STR_DESTROYER.back() - 48, Boats::STR_DESTROYER);
		pcPlayer->SetBoats(pcGrid, rand() %2, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);
		pcPlayer->SetBoats(pcGrid, rand() %2, Boats::STR_PATROL.back() - 48, Boats::STR_PATROL);
	}
	else
	{
		pcExpert = new ComputerPlayerExpert("HAL-9000", humanGrid);

		pcExpert->SetBoats(pcGrid, rand() %2, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
		pcExpert->SetBoats(pcGrid, rand() %2, Boats::STR_BATTLESHIP.back() - 48, Boats::STR_BATTLESHIP);
		pcExpert->SetBoats(pcGrid, rand() %2, Boats::STR_DESTROYER.back() - 48, Boats::STR_DESTROYER);
		pcExpert->SetBoats(pcGrid, rand() %2, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);
		pcExpert->SetBoats(pcGrid, rand() %2, Boats::STR_PATROL.back() - 48, Boats::STR_PATROL);
	}


	assert(pcGrid->Size() != 0);
};

ComputerPlayer* PlayGame::getComputer()
{
	if(gameLevel == 1)
	return this->pcPlayer;
	else
		return this->pcExpert;
}

ComputerGameGrid* PlayGame::getComputerGrid()
{
	return this->pcGrid;
}

HumanPlayer* PlayGame::getHuman()
{
	return this->humanPlayer;
}

HumanGameGrid* PlayGame::getHumanGrid()
{
	return this->humanGrid;
}

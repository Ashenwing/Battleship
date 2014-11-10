#pragma once
#include "ComputerPlayer.h"
#include "ComputerGameGrid.h"
#include "HumanGameGrid.h"
#include "GoodHit.h"
#include <vector>

using namespace Matrix;
using namespace std;

class ComputerPlayerExpert: public ComputerPlayer
{
public:
	ComputerPlayerExpert(string name, GameGrid* humanGrid);
	~ComputerPlayerExpert();
	void SetBoats(GameGrid* gameGrid, bool direction, int boatSize, string boatName);
	bool ShootEnemy(GameGrid* gameGrid);
	void ShootEnemyTest(GameGrid* gameGrid, vector<GoodHit*>& goodHits);
	bool DidIWin(GameGrid* gameGrid);
	vector<GoodHit*> getVec();
	string GetName();
private:
	void BoatHit(int x, int y, string boatName);
	void RandomShot(GameGrid* gameGrid);
	void Attack(int x, int y, GameGrid& gameGrid);
	bool IsBoatDestroyed(string boatName, GameGrid* gameGrid);
	void RemoveBoat(string boatName);
	GameGrid* cheatGrid; // La grille du joueur humain
};


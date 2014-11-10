#pragma once
#include "Player.h"
#include "ComputerGameGrid.h"
#include "GoodHit.h"
#include <vector>

using namespace Matrix;
using namespace std;

class ComputerPlayer: public Player
{
public:
	ComputerPlayer();
	ComputerPlayer(string name);
	~ComputerPlayer();
	virtual void SetBoats(GameGrid* gameGrid, bool direction, int boatSize, string boatName);
	bool ShootEnemy(GameGrid* gameGrid);
	void ShootEnemyTest(GameGrid* gameGrid, vector<GoodHit*>& goodHits);
	vector<GoodHit*> getVec();
	virtual bool DidIWin(GameGrid* gameGrid);
	string GetName();
protected:
	void BoatHit(int x, int y, string boatName, int shotDirection);
	bool Attack(int x, int y, GameGrid& gameGrid, int shotDirection);
	bool CheckMultipleBoatX(GameGrid& gameGrid);
	bool CheckMultipleBoatY(GameGrid& gameGrid);
	virtual bool IsBoatDestroyed(string boatName, GameGrid* gameGrid);
	virtual void RemoveBoat(string boatName);
	virtual void RandomShot(GameGrid* gameGrid);
	vector<GoodHit*> goodHits;
};


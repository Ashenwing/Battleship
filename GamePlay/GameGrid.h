#pragma once
#include "Tile.h"
#include "Boats.h"
#include <vector>

using namespace std;

namespace Matrix
{
	class GameGrid
	{
		public:
			GameGrid(void);
			~GameGrid(void);
			virtual int Size() =0;
			//virtual void SetGameGrid() =0;
			virtual vector<Tile*> getGameVector() = 0;
			virtual bool CheckSpace(unsigned int boatSize, bool direction, unsigned int x, unsigned int y, vector<Tile*> gameGrid) =0;
			virtual bool QuickCheck(unsigned int boatSize, unsigned int x, unsigned int y,  vector<Tile*> gameGrid) =0;
			virtual int getSquareNumber(unsigned int x, unsigned int y) =0;
			virtual bool getSquareCheck(unsigned int x, unsigned int y) =0;
			virtual string getSquareName(unsigned int x, unsigned int y) = 0;
			virtual void setSquareCheck(unsigned int x, unsigned int y, bool) =0;
			virtual void setSquareContent(unsigned int x, unsigned int y, unsigned int boatSize, string boatName) =0;
		protected:
			vector<Tile*> computerVector;
			vector<Tile*> playerVector;
		};
}
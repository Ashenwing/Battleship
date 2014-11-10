#pragma once
#include "GameGrid.h"
#include "../Battleships2/SetupBoatsUI.h"
#include <vector>
#include <string>

using namespace std;

namespace Matrix
{
	class HumanGameGrid: public GameGrid
	{
		public:
			HumanGameGrid();
			HumanGameGrid(vector<Tile*>);
			~HumanGameGrid();
			int Size();
			void SetGameGrid(vector<Tile*>& gameGrid);
			vector<Tile*> getGameVector();
			bool CheckSpace(unsigned int boatSize, bool direction, unsigned int x, unsigned int y, vector<Tile*> gameGrid);
			bool QuickCheck(unsigned int boatSize, unsigned int x, unsigned int y, vector<Tile*> gameGrid);
			vector<Tile*> playerVector;
			int getSquareNumber(unsigned int x, unsigned int y);
			bool getSquareCheck(unsigned int x, unsigned int y);
			string getSquareName(unsigned int x, unsigned int y);
			void setSquareCheck(unsigned int x, unsigned int y, bool);
			void setSquareContent(unsigned int x, unsigned int y, unsigned int boatSize, string boatName);
	};
}


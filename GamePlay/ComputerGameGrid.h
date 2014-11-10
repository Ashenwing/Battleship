#pragma once
#include "GameGrid.h"
#include <vector>

using namespace std;
namespace Matrix
{
	class ComputerGameGrid: public GameGrid
	{
		public:
			ComputerGameGrid(void);
			~ComputerGameGrid(void);
			int Size();
			void SetGameGrid();
			vector<Tile*> getGameVector();
			bool CheckSpace(unsigned int boatSize, bool direction, unsigned int x, unsigned int y, vector<Tile*> gameGrid);
			bool QuickCheck(unsigned int boatSize, unsigned int x, unsigned int y,  vector<Tile*> gameGrid);
			int getSquareNumber(unsigned int x, unsigned int y);
			bool getSquareCheck(unsigned int x, unsigned int y);
			string getSquareName(unsigned int x, unsigned int y);
			void setSquareCheck(unsigned int x, unsigned int y, bool check);
			void setSquareContent(unsigned int x, unsigned int y, unsigned int boatSize, string boatName);
	};
}


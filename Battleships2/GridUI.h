#pragma once
#include "SFML/Graphics.hpp"
#include "../GamePlay/Tile.h"

#define TILE_NUMBER 10
#define TILE_WIDTH 40

using namespace sf;
using namespace std;

/*	Cette classe gère les grilles de jeu
	Author: Annie Belzile
*/
class GridUI
{
public:
	GridUI(void);
	~GridUI(void);

	void CreateGrid(RenderWindow& target, int posX, int posY);
	void UpdateGrid(RenderWindow& target);
	void ResetEmptyGrid();
	void ResetHitGrid(RenderWindow& window, vector<Tile*>& humanGrid);
	Sprite* GetSpriteAtPosition(int posX, int posY);
	Sprite* GetSprite(int posX, int posY);
	Sprite* GetSpriteMatrix();
	Texture& GetEmptyTile();
	Texture& GetBoatTile();
	Texture& GetHitTile();
	Texture& GetMissedTile();
	Texture& GetBoatHitTile();
	int GetTabMatrixCoordinatesX(int x, int y);
	int GetTabMatrixCoordinatesY(int x, int y);

private:
	Texture emptyTile;
	Texture boatTile;
	Texture hitTile;
	Texture missedTile;
	Texture boatHitTile;
	Sprite* tabSpriteMatrix[TILE_NUMBER][TILE_NUMBER];

};


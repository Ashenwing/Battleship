#include "GridUI.h"

GridUI::GridUI(void)
{
}

GridUI::~GridUI(void)
{
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			delete tabSpriteMatrix[x][y];
		}
	}
}

void GridUI::CreateGrid(RenderWindow& target, int posX, int posY)
{
	float yy = posY;
	float xx = posX;
	int row = 1;

	if (emptyTile.loadFromFile("../images/tile.png"))
	{
		for (int x = 0; x < TILE_NUMBER; x++)
		{
			for (int y = 0; y < TILE_NUMBER; y++)
			{
				tabSpriteMatrix[x][y] = new Sprite();
				tabSpriteMatrix[x][y]->setTexture(emptyTile);
				tabSpriteMatrix[x][y]->setPosition(xx,yy);
				target.draw(*tabSpriteMatrix[x][y]);
				xx += TILE_WIDTH;
			}
			xx = posX;
			yy = (posY + (TILE_WIDTH * row));
			row++;
		}
	}
}

Sprite* GridUI::GetSprite(int posX, int posY)
{
	return tabSpriteMatrix[posX][posY];
}

Sprite* GridUI::GetSpriteMatrix()
{
	return **tabSpriteMatrix;
}

Sprite* GridUI::GetSpriteAtPosition(int posX, int posY)
{
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			if (posX >= tabSpriteMatrix[x][y]->getPosition().x && posX <= (tabSpriteMatrix[x][y]->getPosition().x + tabSpriteMatrix[x][y]->getGlobalBounds().width))
			{
				if (posY >= tabSpriteMatrix[x][y]->getPosition().y && posY <= (tabSpriteMatrix[x][y]->getPosition().y + tabSpriteMatrix[x][y]->getGlobalBounds().height))
				{
					return tabSpriteMatrix[x][y];
				}
			}
		}
	}
	
}

Texture& GridUI::GetEmptyTile()
{
	if (emptyTile.loadFromFile("../images/tile.png"))
	{
		return emptyTile;
	}
}


Texture& GridUI::GetBoatTile()
{
	if (boatTile.loadFromFile("../images/boatTile.png"))
	{
		return boatTile;
	}
}

Texture& GridUI::GetBoatHitTile()
{
	if (boatHitTile.loadFromFile("../images/boatHitTile.png"))
	{
		return boatHitTile;
	}
}

Texture& GridUI::GetHitTile()
{
	if (hitTile.loadFromFile("../images/hitTile.png"))
	{
		return hitTile;
	}
}

Texture& GridUI::GetMissedTile()
{
	if (missedTile.loadFromFile("../images/missedTile.png"))
	{
		return missedTile;
	}
}

int GridUI::GetTabMatrixCoordinatesX(int posX, int posY)
{
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			if (posX >= tabSpriteMatrix[x][y]->getPosition().x && posX <= (tabSpriteMatrix[x][y]->getPosition().x + tabSpriteMatrix[x][y]->getGlobalBounds().width))
			{
				if (posY >= tabSpriteMatrix[x][y]->getPosition().y && posY <= (tabSpriteMatrix[x][y]->getPosition().y + tabSpriteMatrix[x][y]->getGlobalBounds().height))
				{
					return x;
				}
			}
		}
	}
}

int GridUI::GetTabMatrixCoordinatesY(int posX, int posY)
{
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			if (posX >= tabSpriteMatrix[x][y]->getPosition().x && posX <= (tabSpriteMatrix[x][y]->getPosition().x + tabSpriteMatrix[x][y]->getGlobalBounds().width))
			{
				if (posY >= tabSpriteMatrix[x][y]->getPosition().y && posY <= (tabSpriteMatrix[x][y]->getPosition().y + tabSpriteMatrix[x][y]->getGlobalBounds().height))
				{
					return y;
				}
			}
		}
	}
}

void GridUI::UpdateGrid(RenderWindow& target)
{
	float xx = tabSpriteMatrix[0][0]->getPosition().x;
	float yy = tabSpriteMatrix[0][0]->getPosition().y;
	float row = 1;

	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			target.draw(*tabSpriteMatrix[x][y]);
			xx += TILE_WIDTH;
		}
		xx = tabSpriteMatrix[0][0]->getPosition().x;
		yy = (tabSpriteMatrix[0][0]->getPosition().y + (TILE_WIDTH * row));
		row++;
	}
}

void GridUI::ResetEmptyGrid()
{
	float xx = tabSpriteMatrix[0][0]->getPosition().x;
	float yy = tabSpriteMatrix[0][0]->getPosition().y;
	float row = 1;

	if (emptyTile.loadFromFile("../images/tile.png"))
	{
		for (int x = 0; x < TILE_NUMBER; x++)
		{
			for (int y = 0; y < TILE_NUMBER; y++)
			{
				tabSpriteMatrix[x][y]->setTexture(emptyTile);
				xx += TILE_WIDTH;
			}
			xx = tabSpriteMatrix[0][0]->getPosition().x;
			yy = (tabSpriteMatrix[0][0]->getPosition().y + (TILE_WIDTH * row));
			row++;
		}
	}
}

void GridUI::ResetHitGrid(RenderWindow& window, vector<Tile*>& humanGrid)
{
	float xx = tabSpriteMatrix[0][0]->getPosition().x;
	float yy = tabSpriteMatrix[0][0]->getPosition().y;
	float row = 1;

		for (int x = 0; x < TILE_NUMBER; x++)
		{
			for (int y = 0; y < TILE_NUMBER; y++)
			{
				if (humanGrid.at(x * 10 + y)->getNumber() != 0 && humanGrid.at(x * 10 + y)->isClicked())
				{
					tabSpriteMatrix[x][y]->setTexture(GetBoatHitTile());
				}
				else if (humanGrid.at(x * 10 + y)->getNumber() != 0 && !humanGrid.at(x * 10 + y)->isClicked())
				{
					tabSpriteMatrix[x][y]->setTexture(GetBoatTile());
				}
				else if (humanGrid.at(x * 10 + y)->getNumber() == 0 && humanGrid.at(x * 10 + y)->isClicked())
				{
					tabSpriteMatrix[x][y]->setTexture(GetMissedTile());
				}
				else if (humanGrid.at(x * 10 + y)->getNumber() == 0 && !humanGrid.at(x * 10 + y)->isClicked())
				{
					tabSpriteMatrix[x][y]->setTexture(GetEmptyTile());
				}
				window.draw(*tabSpriteMatrix[x][y]);
				xx += TILE_WIDTH;
			}
			xx = tabSpriteMatrix[0][0]->getPosition().x;
			yy = (tabSpriteMatrix[0][0]->getPosition().y + (TILE_WIDTH * row));
			row++;
		}
}
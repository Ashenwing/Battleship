#include "PlayerProfile.h"
#include <fstream> 
#include <string>

PlayerProfile::PlayerProfile(HumanGameGrid& saveGrid)
{
	this->saveGrid = saveGrid;
}


PlayerProfile::~PlayerProfile(void)
{
}

bool PlayerProfile::Save()
{
	ofstream writer ("SaveGame.txt");

	if(writer)
	{
		writer.clear();
	}

	for(int i = 0; i < Boats::ROW_SIZE; i++)
	{
		for(int j = 0; j < Boats::ROW_SIZE; j++)
		{
			writer << saveGrid.getSquareName(i, j) << endl;
		}
	}

	writer.close();
	return true;
}

HumanGameGrid& PlayerProfile::Load()
{
	ifstream reader("SaveGame.txt");
	string boatName = "";

	for(int i = 0; i < Boats::ROW_SIZE; i++)
	{
		for( int j = 0; j < Boats::ROW_SIZE; j++)
		{
			getline(reader, boatName);
			this->saveGrid.setSquareContent(i, j, boatName.back() - 48, boatName);
		}
	}
	return this->saveGrid;
}

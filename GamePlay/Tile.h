#pragma once
#include <string>

using namespace std;

class Tile
{
public:
	 Tile();
	 Tile(int number, bool check, string boatName);
	~Tile(void);
    int getNumber();
    string getName();
    bool isClicked();
	void setNumber(int number);
	void setName(string boatName);
    void setClicked(bool check);
private:
	int tileNumber;
    bool clicked;
    string name;
};

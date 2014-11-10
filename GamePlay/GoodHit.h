#pragma once
#include <string>

using namespace std;

class GoodHit
{
public:
	GoodHit(int x, int y, string boatName, int shotDirection);
	~GoodHit(void);
	int getX();
	int getY();
	string getName();
	int getShotDirection();
private:
	int x;
	int y;
	string name;
	int shotDirection;
};


#include "stdafx.h"
#include "CppUnitTest.h"
#include <cassert>
#include "SFML/Graphics.hpp"
#include "../GamePlay/Boats.h"
#include "../GamePlay/PlayGame.h"
#include "../GamePlay/ComputerGameGrid.h"
#include "../GamePlay/ComputerPlayer.h"
#include "../GamePlay/HumanPlayer.h"
#include "../GamePlay/Player.h"
#include "../GamePlay/ComputerPlayerExpert.h"
#include "../GamePlay/GoodHit.h"
#include "../Battleships2/SetupBoatsUI.h"
#include "../Battleships2/NewGameUI.h"
#include "../Battleships2/MenuUI.h"
#include "../Battleships2/GameUI.h"
#include "../Battleships2/DialogUI.h"
#include "../Battleships2/GridUI.h"
#include "../PlayerProfile/PlayerProfile.h"
#include "../Battleships2/EndGamePanelUI.h"

using namespace Matrix;
using namespace Boats;
using namespace std;
using namespace sf;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTests
{		
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(Test_Initialisation_Matrice_Ennemie_Vide)
		{
			Matrix::ComputerGameGrid newG;
			for(unsigned int i = 0; i < newG.getGameVector().size(); i++)
			{
				Assert::AreEqual(0, newG.getGameVector().at(i)->getNumber());
			}
		}

		TEST_METHOD(Test_Initialisation_Matrice_Ennemie_Size)
		{
			Matrix::ComputerGameGrid newG;
			int size = newG.getGameVector().size();

			Assert::AreEqual(100, size);
		}

		TEST_METHOD(Test_Initialisation_Matrice_Ennemie_Bateaux)
		{
			Matrix::GameGrid* newG( new Matrix::ComputerGameGrid());
			ComputerPlayer newP("Fred");
			int counter = 0;

			newP.SetBoats(newG, true, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
			newP.SetBoats(newG, true, Boats::STR_DESTROYER.back() - 48, Boats::STR_DESTROYER);
			newP.SetBoats(newG, false, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);

			for(unsigned int i = 0; i < newG->getGameVector().size(); i++)
			{
				if(newG->getGameVector().at(i)->getNumber() != 0)
				{
					counter++;
				}
			}
			Assert::AreEqual(11, counter);

		}

		TEST_METHOD(Test_destruction_Matrice_Ennemie_BateauSpecifique_Simple)
		{
			vector<GoodHit*> goodHitVector;
			GoodHit* hitVector1 = new GoodHit(1,2, "Aircraft5", 1);
			GoodHit* hitVector2 = new GoodHit(2,2, "Aircraft5", 1);
			GoodHit* hitVector3 = new GoodHit(3,2, "Aircraft5", 1);
			GoodHit* hitVector4 = new GoodHit(4,2, "Aircraft5", 1);
			GoodHit* hitVector5 = new GoodHit(5,2, "Aircraft5", 1);
			
			GoodHit* hitVector6 = new GoodHit(6,2, "Patrol2", 1);
			goodHitVector.push_back(hitVector6);

			goodHitVector.push_back(hitVector1);
			goodHitVector.push_back(hitVector2);
			goodHitVector.push_back(hitVector3);
			goodHitVector.push_back(hitVector4);
			goodHitVector.push_back(hitVector5);

			vector<GoodHit*>::iterator deleter = goodHitVector.begin();

			int counter = 0;
			while(deleter != goodHitVector.end())
			{
				if(goodHitVector.at(counter)->getName() == "Aircraft5")
				{
					goodHitVector.erase(deleter);	
				}
				else
				{
					counter++;
				}
				deleter = goodHitVector.begin() + counter;
			}

			int size = goodHitVector.size();

			Assert::AreEqual(1, size);

		}

		TEST_METHOD(Test_destruction_Matrice_Ennemie_BateauSpecifique_Complicated)
		{
			vector<GoodHit*> goodHitVector;
			GoodHit* hitVector1 = new GoodHit(1,2, "Aircraft5", 1);
			GoodHit* hitVector2 = new GoodHit(2,2, "Submarine3", 1);
			GoodHit* hitVector3 = new GoodHit(3,2, "Aircraft5", 1);
			GoodHit* hitVector4 = new GoodHit(4,2, "Destroyer4", 1);
			GoodHit* hitVector5 = new GoodHit(5,2, "Aircraft5", 1);
			
			GoodHit* hitVector6 = new GoodHit(6,2, "Patrol2", 1);

			goodHitVector.push_back(hitVector6);
			goodHitVector.push_back(hitVector1);
			goodHitVector.push_back(hitVector2);
			goodHitVector.push_back(hitVector3);
			goodHitVector.push_back(hitVector4);
			goodHitVector.push_back(hitVector5);

			vector<GoodHit*>::iterator deleter = goodHitVector.begin();

			int counter = 0;
			while(deleter != goodHitVector.end())
			{
				if(goodHitVector.at(counter)->getName() == "Aircraft5")
				{
					goodHitVector.erase(deleter);	
				}
				else
				{
					counter++;
				}
				deleter = goodHitVector.begin() + counter;
			}

			int size = goodHitVector.size();

			Assert::AreEqual(3, size);
		}

		TEST_METHOD(Ennemie_Attaque)
		{
			Matrix::GameGrid* newG = new Matrix::ComputerGameGrid();
			ComputerPlayer newP("Fred");
			int counter = 0;

			newP.SetBoats(newG, true, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
			newP.SetBoats(newG, true, Boats::STR_DESTROYER.back() - 48, Boats::STR_DESTROYER);
			newP.SetBoats(newG, false, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);
			newP.SetBoats(newG, false, Boats::STR_BATTLESHIP.back() - 48, Boats::STR_BATTLESHIP);
			newP.SetBoats(newG, true, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
			newP.SetBoats(newG, true, Boats::STR_PATROL.back() - 48, Boats::STR_PATROL);
			newP.SetBoats(newG, false, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);

			bool boatHit = false;

			while(newP.getVec().empty())
			{
				newP.ShootEnemy(newG);
			}

			if(newP.getVec().at(0)->getName() == newG->getSquareName(newP.getVec().at(0)->getX(),newP.getVec().at(0)->getY()))
			{
				boatHit = true;
			}
				
			Assert::AreEqual(true, boatHit);
		}

		TEST_METHOD(Ennemie_Attaque_Deux_Fois)
		{
			Matrix::GameGrid* newG = new Matrix::ComputerGameGrid();
			ComputerPlayer newP("Fred");
			int counter = 0;

			newP.SetBoats(newG, true, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
			newP.SetBoats(newG, true, Boats::STR_DESTROYER.back() - 48, Boats::STR_DESTROYER);
			newP.SetBoats(newG, false, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);
			newP.SetBoats(newG, false, Boats::STR_BATTLESHIP.back() - 48, Boats::STR_BATTLESHIP);
			newP.SetBoats(newG, true, Boats::STR_AIRCRAFT.back() - 48, Boats::STR_AIRCRAFT);
			newP.SetBoats(newG, true, Boats::STR_PATROL.back() - 48, Boats::STR_PATROL);
			newP.SetBoats(newG, false, Boats::STR_SUBMARINE.back() - 48, Boats::STR_SUBMARINE);

			while(newP.getVec().empty())
			{
				newP.ShootEnemy(newG);
			}

			while(newP.getVec().size() == 1)
			{
				newP.ShootEnemy(newG);
			}

			int size = newP.getVec().size();
			Assert::AreEqual(2, size);


		}

		TEST_METHOD(Ennemie_Expert_Attaque_Deux_Fois)
		{
			HumanGameGrid* cheat = new HumanGameGrid();
			cheat->setSquareContent(1, 1, 5, "Aircraft5");
			cheat->setSquareContent(1, 2, 5, "Aircraft5");
			cheat->setSquareContent(1, 3, 5, "Aircraft5");
			cheat->setSquareContent(1, 4, 5, "Aircraft5");
			cheat->setSquareContent(1, 5, 5, "Aircraft5");

			cheat->setSquareContent(2, 1, 3, "Submarine3");
			cheat->setSquareContent(3, 1, 3, "Submarine3");
			cheat->setSquareContent(4, 1, 3, "Submarine3");

			ComputerPlayerExpert killer("Ganondorf", cheat);

			while(killer.getVec().size() == 0)
			{
				killer.ShootEnemy(cheat);
			}

			killer.ShootEnemy(cheat);

			int size = killer.getVec().size();
			Assert::AreEqual(2, size);
		}

		//TEST_METHOD(Play_Game)
		//{
		//	//PlayGame newGame;

		//	//newGame.Start();

		//	//int counter = 0;

		//	//for(unsigned int i = 0; i < Boats::ROW_SIZE; i++)
		//	//{
		//	//	for(unsigned int j = 0; j < Boats::ROW_SIZE; j++)
		//	//	{
		//	//		if(newGame.getComputerGrid()->getSquareNumber(i, j) != 0)
		//	//		{
		//	//			counter++;
		//	//		}
		//	//	}
		//	//}
		//	//Assert::AreEqual(17, counter);
		//}


		//TEST_METHOD(Human_Player_Boat_Contiguous_Horizontal)
		//{
		//	SetupBoatsUI testGrid;
		//	vector<int> testArray;
		//	testArray.at(0) = 1;
		//	testArray.at(1) = 0;
		//	testArray.at(2) = 2;
		//	testArray.at(3) = 0;

		//	//Assert::IsTrue(testGrid.areTilesContiguous(testArray));
		//}

		//TEST_METHOD(Human_Player_Boat_Contiguous_Vertical)
		//{
		//	SetupBoatsUI testGrid;
		//	vector<int> testArray;
		//	testArray.at(0) = 0;
		//	testArray.at(1) = 1;
		//	testArray.at(2) = 0;
		//	testArray.at(3) = 2;

		//	//Assert::IsTrue(testGrid.areTilesContiguous(testArray));
		//}

		//TEST_METHOD(Human_Player_Boat_Not_Contiguous)
		//{
		//	SetupBoatsUI testGrid;
		//	vector<int> testArray;
		//	testArray.at(0) = 1;
		//	testArray.at(1) = 0;
		//	testArray.at(2) = 3;
		//	testArray.at(3) = 0;

		//	//Assert::IsFalse(testGrid.areTilesContiguous(testArray));
		//}
	};
}
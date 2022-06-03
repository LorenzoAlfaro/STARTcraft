#pragma once
#include <BWAPI.h>
#include <windows.h> // simulate mouse clicks, getKeyState
using namespace std;
using namespace BWAPI;
class auxFun
{
public:
	static int SupplyTotal(int commandCenterCount, int supplyDepotCount);
	static int usedSupplyTotal(int marineCount, int scvCount);
	static int roomNeeded(int commandCenterCount, int barrackCount);
	static bool validUnit(Unit u, list<int> deadUnits);
	static bool validFrame();
	static bool isUnitDead(list<int>& deadUnits, int id);
	static Position getMousePosition();
	static Position getUnitPosition(Unit centerHere);
	static void displayInsights2(int roomNeeded, int supplyLeft2, int SCVcount, int barracksCount, int marineCount, int StatsCoordinates[][2], int Builders, int deadUnits, int taskQueueCount, int Unexplored);
	static void LeftClick();
	static void RightClick();
};

//Useful functions
//Broodwar->self()->allUnitCount();
//Broodwar->self()->completedUnitCount();
//Broodwar->self()->supplyTotal();
//Broodwar->self()->supplyUsed();
//Broodwar->canBuildHere
//Broodwar->elapsedTime
//Broodwar->getAPM
//Broodwar->getSelectedUnits
//Broodwar->getUnit // need to implemet
//Broodwar->hasPath
//Broodwar->isExplored
//Broodwar->issueCommand
//Broodwar->mapWidth
//Broodwar->pingMinimap
//Broodwar->printf 
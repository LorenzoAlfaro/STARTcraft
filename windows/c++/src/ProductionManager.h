#pragma once
#include <array>
#include <BWAPI.h>

#include "TaskFun.h"
#include "UnitFun.h"
#include "Buildmanager.h"
#include "auxFun.h"
#include "CommMngr.h"
using namespace UnitTypes;
using namespace std;
using namespace BWAPI;
class ProductionManager
{
public:
	static void Manage(int minerals, int gas, int frameCount, list<array<int, 12>>& myTaskQueue, list<int> myDeadUnits, int BarracksCount, int SCVCount, int myMaxBuilding[], int myMaxUnit[], bool almostSupplyBlocked, int roomNeeded);
};


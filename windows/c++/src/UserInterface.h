#pragma once
#include <BWAPI.h>
#include "auxFun.h"  //getKeyState
#include "TaskFun.h"
#include "CommMngr.h"
using namespace std;
using namespace UnitTypes;

class UserInterface
{
public:
	static void ReadInput(string text, list<int> deadUnits, bool& displayStats, Position myPos);

	static void ReadCommand(int frameCount, int& callBack, list<int> deadUnits, list<array<int, 12>>&  taskQueue);
};


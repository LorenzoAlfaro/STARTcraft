#pragma once
#include "TaskFun.h"
#include "UnitFun.h"
#include "Buildmanager.h"

using namespace std;
//using namespace BWAPI;

class TaskEngine
{
public:
	static void taskManager(list<array<int, 12>>& myTaskQueue, int frameCount, int minerals, int gas, Unit CommandCenter, list<int>& Miners, list<int>& Builders);
};

